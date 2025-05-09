#ifndef VEHICLE_C
#define VEHICLE_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char categoria[20]; // 0: Utilitaria | 1: SUV | 2: Sportiva | 3: Elettrico | 4: Moto
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
list getListaVeicoli(void);
void setListaVeicoli(list nuovaLista);
void salvaListaVeicoli(void);
void caricaListaVeicoli(void);
void pulisciListaVeicoli(void);

// Funzioni di gestione veicoli

veicolo creaVeicolo(void);
list aggiungiVeicolo(list);
list rimuoviVeicolo(list);
void stampaVeicolo(veicolo);
void salvaVeicoloFile(list);
list caricaVeicoloFile(list);
int caricaUltimoID(void);

#endif
