@echo off

rem echo compressing...
rem upx.exe _build/libbeam.dll
upx.exe --brute _build/libbeam.dll

pause
