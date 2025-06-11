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
- **Input**: Prenotazione valida per un'utilitaria (tipo 0)
- **Output Atteso**: Dettagli della prenotazione creata
- **Verifica**: Il sistema deve creare correttamente la prenotazione

## TC02: Creazione Prenotazione nel Passato
- **Input**: Prenotazione con data nel passato
- **Output Atteso**: "ERRORE_DATA_1" (data nel passato)
- **Verifica**: Il sistema deve rifiutare la prenotazione e restituire un messaggio di errore appropriato

## TC03: Calcolo Costo Noleggio Valido
- **Input**: Prenotazione valida per un'utilitaria (tipo 0) per 2 ore
- **Output Atteso**: "10.00" (5€/ora × 2 ore)
- **Verifica**: Il sistema deve calcolare correttamente il costo del noleggio

## TC04: Calcolo Costo Noleggio con Utente Non Esistente
- **Input**: Prenotazione con id_utente non esistente
- **Output Atteso**: "ERRORE_UTENTE_NON_TROVATO"
- **Verifica**: Il sistema deve gestire correttamente il caso di utente non trovato e restituire un messaggio di errore appropriato 