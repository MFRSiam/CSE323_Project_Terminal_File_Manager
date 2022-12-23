//
// Created by mfrfo on 12/8/2022.
//

#ifndef CSE323_PROJECT_TERMINAL_FILE_MANEGER_FILEMANAGER_H
#define CSE323_PROJECT_TERMINAL_FILE_MANEGER_FILEMANAGER_H
// C++ Utilities
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

// Linux OS Headers
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>


struct Message{
    std::string message;
    bool field;
    Message():field(false){

    }
};

struct Info{
    bool ReadMode;
    bool WriteMode;
    bool ExecuteMode;
    size_t FileSize;
    std::string CreatedOn;
    std::string ModifiedOn;
    bool GettingInfoSuccess;
    bool Activated;
    Info(): ReadMode(false),WriteMode(false),ExecuteMode(false),FileSize(0),GettingInfoSuccess(false),
        Activated(false),CreatedOn("NULL"),ModifiedOn("NULL")
    {

    }
};

class FileManager final {
public:
    FileManager();
    explicit FileManager(const std::string& path);
    ~FileManager() = default;
    void setWorkingDir(const std::string &dir);

    // Functions
    /*!
     * @param filename The Name of the file you are trying to create
     * @return Return a Message with a text and a boolean value. If The boolean value is false then the action didnt happen successfully.
     */
    Message &CreateANewFile(const std::string &filename);
    Message &CreateANewFolder(const std::string &foldername);
    Message &DeleteAFile(const std::string &filename);
    Message &DeleteAFolder(const std::string &foldername);
    Message &EditAFile(const std::string &oldFilename,const std::string& newFilename);
    Message &CopyFile(const std::string &fileName, const std::string &newPath);

    std::vector<std::string> &ListAll();

    Info &GetProperties(const std::string &filename);


    std::string getPath() const;
    void update();
private:
    void setCurrentDir();


    Message error;
    std::string currentDir;
    std::vector<std::string> elements;
};


#endif //CSE323_PROJECT_TERMINAL_FILE_MANEGER_FILEMANAGER_H
