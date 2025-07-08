# Plugin UWGM per caricamento allegati

## Setup
1. Eseguire da shell dos setup.bat per scaricare automaticamente premake, impostare la uwgm home e il path al toolkit
2. Riavviare la shell
3. Esguire premake.bat per generare il progetto/soluzione, il comando si aspetta come parametro il tipo di progetto da utilizzare fare riferimento alla documentazione premake per le azioni disponibili [premake](https://premake.github.io/docs/Using-Premake/#using-premake-to-generate-project-files)

```bash
	premake.bat vs2022
```

## Build
Il premake genererà 3 target di build (Debug, Release, Distribution)

La build Debug contiene i simboli di debug nessuna ottimizzazione del codice e la definizione della macro DEBUG che abilita determinate funzioni di debugging nel codice \
La build Release non contiene simboli di debug ma non rimuove tutte le istruzioni di pre processore per il debug \
La build Distribution è simile a release ma rimuove tutte le istruzione di preprocessore if DEBUG e if !defined(DISTRIBUTION)

## Loggin/Debug
E' possibile abilitare il logging dell'applicazione su file aggiungendo le seguenti variabili di ambiente NEUTRAL_DATA_LOG_FILE e NEUTRAL_DATA_LOG_LEVEL.

La variabile NEUTRAL_DATA_LOG_FILE deve indicare il percorso completo del file log da generare, il path di direcotry deve esistere

La variable NEUTRAL_DATA_LOG_LEVEL deve indicare il livello di logging, sono ammessi 3 valori (debug, warn, error)