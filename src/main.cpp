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
            ui.SCreateANewFile(arguments[2]);
        }else if(arguments[1] == "-nd"){
            ui.SCreateNewFolder(arguments[2]);
        }
        else if(arguments[1] == "-cy"){
            ui.uicopyfile(arguments[2], arguments[3]);
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