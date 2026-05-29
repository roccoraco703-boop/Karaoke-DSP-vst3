# Build on Windows 11

Prerequisiti:

- Visual Studio 2022 con workload "Desktop development with C++" installato
- CMake >= 3.19 (consigliato 3.24+)
- Git

Istruzioni rapide:

1. Apri "x64 Native Tools Command Prompt for VS 2022" oppure usa PowerShell/Terminal con VS environment.
2. Dalla cartella del progetto esegui:

```
cmake --preset win-msvc-release
cmake --build --preset win-msvc-release --config Release
```

Oppure usa lo script fornito:

Per CMD:

```
.\build_windows.bat
```

Per PowerShell:

```
.\build_windows.ps1
```

Nota: questa repository usa JUCE/CMake; alcuni moduli possono richiedere dipendenze aggiuntive. Se preferisci, posso aggiungere uno script di packaging (NSIS/ZIP) o estendere il workflow CI per generare artefatti.
Nota: questa repository usa JUCE/CMake; alcuni moduli possono richiedere dipendenze aggiuntive.

Installer NSIS:

1. Per creare un installer localmente installa NSIS (https://nsis.sourceforge.io/), poi esegui in PowerShell:

```
choco install nsis -y  # opzionale se usi Chocolatey
.\package_nsis.ps1
```

2. Lo script genererà `artifacts/KaraokeDSP-Setup.exe`.

Nel CI, il workflow Windows ora installa NSIS e carica l'.exe come artefatto.

Eseguire la build nel CI (GitHub Actions):

- Il workflow `windows-build.yml` si attiva su `push`, `pull_request` e ora anche manualmente dalla UI (`Run workflow`).
- Per eseguire manualmente senza push, vai su GitHub > Actions > "Build (Windows)" > "Run workflow" e avvialo.


Icona personalizzata:

- Per usare la tua icona, copia il file PNG nella root del progetto e chiamalo `installer_icon.png` (o fornisci direttamente `installer_icon.ico`).
- Lo script `package_nsis.ps1` proverà automaticamente a convertire `installer_icon.png` in `installer_icon.ico` usando ImageMagick (`magick`). Se non hai ImageMagick installato, puoi installarlo o fornire direttamente un `.ico`.

Esempio (da Linux):

```
cp /home/rocco703/Scaricati/karaoke.png ./installer_icon.png
```

Quindi esegui la creazione dell'installer come sopra.

