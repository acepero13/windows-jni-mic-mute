@echo off
REM Define the path to GCC and JDK
set GCC_PATH=C:\msys64\ucrt64\bin\gcc.exe
set JDK_PATH=C:\Program Files\Eclipse Adoptium\jdk-17.0.7.7-hotspot

REM Get the current working directory as the workspace folder
set WORKSPACE_FOLDER=%CD%

REM Change to the directory where GCC is located
cd C:\msys64\ucrt64\bin

REM Compile the C++ code into a DLL
%GCC_PATH% -fdiagnostics-color=always -g -static-libgcc -static-libstdc++ -shared -static ^
    "%WORKSPACE_FOLDER%\MicrophoneControl.cpp" ^
    -o "%WORKSPACE_FOLDER%\..\resources\com\acepero13\research\audio\windows\lib\MicrophoneControl.dll" ^
    -I "%JDK_PATH%\include" ^
    -I "%JDK_PATH%\include\win32" ^
    -lole32 -lstdc++ -std=c++11

REM Check if the build was successful
if %ERRORLEVEL% == 0 (
    echo Build successful
) else (
    echo Build failed
)

REM Return to the original directory
cd %WORKSPACE_FOLDER%
