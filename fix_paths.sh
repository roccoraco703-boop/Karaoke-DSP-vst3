#!/bin/bash

echo ""
echo "=== FIX CARTELLE E FILE CORROTTI ==="
echo ""

# 1) Trova file e cartelle che iniziano con spazio
BROKEN=$(find . -depth -name " *")

if [ -z "$BROKEN" ]; then
    echo "✔ Nessun file o cartella corrotta trovata."
    exit 0
fi

echo "⚠ Trovati file/cartelle con spazi iniziali:"
echo "$BROKEN"
echo ""

# 2) Rinominazione automatica
echo "🔧 Correzione in corso..."
echo ""

while IFS= read -r item; do
    fixed="$(echo "$item" | sed 's|/ |/|')"
    echo "→ $item"
    echo "  diventa"
    echo "→ $fixed"
    mv "$item" "$fixed"
    echo ""
done <<< "$BROKEN"

echo "✔ Correzione completata!"
