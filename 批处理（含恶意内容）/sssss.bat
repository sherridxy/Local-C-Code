@echo off
set/p var= 是否打开记事本(Y/N)
set i=1
if %var%==Y (
start notepad
pause>nul )
if %var%==N goto :tag1
:end
pause>nul 
exit

:tag1
if %i% equ 10 goto :end
start notepad
set/a i+=1
goto :tag1
