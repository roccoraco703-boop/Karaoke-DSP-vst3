Write-Host "Building on Windows with CMake presets..."
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
  Write-Error "CMake not found. Install Visual Studio and CMake."
  exit 1
}
cmake --preset win-msvc-release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
cmake --build --preset win-msvc-release --config Release
