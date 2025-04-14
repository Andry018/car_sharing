#include <stdio.h>
#include <stdlib.h>
#ifndef VEHICLE_C
#define VEHICLE_C
typedef struct node *list;

typedef struct {
    int id;
    int tipologia;    // 0 = Autoveicolo      1 = Motociclo
    char modello[30]; // Così facciamo contento a gabriele
    char targa[7];
    char posizione[50]; 
    bool disponibile; // 0 = non disponibile | 1 = disponibile
} veicolo;


list creaLista(void);
veicolo creaVeicolo(void);
list aggiungiVeicolo(list);
list rimuoviVeicolo(list);
void stampaVeicolo(veicolo);
void salvaVeicoloFile(list);
void caricaVeicoloFile();
void listaVeicoli(FILE);

#endif
