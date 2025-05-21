#ifndef MENU_H
#define MENU_H

#include "utenti.h"
#include "prenotazioni.h"
#include "veicolo.h"
#include "tariffe.h"
#include "fasce_orarie.h"


// Dichiarazioni delle funzioni di formattazione



void visualizza_tariffe(Utente* current_user);
void gestione_veicoli(void);
void prenota_auto(Utente* current_user);
void visualizza_prenotazioni(void);
void restituisci_auto(void);
void visualizza_disponibilita(void);

void mostra_menu_cliente(Utente* current_user);
void mostra_menu_admin(Utente* current_user);
void gestione_prenotazioni_admin(void);
void mostra_menu_iniziale();
void mostra_logo();
void mostra_menu_login();
int valida_username(const char* username);
int valida_nome_completo(const char* nome);


#endif // MENU_H

