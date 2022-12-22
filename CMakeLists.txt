cmake_minimum_required(VERSION 3.22)
project(CSE323_Project_Terminal_File_Maneger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include(FetchContent)



FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
        )
FetchContent_MakeAvailable(fmt)



add_executable(CSE323_Project_Terminal_File_Maneger src/main.cpp include/UserInterface.cpp include/UserInterface.h include/FileManager.cpp include/FileManager.h)

target_link_libraries(
        CSE323_Project_Terminal_File_Maneger
        PRIVATE
        fmt::fmt
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "tfm")
