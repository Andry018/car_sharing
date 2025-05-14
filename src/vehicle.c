#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vehicle.h"

// Variabile privata
static list listaVeicoli = NULL;

// Funzioni di accesso
list get_lista_veicoli(void) {
    return listaVeicoli;
}

void set_lista_veicoli(list nuovaLista) {
    listaVeicoli = nuovaLista;
}

void salva_lista_veicoli(void) {
    salva_veicolo_file(listaVeicoli);
}

void carica_lista_veicoli(void) {
    listaVeicoli = carica_veicolo_file(listaVeicoli);
}

void pulisci_lista_veicoli(void) {
    while(listaVeicoli != NULL) {
        list temp = listaVeicoli;
        listaVeicoli = listaVeicoli->next;
        free(temp);
    }
}


int carica_ultimo_id()
{
    FILE *fp = fopen("data/veicoli.txt", "r");
    if (fp == NULL)
    {
        return 0;
    }
    
    int max_id = 0;
    veicolo v;
    while (fscanf(fp, "%d %s %s %s %s %d\n", 
                  &v.id, 
                  v.categoria, 
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

veicolo crea_veicolo()
{
    veicolo v;
    static int id = 0; // variabile per id

    if (id == 0)
    {
        printf("Caricamento dell'ultimo ID...\n");
        id = carica_ultimo_id();
    }

    id++;
    v.id = id;
    int scelta;
    printf("Inserisci categoria del veicolo: \n (0 = Utilitaria | 1 = SUV | 2 = Sportiva | 3 = Elettrico | 4 = Moto) ");
    scanf("%d", &scelta);
    switch (scelta) {
        case 0:
            strcpy(v.categoria, "Utilitaria");
            break;
        case 1:
            strcpy(v.categoria, "SUV");
            break;
        case 2:
            strcpy(v.categoria, "Sportiva");
            break;
        case 3:
            strcpy(v.categoria, "Elettrico");
            break;
        case 4:
            strcpy(v.categoria, "Moto");
            break;
        default:
            printf("Categoria non valida.\n");
            return crea_veicolo();
    }
    getchar(); //libera buffer
    printf("Inserisci modello del veicolo: ");
    if (fgets(v.modello, 30, stdin) == NULL) {
        printf("Errore nella lettura del modello.\n");
        strcpy(v.modello, "Sconosciuto");
    }
    v.modello[strcspn(v.modello, "\n")] = 0; // TERMINATORE
    printf("Inserisci targa del veicolo: ");
    if (scanf("%7s", v.targa) != 1) {
        printf("Errore nella lettura della targa.\n");
        strcpy(v.targa, "XXXXXXX");
    }
    v.targa[7] = '\0';    // terminatore
    strcpy(v.posizione, "Deposito");
    v.disponibile = 1;

    return v;
}

list aggiungi_veicolo(list l)
{
    list nuovo = (list)malloc(sizeof(struct node));
    if (nuovo == NULL) {
        printf("Errore nell'allocazione della memoria.\n");
        return l;
    }
    veicolo v = crea_veicolo();
    nuovo->veicoli = v;
    nuovo->next = l;
    return nuovo;
}

list rimuovi_veicolo(list l)
{
    if (l == NULL) {
        printf("La lista dei veicoli è vuota.\n");
        return l;
    }

    list p = l;
    list prev = NULL;
    printf("Inserisci l'id del veicolo da eliminare: ");
    int id;
    scanf("%d", &id);

    bool trovato = false;
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
            printf("Veicolo con ID %d rimosso con successo.\n", id);
            trovato = true;
            break;
        }
        prev = p;
        p = p->next;
    }

    if (!trovato) {
        printf("ERRORE: Veicolo con ID %d non trovato nella lista.\n", id);
    }
    return l;
}

void stampa_veicolo(veicolo v)
{
    printf("ID: %d\n", v.id);
    printf("Categoria: %s\n", v.categoria);
    printf("Modello: %s \n", v.modello);
    printf("Targa: %s\n", v.targa);
    printf("Posizione: %s\n", v.posizione);
    if (v.disponibile == 1) {
        printf("Disponibile: Si\n");
    } else {
        printf("Disponibile: No\n");
    }
}

void salva_veicolo_file(list l)
{
    FILE *fp = fopen("data/veicoli.txt", "w");
    if (fp == NULL)
    {
        printf("Impossibile aprire il file.\n");
        return;
    }
    while (l != NULL)
    {
        fprintf(fp, "%d %s %s %s %s %d\n",
                l->veicoli.id,
                l->veicoli.categoria,
                l->veicoli.modello,
                l->veicoli.targa,
                l->veicoli.posizione,
                l->veicoli.disponibile);
        l = l->next;
    }
    fclose(fp);
    printf("Veicoli salvati nel file data/veicoli.txt\n");
}

list carica_veicolo_file(list l)
{
    FILE *fp = fopen("data/veicoli.txt", "r");
    if (fp == NULL)
    {
        printf("Impossibile aprire il file.\n");
        return l;
    }
    
    veicolo v;
    while (fscanf(fp, "%d %s %s %s %s %d\n", 
                  &v.id, 
                  v.categoria, 
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
