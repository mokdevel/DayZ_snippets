:: Params:
::  %1 : Integer. The setup to select. If left blank, user will be asked for input.

@echo off
call run_setup.bat %1
echo ---
echo Starting client from %dayzLocation% with 
echo -mod=%client_mod%
echo ---
timeout 3

::Change to right drive
cd /D %dayzLocation%
::Change to right directory
cd %dayzLocation%

start .\DayZDiag_x64.exe "-mod=%client_mod%" -filepatching

exit