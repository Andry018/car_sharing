#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vehicle.h"

struct node
{
    veicolo veicoli;
    struct node *next;
};
list creaLista()
{
    return NULL; // crea lista che punta a null
}

veicolo creaVeicolo()
{
    veicolo v;
    static int id = 0; // variabile per id

    if (id == 0)
    {
        printf("Caricamento dell'ultimo ID...\n");
        id = caricaVeicoliFile(&listaVeicoli); // file a lista
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
    struct node *nuovo = (struct node *)malloc(sizeof(struct node));
    veicolo v = creaVeicolo();
    nuovo->veicoli = v;
    nuovo->next = l;
    return nuovo; // aggiunge il nuovo veicolo alla lista;
}

list rimuoviVeicolo(list l)
{
    struct node *p = l;
    struct node *prev = NULL;
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
