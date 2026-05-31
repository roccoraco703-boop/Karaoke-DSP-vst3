# Karaoke DSP — Linux Release

Applicazione standalone e plugin VST3 per elaborazione audio vocale in tempo reale.

---

## Contenuto della release

| File | Descrizione |
|------|-------------|
| `install.sh` | Script di installazione automatico |
| `INSTALL.txt` | Istruzioni di installazione manuale |
| `README.md` | Questo file |

---

## Installazione rapida (automatica)

1. Apri un terminale nella cartella del repository
2. Esegui:
   ```bash
   bash releases/linux/install.sh
   ```
3. Lo script compila e installa automaticamente applicazione e plugin

---

## Requisiti minimi

- **OS:** Linux 64-bit (Fedora 38+, Ubuntu 22.04+, Arch)
- **CPU:** x86_64 con supporto SSE2
- **RAM:** 4 GB consigliati
- **Audio:** PipeWire o PulseAudio
- **Librerie:**
  - `cmake` >= 3.22
  - `gcc/g++` con C++20
  - `alsa-lib-devel`
  - `pulseaudio-libs-devel`

### Installazione dipendenze

**Fedora:**
```bash
sudo dnf install cmake gcc-c++ pkgconfig alsa-lib-devel pulseaudio-libs-devel
```

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install cmake build-essential libasound2-dev libpulse-dev
```

**Arch:**
```bash
sudo pacman -S cmake base-devel alsa-lib libpulse
```

---

## Installazione manuale

Se preferisci compilare manualmente:

```bash
mkdir Build && cd Build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target KaraokeDSPApp --target KaraokeDSP_VST3 -j$(nproc)
```

### Installa l'applicazione

```bash
# Copia eseguibile
cp "Build/Karaoke DSP Console" ~/.local/bin/karaoke-dsp
chmod +x ~/.local/bin/karaoke-dsp

# Copia plugin VST3
mkdir -p ~/.vst3
cp -r "Build/VST3/VST3/Karaoke DSP.vst3" ~/.vst3/
```

---

## Avvio

**Applicazione standalone:**
```bash
karaoke-dsp
```

**Plugin VST3:**
Apri qualsiasi DAW (Ardour, Reaper, Bitwig, Carla) e carica il plugin dalla cartella `~/.vst3/`.

---

## Routing audio di sistema (YouTube, Browser, Bluetooth)

Per catturare l'audio di sistema (es. YouTube) usa uno di questi metodi:

### Metodo 1 — Carla (consigliato)

```bash
sudo dnf install carla    # Fedora
sudo apt install carla    # Ubuntu
```

1. Avvia Carla: `carla`
2. Clicca **+ Add Plugin** → cerca **Karaoke DSP**
3. Nel **Patchbay**, collega `Firefox` → `Karaoke DSP` → `Audio interno`

### Metodo 2 — helvum

```bash
sudo dnf install helvum    # Fedora
sudo apt install helvum    # Ubuntu (repo universe)
```

1. Avvia `helvum`
2. Trascina il cavo da `Firefox` all'input del plugin

### Metodo 3 — Audio Bluetooth

1. Accoppia il dispositivo Bluetooth
2. In Carla/helvum apparirà un nodo `bluez_input...`
3. Instrada il nodo Bluetooth → `Karaoke DSP` → altoparlanti

---

## Disinstallazione

```bash
rm ~/.local/bin/karaoke-dsp
rm -rf ~/.vst3/Karaoke\ DSP.vst3
rm ~/.local/share/applications/karaoke-dsp.desktop
```

---

## Supporto

GitHub: https://github.com/roccoraco703-boop/Karaoke-DSP-vst3

---

**Versione:** 1.0.0 | **Piattaforma:** Linux x86_64 | **Licenza:** Rocco Audio
