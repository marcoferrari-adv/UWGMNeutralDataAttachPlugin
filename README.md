# Plugin UWGM per caricamento allegati

## Setup
1. Modificare il file setup.ps1 indicando nella variabile $premakeVersion la versione di premake da scaricare
2. Modificare nel file vendor/premake/premake5.lua le variabile di ambiente WWGM_HOME e WWGMTK_HOME per puntare rispettivamente all'installazione del uwgm e del relativo toolkit
3. Eseguire da shell dos setup.bat per scaricare automaticamente premake
4. Esguire premake.bat per generare la soluzione e il progetto visual studio

## Build
Il premake genererà 3 target di build (Debug, Release, Distribution)

La build Debug contiene i simboli di debug nessuna ottimizzazione del codice e la definizione della macro DEBUG che abilita determinate funzioni di debugging nel codice \
La build Release non contiene simboli di debug ma non rimuove tutte le istruzioni di pre processore per il debug \
La build Distribution è simile a release ma rimuove tutte le istruzione di preprocessore if DEBUG e if !defined(DISTRIBUTION)