@echo off
set num=45
set begin=2
set interval=2
for /l %%i in (%begin%,%interval%,%num%) do (
echo %%i
)
pause >nul
exit