//
// Created by mfrfo on 12/8/2022.
//

#include "FileManager.h"

// Static Members
int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    int rv = remove(fpath);
    if (rv){
        perror(fpath);
    }
    return rv;
}



// Class Members
FileManager::FileManager() {
    setCurrentDir();
    update();
}

FileManager::FileManager(const std::string& path) {
    this->currentDir = path;
}


void FileManager::setWorkingDir(const std::string &dir) {
    this->currentDir = dir;
}

Message &FileManager::CreateANewFile(const std::string &filename) {
    // Return Entity
    Message *a1 = new Message();
    // Update The Dir
    update();
    // Check If Any File With the same name already Exist
    for(auto name:elements){
        if(name==filename){
            a1->message = "File Already Exists";
            a1->field = false;
            return *a1;
        }
    }

    // Try To Make The New File
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    std::string cName = this->currentDir + "/" + filename;
    const char *pathname = cName.c_str();
    fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if(fd == -1){
        a1->message = "Cant Create The File";
        a1->field = false;
        update();
        return *a1;
    }else{
        a1->message = std::string("Successfully Create A New File Named :") + std::string(" ./") + filename;
        a1->field = true;
        return *a1;
    }


}

Message &FileManager::CreateANewFolder(const std::string &foldername) {
    std::string tpath = this->currentDir + "/" + foldername;
    struct stat st = {0};
    Message *a1 = new Message();
    if (stat(tpath.c_str(), &st) == -1) {
        mkdir(tpath.c_str(), 0700);
        a1->message = std::string("New Folder Created Successfully With The Name ") + foldername;
        a1->field = true;
    }else{
        a1->message = "Cant Create A New Folder With The Given Name As The Folder Already Exist";
        a1->field = false;
    }
    return *a1;
}

Message &FileManager::DeleteAFile(const std::string &filename) {
    int status;
    std::string p_name = this->currentDir + "/" + filename;
    //fgets((char*)p_name.c_str(),(int)p_name.length(),stdin);
    status = remove(p_name.c_str());
    Message *a1 = new Message();
    if( status == 0 ){
        a1->message = "Deleted The File Successfully";
        a1->field = true;
    }
    else
    {
        a1->message = std::string("Could Not Delete The File ") + filename;
        a1->field = false;
    }
    return *a1;
}


Message &FileManager::DeleteAFolder(const std::string &foldername) {
    Message *ret = new Message();
    std::string f_name = this->currentDir + "/" + foldername;
    int kl = nftw(f_name.c_str(), unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
    if(kl == 0){
        ret->message = "Folder Removed Successfully";
        ret->field = true;
    }else if(kl < 0){
        ret->message = "Some Error Occurred";
        ret->field = false;
    }
    update();
    return *ret;
}


Message &FileManager::EditAFile(const std::string &oldFilename, const std::string& newFilename) {
    
    Message *result = new Message();

    std::string oldfiledir = this->currentDir + "/" +oldFilename;
    const char *arroldfiledir = oldfiledir.c_str();

    std::string newfiledir = this->currentDir + "/" + newFilename; 
    const char *arrnewfiledir = newfiledir.c_str();

    int rel = rename(arroldfiledir, arrnewfiledir);

    if(rel == -1)
    {
        result->message = "Failed to rename your file";
        result->field = false; 
        return *result; 
    }
    else
    {
        result->message = "File renamed successfully";
        result->field = true; 
        return *result; 

    }


}

Message &FileManager::CopyFile(const std::string &fileName, const std::string &newPath) {

    char buff;
    Message *result = new Message();
    std::string cpyfile = this->currentDir + "/" + fileName;
    const char *cpyfilename = cpyfile.c_str();
    int file1 = open(cpyfilename, O_RDONLY);
    if(file1 == -1)
    {
        result->message = "The file you are trying to copy does not exist";
        result->field = false;
        return *result;
    }

    std::string pstfile = newPath + "/"+ fileName;
    const char *pstfilename = pstfile.c_str();

    int file2 = open(pstfilename, O_WRONLY | O_CREAT,
				  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
    if(file2 == -1)
    {
        result->message = "failed to copy file in that directory";
        result->field = false;
        return *result;
    }
    else{
        while(read(file1,&buff,1))
        {
            write(file2, &buff,1);
        }
        result->message = "File copied";
        result->field = true;
        return *result;
        close(file1);
	    close(file2);
    }



}


std::vector<std::string> &FileManager::ListAll() {
    return this->elements;
}



void FileManager::update() {
    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(this->currentDir.c_str())) != nullptr){
        while ((ent = readdir (dir)) != nullptr) {
            if ( !strcmp( ent->d_name, "."  )) continue;
            if ( !strcmp( ent->d_name, ".." )) continue;
            std::vector<std::string>::iterator checker =  std::find(std::begin(elements),std::end(elements),ent->d_name);
            if(checker == std::end(elements)){
                this->elements.emplace_back(ent->d_name);
            }
        }
        closedir (dir);
    }else{
        this->error.message = "Cant Open The Directory";
        this->error.field = true;
    }
}


void FileManager::setCurrentDir() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        this->currentDir = cwd;
    } else {
        this->error.message = "Cant Open The Current Dir";
        this->error.field = true;
    }
}

std::string FileManager::getPath() const {
    return this->currentDir;
}

Info &FileManager::GetProperties(const std::string &filename) {
    struct stat stats;
    Info *ret = new Info();
    std::string path = this->currentDir + "/" + filename;

    if (stat(path.c_str(), &stats) == 0)
    {
        if(S_ISREG(stats.st_mode) == 0){
            ret->IsDir = true;
        }
        ret->GettingInfoSuccess = true;
        ret->Activated = true;
        if (stats.st_mode & R_OK)
            ret->ReadMode = true;
        if (stats.st_mode & W_OK)
            ret->WriteMode = true;
        if (stats.st_mode & X_OK)
            ret->ExecuteMode = true;
        ret->FileSize = stats.st_size;

        struct tm dt = *(gmtime(&stats.st_ctime));
        ret->CreatedOn = std::to_string(dt.tm_mday) + " " + std::to_string(dt.tm_mon) + " " +
                std::to_string(dt.tm_year + 1900) + " " + std::to_string(dt.tm_hour) + " " +
                std::to_string(dt.tm_min) + " " + std::to_string(dt.tm_sec);

        dt = *(gmtime(&stats.st_mtime));
        ret->ModifiedOn = std::to_string(dt.tm_mday) + " " + std::to_string(dt.tm_mon) + " " +
                         std::to_string(dt.tm_year + 1900) + " " + std::to_string(dt.tm_hour) + " " +
                         std::to_string(dt.tm_min) + " " + std::to_string(dt.tm_sec);
    }else {
        ret->GettingInfoSuccess = false;
    }
    return *ret;
}
