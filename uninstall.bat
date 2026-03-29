@echo off
REM Cross-platform uninstaller for The JLC Project (Windows version)
REM Follows suckless principles: simple, portable, no bloat

setlocal enabledelayedexpansion

REM Default installation directory
set "INSTALL_DIR=%USERPROFILE%\jlc"

REM Parse command line arguments
if "%1"=="-h" goto usage
if "%1"=="--help" goto usage
if not "%1"=="" set "INSTALL_DIR=%1"

echo Uninstalling The JLC Project from %INSTALL_DIR%...

REM Remove binaries
echo Removing binaries...
for %%b in (mat.exe jgrep.exe move.exe cpy.exe print.exe lf.exe perm.exe spec.exe srt.exe hn.exe chwn.exe brit.exe cnt.exe hd.exe tl.exe tch.exe mkd.exe del.exe lnk.exe cwd.exe env.exe nap.exe dt.exe wm.exe J.exe whoisdat.exe sim.exe short.exe duct.exe) do (
    if exist "%INSTALL_DIR%\%%b" del "%INSTALL_DIR%\%%b"
)

REM Remove man pages
echo Removing man pages...
for %%m in (man\man1\*.1) do (
    if exist "%INSTALL_DIR%\man\man1\%%~nxm" del "%INSTALL_DIR%\man\man1\%%~nxm"
)

echo.
echo Uninstallation complete!
echo.
echo Note: You may need to manually remove %INSTALL_DIR% if it's empty.
goto :eof

:usage
echo Usage: uninstall.bat [INSTALL_DIR]
echo Uninstall The JLC Project utilities
echo.
echo Arguments:
echo   INSTALL_DIR    Installation directory (default: %%USERPROFILE%%\jlc)
echo.
echo Examples:
echo   uninstall.bat                    # Uninstall from %%USERPROFILE%%\jlc
echo   uninstall.bat C:\tools\jlc       # Uninstall from C:\tools\jlc
exit /b 0