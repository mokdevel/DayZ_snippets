@echo off
call run_setup.bat 0
echo ---
echo Building ...
echo ---

:: Change to right drive
cd /D %dayzToolsLocation%
:: Change to right directory
cd %dayzToolsLocation%
cd .\Bin\AddonBuilder

set PACKEDPBOS_DIR=P:\PackedPbos

::---------------------------------------------------------------------------

call :build P:\mod_test mod_test.pbo P:\mod_test_packed\Addons
call :build P:\mod_dcm mod_dcm.pbo P:\mod_dcm_packed\Addons
call :build P:\eAI eai.pbo P:\eAIpacked\Addons

GOTO :done

::---------------------------------------------------------------------------

:build
SET MOD_SOURCE=%1
SET MOD_NAME=%2
SET MOD_DESTINATION=%3

del %MOD_DESTINATION%\*.pbo
start AddonBuilder.exe %MOD_SOURCE% %PACKEDPBOS_DIR% -packonly
copy %PACKEDPBOS_DIR%\%MOD_NAME% %MOD_DESTINATION% 1>NUL

::pause > nul

exit /b

::---------------------------------------------------------------------------

:done
