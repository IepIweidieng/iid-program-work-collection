@echo off& >nul chcp 950& setlocal EnableExtensions
>"%~dp0Out.txt" (
  for /f "tokens=* usebackq" %%a in ("%~dp0In.txt") do (
    echo;         show_vs_and_fs^("%%a", %%a^),
  )
)