# Projeto-CSLP - Image and Video compression

## Members of the group

| Nmec   | Name           | Email                  | Github                                                |
| ------ | -------------- | ---------------------- | ----------------------------------------------------- |
| 107359 | Duarte Cruz    | <duarteccruz@ua.pt>    | [DuarteCruz31](https://github.com/DuarteCruz31)       |
| 108215 | Hugo Correia   | <hf.correia@ua.pt>     | [MrLoydHD](https://github.com/MrLoydHD)               |
| 107637 | André Oliveira | <andreaoliveira@ua.pt> | [andreaoliveira9](https://github.com/andreaoliveira9) |

<br>

## How to run

### Before running the programs, you need to install the following library:

- OpenCV

  _To install it, you need to run the following command:_

  ```
  sudo apt-get install libopencv-dev
  ```

### To run each of the programs, you need to specify the program name on CMakeLists.txt file, and then run the following commands:

```makefile
target_link_libraries(VideoPlayer ${OpenCV_LIBS} )
cmake_minimum_required(VERSION 3.17)
project( ProjetoCSLP )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(SOURCES
  hybridEncodeTest.cpp # For this deliverable use this files (hybridDecodeTest.cpp, hybridEncodeTest.cpp, instraEncodeTest.cpp, intraDecodeTest.cpp)
)
add_executable( ${PROJECT_NAME} ${SOURCES})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
```

### Then, you need to run the following commands:

_You need to be in the src directory of the project_

```
mkdir build && cd build
cmake ..
make
```

### After that, you can run the program by running the following command:

```
./ProjetoCSLP
```

<br>
