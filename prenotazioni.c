#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
CodaPrenotazioni* inizializza_coda() {
    CodaPrenotazioni* coda = (CodaPrenotazioni*)malloc(sizeof(CodaPrenotazioni));
    if (coda == NULL) {
        return NULL;
    }
    coda->testa = NULL;
    coda->coda = NULL;
    coda->dimensione = 0;
    return coda;
}

// Funzione per creare una nuova prenotazione
Prenotazione crea_prenotazione(int id_utente, int id_veicolo, int giorno, int ora_inizio, int ora_fine) {
    static int id_counter = 1; // Contatore statico per generare ID unici
    
    Prenotazione nuova;
    nuova.id_prenotazione = id_counter++;
    nuova.id_utente = id_utente;
    nuova.id_veicolo = id_veicolo;
    nuova.giorno_settimana = giorno;
    nuova.ora_inizio = ora_inizio;
    nuova.ora_fine = ora_fine;
    nuova.stato = IN_ATTESA;
    
    return nuova;
}

// Funzione per verificare se una fascia oraria è valida
int verifica_fascia_oraria(int giorno, int ora_inizio, int ora_fine) {
    if (giorno < 0 || giorno > 6) return 0;
    if (ora_inizio < 0 || ora_inizio > 23) return 0;
    if (ora_fine < 0 || ora_fine > 23) return 0;
    if (ora_inizio >= ora_fine) return 0;
    return 1;
}

// Funzione per aggiungere una prenotazione alla coda
int aggiungi_prenotazione(CodaPrenotazioni* coda, Prenotazione prenotazione) {
    if (coda == NULL) {
        return -1;
    }
    
    // Verifica la validità della fascia oraria
    if (!verifica_fascia_oraria(prenotazione.giorno_settimana, 
                              prenotazione.ora_inizio, 
                              prenotazione.ora_fine)) {
        return -2;
    }
    
    NodoPrenotazione* nuovo_nodo = (NodoPrenotazione*)malloc(sizeof(NodoPrenotazione));
    if (nuovo_nodo == NULL) {
        return -1;
    }
    
    nuovo_nodo->prenotazione = prenotazione;
    nuovo_nodo->prossimo = NULL;
    
    if (coda->coda == NULL) {
        coda->testa = nuovo_nodo;
        coda->coda = nuovo_nodo;
    } else {
        coda->coda->prossimo = nuovo_nodo;
        coda->coda = nuovo_nodo;
    }
    
    coda->dimensione++;
    return 0;
}

// Funzione per rimuovere una prenotazione dalla coda
Prenotazione rimuovi_prenotazione(CodaPrenotazioni* coda) {
    Prenotazione prenotazione_vuota = {0};
    
    if (coda == NULL || coda->testa == NULL) {
        return prenotazione_vuota;
    }
    
    NodoPrenotazione* nodo_da_rimuovere = coda->testa;
    Prenotazione prenotazione = nodo_da_rimuovere->prenotazione;
    
    coda->testa = coda->testa->prossimo;
    if (coda->testa == NULL) {
        coda->coda = NULL;
    }
    
    free(nodo_da_rimuovere);
    coda->dimensione--;
    
    return prenotazione;
}

// Funzione per cercare una prenotazione per ID
Prenotazione* cerca_prenotazione(CodaPrenotazioni* coda, int id_prenotazione) {
    if (coda == NULL) {
        return NULL;
    }
    
    NodoPrenotazione* corrente = coda->testa;
    while (corrente != NULL) {
        if (corrente->prenotazione.id_prenotazione == id_prenotazione) {
            return &(corrente->prenotazione);
        }
        corrente = corrente->prossimo;
    }
    
    return NULL;
}

// Funzione per cercare prenotazioni per giorno e ora
Prenotazione* cerca_prenotazione_per_orario(CodaPrenotazioni* coda, int giorno, int ora) {
    if (coda == NULL) {
        return NULL;
    }
    
    NodoPrenotazione* corrente = coda->testa;
    while (corrente != NULL) {
        if (corrente->prenotazione.giorno_settimana == giorno &&
            corrente->prenotazione.ora_inizio <= ora &&
            corrente->prenotazione.ora_fine > ora) {
            return &(corrente->prenotazione);
        }
        corrente = corrente->prossimo;
    }
    
    return NULL;
}

// Funzione per modificare lo stato di una prenotazione
int modifica_stato_prenotazione(CodaPrenotazioni* coda, int id_prenotazione, StatoPrenotazione nuovo_stato) {
    Prenotazione* prenotazione = cerca_prenotazione(coda, id_prenotazione);
    if (prenotazione == NULL) {
        return -1;
    }
    
    prenotazione->stato = nuovo_stato;
    return 0;
}

// Funzione per pulire la coda
void pulisci_coda(CodaPrenotazioni* coda) {
    if (coda == NULL) {
        return;
    }
    
    while (coda->testa != NULL) {
        NodoPrenotazione* temp = coda->testa;
        coda->testa = coda->testa->prossimo;
        free(temp);
    }
    
    coda->coda = NULL;
    coda->dimensione = 0;
}

// Funzione per liberare la memoria della coda
void distruggi_coda(CodaPrenotazioni* coda) {
    if (coda == NULL) {
        return;
    }
    
    pulisci_coda(coda);
    free(coda);
}
