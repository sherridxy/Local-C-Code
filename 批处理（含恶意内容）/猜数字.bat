@echo off
set/a rand=%random%%%100+1
set count=0
:loop1
set/a count+=1
set/p input=请输入一个1-100间的数字:
if %input% equ %rand% (
echo 猜对了
goto :end
)
if %input% lss %rand% (
echo 小了
goto :loop1
)
if %input% gtr %rand% (
echo 大了
goto :loop1
)

:end
pause >nul
exit