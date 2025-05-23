# Imposta URL e percorsi
$zipUrl = "https://github.com/premake/premake-core/releases/download/v5.0.0-beta6/premake-5.0.0-beta6-windows.zip"
$zipPath = "premake.zip"
$extractPath = "."
$exeName = "premake5.exe"


if (Test-Path -Path $exeName) {
    Write-Host "premake5.exe presente nella directory corrente. Nessuna azione necessaria."
    return
}

# Scarica il file ZIP
Invoke-WebRequest -Uri $zipUrl -OutFile $zipPath

# Estrai il file ZIP
Expand-Archive -Path $zipPath -DestinationPath $extractPath -Force

# Cancella il file ZIP
Remove-Item -Path $zipPath

Write-Host "Premake scaricato e estratto in '$extractPath'. File zip eliminato."