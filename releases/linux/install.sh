#!/usr/bin/env bash
set -e

# Karaoke DSP — Linux Installer
# ============================================

APP_NAME="Karaoke DSP"
VST3_NAME="Karaoke DSP.vst3"
DESKTOP_FILE="karaoke-dsp.desktop"

# Determina directory di installazione
INSTALL_PREFIX="${HOME}/.local"
VST3_DIR="${HOME}/.vst3"
BIN_DIR="${INSTALL_PREFIX}/bin"
SHARE_DIR="${INSTALL_PREFIX}/share/karaoke-dsp"
APPS_DIR="${INSTALL_PREFIX}/share/applications"
ICON_DIR="${INSTALL_PREFIX}/share/icons/hicolor/256x256/apps"

echo "=========================================="
echo "  ${APP_NAME} — Installer Linux"
echo "=========================================="
echo ""

# Verifica dipendenze
echo "[1/5] Verifica dipendenze..."
missing=()
command -v cmake >/dev/null 2>&1 || missing+=("cmake")
command -v g++ >/dev/null 2>&1 || missing+=("g++")
command -v pkg-config >/dev/null 2>&1 || missing+=("pkg-config")

if [ ${#missing[@]} -ne 0 ]; then
    echo "ERROR: Dipendenze mancanti: ${missing[*]}"
    echo "Installale con:"
    echo "  Fedora:  sudo dnf install cmake gcc-c++ pkgconfig alsa-lib-devel pulseaudio-libs-devel"
    echo "  Ubuntu:  sudo apt install cmake build-essential libasound2-dev libpulse-dev"
    exit 1
fi

# Verifica che i file esistano
if [ ! -d "Source" ] || [ ! -f "CMakeLists.txt" ]; then
    echo "ERROR: File sorgente non trovati."
    echo "Esegui questo script dalla root del repository KaraokeDSP."
    exit 1
fi

echo "[2/5] Compilazione in corso..."
mkdir -p Build
cd Build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --target KaraokeDSPApp --target KaraokeDSP_VST3 -j$(nproc)

echo ""
echo "[3/5] Installazione applicazione..."
mkdir -p "${BIN_DIR}"
mkdir -p "${SHARE_DIR}"
mkdir -p "${VST3_DIR}"
mkdir -p "${APPS_DIR}"

# Copia eseguibile standalone
if [ -f "Karaoke DSP Console" ]; then
    cp "Karaoke DSP Console" "${BIN_DIR}/karaoke-dsp"
    chmod +x "${BIN_DIR}/karaoke-dsp"
    echo "  -> Applicazione installata in ${BIN_DIR}/karaoke-dsp"
fi

# Copia plugin VST3
if [ -d "VST3/VST3/${VST3_NAME}" ]; then
    rm -rf "${VST3_DIR}/${VST3_NAME}"
    cp -r "VST3/VST3/${VST3_NAME}" "${VST3_DIR}/"
    echo "  -> Plugin VST3 installato in ${VST3_DIR}/${VST3_NAME}"
fi

echo ""
echo "[4/5] Creazione launcher desktop..."
mkdir -p "${ICON_DIR}"

# Icona placeholder (testo)
if command -v convert >/dev/null 2>&1; then
    convert -size 256x256 xc:"#1a1a2e" -pointsize 24 -fill "#e94560" \
        -gravity center -annotate +0+0 "K DSP" "${ICON_DIR}/karaoke-dsp.png" 2>/dev/null || true
fi

cat > "${APPS_DIR}/${DESKTOP_FILE}" <<EOF
[Desktop Entry]
Name=Karaoke DSP
Comment=Audio DSP Console per elaborazione vocale
Exec=${BIN_DIR}/karaoke-dsp
Icon=karaoke-dsp
Type=Application
Terminal=false
Categories=AudioVideo;Audio;
EOF

chmod +x "${APPS_DIR}/${DESKTOP_FILE}"
echo "  -> Launcher creato"

echo ""
echo "[5/5] Aggiornamento database desktop..."
if command -v update-desktop-database >/dev/null 2>&1; then
    update-desktop-database "${APPS_DIR}" 2>/dev/null || true
fi

echo ""
echo "=========================================="
echo "  Installazione completata!"
echo "=========================================="
echo ""
echo "Avvia l'applicazione:"
echo "  karaoke-dsp"
echo ""
echo "Oppure cerca 'Karaoke DSP' nel menu applicazioni."
echo ""
echo "Il plugin VST3 e' in: ${VST3_DIR}/${VST3_NAME}"
echo ""
