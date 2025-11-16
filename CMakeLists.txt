cmake_minimum_required(VERSION 3.10)

project(Banco_Malvader C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Forçar caminhos absolutos e escapar espaços
get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

# Arquivos fonte com caminhos absolutos
set(SOURCE_FILES
        "${PROJECT_ROOT}/src/main.c"
        "${PROJECT_ROOT}/src/banco.c"
        "${PROJECT_ROOT}/src/cliente.c"
        "${PROJECT_ROOT}/src/io.c"
        "${PROJECT_ROOT}/src/ordenacao.c"
)

# Arquivos de cabeçalho
set(HEADER_FILES
        "${PROJECT_ROOT}/src/banco.h"
        "${PROJECT_ROOT}/src/cliente_data.h"
        "${PROJECT_ROOT}/src/io.h"
        "${PROJECT_ROOT}/src/ordenacao.h"
)

# Verificar se os arquivos existem
foreach(src_file ${SOURCE_FILES})
    if(NOT EXISTS ${src_file})
        message(FATAL_ERROR "Arquivo fonte não encontrado: ${src_file}")
    endif()
endforeach()

# Criar diretório data no build antes de compilar
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")

# Criar executável
add_executable(banco ${SOURCE_FILES} ${HEADER_FILES})

# Incluir diretório src para os headers
target_include_directories(banco PRIVATE "${PROJECT_ROOT}/src")

# Copiar arquivo de clientes para o build (se existir)
if(EXISTS "${PROJECT_ROOT}/data/clientes.txt")
    add_custom_command(
            TARGET banco POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_ROOT}/data/clientes.txt"
            "${CMAKE_CURRENT_BINARY_DIR}/data/clientes.txt"
            COMMENT "Copiando clientes.txt para o diretório de build..."
    )
endif()

# Criar arquivo movimentos.txt vazio se não existir
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/data/movimentos.txt")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/data/movimentos.txt" "")
endif()

# Target para limpar dados
add_custom_target(clean-data
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/data"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/data"
        COMMENT "Limpando dados do banco..."
)

# Target para executar
add_custom_target(run
        COMMAND banco
        DEPENDS banco
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Executando Banco Malvader..."
)

# Target para executar com dados de teste
add_custom_target(run-test
        COMMAND ${CMAKE_COMMAND} -E echo "Criando dados de teste..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_ROOT}/test_data/clientes.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/data/clientes.txt"
        COMMAND banco
        DEPENDS banco
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Executando com dados de teste..."
)

message(STATUS "===========================================")
message(STATUS "  Projeto: ${PROJECT_NAME}")
message(STATUS "  Diretório: ${PROJECT_ROOT}")
message(STATUS "  Compilador: ${CMAKE_C_COMPILER}")
message(STATUS "  Padrão C: C${CMAKE_C_STANDARD}")
message(STATUS "  Modo: ${CMAKE_BUILD_TYPE}")
message(STATUS "===========================================")