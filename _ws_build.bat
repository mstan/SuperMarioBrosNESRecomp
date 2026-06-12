@echo off
setlocal enabledelayedexpansion

rem _ws_build.bat [debug|release|regen-only] — widescreen worktree build.
rem   debug   : regen --reverse-debug, build_debug\ (oracle ON, RDB ON)
rem   release : plain regen, build_release\ (oracle OFF, RDB OFF)
rem   regen-only : plain regen, no compile (for gen diffing)

set "MODE=%~1"
if "%MODE%"=="" set "MODE=debug"

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
cd /d F:\Projects\nesrecomp\_ws\SuperMarioBrosRecomp\nesrecomp
if not exist build_recomp (
    cmake -S recompiler -B build_recomp -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl
    if !ERRORLEVEL! NEQ 0 ( echo RECOMPILER CMAKE FAILED & exit /b 1 )
)
cmake --build build_recomp
if !ERRORLEVEL! NEQ 0 ( echo RECOMPILER BUILD FAILED & exit /b 1 )

cd /d F:\Projects\nesrecomp\_ws\SuperMarioBrosRecomp

if "%MODE%"=="release" (
    echo === STEP 2: Regen game code [plain] ===
    nesrecomp\build_recomp\NESRecomp.exe baserom.nes --game game.toml
    if !ERRORLEVEL! NEQ 0 ( echo REGEN FAILED & exit /b 2 )
    echo === STEP 3: Configure + build release ===
    if not exist build_release (
        cmake -S . -B build_release -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DENABLE_NESTOPIA_ORACLE=OFF -DNESRECOMP_REVERSE_DEBUG=OFF
        if !ERRORLEVEL! NEQ 0 ( echo CMAKE FAILED & exit /b 3 )
    )
    cmake --build build_release
    if !ERRORLEVEL! NEQ 0 ( echo BUILD FAILED & exit /b 4 )
    echo === DONE: build_release\SuperMarioBrosRecomp.exe ===
) else if "%MODE%"=="regen-only" (
    echo === STEP 2: Regen game code [plain] ===
    nesrecomp\build_recomp\NESRecomp.exe baserom.nes --game game.toml
    if !ERRORLEVEL! NEQ 0 ( echo REGEN FAILED & exit /b 2 )
    echo === DONE: regen only ===
) else (
    echo === STEP 2: Regen game code [--reverse-debug] ===
    nesrecomp\build_recomp\NESRecomp.exe baserom.nes --game game.toml --reverse-debug
    if !ERRORLEVEL! NEQ 0 ( echo REGEN FAILED & exit /b 2 )
    echo === STEP 3: Configure + build debug ===
    if not exist build_debug (
        cmake -S . -B build_debug -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DENABLE_NESTOPIA_ORACLE=ON -DNESRECOMP_REVERSE_DEBUG=ON
        if !ERRORLEVEL! NEQ 0 ( echo CMAKE FAILED & exit /b 3 )
    )
    cmake --build build_debug
    if !ERRORLEVEL! NEQ 0 ( echo BUILD FAILED & exit /b 4 )
    echo === DONE: build_debug\SuperMarioBrosRecomp.exe ===
)
