@echo off
setlocal enabledelayedexpansion

rem build_rdb.bat — Debug build with the reverse debugger + embedded
rem Nestopia oracle. Slow, bloated, has every observability hook.
rem
rem Produces: build_debug\SuperMarioBrosRecomp.exe  (~8.2 MiB)
rem Flags:    ENABLE_NESTOPIA_ORACLE=ON, NESRECOMP_REVERSE_DEBUG=ON
rem Regen:    NESRecomp.exe --reverse-debug (emits RDB_STORE8 /
rem           RDB_BLOCK_HOOK / rdb_on_call hooks in the generated C).
rem
rem Coexists with the non-debug build in build_release\ from
rem build_all.bat.  Switching between them does NOT require rebuilding
rem — just run the other .exe.
rem
rem See nesrecomp/REVERSE_DEBUGGER.md and TCP.md for the rdb_* /
rem emu_* command surface.

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

echo === STEP 2: Regen game code WITH --reverse-debug ===
cd /d F:\Projects\nesrecomp-release\SuperMarioBrosRecomp
nesrecomp\build_recomp\NESRecomp.exe baserom.nes --game game.toml --reverse-debug
if !ERRORLEVEL! NEQ 0 ( echo REGEN FAILED & exit /b 2 )

echo === STEP 3: Configure + build debug ===
if not exist build_debug (
    cmake -S . -B build_debug -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DENABLE_NESTOPIA_ORACLE=ON -DNESRECOMP_REVERSE_DEBUG=ON
    if !ERRORLEVEL! NEQ 0 ( echo CMAKE FAILED & exit /b 3 )
)
cmake --build build_debug
if !ERRORLEVEL! NEQ 0 ( echo BUILD FAILED & exit /b 4 )

rem debug.ini presence enables the TCP debug server (extras.c)
echo ; empty marker > build_debug\debug.ini

echo === DEBUG BUILD DONE: build_debug\SuperMarioBrosRecomp.exe ===
echo     TCP:  127.0.0.1:4370  (native + oracle)
echo     RDB:  regen emitted   rdb_on_call / RDB_BLOCK_HOOK / RDB_STORE8
echo     Oracle: requires --emulated at launch for emu_* commands
