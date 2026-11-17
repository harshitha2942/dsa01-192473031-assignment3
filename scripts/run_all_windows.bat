@echo off
setlocal
for %%T in (Task01 Task02 Task03 Task04 Task05 Task06 Task07) do (
  echo ===== %%T =====
  g++ -std=c++17 -Wall -Wextra -pedantic %%T\main.cpp -o %%T\program.exe
  if errorlevel 1 exit /b 1
  %%T\program.exe
)
