# Terminal File Manager

A Terminal Based File Manager, It does simple things to make file management easy.

Use Cmake to build the project

    mkdir build
    cd build
    cmake ../ 
    make

Some Features Are,

1. Create A new File
2. Delete File 
3. Create a Folder 
4. Delete Folder

## Arguments

| Arguments | Description                                          |             Input              |
|-----------|------------------------------------------------------|:------------------------------:|
| -n        | Makes A New File                                     |            filename            |
| -nd       | Makes A New Folder                                   |           foldername           |
| -l        | List All Element                                     |              none              |
| -r        | Delete A File                                        |            filename            |
| -rd       | Delete A Directory                                   |           foldername           |
| -o        | Opens The File                                       |            filename            |
| -s        | Details of The File                                  |            filename            |
| -e        | Edit The Filename                                    |  old filename , new filename   |
| -ed       | Edit The Foldername                                  | old foldername, new foldername |
| -cy       | Copy a File                                          | filename, New Directory        | 
