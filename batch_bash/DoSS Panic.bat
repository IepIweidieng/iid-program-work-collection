@echo off
setlocal EnableExtensions

:main  ::(str[])->(int)
    if "%1" NEQ "" ( call :doScriptPanic & exit /b 0 )
    start "" "%~s0" SP
    >NUL 2>&1 (
        taskkill /f /fi "imagename eq cmd.exe"
        taskkill /f /fi "imagename eq conhost.exe"
    )
    exit /b 0

:doScriptPanic  ::(void)->(void)
    set script="%temp%\%random%.vbs"
    >%script% (
      echo:Set UAC=CreateObject^("Shell.Application"^)
    )
    for /l %%a in (1,1,4) do >>%script% (
      echo:UAC.ShellExecute "%windir%\System32\taskkill.exe","/f /fi ""imagename eq cmd.exe""","","",0
      echo:UAC.ShellExecute "%windir%\System32\taskkill.exe","/f /fi ""imagename eq conhost.exe""","","",0
    )

    for /l %%a in (1,1,4) do (
      call %script%
    )
    del /f /q %script%

    goto :eof