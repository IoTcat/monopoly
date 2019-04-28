@echo off
title C++ Assignment Controller

:menu
cls
echo.
echo Please Select:
echo ==============================
echo.
echo 1. view instruction
echo.
echo 2. compile
echo.
echo 3. open game
echo.
echo 4. exit
echo.
echo ==============================
echo.
echo.
set /p user_input=Please Input a Number = 
if %user_input% equ 1 goto instr
if %user_input% equ 2 goto gcc
if %user_input% equ 3 goto open
if %user_input% equ 4 goto end
goto menu



:instr
start https://github.com/IoTcat/monopoly#monopoly
goto menu

:open
start bin/monopoly.exe
goto menu

:gcc
where g++>nul
cls
if errorlevel 1 (
echo gcc NOT FOUND in your computer!!
echo Press any key to start installation!
pause>nul
goto install
) else (
echo Detected gcc Environment..
echo Start to compile!!
goto compile
)



:install
cls
echo Please download and run the gcc install program.
ping 127.0.0.1 >nul
start https://yimian-setup.obs.myhwclouds.com/setup/tdm64-gcc-5.1.0-2.exe
ping 127.0.0.1 >nul
cls
echo After install, Please restart this script to compile!!&&pause&&exit


:compile
cls
echo compiling...
g++ -O2 -o monopoly src/main.cpp src/controller.cpp src/food.cpp src/roll.cpp src/player.cpp src/square.cpp src/msgbox.cpp src/scoreboard.cpp src/hintbox.cpp src/map.cpp src/point.cpp src/snake.cpp src/startinterface.cpp src/tools.cpp lib/ovo.cpp -std=c++11 -fexec-charset=utf-8
echo compile finished! The program is in current folder!
echo Press any key to open it!
#pause
start monopoly.exe
goto menu




:end