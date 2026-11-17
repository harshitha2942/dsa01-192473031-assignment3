#!/usr/bin/env bash
set -e
for task in Task01 Task02 Task03 Task04 Task05 Task06 Task07; do
  echo "===== $task ====="
  g++ -std=c++17 -Wall -Wextra -pedantic "$task/main.cpp" -o "$task/program"
  "./$task/program"
done
