; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Translit"
#define MyAppVersion "1.0.2.140"
#define MyAppPublisher "artem78"
#define MyAppURL "https://github.com/artem78/Translit"
#define MyAppExeName "Translit.exe"

; Custom definitions
#define RegSectionName "Translit"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{426562D3-2BB5-48C1-882F-73AB3F77C6A9}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
DisableProgramGroupPage=yes
OutputDir=build\installer
OutputBaseFilename=Translit Setup
SetupIconFile=Translit.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Files]
Source: "build\Translit.exe"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"

;[Run]
;Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: "HKCR"; Subkey: "*\Shell\{#RegSectionName}"; ValueType: string; ValueName: "MUIVerb"; ValueData: "Транслит"; Flags: uninsdeletekey; Tasks: addToExplorerContextMenu
Root: "HKCR"; Subkey: "*\Shell\{#RegSectionName}"; ValueType: string; ValueName: "icon"; ValueData: "{app}\{#MyAppExeName}"; Flags: uninsdeletekey; Tasks: addToExplorerContextMenu
Root: "HKCR"; Subkey: "*\Shell\{#RegSectionName}\command"; ValueType: string; ValueData: """{app}\{#MyAppExeName}"" ""%1"""; Flags: uninsdeletekey; Tasks: addToExplorerContextMenu

[Tasks]
Name: "addToExplorerContextMenu"; Description: "Добавить в контекстное меню Проводника"
