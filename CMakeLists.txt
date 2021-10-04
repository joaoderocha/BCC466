cmake_minimum_required(VERSION 3.20)
project (BCC466)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        BCC466 main.cpp
        src/Arquivos.cpp
        src/Arquivos.h
        src/Construcao.cpp
        src/Construcao.h
        src/Descida.cpp
        src/Descida.h
        src/GRASP.cpp
        src/GRASP.h
        src/Menus.cpp
        src/Menus.h
        src/MS.cpp
        src/MS.h
        src/SA.cpp
        src/SA.h
        src/Util.cpp
        src/Util.h
)