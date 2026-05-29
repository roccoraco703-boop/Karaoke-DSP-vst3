#!/bin/bash

echo ""
echo "=== CONTROLLO FILE MANCANTI NEL CMakeLists ==="
echo ""

CMAKE="CMakeLists.txt"

if [ ! -f "$CMAKE" ]; then
    echo "❌ ERRORE: CMakeLists.txt non trovato!"
    exit 1
fi

echo "📄 Analizzo CMakeLists.txt..."
echo ""

# Estrae i file elencati in SHARED_SOURCES
LIST=$(grep -oP '(?<=\$\{SRC_ROOT\}/)[A-Za-z0-9_\/\.]+' "$CMAKE")

MISSING=()
EXISTING=()

echo "🔍 Controllo file elencati nel CMakeLists:"
echo ""

while IFS= read -r file; do
    FULL="Source/$file"
    if [ -f "$FULL" ]; then
        echo "✔ OK: $FULL"
        EXISTING+=("$FULL")
    else
        echo "❌ MANCANTE: $FULL"
        MISSING+=("$FULL")
    fi
done <<< "$LIST"

echo ""
echo "=============================================="
echo "📌 RISULTATO"
echo "=============================================="
echo ""

if [ ${#MISSING[@]} -eq 0 ]; then
    echo "🎉 Nessun file mancante! Il CMakeLists è corretto."
else
    echo "⚠ File mancanti nel progetto:"
    for f in "${MISSING[@]}"; do
        echo "   → $f"
    done
fi

echo ""
echo "=============================================="
echo "📌 FILE PRESENTI MA NON INCLUSI NEL CMakeLists"
echo "=============================================="
echo ""

# Trova tutti i file reali
REAL=$(find Source -type f | sed 's|^Source/||')

for f in $REAL; do
    if ! grep -q "$f" <<< "$LIST"; then
        echo "   → $f"
    fi
done

echo ""
echo "✔ Controllo completato!"
