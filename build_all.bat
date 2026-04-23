@echo off
setlocal enabledelayedexpansion

rem build_all.bat — Release (non-debug) build.
rem
rem Produces: build_release\SuperMarioBrosRecomp.exe  (~3.0 MiB)
rem Flags:    ENABLE_NESTOPIA_ORACLE=OFF, NESRECOMP_REVERSE_DEBUG=OFF
rem Regen:   plain (no --reverse-debug)
rem
rem Coexists with the debug build in build_debug\ from build_rdb.bat.
rem Switching between them does NOT require rebuilding — just run the
rem other .exe.  Different output dirs keep CMake caches isolated.

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64 >nul 2>&1

set "CLEANPATH="
for %%p in ("%PATH:;=" "%") do (
    echo %%~p | findstr /i /c:"msys64" /c:"mingw" >nul 2>&1
    if errorlevel 1 (
        if defined CLEANPATH (set "CLEANPATH=!CLEANPATH!;%%~p") else (set "CLEANPATH=%%~p")
    )
)
set "PATH=%CLEANPATH%"

set "VSCMAKE=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
set "VSNINJA=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja"
set "PATH=%VSCMAKE%;%VSNINJA%;%PATH%"

echo === STEP 1: Build recompiler ===
cd /d F:\Projects\nesrecomp-release\SuperMarioBrosRecomp\nesrecomp
if not exist build_recomp (
    cmake -S recompiler -B build_recomp -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl
    if !ERRORLEVEL! NEQ 0 ( echo RECOMPILER CMAKE FAILED & exit /b 1 )
)
cmake --build build_recomp
if !ERRORLEVEL! NEQ 0 ( echo RECOMPILER BUILD FAILED & exit /b 1 )

echo === STEP 2: Regen game code (plain) ===
cd /d F:\Projects\nesrecomp-release\SuperMarioBrosRecomp
nesrecomp\build_recomp\NESRecomp.exe baserom.nes --game game.toml
if !ERRORLEVEL! NEQ 0 ( echo REGEN FAILED & exit /b 2 )

echo === STEP 3: Configure + build non-debug ===
if not exist build_release (
    cmake -S . -B build_release -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DENABLE_NESTOPIA_ORACLE=OFF -DNESRECOMP_REVERSE_DEBUG=OFF
    if !ERRORLEVEL! NEQ 0 ( echo CMAKE FAILED & exit /b 3 )
)
cmake --build build_release
if !ERRORLEVEL! NEQ 0 ( echo BUILD FAILED & exit /b 4 )

rem Release builds never ship debug.ini — strip if a stale copy exists.
if exist build_release\debug.ini del build_release\debug.ini

echo === RELEASE BUILD DONE: build_release\SuperMarioBrosRecomp.exe ===
