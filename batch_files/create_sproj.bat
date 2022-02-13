cls
@echo off
p:
cd p:\eai

setlocal enableextensions enabledelayedexpansion

:: Get current Folder (e.g: .bat file in P:/MyMod -> MyMod)
for %%I in (.) do set CurrentFolder=%%~nxI

:: Set the needed parts for the .xml format
set "front=^<file path^=^"%CurrentFolder%^/"
set mid=^"
set "end= ^/^> "


echo ^<?xml version^=^"1.0^" encoding^=^"UTF-8^" ^?^> > %CurrentFolder%.sproj
echo ^<project^> >> %CurrentFolder%.sproj

for /f "delims=" %%F in ('forfiles /s /m *.c /c "cmd /c echo @relpath"') do (
	:: Get the relative path of the current file ( ".\MyMod\scripts\4_Something\file.c")
	set old=%%~F
	:: Change from \ to / (...)
	set new=!old:\=/!
	:: and remove the silly ./ from the path
	set new=!new:./=!
	:: Build the string (god what a mess...)
	echo 	%front%!new!!mid!%end% >> %CurrentFolder%.sproj
)
:: Add the end-tag
echo ^</project^> >> %CurrentFolder%.sproj


pause