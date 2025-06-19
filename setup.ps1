# Imposta URL e percorsi
$premakeVersion = "5.0.0-beta6"
$zipUrl = "https://github.com/premake/premake-core/releases/download/v$premakeVersion/premake-$premakeVersion-windows.zip"
$zipPath = "premake.zip"
$extractPath = "."
$exeName = "premake5.exe"


if (Test-Path -Path $exeName) {
    Write-Host "premake5.exe presente nella directory corrente. Nessuna azione necessaria."
}
else {
	# Scarica il file ZIP
	Invoke-WebRequest -Uri $zipUrl -OutFile $zipPath

	# Estrai il file ZIP
	Expand-Archive -Path $zipPath -DestinationPath $extractPath -Force

	# Cancella il file ZIP
	Remove-Item -Path $zipPath

	Write-Host "Premake scaricato e estratto in '$extractPath'. File zip eliminato."
}

while ($true) {
	$uwgmHome = Read-Host "Inserire percorso installazione uwgm"
	if (-not $uwgmHome.EndsWith("\")) {
		$uwgmHome += "\"
	}

	$uwgmIni = $uwgmHome + "wgmclient.ini"

	if (Test-Path -Path $uwgmIni) {
		[Environment]::SetEnvironmentVariable("UWGM_HOME", $uwgmHome, "User")
		break
	}
	Write-Host "Posizione home uwgm non valida"
}

while ($true) {
	$uwgmToolkit = Read-Host "Inserire percorso installazione uwgmtoolkit"
	if (-not $uwgmToolkit.EndsWith("\")) {
		$uwgmToolkit += "\"
	}

	$wwgmtkH = $uwgmToolkit + "src\includes\wwgmtk.h"

	if (Test-Path -Path $wwgmtkH) {
		[Environment]::SetEnvironmentVariable("UWGM_TK_HOME", $uwgmToolkit, "User")
		break
	}
	Write-Host "Posizione toolkit uwgm non valida"
}

Write-Host "Riavviare la shell ed eseguire ora premake.bat"