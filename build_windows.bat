@echo off
REM Build script for Windows using CMake presets (Visual Studio 2022 x64)
cmake --version || (
  echo CMake not found. Install Visual Studio and CMake.
  exit /b 1
)
cmake --preset win-msvc-release
if errorlevel 1 exit /b %errorlevel%
cmake --build --preset win-msvc-release --config Release
