cmake_minimum_required(VERSION 3.14)
project(Kophi)

set(CMAKE_CXX_STANDARD 11)

add_library(Kophi
        include/Kophi/Utils.h
        include/Kophi/Private.h
        include/Kophi/JavaClass.h
        include/Kophi/JavaConstant.h
        include/Kophi/JavaProperty.h
        include/Kophi/JavaAttribute.h
        include/Kophi/JavaInstruction.h

        src/Utils.cpp
        src/Private.cpp
        src/JavaClass.cpp
        src/JavaConstant.cpp
        src/JavaProperty.cpp
        src/JavaAttribute.cpp
        src/JavaInstruction.cpp)

target_include_directories(Kophi PUBLIC include)
