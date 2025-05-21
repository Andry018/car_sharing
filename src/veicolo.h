#ifndef veicolo_C
#define veicolo_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tariffe.h"

typedef struct {
    int id;
    TipoVeicolo tipo;  // Usando l'enum TipoVeicolo invece di una stringa
    char modello[30];
    char targa[8];
    char posizione[50]; 
    int disponibile; // 0 = non disponibile | 1 = disponibile
} veicolo;

typedef struct node {
    veicolo veicoli;
    struct node *next;
} *list;

// Funzioni di accesso alla lista
list get_lista_veicoli(void);
void set_lista_veicoli(list nuovaLista);
void salva_lista_veicoli(void);
void carica_lista_veicoli(void);
void pulisci_lista_veicoli(void);

// Funzioni di gestione veicoli
veicolo crea_veicolo(void);
list aggiungi_veicolo(list);
list rimuovi_veicolo(list);
void stampa_veicolo(veicolo);
void salva_veicolo_file(list);
list carica_veicolo_file(list);
int carica_ultimo_id(void);

#endif
