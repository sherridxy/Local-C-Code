@echo off
set var=100
set x=0
set y=0
set z=0
set temp=0
:begin
if %var% gtr 999 (goto :end)
set/a x=%var%/100
set/a y=%var%/10-10*%x%
set/a z=%var%-100*%x%-10*%y%
set/a temp=%x%*%x%*%x%+%y%*%y%*%y%+%z%*%z%*%z%
if %var% equ %temp% (echo %var%)
set/a var+=1
goto :begin
:end
pause