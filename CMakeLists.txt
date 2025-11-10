
cmake_minimum_required(VERSION 3.10)

project(Banco_Malvader C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")


set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")


set(SOURCE_FILES
        src/main.c
        src/banco.c
        src/cliente.c
        src/io.c
        src/ordenacao.c
        src/cliente.c
)

set(HEADER_FILES
        src/banco.h
        src/cliente_data.h
        src/io.h
        src/ordenacao.h
)

add_executable(banco ${SOURCE_FILES} ${HEADER_FILES})

add_custom_command(
        TARGET banco POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/data/clientes.txt
        ${CMAKE_CURRENT_BINARY_DIR}/data/clientes.txt
        COMMENT "Copiando clientes.txt para o diretório de build..."
)


target_include_directories(banco PRIVATE src)



file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)



add_custom_target(clean-data
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/data
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/data
        COMMENT "Limpando dados do banco..."
)

add_custom_target(run
        COMMAND banco
        DEPENDS banco
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Executando Banco Malvader..."
)


add_custom_target(run-test
        COMMAND ${CMAKE_COMMAND} -E echo "Criando dados de teste..."
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/test_data/clientes.txt ${CMAKE_CURRENT_BINARY_DIR}/data/
        COMMAND banco
        DEPENDS banco
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Executando com dados de teste..."
)


message(STATUS "===========================================")
message(STATUS "  Projeto: ${PROJECT_NAME}")
message(STATUS "  Compilador: ${CMAKE_C_COMPILER}")
message(STATUS "  Padrão C: C${CMAKE_C_STANDARD}")
message(STATUS "  Modo: ${CMAKE_BUILD_TYPE}")
message(STATUS "===========================================")
