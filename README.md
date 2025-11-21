
# Banco Malvader – Sistema Bancário em C

Sistema bancário modular em linguagem C, desenvolvido como projeto acadêmico.  
O sistema implementa manipulação de clientes, operações bancárias, listagens, ordenação e persistência de dados em arquivos de texto.  
Toda a documentação do código-fonte é gerada automaticamente com **Doxygen**.

---

## Objetivos do Projeto

- Aplicar fundamentos de modularização em C.  
- Separação de responsabilidades entre módulos.  
- Persistência de dados utilizando arquivos texto.  
- Uso de ponteiros, estruturas, vetores dinâmicos, ordenação e busca.  
- Documentação de código profissional via Doxygen.

---

## Funcionalidades

- Cadastro de clientes
- Depósito
- Saque
- Transferência entre contas
- Alteração de dados
- Consulta de saldos
- Exclusão lógica de clientes (marcando como inativo)
- Reativação de contas
- Ordenação:
  - por nome
  - por número da conta
- Registro de movimentações em arquivo

---

## Estrutura de diretórios

```
Banco_Malvader/
│
├── src/
│   ├── main.c               # Função principal / loop do menu
│   ├── banco.c              # Lógica de operações bancárias
│   ├── banco.h
│   ├── cliente.c            # Controle dos dados de clientes
│   ├── cliente_data.h
│   ├── ordenacao.c          # Ordenação (quicksort + comparadores)
│   ├── ordenacao.h
│   ├── io.c                 # Funções de entrada e validação
│   ├── io.h
│   └── ...
│
├── data/
│   ├── clientes.txt
│   ├── movimentos.txt
│   └── ...
│
├── README.md
└── Doxyfile
```

---

## Módulos principais

### `banco.c`  
Contém a lógica principal do sistema bancário:

- depósito  
- saque  
- transferência  
- carregamento e gravação de dados  
- busca de clientes

### `cliente.c` / `cliente_data.h`  
Define a estrutura `Cliente` e funções associadas.

### `ordenacao.c`  
Implementa `quicksort` e comparadores para ordenar:

- por nome  
- por número da conta

### `io.c`  
Funções de leitura e validação do usuário:

- leitura de `int`, `double`, strings  
- limpeza de buffer  
- leitura formatada para conta e valor

### `main.c`  
Controla:

- o menu do programa  
- chamadas aos módulos  
- execução do loop principal

---

## Requisitos

- GCC (ou outro compilador C)
- CMake (opcional)
- Doxygen (para gerar documentação)

### Verificar se o compilador está instalado

```bash
gcc --version
```

### Verificar Doxygen

```bash
doxygen --version
```

---

## Como compilar

### Via GCC (modo rápido)

```bash
gcc -o banco src/*.c
./banco
```

### Windows (MinGW)

```bash
gcc -o banco.exe src/*.c
banco.exe
```

---

## Compilar usando CMake

```bash
mkdir build
cd build
cmake ..
make
./banco
```

Windows:

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
banco.exe
```

---

## Gerar documentação com Doxygen

### 1 Criar Doxyfile (se ainda não existir)

```bash
doxygen -g
```

### 2 Editar no Doxyfile:

```
PROJECT_NAME           = "Banco Malvader"
INPUT                  = ./src
RECURSIVE              = YES
GENERATE_HTML          = YES
GENERATE_LATEX         = YES
OUTPUT_DIRECTORY = docs
```

> Para o README virar a página inicial da documentação:

```
USE_MDFILE_AS_MAINPAGE = README.md
```

### 3 Gerar documentação

```bash
doxygen Doxyfile
```

### 4 Abrir no navegador

```
docs/html/index.html
```

---

## Alguns comandos úteis

Eliminar build do CMake:

```bash
rm -rf build
```

Regenerar docs:

```bash
doxygen Doxyfile
```

---

## Autores

**Cesar Amaru**,
**Carlos Eduardo Estrela**,
**Thyago Oliveira**,
**Samuel RIbeiro Braga**,
**Yan Gabriel Pereira**

---

## 🏁 Licença

Projeto criado para fins acadêmicos, podendo ser utilizado como base para estudos, ensino e evolução de projetos C.
