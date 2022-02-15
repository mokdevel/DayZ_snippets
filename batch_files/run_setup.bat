:: Params:
::  %1 : Integer. The setup to select. If left blank, user will be asked for input.

@echo off

:: Check that P-drive is mapped
if NOT exist P:\ (
	echo ---
    echo ERROR: P-drive is not mapped!
	echo ---
	pause > nul
	exit
)

::---------------------------------------------------------------------------

set DAYZ_EXPERIMENTAL=FALSE

::---------------------------------------------------------------------------

:: Copy a windowed client config
:: DayZ overwrites the file annoyingly and if you want to have a small window 
:: while developing, copy a fresh .cfg at start.
set documentsLocation=C:\Users\anter\Documents

copy .\DayZ_windowed.cfg %documentsLocation%\DayZ\DayZ.cfg 1>NUL
if /I NOT "%DAYZ_EXPERIMENTAL%"=="true" GOTO NOT_EXP_1
	copy .\DayZ_windowed.cfg "%documentsLocation%\DayZ Exp\DayZ Exp.cfg" 1>NUL
:NOT_EXP_1

:: Game location
set dayzLocation=F:\SteamLibrary\steamapps\common\DayZ\
set dayzdrive_P=F:\DayZ_drive_P\

:: Game location - experimental
set dayzLocation_exp=F:\SteamLibrary\steamapps\common\"DayZ Exp"\
set dayzdrive_P_exp=F:\DayZ_drive_P_exp\

:: Dayz tools location
set dayzToolsLocation=F:\SteamLibrary\steamapps\common\DayZ Tools\

::---------------------------------------------------------------------------

:: Symlink the needed mods
:: NOTE: Mods with spaces in their names may has issues. You can assign them a non-spaced name.
mklink /J P:\@CF "%dayzLocation%\!Workshop\@CF" 2>NUL
mklink /J P:\@CF-Test "%dayzLocation%\!Workshop\@CF-Test" 2>NUL
mklink /J P:\@eAI "%dayzLocation%\!Workshop\@eAI" 2>NUL
mklink /J P:\@Community-Online-Tools "%dayzLocation%\!Workshop\@Community-Online-Tools" 2>NUL
mklink /J P:\@SurvivorMissions "%dayzLocation%\!Workshop\@Survivor Missions" 2>NUL
::mklink /J "P:\@Survivor Missions" "%dayzLocation%\!Workshop\@Survivor Missions" 2>NUL
mklink /J P:\@BasicMap "%dayzLocation%\!Workshop\@Basic Map" 2>NUL

call :SYMLINK_DEVDIRS %dayzLocation% %dayzdrive_P%
call :SYMLINK_DEVDIRS %dayzLocation_exp% %dayzdrive_P%
call :SYMLINK_DEVDIRS_TO_EXP %dayzdrive_P_exp% %dayzdrive_P% 

goto :START_SETUP

::---------------------------------------------------------------------------
:: Symlink the mods you're developing to DayZ root folder

:SYMLINK_DEVDIRS
	if exist %1	(
		:: Symlink the mpmissions folder to DayZ root folder
		mklink /J %1\mpmissions %2\mpmissions 2>NUL

		:: Symlink the mods you're developing to DayZ root folder
		mklink /J %1\mod_test %2\mod_test 2>NUL
		mklink /J %1\mod_test_server %2\mod_test_server 2>NUL
		mklink /J %1\eAI %2\eAI 2>NUL
		mklink /J %1\mod_dcm %2\mod_dcm 2>NUL
	) else (
		echo ERROR: DayZ Experimental does not exist if %1 !
	)
exit /b

::---------------------------------------------------------------------------
:: Symlink the source code dirs from main P-drive to experimental P-drive

:SYMLINK_DEVDIRS_TO_EXP
	if exist %1	(
		:: Symlink the mpmissions folder
		mklink /J %1\mpmissions %2\mpmissions 2>NUL	
		
		:: Symlink the mods you're developing to DayZ root folder
		mklink /J %1\mod_code %2\mod_code 2>NUL	
		mklink /J %1\mod_test %2\mod_test 2>NUL
		mklink /J %1\mod_test_packed %2\mod_test_packed 2>NUL
		mklink /J %1\mod_test_server %2\mod_test_server 2>NUL
		mklink /J %1\eAI %2\eAI 2>NUL
		mklink /J %1\eAIpacked %2\eAIpacked 2>NUL
		mklink /J %1\mod_dcm %2\mod_dcm 2>NUL
		mklink /J %1\mod_dcm_packed %2\mod_dcm_packed 2>NUL
	) else (
		echo ERROR: Experimental P-drive does not exist in %1 !
		timeout 4
	)
	
exit /b

::---------------------------------------------------------------------------
:START_SETUP

if /I NOT "%DAYZ_EXPERIMENTAL%"=="true" GOTO NOT_EXP_2
	echo -------------------------------------------------
	echo ----------- RUNNING DAYZ EXPERIMENTAL -----------
	echo -------------------------------------------------
	set dayzLocation=%dayzLocation_exp%
:NOT_EXP_2

::---------------------------------------------------------------------------

echo Select setup to run:
echo 0 - Basic setup for other 
echo 1 - mod_test, CF-Test, COT (basic mod testing)
echo 2 - mod_test, mod_test_server (basic mod testing on client and server, CF, COT, BasicMap)
echo 3 - mod_dcm, CF-Test, COT, BasicMap, SurvivorMissions, eAI
echo 4 - 

:: Check if number was given as the param
if "%~1"=="" goto SETUP_SELECT
set INPUT=%1
echo Running SETUP_%INPUT%.
timeout 1
goto SETUP_PARAM

:SETUP_SELECT
set INPUT=
set /P INPUT=Pick a number: %=%
:SETUP_PARAM

goto SETUP_%INPUT%

::------------------------------------
:SETUP_0

:: Do nothing

goto SETUP_DONE

::------------------------------------
:SETUP_1
:: Set client params
::set client_mod=
set client_mod=P:\mod_test_packed;P:\@CF-Test;P:\@Community-Online-Tools;
::set client_mod=P:\FirstModPacked;

:: Set server params
set server_mod=P:\@CF-Test;P:\@Community-Online-Tools;
set server_servermod=

:: Set workbench params
set workbench_mod=P:\mod_test_packed;
::set workbench_mod=P:\FirstModPacked;

goto SETUP_DONE

::------------------------------------
:SETUP_2
:: Set client params
set client_mod=P:\@CF;P:\@Community-Online-Tools;P:\mod_test_packed;P:\mod_test_server_packed;P:\@BasicMap;

:: Set server params
set server_mod=P:\@CF;P:\@Community-Online-Tools;P:\mod_test_server_packed;P:\@BasicMap;
set server_servermod=

:: Set workbench params
set workbench_mod=P:\@CF;P:\@Community-Online-Tools;P:\mod_test_packed;P:\mod_test_server_packed;P:\@BasicMap;
::set workbench_mod=P:\@CF;P:\@Community-Online-Tools;P:\mod_test_packed;P:\mod_test_server_packed;
::set workbench_mod=P:\FirstModPacked;

goto SETUP_DONE

::------------------------------------
:SETUP_3
:: Set client params
::set client_mod=P:\@CF-Test;P:\@Community-Online-Tools;P:\mod_dcm_packed;P:\@BasicMap;
set client_mod=P:\@CF-Test;P:\@Community-Online-Tools;P:\@BasicMap;P:\eAIPacked;P:\mod_dcm_packed;

:: Set server params
set server_mod=P:\@CF-Test;P:\@Community-Online-Tools;P:\mod_dcm_packed;P:\@BasicMap;P:\eAIPacked;
set server_servermod=P:\@SurvivorMissions;

:: Set workbench params
set workbench_mod=P:\@CF-Test;P:\@Community-Online-Tools;P:\mod_dcm_packed;P:\@BasicMap;P:\eAIPacked;

goto SETUP_DONE

::------------------------------------
:SETUP_X

:: Set client params
::set client_mod=P:\@CF;P:\eAIpacked;P:\@Community-Online-Tools;

:: Set server params
::set server_mod=P:\@CF;P:\eAIpacked;P:\@Community-Online-Tools;
::set server_servermod=P:\@CF;P:\eAIpacked;P:\@Community-Online-Tools;

:: Set workbench params
::set workbench_mod=P:\@CF;P:\@SurvivorMissions;P:\mod_test;

:SETUP_DONE
:: Set common server params
set server_profiles=P:\profiles
set server_mission=P:\mpmissions\dayzOffline.chernarusplus
set server_config=P:\serverDZ.cfg

::---------------------------------------------------------------------------

:: Change to right drive
::cd /D %dayzLocation%
:: Change to right directory
::cd %dayzLocation%

:: Batch file syntax
:: 1>NUL : Disables output of success
:: 2>NUL : Disables output of failure