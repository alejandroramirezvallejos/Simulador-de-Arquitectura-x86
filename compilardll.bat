@echo off
echo Actualizando simulador para Excel...

REM Compilar en CODE
cd CODE
g++ -shared -o simulador.dll main.cpp src/*.cpp -std=c++20
cd ..

REM Copiar a raíz (donde está Excel)
if exist "CODE\simulador.dll" (
    copy "CODE\simulador.dll" "simulador.dll" >nul 2>&1
    echo ✅ DLL actualizada para Excel
) else (
    echo ❌ Error: No se compiló la DLL
)

pause