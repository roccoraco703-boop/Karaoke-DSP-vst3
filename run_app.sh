#!/bin/bash

APP="./Build/Karaoke DSP Console"

if [ ! -f "$APP" ]; then
    echo "Errore: applicazione non trovata!"
    exit 1
fi

echo "Avvio Karaoke DSP Console..."
"$APP"

git add . && git commit -m "Add Windows CI packaging/NSIS installer and icon" && git push origin HEAD
