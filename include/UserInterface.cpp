//
// Created by mfrfo on 12/8/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface(FileManager &x) :status(true) {
    this->mainFM = &x;
    mainFM->update();
}

void UserInterface::SCreateANewFile(const std::string &filename) {
    Message ret = mainFM->CreateANewFile(filename);
    if(ret.field){
        fmt::print( fg(fmt::color::green), "Message: {}\n", ret.message);
    }else{
        fmt::print(fg(fmt::color::red), "Message: {}\n" , ret.message);
        std::string newName;
        if(takeInputs(newName)){
            this->SCreateANewFile(newName);
        }
    }
}

void UserInterface::SCreateNewFolder(const std::string &foldername) {
    Message ret = mainFM->CreateANewFolder(foldername);
    if(ret.field){
        fmt::print(fg(fmt::color::green),"Message: {}\n",ret.message);
    }else{
        fmt::print(fg(fmt::color::red),"Message: {}\n",ret.message);
        std::string newName;
        if(takeInputs(newName)){
            this->SCreateNewFolder(newName);
        }
    }
}

bool UserInterface::takeInputs(std::string &input) {
    fmt::print(fg(fmt::color::alice_blue), "Please Input a New Name Or -1 To Exit\n");
    std::string l_input;
    std::cin >> l_input;
    if(l_input == "-1"){
        return false;
    }else{
        input = l_input;
        return true;
    }
}

void UserInterface::SCopyfile(const std::string &fileName, const std::string &newPath)
{
    Message ret = mainFM->CopyFile(fileName, newPath); 
    if(ret.field){
        fmt::print( fg(fmt::color::green), "Message: {}\n", ret.message);
    }else{
        fmt::print(fg(fmt::color::red), "Message: {}\n" , ret.message);
    }
}

void UserInterface::SEditAFile(const std::string &oldFilename, const std::string& newFilename)
{

   Message ret = mainFM->EditAFile(oldFilename, newFilename); 
    if(ret.field){
        fmt::print( fg(fmt::color::green), "Message: {}\n", ret.message);
    }else{
        fmt::print(fg(fmt::color::red), "Message: {}\n" , ret.message);
    }
}

void UserInterface::SDeleteAFile(const std::string &deletefile) {
    Message ret = mainFM->DeleteAFile(deletefile);
    if(ret.field){
        fmt::print(fg(fmt::color::green),"Message: {}\n",ret.message);
    }else{
        fmt::print(fg(fmt::color::red),"Message: {}\n",ret.message);
        std::string filename;
        if(takeInputs(filename)){
            this->SDeleteAFile(filename);
        }
    }
}

void UserInterface::SDeleteAFolder(const std::string &deletefolder) {
    Message ret = mainFM->DeleteAFolder(deletefolder);
    if(ret.field){
        fmt::print(fg(fmt::color::green),"Message: {}\n",ret.message);
    }else{
        fmt::print(fg(fmt::color::red),"Message: {}\n",ret.message);
        std::string foldername;
        if(takeInputs(foldername)){
            this->SDeleteAFolder(foldername);
        }
    }
}

void UserInterface::SListAllElements(const std::string &path) {
    int counter = 1;
    fmt::print(fg(fmt::color::yellow), "PATH : {}\n", path);
    fmt::print(fg(fmt::color::yellow_green), "Contains: ");

    std::vector<std::string> &r = this->mainFM->ListAll();
    for(auto x : r){
        fmt::print(fg(fmt::color::green_yellow),"{}. {} \n",counter,x);
        counter++;
    }
}

void UserInterface::SGetInfo(const std::string &filename) {
    Info x = this->mainFM->GetProperties(filename);
    if(x.GettingInfoSuccess){
        if(x.IsDir){
            fmt::print(fg(fmt::color::light_sky_blue),"This is a Folder\n");
        }
        if(x.ReadMode){
            fmt::print(fg(fmt::color::green),"READ ");
        }
        if(x.WriteMode){
            fmt::print(fg(fmt::color::light_coral),"WRITE ");
        }
        if(x.ExecuteMode){
            fmt::print(fg(fmt::color::light_pink),"EXECUTABLE ");
        }
        fmt::print("\n");
        fmt::print(fg(fmt::color::light_blue),"File Size: {} bytes\n",x.FileSize);
        fmt::print(fg(fmt::color::light_blue),"Created On: {}\n", x.CreatedOn);
        fmt::print(fg(fmt::color::light_blue),"Modified On {}\n", x.ModifiedOn);
    }else{
        fmt::print(fg(fmt::color::red),"Failed To Retrive Info\n");
    }
}

