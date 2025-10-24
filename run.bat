@echo off
REM Script para compilar y ejecutar el proyecto Taller2CPP

echo ========================================
echo Compilando proyecto...
echo ========================================
g++ -std=gnu++17 -O2 -Wall -Wextra -Iinclude -o build/taller.exe src/App.cpp src/SparseMatrix.cpp src/Node.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo Compilacion exitosa!
    echo Ejecutando programa...
    echo ========================================
    echo.
    build\taller.exe
) else (
    echo.
    echo ========================================
    echo ERROR: La compilacion fallo
    echo ========================================
    pause
)
