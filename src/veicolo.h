#ifndef veicolo_C
#define veicolo_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tariffe.h"

// Forward declarations per information hiding
typedef struct Veicolo* Veicolo;
typedef struct node* list;

// Funzioni di accesso alla lista
list get_lista_veicoli(void);
void set_lista_veicoli(list nuovaLista);
void salva_lista_veicoli(void);
void carica_lista_veicoli(void);
void pulisci_lista_veicoli(void);

// Funzioni di gestione veicoli
Veicolo crea_veicolo(void);
list aggiungi_veicolo(list);
list rimuovi_veicolo(list);
void stampa_veicolo(Veicolo v);
void salva_veicolo_file(list);
list carica_veicolo_file(list);
int carica_ultimo_id(void);

// Getter functions
int get_id_veicolo(Veicolo v);
int get_tipo_veicolo(Veicolo v);
const char* get_modello_veicolo(Veicolo v);
const char* get_targa_veicolo(Veicolo v);
const char* get_posizione_veicolo(Veicolo v);
int get_disponibilita_veicolo(Veicolo v);
Veicolo get_veicolo_da_lista(list *l);
list get_next_node(list l);

// Setter functions
void set_id_veicolo(Veicolo v, int id);
void set_tipo_veicolo(Veicolo v, int tipo);
void set_modello_veicolo(Veicolo v, const char* modello);
void set_targa_veicolo(Veicolo v, const char* targa);
void set_posizione_veicolo(Veicolo v, const char* posizione);
void set_disponibilita_veicolo(Veicolo v, int disponibilita);

// Funzioni di ricerca
Veicolo cerca_veicolo(list l, int id);
void modifica_veicolo(list l, int id);

// Funzioni di stampa
void stampa_lista_veicoli(list l);
void stampa_veicoli_disponibili(list l);
void stampa_veicoli_non_disponibili(list l);
void stampa_veicoli_per_tipo(list l, int tipo);
void stampa_veicoli_per_posizione(list l, const char* posizione);
void stampa_veicoli_per_modello(list l, const char* modello);
void stampa_veicoli_per_targa(list l, const char* targa);
void stampa_veicoli_per_id(list l, int id);
void stampa_veicoli_per_tipo_e_posizione(list l, int tipo, const char* posizione);
void stampa_veicoli_per_tipo_e_disponibilita(list l, int tipo, bool disponibile);
void stampa_veicoli_per_posizione_e_disponibilita(list l, const char* posizione, bool disponibile);
void stampa_veicoli_per_tipo_posizione_e_disponibilita(list l, int tipo, const char* posizione, bool disponibile);

const char* get_nome_tipo_veicolo(int tipo);

#endif
