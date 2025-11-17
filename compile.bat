@echo off
echo ===============================================
echo   BANCO MALVADER - COMPILACAO
echo ===============================================
echo.


if not exist "build" (
    echo [1/4] Criando diretorio build...
    mkdir build
) else (
    echo [1/4] Diretorio build ja existe
)

echo [2/4] Configurando projeto com CMake...
cd build
cmake .. -G "MinGW Makefiles"

if errorlevel 1 (
    echo.
    echo ERRO: Falha na configuracao do CMake!
    echo Verifique se o CMake e MinGW estao instalados.
    pause
    exit /b 1
)

echo [3/4] Compilando projeto...
cmake --build .

if errorlevel 1 (
    echo.
    echo ERRO: Falha na compilacao!
    echo Verifique os erros acima.
    pause
    exit /b 1
)

echo [4/4] Criando diretorio de dados...
if not exist "data" mkdir data

cd ..

echo.
echo ===============================================
echo   COMPILACAO CONCLUIDA COM SUCESSO!
echo ===============================================
echo.
echo Executavel: build\banco.exe
echo.
echo Para executar:
echo   1. Execute run.bat
echo   2. Ou: cd build ^&^& banco.exe
echo.
pause