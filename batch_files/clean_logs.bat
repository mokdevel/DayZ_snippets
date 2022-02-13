@echo off

call :cleanup "P:\profiles"
call :cleanup "C:\Users\anter\AppData\Local\DayZ"
call :cleanup "C:\Users\anter\AppData\Local\DayZ Exp"
goto :end

:cleanup
::Change to right drive and its root
SET DIR=%1
echo %DIR%
cd /D %DIR%

del *.rpt
del *.log
del *.bidmp
del *.mdmp
del *.adm
exit /b

:end