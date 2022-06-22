add_library(BCC466
        Arquivos.cpp
        Arquivos.h
        Construcao.cpp
        Construcao.h
        Descida.cpp
        Descida.h
        GRASP.cpp
        GRASP.h
        Menus.cpp
        Menus.h
        MS.cpp
        MS.h
        SA.cpp
        SA.h
        Util.cpp
        Util.h
        ILS.h
        ILS.cpp
        LAHC.cpp
        LAHC.h
        BT.cpp
        BT.h
        )

target_include_directories(BCC466 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})