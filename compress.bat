@echo off

rem echo compressing...
rem upx.exe _build/micron.exe
rem upx.exe _build/OpenAL32.dll
upx.exe --brute _build/micron.exe
upx.exe --brute _build/OpenAL32.dll

pause
