//
// Created by mfrfo on 12/8/2022.
//

#include "UserInterface.h"

UserInterface::UserInterface(FileManager &x) :status(true) {
    this->mainFM = &x;
    mainFM->update();
}

void UserInterface::SCreateANewFile(const std::string filename) {
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

void UserInterface::SCreateNewFolder(const std::string foldername) {
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

void UserInterface::uicopyfile(const std::string &fileName, const std::string &newPath)
{
    Message ret = mainFM->CopyFile(fileName, newPath); 
    if(ret.field){
        fmt::print( fg(fmt::color::green), "Message: {}\n", ret.message);
    }else{
        fmt::print(fg(fmt::color::red), "Message: {}\n" , ret.message);
    }
}

void UserInterface::uiEditAFile(const std::string &oldFilename, const std::string& newFilename)
{

   Message ret = mainFM->EditAFile(oldFilename, newFilename); 
    if(ret.field){
        fmt::print( fg(fmt::color::green), "Message: {}\n", ret.message);
    }else{
        fmt::print(fg(fmt::color::red), "Message: {}\n" , ret.message);
    }
}



