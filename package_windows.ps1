Write-Host "Packaging Windows build outputs..."
$root = Split-Path -Parent $MyInvocation.MyCommand.Definition
$buildDir = Join-Path $root 'Build\win-msvc-release'
if (-not (Test-Path $buildDir)) {
  Write-Error "Build directory not found: $buildDir"
  exit 1
}
$outDir = Join-Path $root 'artifacts'
if (-not (Test-Path $outDir)) { New-Item -ItemType Directory -Path $outDir | Out-Null }
$zipPath = Join-Path $outDir 'KaraokeDSP-win.zip'
if (Test-Path $zipPath) { Remove-Item $zipPath -Force }
Write-Host "Compressing $buildDir -> $zipPath"
Compress-Archive -Path (Join-Path $buildDir '*') -DestinationPath $zipPath -Force
Write-Host "Package created: $zipPath"
