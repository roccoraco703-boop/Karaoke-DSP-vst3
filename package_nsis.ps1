Write-Host "Packaging NSIS installer..."
$root = Split-Path -Parent $MyInvocation.MyCommand.Definition
$buildDir = Join-Path $root 'Build\win-msvc-release'
if (-not (Test-Path $buildDir)) {
  Write-Error "Build directory not found: $buildDir"
  exit 1
}
$outDir = Join-Path $root 'artifacts'
if (-not (Test-Path $outDir)) { New-Item -ItemType Directory -Path $outDir | Out-Null }

$exeName = 'KaraokeDSP-Setup.exe'
$exePath = Join-Path $outDir $exeName

if (-not (Get-Command makensis -ErrorAction SilentlyContinue)) {
  Write-Error "makensis (NSIS) not found in PATH. Install NSIS (choco install nsis)"
  exit 1
}


Write-Host "Running makensis to create installer..."
# Pass definitions so installer.nsi can reference them
$quotedBuild = $buildDir -replace "\\", "\\\\"

# Prepare optional defines for ICON and EULA if present in repo root
$defines = @("-DBUILD_DIR=\"$quotedBuild\"", "-DOUTFILE=\"$exePath\"")
$iconPath = Join-Path $root 'installer_icon.ico'
# If an ICO isn't present but a PNG is, try to convert it to ICO using ImageMagick
$pngPath = Join-Path $root 'installer_icon.png'
$icoPath = $iconPath
if (-not (Test-Path $icoPath) -and (Test-Path $pngPath)) {
  Write-Host "Found installer_icon.png; attempting to convert to installer_icon.ico using ImageMagick..."
  if (Get-Command magick -ErrorAction SilentlyContinue) {
    & magick convert "$pngPath" -define icon:auto-resize=256,128,64,48,32,16 "$icoPath"
    if (Test-Path $icoPath) { Write-Host "Converted PNG -> ICO: $icoPath" }
    else { Write-Warning "Conversion failed; installer_icon.ico not created." }
  } elseif (Get-Command convert -ErrorAction SilentlyContinue) {
    & convert "$pngPath" -define icon:auto-resize=256,128,64,48,32,16 "$icoPath"
    if (Test-Path $icoPath) { Write-Host "Converted PNG -> ICO: $icoPath" }
    else { Write-Warning "Conversion failed; installer_icon.ico not created." }
  } else {
    Write-Host "ImageMagick not found. To convert PNG to ICO locally install ImageMagick or provide installer_icon.ico manually."
  }
}

if (Test-Path $icoPath) {
  $quotedIcon = $icoPath -replace "\\", "\\\\"
  $defines += "-DICON=\"$quotedIcon\""
  Write-Host "Using installer icon: $icoPath"
}
$eulaPath = Join-Path $root 'EULA.txt'
if (Test-Path $eulaPath) {
  $quotedEula = $eulaPath -replace "\\", "\\\\"
  $defines += "-DEULA=\"$quotedEula\""
  Write-Host "Using EULA file: $eulaPath"
}

& makensis @defines (Join-Path $root 'installer.nsi')

if ($LASTEXITCODE -ne 0) { Write-Error "makensis failed with exit code $LASTEXITCODE"; exit $LASTEXITCODE }

Write-Host "NSIS installer created: $exePath"
