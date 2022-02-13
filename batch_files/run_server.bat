:: Params:
::  %1 : Integer. The setup to select. If left blank, user will be asked for input.

@echo off
call run_setup.bat %1
echo ---
echo Starting server from %dayzLocation% with 
echo -mod=%server_mod% 
echo -servermod=%server_servermod%
echo -profiles=%server_profiles%
echo -mission=%server_mission%
echo -config=%server_config%
echo ---
timeout 4

::Change to right drive
::cd /D %dayzLocation%
::Change to right directory
::cd %dayzLocation%

:: Change to P: drive
:: For some reason DayZ is not capable of finding the right files/dirs if started from DayZ 
:: installation dir. This even if all the params have full path-filename (eg. -config=P:\serverDZ.cfg). 
:: Especially "@Survivor Missions" gave issues.
cd P:
::echo start %dayzLocation%\DayZDiag_x64.exe -server -config=%server_config% -profiles=%server_profiles% -dologs -adminlog -netlog -freezecheck -filePatching "-scriptDebug=true" -mission=%server_mission% "-mod=%server_mod%" "-servermod=%server_servermod%"
::echo %dayzLocation%\DayZDiag_x64.exe -server -config=%server_config% -profiles=%server_profiles% -dologs -adminlog -netlog -freezecheck -filePatching "-scriptDebug=true" -mission=%server_mission% "-mod=%server_mod%" "-servermod=%server_servermod%"
start %dayzLocation%\DayZDiag_x64.exe -server -config=%server_config% -profiles=%server_profiles% -dologs -adminlog -netlog -freezecheck -filePatching "-scriptDebug=true" -mission=%server_mission% "-mod=%server_mod%" "-servermod=%server_servermod%"

exit