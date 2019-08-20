@echo off

rem echo compressing...
rem upx.exe _build/libspark.dll
upx.exe --brute _build/libspark.dll

pause
