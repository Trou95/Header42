cmake_minimum_required(VERSION 3.24)
project(FileHeader)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/Utils)
include_directories(src/Utils/FileService)

add_executable(FileHeader
        src/Utils/FileService/FileService.cpp
        src/Utils/FileService/FileService.h
        src/Utils/Utils.cpp
        src/Utils/Utils.h
        src/main.cpp src/HeaderReplacer.cpp src/Utils/Logger/Logger.cpp src/Utils/Logger/LogService.cpp src/Entities/Header.cpp)
