#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vehicle.h"

// Variabile privata
static list listaVeicoli = NULL;

// Funzioni di accesso
list getListaVeicoli(void) {
    return listaVeicoli;
}

void setListaVeicoli(list nuovaLista) {
    listaVeicoli = nuovaLista;
}

void salvaListaVeicoli(void) {
    salvaVeicoloFile(listaVeicoli);
}

void caricaListaVeicoli(void) {
    listaVeicoli = caricaVeicoloFile(listaVeicoli);
}

void pulisciListaVeicoli(void) {
    while(listaVeicoli != NULL) {
        list temp = listaVeicoli;
        listaVeicoli = listaVeicoli->next;
        free(temp);
    }
}

list creaLista()
{
    return NULL; // crea lista che punta a null
}

int caricaUltimoID()
{
    FILE *fp = fopen("veicoli.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }
    
    int max_id = 0;
    veicolo v;
    while (fscanf(fp, "%d %d %s %s %s %d\n", 
                  &v.id, 
                  &v.tipologia, 
                  v.modello, 
                  v.targa, 
                  v.posizione, 
                  &v.disponibile) != EOF) {
        if (v.id > max_id) {
            max_id = v.id;
        }
    }
    fclose(fp);
    return max_id;
}

veicolo creaVeicolo()
{
    veicolo v;
    static int id = 0; // variabile per id

    if (id == 0)
    {
        printf("Caricamento dell'ultimo ID...\n");
        id = caricaUltimoID();
    }

    id++;
    v.id = id;

    printf("Inserisci tipologia del veicolo: (0 = Autoveicolo | 1 = Motociclo) ");
    scanf("%d", &v.tipologia);
    printf("Inserisci modello del veicolo: ");
    scanf("%s", v.modello);
    printf("Inserisci targa del veicolo: ");
    scanf("%s", v.targa);
    strcpy(v.posizione, "Deposito");
    v.disponibile = true;

    return v;
}

list aggiungiVeicolo(list l)
{
    list nuovo = (list)malloc(sizeof(struct node));
    veicolo v = creaVeicolo();
    nuovo->veicoli = v;
    nuovo->next = l;
    return nuovo; // aggiunge il nuovo veicolo alla lista;
}

list rimuoviVeicolo(list l)
{
    list p = l;
    list prev = NULL;
    printf("Inserisci l'id del veicolo da eliminare: ");
    int id;
    scanf("%d", &id);

    while (p != NULL)
    {
        if (p->veicoli.id == id)
        {
            if (prev == NULL)
            {
                l = p->next;
            }
            else
            {
                prev->next = p->next;
            }
            free(p);
            printf("Veicolo con ID %d rimosso.\n", id);
            return l;
        }
        prev = p;
        p = p->next;
    }

    printf("Veicolo con ID %d non trovato.\n", id);
    return l;
}

void stampaVeicolo(veicolo v)
{
    printf("ID: %d\n", v.id);
    printf("Tipologia: %d\n", v.tipologia);
    printf("Modello: %s \n", v.modello);
    printf("Targa: %s\n", v.targa);
    printf("Posizione: %s\n", v.posizione);
    printf("Disponibile: %s\n", v.disponibile ? "true" : "false");
}

void salvaVeicoloFile(list l)
{
    FILE *fp = fopen("veicoli.txt", "w");
    if (fp == NULL)
    {
        printf("Impossibile aprire il file.\n");
        return;
    }
    while (l != NULL)
    {
        fprintf(fp, "%d %d %s %s %s %d\n",
                l->veicoli.id,
                l->veicoli.tipologia,
                l->veicoli.modello,
                l->veicoli.targa,
                l->veicoli.posizione,
                l->veicoli.disponibile);
        l = l->next;
    }
    fclose(fp);
    printf("Veicoli salvati nel file veicoli.txt\n");
}

list caricaVeicoloFile(list l)
{
    FILE *fp = fopen("veicoli.txt", "r");
    if (fp == NULL)
    {
        printf("Impossibile aprire il file.\n");
        return l;
    }
    
    veicolo v;
    while (fscanf(fp, "%d %d %s %s %s %d\n", 
                  &v.id, 
                  &v.tipologia, 
                  v.modello, 
                  v.targa, 
                  v.posizione, 
                  &v.disponibile) != EOF) {
        list nuovo = (list)malloc(sizeof(struct node));
        nuovo->veicoli = v;
        nuovo->next = l;
        l = nuovo;
    }
    
    fclose(fp);
    return l;
}
