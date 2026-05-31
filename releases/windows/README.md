# Karaoke DSP — Windows Release

Applicazione standalone e plugin VST3 per elaborazione audio vocale in tempo reale.

---

## Contenuto della release

| File | Descrizione |
|------|-------------|
| `KaraokeDSP-Setup.exe` | Installer automatico con wizard (consigliato) |
| `install.ps1` | Script PowerShell che copia i file già compilati |
| `installer.nsi` | Script NSIS per compilare l'installer .exe (vedi "Compilare l'installer" sotto) |
| `INSTALL.txt` | Istruzioni di installazione manuale |
| `README.md` | Questo file |
| `payload/` | Cartella con eseguibile e plugin VST3 |

---

## Installazione rapida (Installer .exe)

`KaraokeDSP-Setup.exe` è un installer standalone con wizard grafico — doppio click e segui le istruzioni.

> **Nota:** `KaraokeDSP-Setup.exe` **non** si crea con `install.ps1`. Sono due strumenti diversi.

1. Esegui `KaraokeDSP-Setup.exe`
2. Segui la procedura guidata
3. L'installer copia l'applicazione, il plugin VST3 e crea i collegamenti

---

## Installazione con PowerShell (install.ps1)

`install.ps1` copia i file già compilati (presenti nella cartella `payload/`) nella posizione corretta del sistema — è un'alternativa all'installer .exe.

1. Apri **PowerShell** come Amministratore
2. Vai nella cartella della release
3. Esegui:
   ```powershell
   powershell -ExecutionPolicy Bypass -File install.ps1
   ```

**Nota:** `install.ps1` richiede che i file compilati siano presenti nella cartella `payload/`. Non compila il codice sorgente.

---

## Requisiti minimi

- **OS:** Windows 10/11 64-bit
- **CPU:** x86_64 con supporto SSE2
- **RAM:** 4 GB consigliati
- **Audio:** WASAPI o ASIO (consigliato per latenza bassa)
- **Redist:** Visual C++ Redistributable 2019+ (solitamente già presente)

---

## Installazione manuale

Se preferisci copiare i file manualmente:

1. Estrai il contenuto di `payload/`
2. Copia `Karaoke DSP Console.exe` in una cartella a scelta
3. Copia la cartella `Karaoke DSP.vst3` in:
   ```
   %LOCALAPPDATA%\VST3\
   ```
   (es. `C:\Users\TUO_NOME\AppData\Local\VST3\`)
4. Crea un collegamento sul Desktop se desiderato

---

## Avvio

**Applicazione standalone:**
- Doppio click su `KaraokeDSP.exe` o usa il collegamento sul Desktop

**Plugin VST3:**
- Apri il tuo DAW preferito
- Cerca `Karaoke DSP` nella lista plugin VST3
- Caricalo su una traccia audio

---

## DAW supportati

Il plugin VST3 è compatibile con tutti i principali DAW:

- **FL Studio** — `Channel Rack > + > More plugins`
- **Ableton Live** — `Audio Effects > VST3`
- **Reaper** — `FX > VST3`
- **Cubase** — `Studio > More Instruments/Effects`
- **Studio One** — `Browser > Effects > VST3`
- **Cakewalk** — `FX > VST3`
- **Bitwig Studio** — `Device Panel > + > VST3`

---

## Routing audio di sistema (YouTube, Browser, etc.)

Su Windows per catturare l'audio di sistema (YouTube, Spotify, etc.) esistono diverse opzioni:

### Metodo 1 — Virtual Audio Cable (VB-Cable)

1. Installa **VB-Cable** (gratuito): https://vb-audio.com/Cable/
2. In Windows, imposta l'output predefinito su `CABLE Input`
3. Nel DAW, seleziona `CABLE Output` come input della traccia
4. Carica il plugin `Karaoke DSP` sul canale

### Metodo 2 — VoiceMeeter (più avanzato)

1. Installa **VoiceMeeter Banana** (gratuito): https://vb-audio.com/Voicemeeter/
2. Configura il routing virtuale
3. Instrada l'audio di sistema → VoiceMeeter → DAW con Karaoke DSP

### Metodo 3 — Loopback scheda audio (ASIO)

Alcune schede audio professionali supportano il loopback hardware:
- Apri il pannello di controllo della scheda audio
- Attiva `Loopback` o `Stereo Mix`
- Nel DAW, seleziona quel canale come input

---

## Compilare l'installer .exe (da sviluppatore)

Per creare `KaraokeDSP-Setup.exe` partendo da zero:

1. **Su Windows**, installa **NSIS**: https://nsis.sourceforge.io/
2. Compila il progetto in modalità Release (usa Visual Studio o CMake)
3. Esegui:
   ```powershell
   cd /percorso/del/repository
   & "C:\Program Files (x86)\NSIS\makensis.exe" /DOUTFILE="KaraokeDSP-Setup.exe" /DBUILD_DIR="Build\win-msvc-release" installer.nsi
   ```

Oppure usa lo script `package_nsis.ps1` (richiede PowerShell + NSIS):
```powershell
.\package_nsis.ps1
```

> **Attenzione:** La compilazione dell'installer .exe è possibile **solo su Windows** (richiede `makensis`).

---

## Disinstallazione

**Metodo 1 (Installer .exe):**
- Vai in `Impostazioni > App > Karaoke DSP > Disinstalla`

**Metodo 2 (Script PowerShell / Manuale):**
- Elimina la cartella `%LOCALAPPDATA%\Programs\KaraokeDSP`
- Elimina `%LOCALAPPDATA%\VST3\Karaoke DSP.vst3`
- Elimina i collegamenti Desktop/Start Menu

---

## Supporto

GitHub: https://github.com/roccoraco703-boop/Karaoke-DSP-vst3

---

**Versione:** 1.0.0 | **Piattaforma:** Windows 10/11 x64 | **Licenza:** Rocco Audio
