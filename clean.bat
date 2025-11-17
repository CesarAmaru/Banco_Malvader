@echo off
echo ===============================================
echo   BANCO MALVADER - LIMPEZA
echo ===============================================
echo.
echo Este script vai DELETAR os seguintes itens:
echo   - Pasta build/ (compilacao)
echo   - Arquivos temporarios
echo.
echo AVISO: Os dados em build/data/ serao perdidos!
echo.
set /p confirm="Tem certeza? (S/N): "

if /i not "%confirm%"=="S" (
    echo.
    echo Operacao cancelada.
    pause
    exit /b 0
)

echo.
echo Limpando projeto...
echo.


if exist "build" (
    echo [1/3] Removendo pasta build...
    rmdir /s /q "build"
    echo Pasta build removida.
) else (
    echo [1/3] Pasta build nao existe.
)


if exist "CMakeCache.txt" (
    echo [2/3] Removendo CMakeCache.txt...
    del /q "CMakeCache.txt"
)

if exist "CMakeFiles" (
    echo [2/3] Removendo CMakeFiles...
    rmdir /s /q "CMakeFiles"
)

echo [3/3] Limpeza concluida!

echo.
echo ===============================================
echo   PROJETO LIMPO COM SUCESSO!
echo ===============================================
echo.
echo Para recompilar, execute: compile.bat
echo.
pause