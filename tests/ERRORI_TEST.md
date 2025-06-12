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

## Formato Input Test
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

## Formato Output Test
In caso di successo, l'output sarà:
```
id_prenotazione id_utente id_veicolo timestamp_inizio timestamp_fine stato priorita posizione_riconsegna
```

In caso di errore, l'output sarà uno dei messaggi di errore descritti sopra.

# Test Case per la Gestione degli Errori

## Schema degli Input per Tipo di Test

### Test Creazione Prenotazione (TC01, TC02)
Input: 8 argomenti
1. id_utente (int)
2. id_veicolo (int)
3. giorno_inizio (int)
4. ora_inizio (int)
5. giorno_fine (int)
6. ora_fine (int)
7. tipo_prenotazione (int)
8. id_prenotazione (int)

### Test Calcolo Costo Noleggio (TC03, TC04)
Input: 6 argomenti
1. id_prenotazione (int)
2. id_veicolo (int)
3. giorno_inizio (int)
4. ora_inizio (int)
5. giorno_fine (int)
6. ora_fine (int)

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

## TC11: Calcolo Costo Noleggio Valido
- **Input**: Prenotazione valida per un'utilitaria (tipo 0) per 2 ore
- **Output Atteso**: "10.00" (5€/ora × 2 ore)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio

## TC12: Calcolo Costo Noleggio con Utente Non Esistente
- **Input**: Prenotazione con id_utente non esistente
- **Output Atteso**: "ERRORE_UTENTE_NON_TROVATO"
- **Verifica**: Il sistema deve gestire correttamente il caso di utente non trovato e restituire un messaggio di errore appropriato 

## TC13: Visualizzazione Disponibilità Veicoli
- **Input**: 
  - giorno_inizio: 1
  - ora_inizio: 10
  - giorno_fine: 1
  - ora_fine: 12
- **Setup**:
  - Veicolo 1 (JeepRenegade): prenotazione confermata per giorno 1, 10-12
  - Veicolo 2 (HondaCBR): nessuna prenotazione nel periodo
- **Output Atteso**: Solo il veicolo 2 (HondaCBR) dovrebbe essere mostrato come disponibile
- **Verifica**: Il sistema deve:
  1. Mostrare correttamente solo i veicoli disponibili nel periodo richiesto
  2. Escludere i veicoli con prenotazioni confermate nel periodo
  3. Considerare correttamente lo stato delle prenotazioni (confermate vs non confermate)
  4. Gestire correttamente l'aggiornamento della disponibilità dei veicoli in base al calendario

## TC14: Visualizzazione Storico Prenotazioni
- **Input**: 
  - id_utente: 1
- **Setup**:
  - Utente 1: ha una prenotazione confermata per il veicolo 1 (giorno 1, 10-12)
  - Utente 2: ha una prenotazione confermata per il veicolo 2 (giorno 2, 14-16)
- **Output Atteso**: Solo la prenotazione dell'utente 1 dovrebbe essere mostrata
- **Verifica**: Il sistema deve:
  1. Mostrare correttamente tutte le prenotazioni dell'utente specificato
  2. Non mostrare le prenotazioni di altri utenti
  3. Includere tutti i dettagli della prenotazione (id, veicolo, date, stato, priorità, posizione)
  4. Gestire correttamente il formato di output per ogni prenotazione 

  ## TC15: Visualizzazione Storico Prenotazioni
  **Input**
    id_utente: 0
  **Setup**
    Utente 1: ha una prenotazione confermata per il veicolo 1(giorno 1, 10-12)
              ha una prenotazione non confermata per il veicolo 2(giorno 2, 14-16)
    Utente 2: ha una prenotazione confermata per il veicolo 3(giorno 3, 9-11)
              ha una prenotazione non confermata per il veicolo 4(giorno 4, 13-15)
  **Output Atteso**: Tutte le prenotazioni di tutti gli utenti dovrebbero essere mostrate
  - **Verifica**: Il sistema deve:
  1. Mostrare correttamente tutte le prenotazioni di tutti gli utenti
  2. Includere tutti i dettagli della prenotazione (id, veicolo, date, stato, priorità, posizione)
  3. Gestire correttamente il formato di output per ogni prenotazione 