#ifndef VEHICLE_C
#define VEHICLE_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int tipologia;    // 0 = Autoveicolo      1 = Motociclo
    char modello[30];
    char targa[7];
    char posizione[50]; 
    bool disponibile; // 0 = non disponibile | 1 = disponibile
} veicolo;

typedef struct node {
    veicolo veicoli;
    struct node *next;
} *list;

// Funzioni di accesso alla lista
list getListaVeicoli(void);
void setListaVeicoli(list nuovaLista);
void salvaListaVeicoli(void);
void caricaListaVeicoli(void);
void pulisciListaVeicoli(void);

// Funzioni di gestione veicoli
list creaLista(void);
veicolo creaVeicolo(void);
list aggiungiVeicolo(list);
list rimuoviVeicolo(list);
void stampaVeicolo(veicolo);
void salvaVeicoloFile(list);
list caricaVeicoloFile(list);
int caricaUltimoID(void);

#endif
