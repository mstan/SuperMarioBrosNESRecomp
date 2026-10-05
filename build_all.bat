@echo off
rem Cycle is the release default. Pass -Rom if the NTSC ROM has another name.
"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\build.ps1" %*
exit /b %ERRORLEVEL%
