# 📁 Struttura del Progetto

## 🗂️ Organizzazione Directory

```
car_sharing/
├── src/
│   ├── main.c
│   ├── prenotazioni.c
│   ├── prenotazioni.h
│   ├── vehicle.c
│   ├── vehicle.h
│   ├── utenti.c
│   ├── utenti.h
│   ├── fasceorarie.c
│   └── fasceorarie.h
├── data/
│   ├── prenotazioni.txt
│   ├── utenti.txt
│   └── veicoli.txt
├── docs/
│   ├── guida-utente.md
│   ├── documentazione-tecnica.md
│   ├── struttura-progetto.md
│   ├── componenti-api.md
│   └── note-sviluppo.md
├── Makefile
└── README.md
```

## 📄 Descrizione File

### File Sorgente
- `main.c`: Entry point dell'applicazione e gestione menu principale
- `prenotazioni.c/h`: Sistema di gestione prenotazioni
- `vehicle.c/h`: Gestione parco veicoli
- `utenti.c/h`: Gestione utenti e autenticazione
- `fasceorarie.c/h`: Gestione calendario e disponibilità

### File di Dati
- `prenotazioni.txt`: Archivio prenotazioni
- `utenti.txt`: Database utenti registrati
- `veicoli.txt`: Catalogo veicoli disponibili

### Documentazione
- `guida-utente.md`: Guida utente
- `documentazione-tecnica.md`: Documentazione tecnica
- `struttura-progetto.md`: Struttura progetto
- `componenti-api.md`: API e componenti
- `note-sviluppo.md`: Note di sviluppo

## 🛠️ Build System

### Makefile
```makefile
CC = gcc
CFLAGS = -Wall -Wextra
SRC = src
OBJ = obj

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)

car_sharing: $(OBJECTS)
    $(CC) $(OBJECTS) -o $@

$(OBJ)/%.o: $(SRC)/%.c
    $(CC) $(CFLAGS) -c $< -o $@
```

## 📦 Dipendenze
- Compilatore C (GCC raccomandato)
- Make/MinGW32-make per Windows
- Librerie standard C

## 🔄 Workflow di Sviluppo

### Compilazione
1. Posizionarsi nella directory principale
2. Eseguire `make` o `mingw32-make`
3. Verificare output compilazione

### Esecuzione
1. Avviare l'eseguibile generato
2. Login come admin o utente
3. Navigare nel menu principale

### Sviluppo
1. Modificare i file sorgente
2. Compilare con `make`
3. Testare le modifiche
4. Committare i cambiamenti 