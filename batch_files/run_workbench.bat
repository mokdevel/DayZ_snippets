:: Params:
::  %1 : Integer. The setup to select. If left blank, user will be asked for input.

@echo off
call run_setup.bat %1
echo ---
echo Starting workbench from %dayzToolsLocation%\Bin\Workbench\
echo -mod=%workbench_mod% 
echo ---
timeout 5

::Change to right drive
cd /D %dayzToolsLocation%
::Change to right directory
cd %dayzToolsLocation%
cd .\Bin\Workbench

start .\workbenchApp.exe "-mod=%workbench_mod%"
::start .\workbenchApp.exe -gproj=P:\dayz.gproj "-mod=%workbench_mod%"

exit