#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <stdbool.h>
#include "data_sistema.h"

// Forward declarations
struct Prenotazione;
struct CodaPrenotazioni;

// Typedefs
typedef struct Prenotazione Prenotazione;
typedef struct CodaPrenotazioni CodaPrenotazioni;

// Costanti per gli stati delle prenotazioni
#define STATO_IN_ATTESA 0
#define STATO_CONFERMATA 1
#define STATO_COMPLETATA 2
#define STATO_CANCELLATA 3

// Funzioni di utilità per le date
int converti_in_timestamp(int giorno, int ora);
int estrai_giorno(int timestamp);
int estrai_ora(int timestamp);

// Funzioni per la gestione delle prenotazioni
struct Prenotazione* crea_prenotazione(int id_utente, int id_veicolo, 
                                     int giorno_inizio, int ora_inizio,
                                     int giorno_fine, int ora_fine, 
                                     int priorita);

int verifica_fascia_oraria(int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);

void scambia_prenotazioni(struct Prenotazione* a, struct Prenotazione* b);
void bubble_up(struct CodaPrenotazioni* coda, int index);
void bubble_down(struct CodaPrenotazioni* coda, int index);

int aggiungi_prenotazione(struct CodaPrenotazioni* coda, struct Prenotazione* prenotazione);
struct Prenotazione rimuovi_prenotazione(struct CodaPrenotazioni* coda);
struct Prenotazione* cerca_prenotazione(struct CodaPrenotazioni* coda, int id_prenotazione);
struct Prenotazione* cerca_prenotazione_per_orario(struct CodaPrenotazioni* coda, int giorno, int ora);

int modifica_stato_prenotazione(struct CodaPrenotazioni* coda, int id_prenotazione, int nuovo_stato);

void stampa_prenotazione(struct Prenotazione p);
void salva_prenotazioni_su_file(struct CodaPrenotazioni* coda);
int carica_prenotazioni_da_file(struct CodaPrenotazioni* coda);
void carica_prenotazioni();
void pulisci_coda(struct CodaPrenotazioni* coda);
void distruggi_coda(struct CodaPrenotazioni* coda);

void aggiorna_priorita_prenotazioni(struct CodaPrenotazioni* coda);
void rimuovi_prenotazioni_scadute(struct CodaPrenotazioni* coda);
void stampa_data_sistema();

int valida_data_prenotazione(int giorno_ora_inizio, int giorno_ora_fine);
int verifica_sovrapposizioni(struct CodaPrenotazioni* coda, int id_veicolo, int giorno_ora_inizio, int giorno_ora_fine);

// Getter functions
int get_id_prenotazione(struct Prenotazione* p);
int get_id_utente_prenotazione(struct Prenotazione* p);
int get_id_veicolo_prenotazione(struct Prenotazione* p);
int get_giorno_ora_inizio(struct Prenotazione* p);
int get_giorno_ora_fine(struct Prenotazione* p);
int get_stato_prenotazione(struct Prenotazione* p);
int get_priorita(struct Prenotazione* p);

// Helper functions to get specific time components
int get_giorno_inizio(struct Prenotazione* p);
int get_ora_inizio(struct Prenotazione* p);
int get_giorno_fine(struct Prenotazione* p);
int get_ora_fine(struct Prenotazione* p);

// Setter functions
void set_id_prenotazione(int id_prenotazione, struct Prenotazione* p);
void set_id_utente_prenotazione(int id_utente, struct Prenotazione* p);
void set_id_veicolo_prenotazione(int id_veicolo, struct Prenotazione* p);
void set_giorno_ora_inizio(int giorno_ora_inizio, struct Prenotazione* p);
void set_giorno_ora_fine(int giorno_ora_fine, struct Prenotazione* p);
void set_stato_prenotazione(int stato, struct Prenotazione* p);
void set_priorita(int priorita, struct Prenotazione* p);

#endif // PRENOTAZIONI_H 