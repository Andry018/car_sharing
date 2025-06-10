#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "veicolo.h"
#include "prenotazioni.h"
#include "utenti.h"

// Definizione del tipo list per i test
typedef struct node {
    Veicolo v;
    struct node* next;
} *list;

// Funzioni di test per i veicoli
list get_lista_veicoli_test(void);
void pulisci_lista_veicoli_test(void);

// Funzioni di test per le prenotazioni
Prenotazione crea_prenotazione_test(int id_utente, int id_veicolo, int giorno_inizio, int ora_inizio,
                                  int giorno_fine, int ora_fine, int priorita, int posizione_riconsegna,
                                  int id_prenotazione);

// Funzioni di test per la coda
CodaPrenotazioni get_coda_test(void);
void pulisci_coda_test(void);
bool coda_vuota_test(void);
Prenotazione estrai_test(void);

#endif // TEST_UTILS_H 