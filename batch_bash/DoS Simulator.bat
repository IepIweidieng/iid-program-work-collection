@echo off
set LIMIT=10

:main  ::(str[])->(int)
    set n=%1
    set/a n = n + 1

    if %n% LSS %LIMIT% (
        %0 %n% | %0 %n%
    ) else if %n% EQU %LIMIT% (
        pause
    )

    exit/b 0