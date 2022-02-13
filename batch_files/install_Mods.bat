@echo off
@rem http://media.steampowered.com/installer/steamcmd.zip
::SETLOCAL ENABLEDELAYEDEXPANSION

:: DEFINE the following variables where applicable to your install

SET STEAMLOGIN=mokdevel3
SET ServerBRANCH=223350

SET RootPath=C:\DayZServer
SET ServerPath=%RootPath%\server
SET STEAMPATH=%RootPath%\Steamcmd
SET WORKSHOPPATH=F:\SteamLibrary\steamapps\common\DayZ\!Workshop

IF [%STEAMLOGIN%]==[] goto :error
IF [%ServerPath%]==[] goto :error

SET SERVER_MODPARAM=
SET SERVER_SERVERMODPARAM=


::--------------------------------------------------------------------------
:: The installation 

:normal_install
::call :install @eAI "P:\eAIpacked"
::call install <SYMLINK NAME IN SERVER DIR> <DESTINATION which is a DIRECTORY or MOD under !Workshop>
call :install @eAI @eAI
call :install @CF @CF
call :install @Community-Online-Tools @Community-Online-Tools
call :install @zSpawnSelection @zSpawnSelection
call :install @FreeHelicopters "@Free Helicopters"
call :install @DabsFramework "@Dabs Framework"
call :install @SurvivorMissions "@Survivor Missions"
call :install @DeerIsle @DeerIsle
call :install @DayZ-Expansion @DayZ-Expansion
call :install @DayZ-Expansion-Core @DayZ-Expansion-Core
call :install @DayZ-Expansion-Licensed @DayZ-Expansion-Licensed
call :install @DayZ-Expansion-Vehicles @DayZ-Expansion-Vehicles
call :install @DayZ-Expansion-Book @DayZ-Expansion-Book

goto :end

::--------------------------------------------------------------------------
:: Install

:install
SET MODNAME=%1
SET MOD=%2
SET SERVERMOD=%3
echo ------------------------------------------------------------------------
echo ---Installing: %MODNAME% (ID: %MOD%)
if not exist %ServerPath%\%MODNAME% goto NO_RMDIR
rmdir %ServerPath%\%MODNAME%
:NO_RMDIR

::Change to right drive and its root
cd /D %MOD%
cd \
::Check if dir exists and link
if exist %MOD%\ goto :linkpath1
if not exist %MOD%\ goto :linkpath2
goto :linkcontinue

:linkpath1
	echo Linked %MODNAME%
	SET LINK_CMD="%ServerPath%\%MODNAME%" "%MOD%"
	goto :linkdo
:linkpath2
	echo Linked %MODNAME%
	SET LINK_CMD="%ServerPath%\%MODNAME%" "%WORKSHOPPATH%\%MOD%"
	goto :linkdo

:linkdo
	::Clean the LINK_CMD by replacing "@ -> @
	set LINK_CMD=%LINK_CMD:"@=@%
	::Clean the LINK_CMD by replacing "" -> "
	set LINK_CMD=%LINK_CMD:""="%
::	echo %LINK_CMD%
	mklink /j %LINK_CMD%
	
:linkcontinue
cd /D %RootPath%

:: Copy keys under server\keys if available
copy %ServerPath%\%MODNAME%\keys\*.bikey %ServerPath%\keys
:: Set server mod parameters
IF [%3]==[] SET SERVER_MODPARAM=%SERVER_MODPARAM%%MODNAME%;
IF [%3]==[true] SET SERVER_SERVERMODPARAM=%SERVER_SERVERMODPARAM%%MODNAME%;
echo.
exit /b

::--------------------------------------------------------------------------
:: The End 

:end
echo.
echo     Your DayZ server is now up to date
echo 	-mod=%SERVER_MODPARAM%
echo 	-servermod=%SERVER_SERVERMODPARAM%
echo     key "ENTER" to exit
pause
exit /b

:error
::--------------------------------------------------------------------------
:: Error
echo.
echo    ERROR: Please check that you have defined the STEAMLOGIN and ServerPath parameters
echo.
echo     key "ENTER" to exit
pause
exit /b