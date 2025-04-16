#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

// Stati possibili di una prenotazione
typedef enum {
    IN_ATTESA,
    CONFERMATA,
    COMPLETATA,
    CANCELLATA
} StatoPrenotazione;

// Struttura per rappresentare una prenotazione
typedef struct {
    int id_prenotazione;
    int id_utente;
    int id_veicolo;
    int giorno_settimana;  // 0-6 (Lun-Dom)
    int ora_inizio;        // 0-23
    int ora_fine;          // 0-23
    StatoPrenotazione stato;
} Prenotazione;

// Nodo della coda
typedef struct NodoPrenotazione {
    Prenotazione prenotazione;
    struct NodoPrenotazione* prossimo;
} NodoPrenotazione;

// Struttura della coda
typedef struct {
    NodoPrenotazione* testa;
    NodoPrenotazione* coda;
    int dimensione;
} CodaPrenotazioni;

// Funzione per inizializzare una nuova coda
CodaPrenotazioni* inizializza_coda(void);

// Funzione per creare una nuova prenotazione
Prenotazione crea_prenotazione(int id_utente, int id_veicolo, int giorno, int ora_inizio, int ora_fine);

// Funzione per verificare se una fascia oraria è valida
int verifica_fascia_oraria(int giorno, int ora_inizio, int ora_fine);

// Funzione per aggiungere una prenotazione alla coda
int aggiungi_prenotazione(CodaPrenotazioni* coda, Prenotazione prenotazione);

// Funzione per rimuovere una prenotazione dalla coda
Prenotazione rimuovi_prenotazione(CodaPrenotazioni* coda);

// Funzione per cercare una prenotazione per ID
Prenotazione* cerca_prenotazione(CodaPrenotazioni* coda, int id_prenotazione);

// Funzione per cercare prenotazioni per giorno e ora
Prenotazione* cerca_prenotazione_per_orario(CodaPrenotazioni* coda, int giorno, int ora);

// Funzione per modificare lo stato di una prenotazione
int modifica_stato_prenotazione(CodaPrenotazioni* coda, int id_prenotazione, StatoPrenotazione nuovo_stato);

// Funzione per pulire la coda
void pulisci_coda(CodaPrenotazioni* coda);

// Funzione per liberare la memoria della coda
void distruggi_coda(CodaPrenotazioni* coda);

#endif /* PRENOTAZIONI_H */
