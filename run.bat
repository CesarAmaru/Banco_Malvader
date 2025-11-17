@echo off
echo ===============================================
echo   BANCO MALVADER - EXECUTANDO
echo ===============================================
echo.

if not exist "build\banco.exe" (
    echo ERRO: Executavel nao encontrado!
    echo.
    echo Execute primeiro: compile.bat
    echo.
    pause
    exit /b 1
)


if not exist "build\data" (
    echo Criando diretorio de dados...
    mkdir "build\data"
)

cd build
echo Iniciando Banco Malvader...
echo.
banco.exe

cd ..

echo.
echo ===============================================
echo   PROGRAMA ENCERRADO
echo ===============================================
pause