@echo off

rem echo compressing...
rem upx.exe _build/libmicron.dll
upx.exe --brute _build/libmicron.dll

pause
