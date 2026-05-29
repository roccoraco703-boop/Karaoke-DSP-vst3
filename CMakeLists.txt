cmake_minimum_required(VERSION 3.22)

project(KaraokeDSP VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================================
# JUCE
# ==========================================================
set(JUCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/JUCE")
add_subdirectory(${JUCE_DIR})

# ==========================================================
# Sorgenti condivisi (solo quelli REALI)
# ==========================================================
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Source")

set(SHARED_SOURCES
    ${SRC_ROOT}/Main.cpp
    ${SRC_ROOT}/PluginProcessor.cpp
    ${SRC_ROOT}/PluginProcessor.h

    # UI
    ${SRC_ROOT}/UI/MainComponent.cpp
    ${SRC_ROOT}/UI/MainComponent.h
    ${SRC_ROOT}/UI/Knob.cpp
    ${SRC_ROOT}/UI/Knob.h
    ${SRC_ROOT}/UI/VuMeter.cpp
    ${SRC_ROOT}/UI/VuMeter.h
    ${SRC_ROOT}/UI/TunerComponent.cpp
    ${SRC_ROOT}/UI/TunerComponent.h
    ${SRC_ROOT}/UI/MixerChannelComponent.cpp
    ${SRC_ROOT}/UI/MixerChannelComponent.h

    # DSP
    ${SRC_ROOT}/DSP/DSPChain.cpp
    ${SRC_ROOT}/DSP/DSPChain.h
    ${SRC_ROOT}/DSP/Delay.cpp
    ${SRC_ROOT}/DSP/Delay.h
    ${SRC_ROOT}/DSP/Reverb.cpp
    ${SRC_ROOT}/DSP/Reverb.h
    ${SRC_ROOT}/DSP/PitchShifter.cpp
    ${SRC_ROOT}/DSP/PitchShifter.h
    ${SRC_ROOT}/DSP/PitchDetection.cpp
    ${SRC_ROOT}/DSP/PitchDetection.h
    ${SRC_ROOT}/DSP/Mixer.cpp
    ${SRC_ROOT}/DSP/Mixer.h
)

# ==========================================================
# 1) Applicazione Standalone
# ==========================================================
juce_add_gui_app(KaraokeDSPApp
    PRODUCT_NAME "Karaoke DSP Console"
    VERSION      ${PROJECT_VERSION}
    COMPANY_NAME "Rocco Audio"
    BUNDLE_ID    com.rocco.karaokedsp
)

target_compile_definitions(KaraokeDSPApp PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_sources(KaraokeDSPApp PRIVATE ${SHARED_SOURCES})

target_link_libraries(KaraokeDSPApp PRIVATE
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_dsp
)

# ==========================================================
# 2) Plugin VST3
# ==========================================================
juce_add_plugin(KaraokeDSP_VST3
    PRODUCT_NAME "Karaoke DSP"
    VERSION      ${PROJECT_VERSION}
    COMPANY_NAME "Rocco Audio"
    BUNDLE_ID    com.rocco.karaokedsp.vst3

    FORMATS VST3
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
)

target_compile_definitions(KaraokeDSP_VST3 PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_FORCE_USE_LEGACY_PARAM_IDS=0
    JUCE_PLUGINHOST_VST=0
    JUCE_PLUGINHOST_VST3=1
)

target_sources(KaraokeDSP_VST3 PRIVATE ${SHARED_SOURCES})

# Ensure the format-specific wrapper target gets the plugin filter symbol
target_sources(KaraokeDSP_VST3_VST3 PRIVATE ${SRC_ROOT}/PluginProcessor.cpp)

target_link_libraries(KaraokeDSP_VST3 PRIVATE
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_dsp
)

# ==========================================================
# Linux
# ==========================================================
if(UNIX AND NOT APPLE)
    target_compile_definitions(KaraokeDSPApp PRIVATE JUCE_ALSA=1 JUCE_JACK=1)
    target_compile_definitions(KaraokeDSP_VST3 PRIVATE JUCE_ALSA=1 JUCE_JACK=1)

    find_package(Threads REQUIRED)

    target_link_libraries(KaraokeDSPApp PRIVATE Threads::Threads dl pthread)
    target_link_libraries(KaraokeDSP_VST3 PRIVATE Threads::Threads dl pthread)
endif()

# ==========================================================
# Output
# ==========================================================
set_target_properties(KaraokeDSPApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

set_target_properties(KaraokeDSP_VST3 PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/VST3"
)
