@echo off
REM Cross-platform installer for The JLC Project (Windows version)
REM Follows suckless principles: simple, portable, no bloat

setlocal enabledelayedexpansion

REM Default installation directory
set "INSTALL_DIR=%USERPROFILE%\jlc"

REM Parse command line arguments
if "%1"=="-h" goto usage
if "%1"=="--help" goto usage
if not "%1"=="" set "INSTALL_DIR=%1"

echo Installing The JLC Project to %INSTALL_DIR%...

REM Compile all utilities using MinGW/MSYS2
echo Compiling utilities...
mingw32-make clean >nul 2>&1
if errorlevel 1 (
    echo WARNING: mingw32-make not found, trying make...
    make clean >nul 2>&1
)
mingw32-make >nul 2>&1
if errorlevel 1 (
    echo WARNING: make not found, trying direct compilation...

    REM Fallback compilation for Windows
    gcc -O3 -flto -DNDEBUG -Wall -Wextra mat.c -o mat.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra jgrep.c -o jgrep.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra move.c -o move.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra cpy.c -o cpy.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra print.c -o print.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra lf.c -o lf.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra perm.c -o perm.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra spec.c -o spec.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra srt.c -o srt.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra hn.c -o hn.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra chwn.c -o chwn.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra brit.c -o brit.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra cnt.c -o cnt.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra hd.c -o hd.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra tl.c -o tl.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra tch.c -o tch.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra mkd.c -o mkd.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra del.c -o del.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra lnk.c -o lnk.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra cwd.c -o cwd.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra env.c -o env.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra nap.c -o nap.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra dt.c -o dt.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra wm.c -o wm.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra J.c -o J.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra whoisdat.c -o whoisdat.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra sim.c -o sim.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra short.c -o short.exe
    gcc -O3 -flto -DNDEBUG -Wall -Wextra duct.c -o duct.exe
)

REM Create installation directory
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
if not exist "%INSTALL_DIR%\man" mkdir "%INSTALL_DIR%\man"
if not exist "%INSTALL_DIR%\man\man1" mkdir "%INSTALL_DIR%\man\man1"

REM Install binaries
echo Installing binaries...
copy *.exe "%INSTALL_DIR%" >nul 2>&1

REM Install man pages
echo Installing man pages...
copy man\man1\*.1 "%INSTALL_DIR%\man\man1" >nul 2>&1

echo.
echo Installation complete!
echo Binaries installed to: %INSTALL_DIR%
echo.
echo To use the utilities, add %INSTALL_DIR% to your PATH environment variable.
echo Or run them directly from the installation directory.
goto :eof

:usage
echo Usage: install.bat [INSTALL_DIR]
echo Install The JLC Project utilities
echo.
echo Arguments:
echo   INSTALL_DIR    Installation directory (default: %%USERPROFILE%%\jlc)
echo.
echo Examples:
echo   install.bat                    # Install to %%USERPROFILE%%\jlc
echo   install.bat C:\tools\jlc       # Install to C:\tools\jlc
exit /b 0