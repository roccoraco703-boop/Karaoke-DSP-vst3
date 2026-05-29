
; NSIS installer script for KaraokeDSP
; Expects BUILD_DIR and OUTFILE and optionally ICON and EULA defined via makensis -D flags

!include MUI2.nsh

!ifdef OUTFILE
!else
  !define OUTFILE "KaraokeDSP-Setup.exe"
!endif

!ifdef ICON
  Icon "${ICON}"
!endif

!ifdef EULA
  !insertmacro MUI_PAGE_LICENSE "${EULA}"
!endif

Name "Karaoke DSP"
OutFile ${OUTFILE}
InstallDir "$PROGRAMFILES\\KaraokeDSP"

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_LANGUAGE "English"

Section "Install"
  SetOutPath "$INSTDIR"
  ; Copy all files from build directory
  File /r "${BUILD_DIR}\\*"
  ; If an installer icon was provided, include it in the install directory
  !ifdef ICON
    File "${ICON}"
  !endif
  ; Create Start Menu shortcut
  CreateDirectory "$SMPROGRAMS\\KaraokeDSP"
  CreateShortCut "$SMPROGRAMS\\KaraokeDSP\\KaraokeDSP.lnk" "$INSTDIR\\KaraokeDSP.exe"
SectionEnd

Section "Uninstall"
  Delete "$INSTDIR\\KaraokeDSP.exe"
  RMDir /r "$INSTDIR"
  Delete "$SMPROGRAMS\\KaraokeDSP\\KaraokeDSP.lnk"
  RMDir "$SMPROGRAMS\\KaraokeDSP"
SectionEnd
