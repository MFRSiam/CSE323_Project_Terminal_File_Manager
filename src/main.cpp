// Main Input
#include <iostream>
#include <vector>

// UI Library Inputs
#include <fmt/core.h>

// Custom Imports
#include "FileManager.h"
#include "UserInterface.h"


int main(int argc, char **argv) {
    FileManager sb;
    UserInterface ui(sb);
    if(argc < 2){
        fmt::print("Invalid Argument");
        return -1;
    }else{
        std::vector<std::string> arguments(argc);
        for(int i=0;i<argc;i++){
            arguments[i] = argv[i];
        }
        if(arguments[1] == "-n"){
            if(arguments[2].length() < 1){
                ui.InvalidArg();
            }else{
                ui.SCreateANewFile(arguments[2]);
            }
        }else if(arguments[1] == "-nd"){
            if(arguments[2].length() < 1){
                ui.InvalidArg();
            }else{
                ui.SCreateNewFolder(arguments[2]);
            }
        }
        else if(arguments[1] == "-cy"){
            ui.SCopyfile(arguments[2], arguments[3]);
        }
        else if(arguments[1] == "-e"){
            ui.SEditAFile(arguments[2], arguments[3]);
        }else if(arguments[1] == "-r"){
            ui.SDeleteAFile(arguments[2]);
        }else if(arguments[1] == "-rd"){
            ui.SDeleteAFolder(arguments[2]);
        }else if(arguments[1] == "-l"){
            ui.SListAllElements(arguments[0]);
        }else if(arguments[1] == "-s"){
            ui.SGetInfo(arguments[2]);
        }else{
            ui.InvalidArg();
        }


    }


    return 0;
}




//std::string filename1 = argv[0];
//std::string filename2 = argv[1];
//std::string filename3 = argv[2];
//
//if(argv[1] == std::string("-n")){
//Message tst = sb.CreateANewFile(filename3);
//fmt::print("Txt: {} \n Action:{} \n",tst.message,tst.field);
//}else{
//fmt::print("Wrong Argument\n");
//}