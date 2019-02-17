@echo off

rem echo compressing...
rem upx.exe _build/micron.exe
upx.exe --brute _build/micron.exe

pause
