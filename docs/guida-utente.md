# Guida Utente - Sistema di Car Sharing

## Interfaccia Utente
L'interfaccia utente è stata ottimizzata per la massima compatibilità con tutti i terminali Windows e sistemi operativi. Utilizza:
- Caratteri ASCII standard per la visualizzazione dei menu
- Colori per evidenziare le diverse sezioni
- Layout pulito e facilmente leggibile

## Processo di Prenotazione
1. Selezionare "Prenota un'auto" dal menu principale
2. Visualizzare i veicoli disponibili con le relative tariffe
3. Inserire:
   - ID del veicolo desiderato
   - Giorno e ora di inizio (0-6 per i giorni, 0-23 per le ore)
   - Giorno e ora di fine
4. Confermare la prenotazione
   - La priorità viene assegnata automaticamente dal sistema
   - Non è più necessario inserire manualmente la priorità

## Stati delle Prenotazioni
Le prenotazioni possono essere in uno dei seguenti stati:
- **In attesa** (giallo): prenotazione appena creata
- **Confermata** (verde): approvata dall'amministratore
- **Completata** (ciano): servizio concluso
- **Cancellata** (rosso): prenotazione annullata

## Visualizzazione Disponibilità
1. Selezionare "Visualizza disponibilità" dal menu
2. Consultare la lista dei veicoli con il loro stato attuale
3. Inserire l'ID del veicolo per vedere il calendario dettagliato
4. Il sistema mostra la disponibilità per ogni giorno e fascia oraria

## Tariffe e Sconti
- Ogni tipo di veicolo ha una tariffa oraria specifica
- Sono disponibili sconti fedeltà basati sul numero di noleggi completati
- Il sistema mostra sempre il costo stimato prima della conferma

## Funzionalità Admin
Gli amministratori hanno accesso a funzionalità aggiuntive:
1. Gestione completa dei veicoli
2. Gestione delle prenotazioni di tutti gli utenti
3. Modifica degli stati delle prenotazioni
4. Gestione utenti
5. Avanzamento del tempo di sistema

## 👥 Gestione Utenti

### Tipologie di Utenti
1. **Utente Amministratore**
   - ID: 0
   - Accesso completo al sistema
   - Gestione utenti e veicoli
   - Modifica stato prenotazioni

2. **Utente Standard**
   - ID > 0
   - Gestione prenotazioni personali
   - Visualizzazione disponibilità
   - Modifica stato prenotazioni personali

### Operazioni Utente
- **Registrazione**
  - Creazione nuovo account
  - Assegnazione automatica ID
  - Gestione nome completo e nome utente
- **Accesso**
  - Login con nome utente
  - Supporto per ruoli differenziati
  - Gestione sessione utente

## 🚗 Gestione Veicoli
- Visualizzazione lista completa veicoli
- Verifica disponibilità
- Selezione per prenotazione

## 📅 Sistema di Prenotazioni

### Creazione Prenotazione
1. Selezionare un veicolo disponibile
2. Scegliere data e ora di inizio
3. Definire durata della prenotazione
4. Confermare la prenotazione

### Stati della Prenotazione
- **In Attesa**: Prenotazione iniziale
- **Confermata**: Approvata dall'amministratore
- **Completata**: Servizio concluso
- **Annullata**: Prenotazione cancellata

### Gestione Prenotazioni
- Visualizzazione prenotazioni personali
- Modifica prenotazioni esistenti
- Cancellazione prenotazioni
- Verifica stato prenotazione

## 🔧 Risoluzione Problemi

### Problemi di Accesso
- Verificare correttezza nome utente
- Controllare maiuscole/minuscole
- Contattare amministratore se il problema persiste

### Problemi con le Prenotazioni
- Verificare disponibilità veicolo
- Controllare sovrapposizioni
- Verificare stato utente

### Errori di Sistema
- Riavviare l'applicazione
- Verificare la connessione
- Contattare il supporto tecnico 