@echo off

rem echo compressing...
rem upx.exe _build/libwiz3d.dll
upx.exe --brute _build/libwiz3d.dll

pause
