:: Required VSCode plugins:
:: C/C++
:: CMake Tools
:: Clang-Format

@echo off
setlocal

:: Options.
set GetLabels_ROOT=%~dp0/..

:: Set MSBuild environment variables.
set VSWHERE="%ProgramFiles(x86)%/Microsoft Visual Studio/Installer/vswhere.exe"
set VSWHEREOPT=-version ^^^[16.0^^^,17.0^^^) -requires Microsoft.Component.MSBuild -property installationPath
for /f "usebackq tokens=*" %%i in (`%VSWHERE% %VSWHEREOPT%`) do (
  if exist "%%i" set VS2019INSTALLDIR=%%i
)

:: Setup developer command prompt for Visual Studio.
call "%VS2019INSTALLDIR%/Common7/Tools/VsDevCmd.bat" -arch=x64

call code "%GetLabels_ROOT%"

:eof
  endlocal
  ::pause
exit /b %ERRORLEVEL%
