cmake_minimum_required(VERSION 3.26)
project(parte_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(VainOurObjects)

add_executable(parte_2
        VainOurObjects/aux_arquivos.c
        VainOurObjects/aux_arquivos.h
        VainOurObjects/aux_funcoes.c
        VainOurObjects/aux_funcoes.h
        VainOurObjects/aux_geral.c
        VainOurObjects/aux_geral.h
        VainOurObjects/defs.h
        VainOurObjects/main.c)
