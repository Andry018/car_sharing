#ifndef MENU_H
#define MENU_H

#include "utenti.h"
#include "prenotazioni.h"
#include "veicolo.h"
#include "tariffe.h"
#include "fasce_orarie.h"


// Dichiarazioni delle funzioni di formattazione



void visualizza_tariffe(Utente utente_corrente);
void gestione_veicoli(void);
void prenota_auto(Utente utente_corrente);
void visualizza_prenotazioni(Utente utente_corrente);
void restituisci_auto(void);
void visualizza_disponibilita(void);

void mostra_menu_cliente(Utente utente_corrente);
void mostra_menu_amministratore(Utente utente_corrente);
void gestione_prenotazioni_amministratore(void);
void mostra_menu_iniziale();
void mostra_logo();
void mostra_menu_login();
void gestione_utenti_amministratore(void);



#endif // MENU_H

