#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include "data_sistema.h"
#include <stdbool.h>

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
    int giorno_ora_inizio;  // Formato: giorno*24*60 + ora*60 
    int giorno_ora_fine;    // Formato: giorno*24*60 + ora*60 
    StatoPrenotazione stato;
    int priorita;          // Campo per la priorità (più basso = più prioritario)
} Prenotazione;

// Struttura della coda con priorità
typedef struct {
    Prenotazione* heap;    // Array dinamico per l'heap
    int capacita;          // Capacità massima dell'array
    int dimensione;        // Numero di elementi attuali
} CodaPrenotazioni;

// Funzioni di utilità per l'heap
#define GENITORE(i) ((i - 1) / 2)
#define FIGLIO_SINISTRO(i) (2 * i + 1)
#define FIGLIO_DESTRO(i) (2 * i + 2)

// Funzioni di utilità per i timestamp
int converti_in_timestamp(int giorno, int ora);
int estrai_giorno(int timestamp);
int estrai_ora(int timestamp);

// Funzione per ottenere la coda globale
CodaPrenotazioni* get_coda_prenotazioni();

// Funzione per inizializzare una nuova coda
CodaPrenotazioni* inizializza_coda();

// Funzione per creare una nuova prenotazione
Prenotazione crea_prenotazione(int id_utente, int id_veicolo, int giorno_inizio, 
                             int ora_inizio, int giorno_fine, int ora_fine, int priorita);

// Funzione per verificare se una fascia oraria è valida
int verifica_fascia_oraria(int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);

// Funzione per scambiare due prenotazioni
void scambia_prenotazioni(Prenotazione* a, Prenotazione* b);

// Funzione per fare bubble up nell'heap
void bubble_up(CodaPrenotazioni* coda, int index);

// Funzione per fare bubble down nell'heap
void bubble_down(CodaPrenotazioni* coda, int index);

// Funzione per aggiungere una prenotazione alla coda
int aggiungi_prenotazione(CodaPrenotazioni* coda, Prenotazione prenotazione);

// Funzione per rimuovere la prenotazione con priorità più alta
Prenotazione rimuovi_prenotazione(CodaPrenotazioni* coda);

// Funzione per cercare una prenotazione per ID
Prenotazione* cerca_prenotazione(CodaPrenotazioni* coda, int id_prenotazione);

// Funzione per cercare prenotazioni per giorno e ora
Prenotazione* cerca_prenotazione_per_orario(CodaPrenotazioni* coda, int giorno, int ora);

// Funzione per modificare lo stato di una prenotazione
int modifica_stato_prenotazione(CodaPrenotazioni* coda, int id_prenotazione, 
                              StatoPrenotazione nuovo_stato);

// Funzione per stampare una prenotazione
void stampa_prenotazione(Prenotazione prenotazione);

// Funzione per salvare le prenotazioni su un file
void salva_prenotazioni_su_file(CodaPrenotazioni* coda);

// Funzione per caricare le prenotazioni da un file
int carica_prenotazioni_da_file(CodaPrenotazioni* coda);

// Funzione per caricare da file void
void carica_prenotazioni();

// Funzione per pulire la coda
void pulisci_coda(CodaPrenotazioni* coda);

// Funzione per liberare la memoria della coda
void distruggi_coda(CodaPrenotazioni* coda);

// Nuove funzioni per la gestione delle prenotazioni con data di sistema
void aggiorna_priorita_prenotazioni(CodaPrenotazioni* coda);
void rimuovi_prenotazioni_scadute(CodaPrenotazioni* coda);
void stampa_data_sistema();

// Nuove funzioni di validazione
int valida_data_prenotazione(int giorno_ora_inizio, int giorno_ora_fine);
int verifica_sovrapposizioni(CodaPrenotazioni* coda, int id_veicolo, int giorno_ora_inizio, int giorno_ora_fine);

// Dichiarazioni delle funzioni per la gestione delle date
DataSistema get_data_sistema(void);
int converti_data_in_timestamp(DataSistema data);
int calcola_priorita_temporale(int timestamp);
void set_color(int color);

// Funzione per contare le prenotazioni completate di un utente
int conta_prenotazioni_completate(CodaPrenotazioni* coda, int id_utente);

#endif // PRENOTAZIONI_H 