#!/bin/bash

APP="KaraokeDSP"
BUILD_DIR="Build"

echo -e "\n\033[1;36m==> Pulizia cartella Build/\033[0m"
rm -rf $BUILD_DIR
mkdir $BUILD_DIR

echo -e "\n\033[1;36m==> Configurazione CMake (Release)\033[0m"
cmake -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo -e "\033[1;31mERRORE: configurazione CMake fallita.\033[0m"
    exit 1
fi

echo -e "\n\033[1;36m==> Compilazione con Ninja\033[0m"
cmake --build $BUILD_DIR --config Release

if [ $? -ne 0 ]; then
    echo -e "\033[1;31mERRORE: compilazione fallita.\033[0m"
    exit 1
fi

echo -e "\n\033[1;32m==> Compilazione completata con successo!\033[0m"

echo -e "\n\033[1;33m==> File generati:\033[0m"
echo " - Standalone: $BUILD_DIR/${APP}App"
echo " - Plugin VST3: $BUILD_DIR/VST3/${APP}_VST3.vst3"

echo -e "\n\033[1;32mPuoi avviare l'app con:\033[0m"
echo "./$BUILD_DIR/${APP}App"

echo -e "\n\033[1;32mPuoi installare il VST3 con:\033[0m"
echo "./install_vst3.sh"
