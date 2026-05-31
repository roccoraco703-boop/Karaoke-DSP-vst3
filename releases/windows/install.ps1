# Karaoke DSP — Windows Installer (PowerShell)
# ============================================
# Run as Administrator:  powershell -ExecutionPolicy Bypass -File install.ps1

$AppName     = "Karaoke DSP"
$Vst3Name    = "Karaoke DSP.vst3"
$InstallDir  = "$env:LOCALAPPDATA\Programs\KaraokeDSP"
$Vst3Dir     = "$env:LOCALAPPDATA\VST3"
$StartMenu   = "$env:APPDATA\Microsoft\Windows\Start Menu\Programs"
$Desktop     = [Environment]::GetFolderPath("Desktop")

function Write-Header($text) {
    Write-Host "==========================================" -ForegroundColor Cyan
    Write-Host "  $text" -ForegroundColor Cyan
    Write-Host "==========================================" -ForegroundColor Cyan
}

function Test-Admin {
    $currentPrincipal = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
    return $currentPrincipal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

Write-Header "Karaoke DSP Windows Installer"

# Check admin
if (-not (Test-Admin)) {
    Write-Warning "Administrator privileges recommended for system-wide VST3 registration."
    Write-Host "Continuing with user-local installation..." -ForegroundColor Yellow
}

# Check for installer payload
$PayloadDir = Join-Path $PSScriptRoot "payload"
if (-not (Test-Path $PayloadDir)) {
    Write-Error "Payload folder not found: $PayloadDir"
    Write-Host "Please ensure the installer archive was extracted completely."
    exit 1
}

# Create directories
Write-Host "`n[1/5] Creating directories..." -ForegroundColor Green
New-Item -ItemType Directory -Force -Path $InstallDir | Out-Null
New-Item -ItemType Directory -Force -Path $Vst3Dir | Out-Null

# Copy application files
Write-Host "[2/5] Installing application files..." -ForegroundColor Green
$ExeSource = Join-Path $PayloadDir "Karaoke DSP Console.exe"
if (Test-Path $ExeSource) {
    Copy-Item $ExeSource (Join-Path $InstallDir "KaraokeDSP.exe") -Force
    Write-Host "  -> Application installed"
} else {
    Write-Warning "Application executable not found in payload"
}

# Copy VST3 plugin
Write-Host "[3/5] Installing VST3 plugin..." -ForegroundColor Green
$Vst3Source = Join-Path $PayloadDir $Vst3Name
if (Test-Path $Vst3Source) {
    $Vst3Target = Join-Path $Vst3Dir $Vst3Name
    if (Test-Path $Vst3Target) {
        Remove-Item $Vst3Target -Recurse -Force
    }
    Copy-Item $Vst3Source $Vst3Dir -Recurse -Force
    Write-Host "  -> VST3 plugin installed to: $Vst3Dir"
} else {
    Write-Warning "VST3 plugin not found in payload"
}

# Create Start Menu shortcut
Write-Host "[4/5] Creating shortcuts..." -ForegroundColor Green
$WshShell = New-Object -ComObject WScript.Shell
$Shortcut = $WshShell.CreateShortcut("$StartMenu\$AppName.lnk")
$Shortcut.TargetPath = Join-Path $InstallDir "KaraokeDSP.exe"
$Shortcut.WorkingDirectory = $InstallDir
$Shortcut.IconLocation = Join-Path $InstallDir "KaraokeDSP.exe"
$Shortcut.Save()
Write-Host "  -> Start Menu shortcut created"

# Create Desktop shortcut
$Shortcut2 = $WshShell.CreateShortcut("$Desktop\$AppName.lnk")
$Shortcut2.TargetPath = Join-Path $InstallDir "KaraokeDSP.exe"
$Shortcut2.WorkingDirectory = $InstallDir
$Shortcut2.IconLocation = Join-Path $InstallDir "KaraokeDSP.exe"
$Shortcut2.Save()
Write-Host "  -> Desktop shortcut created"

# Register VST3 path in registry (for DAWs that scan registry)
Write-Host "[5/5] Registering VST3 path..." -ForegroundColor Green
$regPath = "HKCU:\Software\VST\VST3 Paths"
if (-not (Test-Path $regPath)) {
    New-Item -Path $regPath -Force | Out-Null
}
Set-ItemProperty -Path $regPath -Name "KaraokeDSP" -Value $Vst3Dir -Force
Write-Host "  -> VST3 path registered"

Write-Host "`n==========================================" -ForegroundColor Green
Write-Host "  Installation Complete!" -ForegroundColor Green
Write-Host "==========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Launch the app from the Start Menu or Desktop."
Write-Host "VST3 plugin location: $Vst3Dir\$Vst3Name"
Write-Host ""
Write-Host "Supported DAWs: FL Studio, Ableton Live, Reaper, Cubase, Studio One, etc."
Write-Host ""
