@echo off
echo ===============================================
echo   BANCO MALVADER - COMPILAR E EXECUTAR
echo ===============================================
echo.

echo Etapa 1: Compilando o projeto...
echo.
call compile.bat

if errorlevel 1 (
    echo.
    echo Compilacao falhou! Abortando execucao.
    pause
    exit /b 1
)

echo.
echo ===============================================
echo Etapa 2: Executando o programa...
echo ===============================================
echo.

REM Pequena pausa para visualizar mensagem
timeout /t 2 /nobreak >nul

call run.bat