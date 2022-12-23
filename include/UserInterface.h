//
// Created by mfrfo on 12/8/2022.
//

#ifndef CSE323_PROJECT_TERMINAL_FILE_MANEGER_USERINTERFACE_H
#define CSE323_PROJECT_TERMINAL_FILE_MANEGER_USERINTERFACE_H
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <fmt/color.h>
#include "FileManager.h"

class UserInterface {
public:
    UserInterface(FileManager &x);
    ~UserInterface() = default;

    void SCreateANewFile(const std::string &filename);
    void SCopyfile(const std::string &fileName, const std::string &newPath);
    void SEditAFile(const std::string &oldFilename, const std::string& newFilename);
    void SDeleteAFile(const std::string &deletefile);
    void SDeleteAFolder(const std::string &deletefolder);
    void SCreateNewFolder(const std::string &foldername);
    void SListAllElements(const std::string &path);
    void SGetInfo(const std::string &filename);
    void InvalidArg();
private:
    bool takeInputs(std::string &input);
    std::string Display;
    bool status;
    FileManager *mainFM;
};


#endif //CSE323_PROJECT_TERMINAL_FILE_MANEGER_USERINTERFACE_H
