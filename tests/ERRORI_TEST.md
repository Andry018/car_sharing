# Documentazione Errori Test Case

Questo documento descrive tutti i possibili errori che possono essere generati durante l'esecuzione dei test case.

## Errori di Fascia Oraria
```
ERRORE_FASCIA_ORARIA
```
Generato quando:
- Il giorno di inizio è < 0 o > 6
- Il giorno di fine è < 0 o > 6
- L'ora di inizio è < 0 o > 23
- L'ora di fine è < 0 o > 23
- Il timestamp di inizio è >= timestamp di fine

## Errori di Data
```
ERRORE_DATA_1
```
Generato quando:
- La data di inizio è nel passato rispetto alla data di sistema
- Esempio: data sistema = Lunedì 8:00, prenotazione inizia Lunedì 7:00

```
ERRORE_DATA_2
```
Generato quando:
- La data di fine è precedente o uguale alla data di inizio
- Esempio: inizio = Lunedì 10:00, fine = Lunedì 9:00

## Errori di Utente
```
ERRORE_UTENTE_NON_TROVATO
```
Generato quando:
- L'ID utente specificato non esiste nel sistema
- Esempio: tentativo di prenotazione con id_utente = 999 quando non esiste

## Errori di Veicolo
```
ERRORE_VEICOLO_NON_TROVATO
```
Generato quando:
- L'ID veicolo specificato non esiste nel sistema
- Esempio: tentativo di prenotazione con id_veicolo = 999 quando non esiste

## Errori di posizione non valida
```
ERRORE_POSIZIONE_RICONSEGNA
```
Generato quando:
- La posizioni di riconsegna non è una di quelle esistenti
- Esempio: tentativo di prenotazione con posizione_riconsenga = 999 quando non esiste

# Test Crea Prenotazione
## Formato Input 
Ogni test case accetta 8 valori in input:
```
id_utente id_veicolo giorno_inizio ora_inizio giorno_fine ora_fine priorita posizione_riconsegna
```

Dove:
- id_utente: intero positivo
- id_veicolo: intero positivo
- giorno_inizio: 0-6 (Lunedì-Domenica)
- ora_inizio: 0-23
- giorno_fine: 0-6 (Lunedì-Domenica)
- ora_fine: 0-23
- priorita: -1 per calcolo automatico, altrimenti intero positivo
- posizione_riconsegna: intero positivo

## Formato Output 
In caso di successo, l'output sarà:
```
id_prenotazione id_utente id_veicolo timestamp_inizio timestamp_fine stato priorita posizione_riconsegna
```

In caso di errore, l'output sarà uno dei messaggi di errore descritti sopra.

# Test Costo Noleggio
## Formato Input
Ogni test accetta 6 valori in input:
```
id_prenotazione id_veicolo giorno_inizio ora_inizio giorno_fine ora_fine
```
Dove:
- id_prenotazione: intero positivo
- id_veicolo: intero positivo
- giorno_inizio: 0-6 (Lunedì-Domenica)
- ora_inizio: 0-23
- giorno_fine: 0-6 (Lunedì-Domenica)
- ora_fine: 0-23

## Formato Output 
In caso di successo l'output sarà:
```
costo
```
In caso di errore, l'output sarà uno dei messaggi di errore descritti sopra.

# Test Visualizza Disponibilità
## Formato Input
Ogni Test accetta 4 valori:
```
giorno_inizio ora_inizio giorno_fine ora_fine
```
Dove:
- giorno_inizio: 0-6 (Lunedì-Domenica)
- ora_inizio: 0-23
- giorno_fine: 0-6 (Lunedì-Domenica)
- ora_fine: 0-23

## Setup Veicoli
Prenotazioni Confermate:

Veicolo 1 (Fiat500, id=1)
- giorno 1, 10-12 (martedì 10-12)
- giorno 3, 6-7 (giovedì 6-7)

Veicolo 2 (HondaCBR, id=2)
- giorno 2, 14-16 (mercoledì 14-16)
- giorno 3, 2-3 (giovedì 2-3)
- giorno 3, 6-7 (giovedì 6-7)

Veicolo 3 (JeepWrangler, id=3)
- giorno 3, 2-3 (giovedì 2-3)
- giorno 3, 6-7 (giovedì 6-7)

Veicolo 4 (TeslaModelS, id=4)
- giorno 3, 3-4 (giovedì 3-4)
- giorno 3, 6-7 (giovedì 6-7)

## Formato Output 
In caso di successo l'output sarà:
```
1. Descrizione veicoli disponibili:
id_veicolo modello posizione

2. Nessun veicolo se non disponibili
```
In caso di errore, l'output sarà uno dei messaggi di errore descritti sopra.

## Test Storico Prenotazioni
 ## Formato Input
Ogni test accetta 1 valore in input:
```
id_utente
```
dove:
id_utente = intero positivo

## Formato Output 
In caso di successo l'output sarà:
```
id_prenotazione id_utente id_veicolo timestamp_inizio timestamp_fine stato priorita posizione_riconsegna
id_prenotazione id_utente id_veicolo timestamp_inizio timestamp_fine stato priorita posizione_riconsegna
ecc...

```
In caso di errore, l'output sarà uno dei messaggi di errore descritti sopra.

# Schema degli Input per Tipo di Test

### Test Creazione Prenotazione (TC01, TC13)
Input: 8 argomenti
1. id_utente (int)
2. id_veicolo (int)
3. giorno_inizio (int)
4. ora_inizio (int)
5. giorno_fine (int)
6. ora_fine (int)
7. tipo_prenotazione (int)
8. id_prenotazione (int)

### Test Calcolo Costo Noleggio (TC14, TC28)
Input: 6 argomenti
1. id_prenotazione (int)
2. id_veicolo (int)
3. giorno_inizio (int)
4. ora_inizio (int)
5. giorno_fine (int)
6. ora_fine (int)

### Test Visualizza Disponibilita (TC29, TC38)
Input: 4 argomenti
1. giorno_inizio (int)
2. ora_inizio (int)
3. giorno_fine (int)
4. ora_fine (int)

### Test Storico Prenotazioni (TC39, TC42)
Input: 1 argomento
1. id_utente (int)

## Test Case

## TC01: Creazione Prenotazione Valida
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 1
  ora_fine: 10
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: Dettagli della prenotazione creata
- **Verifica**: Il sistema deve creare correttamente la prenotazione

## TC02: Creazione Prenotazione nel Passato
- **Input**:
  id_utente: 2
  id_veicolo: 2
  giorno_inizio: 0
  ora_inizio: 0
  giorno_fine: 1
  ora_fine: 0
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_DATA_1" (data nel passato)
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC03: Creazione Prenotazione Data di fine precedente a Data inizio
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 1
  ora_inizio: 12
  giorno_fine: 1
  ora_fine: 10
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_FASCIA_ORARIA" 
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC04: Creazione Prenotazione Utente non esistente
- **Input**: 
  id_utente: 999
  id_veicolo: 2
  giorno_inizio: 1
  ora_inizio: 10
  giorno_fine: 1
  ora_fine: 12
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_UTENTE_NON_TROVATO" 
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC05: Creazione Prenotazione Veicolo non esistente
- **Input**: 
  id_utente: 1
  id_veicolo: 999
  giorno_inizio: 1
  ora_inizio: 10
  giorno_fine: 1
  ora_fine: 12
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_VEICOLO_NON_TROVATO" 
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC06: Creazione Prenotazione con Giorno fuori range
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 7
  ora_inizio: 10
  giorno_fine: 8
  ora_fine: 12
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_FASCIA_ORARIA" 
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC07: Creazione Prenotazione con Ora fuori range
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 1
  ora_inizio: 24
  giorno_fine: 1
  ora_fine: 26
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_FASCIA_ORARIA" 
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC08: Creazione Prenotazione con priorità manuale
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 1
  ora_inizio: 10
  giorno_fine: 1
  ora_fine: 12
  priorità: 5
  posizione_riconsegna: 0
- **Output Atteso**: Dettagli della prenotazione creata con priorità impostata a 5
- **Verifica**: Il sistema deve creare correttamente la prenotazione

## TC09: Creazione Prenotazione che copre tutta la settimana da data avvio sistema
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 0
  ora_inizio: 8
  giorno_fine: 6
  ora_fine: 23
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: Dettagli della prenotazione creata 
- **Verifica**: Il sistema deve creare correttamente la prenotazione

## TC10: Creazione Prenotazione che copre tutta la settimana
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 0
  ora_inizio: 0
  giorno_fine: 6
  ora_fine: 23
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_DATA_1" (Data inizio precedente a data sistema)
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC11: Creazione Prenotazione con durata zero
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 2
  ora_inizio: 15
  giorno_fine: 2
  ora_fine: 15
  priorità: -1
  posizione_riconsegna: 0
- **Output Atteso**: "ERRORE_FASCIA_ORARIA" 
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC12: Creazione Prenotazione con posizione riconsegna diversa
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 3
  ora_inizio: 8
  giorno_fine: 3
  ora_fine: 10
  priorità: -1
  posizione_riconsegna: 2
- **Output Atteso**: 18 1 2 80 82 0 72 2
- **Verifica**: Il sistema deve creare correttamente la prenotazione, con la posizione di riconsegna nuova

## TC13: Creazione Prenotazione con posizione riconsegna non esistente
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 3
  ora_inizio: 8
  giorno_fine: 3
  ora_fine: 10
  priorità: -1
  posizione_riconsegna: 999
- **Output Atteso**: ERRORE_POSIZIONE_RICONSEGNA
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC14: Calcolo Costo Noleggio Valido Utilitaria (tipo: 0)
- **Input**: 
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 12
- **Output Atteso**: "10.00" (5€/ora × 2 ore)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di un'utilitaria

## TC15: Calcolo Costo Noleggio con Utente Non Esistente
- **Input**: 
  id_utente: 1
  id_veicolo: 999
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 12
- **Output Atteso**: "ERRORE_UTENTE_NON_TROVATO"
- **Verifica**: Il sistema deve gestire correttamente il caso di utente non trovato e restituire un messaggio di errore appropriato 

## TC16: Calcolo Costo Noleggio su più giorni
- **Input**:
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 22
  giorno_fine: 1
  ora_fine: 2
- **Output Atteso**: "20.00"
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio posto su due giorni diversi 

## TC17: Calcolo Costo Noleggio con durata zero
- **Input**:
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 10
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire il caso in cui ora_inizio == ora_fine

## TC18: Calcolo Costo Noleggio con ora_fine < ora_inizio nello stesso giorno
- **Input**:
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 12
  giorno_fine: 0
  ora_fine: 10
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire il caso in cui ora_fine < ora_inizio nello stesso giorno (caso limite)

## TC19: Calcolo Costo Noleggio con giorno_fine < giorno_inizio 
- **Input**:
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 2
  ora_inizio: 10
  giorno_fine: 1
  ora_fine: 12
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire il caso in cui giorno_fine < giorno_inizio (caso limite)

## TC20: Calcolo Costo Noleggio con veicolo non esistente
- **Input**:
  id_utente: 1
  id_veicolo: 999
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 12
- **Output Atteso**: ERRORE_VEICOLO_NON_TROVATO
- **Verifica**: Il sistema deve gestire il caso di veicolo non trovato.

## TC21: Calcolo Costo Noleggio con orari fuori range
- **Input**:
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 25
  giorno_fine: 0
  ora_fine: 27
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire orari non validi.

## TC22: Calcolo Costo Noleggio con giorni fuori range
- **Input**:
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 25
  giorno_fine: 0
  ora_fine: 27
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire giorni non validi.

## TC23: Calcolo Costo Noleggio Valido SUV (tipo: 1)
- **Input**: 
  id_utente: 1
  id_veicolo: 3
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 15
- **Output Atteso**: "40.00" (8€/ora × 5 ore)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di un SUV

## TC24: Calcolo Costo Noleggio Valido SPortiva (tipo: 2)
- **Input**: 
  id_utente: 1
  id_veicolo: 4
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 15
- **Output Atteso**: "62.50" (12.50€/ora × 5 ore)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di una Sportiva

## TC25: Calcolo Costo Noleggio Valido Moto (tipo: 3)
- **Input**: 
  id_utente: 1
  id_veicolo: 2
  giorno_inizio: 0
  ora_inizio: 10
  giorno_fine: 0
  ora_fine: 15
- **Output Atteso**: "20.00" (4€/ora × 5 ore)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di una moto

## TC26: Calcolo Costo Noleggio Valido Utilitaria (tipo: 0) per 24 ore
- **Input**: 
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 1
  ora_inizio: 0
  giorno_fine: 2
  ora_fine: 0
- **Output Atteso**: "100.00" (5€/ora × (24 ore - 4 ore di sconto), si applica lo sconto "PACCHETTI ORARI", in cui ogni 5 ore noleggiate la sesta è gratuita, quindi su 24 ore 4 saranno gratuite, e se ne pagheranno 20)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di una Utilitaria 
applicando lo sconto "PACCHETTI ORARI"

## TC27: Calcolo Costo Noleggio Valido Utilitaria (tipo: 0) per 6 giorni
- **Input**: 
  id_utente: 1
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 23
  giorno_fine: 6
  ora_fine: 23
- **Output Atteso**: "600.00" (5€/ora × (144 ore - 24 ore di sconto), si applica lo sconto "PACCHETTI ORARI", in cui ogni 5 ore noleggiate la sesta è gratuita, quindi su 144 ore 24 saranno gratuite, e se ne pagheranno 120)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di una Utilitaria 
applicando lo sconto "PACCHETTI ORARI"

## TC28: Calcolo Costo Noleggio Valido Utilitaria (tipo: 0) per 6 giorni, avendo completato in precedenza già 10 noleggi
- **Input**: 
  id_utente: 2
  id_veicolo: 1
  giorno_inizio: 0
  ora_inizio: 23
  giorno_fine: 6
  ora_fine: 23
- **Output Atteso**: "540.00" (5€/ora × (144 ore - 24 ore di sconto) - 10%, si applica lo sconto "PACCHETTI ORARI", in cui ogni 5 ore noleggiate la sesta è gratuita, quindi su 144 ore 24 saranno gratuite, inoltre si applica un 10% di sconto siccome l'utente in questione ha 10 noleggi completati, per cui si applica lo sconto "SCONTO FEDELTA'" che applica un 10% di sconto all'11 noleggio effettuato, dopo 10 completati)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio di una Utilitaria 
applicando lo sconto "PACCHETTI ORARI" e "SCONTO FEDELTA'"

## TC29: Visualizzazione Disponibilità con tutti i Veicoli Disponibili
- **Input**: 
  - giorno_inizio: 2
  - ora_inizio: 8
  - giorno_fine: 2
  - ora_fine: 10
- **Output Atteso**: 
  4 TeslaModelS Posizione D
  3 JeepWrangler Posizione C
  2 HondaCBR Posizione B
  1 Fiat500 Deposito
- **Verifica**: Il sistema deve:
  Mostrare correttamente i veicoli disponibili nel periodo richiesto.

## TC30: Visualizzazione Disponibilità con nessun Veicolo Disponibile
- **Input**: 
  - giorno_inizio: 3
  - ora_inizio: 6
  - giorno_fine: 3
  - ora_fine: 7
- **Output Atteso**: 
- **Verifica**: Il sistema deve:
  Non mostrare nessun Veicolo.

## TC31: Visualizzazione Disponibilità con 3 Veicoli Disponibili
  - giorno_inizio: 2
  - ora_inizio: 14
  - giorno_fine: 2
  - ora_fine: 16
- **Output Atteso**: 
  4 TeslaModelS Posizione D
  3 JeepWrangler Posizione C
  1 Fiat500 Deposito
- **Verifica**: Il sistema deve:
  Mostrare correttamente i veicolo disponibili nel periodo richiesto

  ## TC32: Visualizzazione Disponibilità con 3 Veicoli Disponibili
  - giorno_inizio: 1
  - ora_inizio: 10
  - giorno_fine: 1
  - ora_fine: 12
- **Output Atteso**: 
  4 TeslaModelS Posizione D
  3 JeepWrangler Posizione C
  2 HondaCBR Posizione B
- **Verifica**: Il sistema deve:
  Mostrare correttamente i veicolo disponibili nel periodo richiesto

  ## TC33: Visualizzazione Disponibilità con 3 Veicoli Disponibili
  - giorno_inizio: 3
  - ora_inizio: 3
  - giorno_fine: 3
  - ora_fine: 4
- **Output Atteso**: 
  3 JeepWrangler Posizione C
  2 HondaCBR Posizione B
  1 Fiat500 Deposito
- **Verifica**: Il sistema deve:
  Mostrare correttamente i veicolo disponibili nel periodo richiesto

  ## TC34: Visualizzazione Disponibilità con 3 Veicoli Disponibili
  - giorno_inizio: 3
  - ora_inizio: 2
  - giorno_fine: 3
  - ora_fine: 3
- **Output Atteso**: 
  4 TeslaModelS Posizione D
  2 HondaCBR Posizione B
  1 Fiat500 Deposito
- **Verifica**: Il sistema deve:
  Mostrare correttamente i veicolo disponibili nel periodo richiesto

  ## TC35: Visualizzazione Disponibilità con 2 Veicoli Disponibili
  - giorno_inizio: 3
  - ora_inizio: 2
  - giorno_fine: 3
  - ora_fine: 4
- **Output Atteso**: 
  2 HondaCBR Posizione B
  1 Fiat500 Deposito
- **Verifica**: Il sistema deve:
  Mostrare correttamente i veicolo disponibili nel periodo richiesto

  ## TC36: Visualizzazione Disponibilità con Giorno fuori range
  - giorno_inizio: 7
  - ora_inizio: 10
  - giorno_fine: 8
  - ora_fine: 12
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire orari non validi

  ## TC37: Visualizzazione Disponibilità con Giorno fuori range
  - giorno_inizio: 1
  - ora_inizio: 24
  - giorno_fine: 1
  - ora_fine: 25
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire orari non validi

  ## TC38: Visualizzazione Disponibilità con stessa ora
  - giorno_inizio: 2
  - ora_inizio: 4
  - giorno_fine: 2
  - ora_fine: 4
- **Output Atteso**: ERRORE_FASCIA_ORARIA
- **Verifica**: Il sistema deve gestire orari non validi

  ## TC39: Visualizzazione Storico Prenotazioni
  **Input**
    id_utente: 1
  **Output Atteso**: Tutte le prenotazioni dell'utente con id_utente 1, vengono stampate
  - **Verifica**: Il sistema deve:
  1. Mostrare correttamente tutte le prenotazioni dell'utente con id_utente 1
  2. Non mostrare le prenotazioni di altri utenti
  3. Includere tutti i dettagli della prenotazione (id, veicolo, date, stato, priorità, posizione)
  4. Gestire correttamente il formato di output per ogni prenotazione

  ## TC40: Visualizzazione Storico Prenotazioni
  **Input**
    id_utente: 2
  **Output Atteso**: Tutte le prenotazioni dell'utente con id_utente 2, vengono stampate
  - **Verifica**: Il sistema deve:
  1. Mostrare correttamente tutte le prenotazioni dell'utente con id_utente 2
  2. Non mostrare le prenotazioni di altri utenti
  3. Includere tutti i dettagli della prenotazione (id, veicolo, date, stato, priorità, posizione)
  4. Gestire correttamente il formato di output per ogni prenotazione

  ## TC41: Visualizzazione Storico Prenotazioni
  **Input**
    id_utente: 999
  **Output Atteso**: "ERRORE_UTENTE_NON_TROVATO"
  - **Verifica**: Il sistema deve stampare un messaggio di errore 

## TC42: Visualizzazione Storico Prenotazioni
- **Input**: 
  - id_utente: 0
- **Output Atteso**: Tutte le prenotazioni degli utenti registrati, vengono stampate
- **Verifica**: Il sistema deve:
  1. Mostrare correttamente tutte le prenotazioni degli utenti registrati
  2. Includere tutti i dettagli della prenotazione (id, veicolo, date, stato, priorità, posizione)
  3. Gestire correttamente il formato di output per ogni prenotazione 