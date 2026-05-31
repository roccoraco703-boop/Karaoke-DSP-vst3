#!/usr/bin/env bash
# Script upload Karaoke DSP website su Altervista
# ================================================

# SOSTITUISCI QUESTI VALORI CON I TUOI DATI REALI:
FTP_USER="TUO_USERNAME"
FTP_PASS="TUO_PASSWORD"
FTP_HOST="ftp.tuo-sito.altervista.org"

LOCAL_DIR="/home/rocco703/Scrivania/KaraokeDSP/releases/website"

echo "Upload in corso..."

lftp -u "$FTP_USER","$FTP_PASS" "$FTP_HOST" <<EOF
set ssl:verify-certificate no
set ftp:ssl-allow yes

# Upload pagina principale (renamed per Altervista)
put "$LOCAL_DIR/index_altervista.html" -o /public_html/index.html

# Upload cartella linux
mkdir -p /public_html/linux/
put "$LOCAL_DIR/linux/install.sh" -o /public_html/linux/install.sh
put "$LOCAL_DIR/../linux/README.md" -o /public_html/linux/README.md
put "$LOCAL_DIR/../linux/INSTALL.txt" -o /public_html/linux/INSTALL.txt

# Upload cartella windows
mkdir -p /public_html/windows/
put "$LOCAL_DIR/windows/install.ps1" -o /public_html/windows/install.ps1
put "$LOCAL_DIR/../windows/README.md" -o /public_html/windows/README.md
put "$LOCAL_DIR/../windows/INSTALL.txt" -o /public_html/windows/INSTALL.txt

bye
EOF

echo "Upload completato!"
echo "Visita: http://tuo-sito.altervista.org/"
