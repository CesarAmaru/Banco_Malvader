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

## Estrutura dos Módulos

### `banco.c`
Responsável por:

- depósito  
- saque  
- transferência  
- carregamento e gravação de dados  
- busca de clientes

### `cliente.c` / `cliente_data.h`
Define a estrutura `Cliente` e funções associadas.

### `ordenacao.c`
Implementa `quicksort` e comparadores:

- por nome  
- por número da conta

### `io.c`
Funções de entrada e validação:

- leitura de `int`, `double` e strings  
- tratamento de buffer  
- leitura formatada para conta e valor

### `main.c`
Controla:

- o menu  
- chamadas aos módulos  
- laço principal de execução

---

## Requisitos

- GCC, Clang, MSVC ou outro compilador C.  
- CMake (opcional).  
- Doxygen (para documentação).  
- LaTeX (MiKTeX, TexLive ou MacTex – para gerar PDF).

---

## Executar no Terminal (Windows)

Pré-requisitos:

- CMake instalado  
- Compilador C (MinGW-w64, Clang, MSVC…)

### Passo a passo

1. Pressione `Win + R`, digite:  
   ```
   cmd
   ```
2. Vá até o diretório do projeto, por exemplo:

```bash
cd "C:\Users\...\Banco_Malvader"
```

3. Para compilar:

```
compile.bat
```

4. Para executar:

```
run.bat
```

5. Ou compilação + execução automática:

```
start.bat
```

---

## Compilar manualmente com GCC

### Linux

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

## Compilando com CMake

```bash
mkdir build
cd build
cmake ..
make
./banco
```

### Windows

```bash
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
banco.exe
```

---

## Gerar documentação com Doxygen
Pré-requisitos:
- Doxygen instalado na máquina

### 1. Criar Doxyfile
Vá até o diretório do projeto, e digite:
```bash
doxygen -g
```

### 2. Configurar

No Doxyfile altere:

```
PROJECT_NAME     = "Banco Malvader"
INPUT            = ./src
RECURSIVE        = YES
GENERATE_HTML    = YES
GENERATE_LATEX   = YES
OUTPUT_DIRECTORY = docs
```

Para usar o README como página inicial:

```
USE_MDFILE_AS_MAINPAGE = README.md
```

### 3. Gerar documentação

```bash
doxygen Doxyfile
```

---

# Visualizar HTML

```bash
start html/index.html
```

ou

```bash
start docs/html/index.html
```

---

# Gerar PDF da Documentação com LaTeX

## 1. Instalar LaTeX

### Windows (recomendado)
Instalar MiKTeX:

https://miktex.org/download

Marque:

```
Install missing packages automatically
```

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install texlive-full
```

### macOS

```bash
brew install mactex
```

---

## 2. Compilar PDF

Depois de gerar o LaTeX com o Doxygen:

```bash
cd latex
```

Use o XeLaTeX (melhor para Unicode):

```bash
xelatex refman.tex
xelatex refman.tex
```

O PDF será criado em:

```
latex/refman.pdf
```
ou 

```
docs/latex/refman.pdf
```
---

## 3. Abrir o PDF

### Windows

```bash
start refman.pdf
```

### Linux

```bash
xdg-open refman.pdf
```

### macOS

```bash
open refman.pdf
```

---

# Compilar pelo CLion

1. Abrir o projeto  
2. Esperar o CMake carregar  
3. `Ctrl + F9` para compilar  
4. `Shift + F10` para executar

---

## Comandos Úteis

Apagar build do CMake:

```bash
rm -rf build
```

Gerar documentação novamente:

```bash
doxygen Doxyfile
```

Recompilar PDF:

```bash
cd latex
xelatex refman.tex
```

---

## Autores

- Carlos Eduardo Estrela  
- Cesar Amaru  
- Thyago Oliveira  
- Samuel Ribeiro Braga  
- Yan Gabriel Pereira

---

## 🏁 Licença

Projeto criado para fins acadêmicos, podendo ser utilizado como base para estudos, ensino e evolução de projetos C.
