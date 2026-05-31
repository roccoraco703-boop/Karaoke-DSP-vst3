# Karaoke DSP

Applicazione audio e plugin VST3 per elaborazione vocale in tempo reale. Include effetti DSP (pitch shifting, delay, reverb, EQ, mixer) con interfaccia UI dark/metallica.

---

## Caratteristiche

- **App Standalone** (`Karaoke DSP Console`) — eseguibile JUCE con interfaccia completa
- **Plugin VST3** (`Karaoke DSP.vst3`) — caricabile in qualsiasi DAW
- **Effetti DSP reali:**
  - Pitch Shifting (±12 semitoni)
  - Delay (0–1 secondo)
  - Reverb (wet level)
  - Equalizzatore 4 bande
  - Mixer con gain, pan, mute, solo
  - Master gain (0–2x)
  - Pitch Detection (tuner)
- **Bypass** — disattiva tutti gli effetti, pass-through audio
- **Monitor** — selezione del dispositivo di input dal dropdown
- **VU Meters analogici** — livelli audio reali, non demo
- **Tema dark metallico** — LookAndFeel custom

---

## Requisiti

- **OS:** Linux (Fedora 44+ testato), Windows, macOS
- **CMake:** >= 3.22
- **Compilatore:** GCC/Clang con supporto C++20
- **Librerie:**
  - `libasound2-dev` (ALSA)
  - `libpulse-dev` (PulseAudio)
  - `libjack-jackd2-dev` (JACK, opzionale)
- **Backend audio su Linux:** PipeWire (consigliato) o PulseAudio

---

## Compilazione

```bash
# Clona il repository
git clone https://github.com/roccoraco703-boop/Karaoke-DSP-vst3.git
cd Karaoke-DSP-vst3

# Crea cartella build
mkdir Build && cd Build

# Genera Makefile con CMake
cmake ..

# Compila app standalone e plugin VST3
cmake --build . -j$(nproc)
```

### Target

- `KaraokeDSPApp` — applicazione standalone
- `KaraokeDSP_VST3` — plugin VST3

---

## App Standalone

### Avvio

```bash
cd Build
./Karaoke\ DSP\ Console
```

### Controlli UI

| Controllo | Funzione |
|-----------|----------|
| **PITCH** | Trasposizione in semitoni |
| **DELAY** | Tempo di ritardo |
| **REVERB** | Livello riverbero |
| **MASTER** | Gain master |
| **EQ (LOW/MID/HIGH/PRES)** | Equalizzatore 4 bande |
| **VOLUME / PAN** | Gain e panning canali |
| **MUTE / SOLO** | Silenzia / isola canale |
| **BYPASS** | Disattiva tutti gli effetti |
| **MONITOR** | Cambia dispositivo di input dal dropdown |
| **Input Selector** | Selezione manuale del dispositivo audio di input |

### Audio di sistema (YouTube, Browser, Bluetooth)

L'app standalone su Linux usa il backend **PulseAudio** (attivato nel `CMakeLists.txt`). Per catturare l'audio di sistema (es. YouTube) è necessario un **host DAW** o il routing con PipeWire.

#### Metodo 1 — Carla (consigliato)

1. Installa Carla:
   ```bash
   sudo dnf install carla
   ```
2. Avvia Carla e aggiungi il plugin VST3:
   ```bash
   carla
   ```
3. Clicca **+ Add Plugin** → cerca **Karaoke DSP** → doppio click
4. Nel **Patchbay**, collega:
   - `Firefox` → `Karaoke DSP` input
   - `Karaoke DSP` output → `Audio interno` playback

#### Metodo 2 — helvum (routing PipeWire)

1. Installa helvum:
   ```bash
   sudo dnf install helvum
   ```
2. Avvia:
   ```bash
   helvum
   ```
3. Trascina il cavo dall'output di Firefox all'input dell'app KaraokeDSP (o del dispositivo ALSA associato)

#### Metodo 3 — Audio Bluetooth

1. Accoppia il dispositivo Bluetooth (microfono, casse, cuffie)
2. In Carla/helvum apparirà un nodo tipo `bluez_input...`
3. Instrada il nodo Bluetooth → `Karaoke DSP` → altoparlanti

---

## Plugin VST3

### Installazione

Copia la cartella del plugin nella cartella VST3 standard:

```bash
mkdir -p ~/.vst3
cp -r Build/VST3/VST3/Karaoke\ DSP.vst3 ~/.vst3/
```

### DAW supportati

- **Ardour** — `Session > Plugin Manager`
- **Reaper** — `Insert > Virtual instrument on new track`
- **Bitwig Studio** — `Device Panel > + > VST3`
- **Carla** — `+ Add Plugin > VST3 > Karaoke DSP`
- **Cualunque DAW con supporto VST3**

### Note

- Il plugin **non** gestisce dispositivi audio — riceve solo il segnale dal DAW
- Il routing audio (microfono, YouTube, Bluetooth) è gestito dal DAW e dal sistema operativo

---

## Struttura del progetto

```
KaraokeDSP/
├── CMakeLists.txt          # Configurazione CMake
├── README.md               # Questo file
├── Source/
│   ├── Main.cpp            # Entry point app standalone
│   ├── PluginProcessor.cpp # Wrapper VST3
│   ├── UI/                 # Componenti GUI
│   │   ├── MainComponent.{h,cpp}
│   │   ├── ChannelStrip.{h,cpp}
│   │   ├── EqualizerSection.{h,cpp}
│   │   ├── AnalogVuMeter.{h,cpp}
│   │   ├── DigitalDisplay.{h,cpp}
│   │   ├── Knob.{h,cpp}
│   │   ├── LookAndFeelStudio.h
│   │   └── ...
│   └── DSP/                # Elaborazione audio
│       ├── DSPChain.{h,cpp}
│       ├── PitchShifter.{h,cpp}
│       ├── Delay.{h,cpp}
│       ├── Reverb.{h,cpp}
│       ├── Mixer.{h,cpp}
│       └── PitchDetection.{h,cpp}
├── Build/                  # Artefatti di build (gitignored)
└── JUCE/                   # Framework JUCE (submodule)
```

---

## Risoluzione problemi

### `Audio device error: No such file or directory`

JUCE su Linux usa ALSA come default, ma i dispositivi PipeWire virtuali non sono apribili da ALSA. La soluzione è compilare con **PulseAudio** attivato:

```cmake
# CMakeLists.txt — sezione Linux
target_compile_definitions(KaraokeDSPApp PRIVATE JUCE_ALSA=1 JUCE_JACK=1 JUCE_PULSEAUDIO=1)
```

Poi ricompila:
```bash
cd Build
cmake .. && cmake --build . -j$(nproc)
```

### Carla crasha con `bufferSize` mismatch

Carla con backend JACK può crashare se il buffer size non coincide. Avvia Carla con PulseAudio:
```bash
carla --audio-pulse
```

### Il plugin non compare nel DAW

- Verifica che il plugin sia in `~/.vst3/` o `/usr/lib/vst3/`
- Riavvia il DAW dopo aver copiato il plugin
- Nel DAW, esegui una **rescan** dei plugin VST3

---

## Licenza

Progetto personale di Rocco Audio.

---

## GitHub

https://github.com/roccoraco703-boop/Karaoke-DSP-vst3
