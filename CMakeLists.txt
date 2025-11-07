cmake_minimum_required(VERSION 4.0)
project(Banco_Malvader C)

set(CMAKE_C_STANDARD 11)

add_executable(Banco_Malvader src/main.c
        src/cliente_data.h
        src/banco.h
        src/banco.c
        src/persistencia.c
        src/persistencia.h
        src/ordenacao.c
        src/ordenacao.h
        src/validacao.h
        src/validacao.c
        src/io.h
        src/io.c
)
