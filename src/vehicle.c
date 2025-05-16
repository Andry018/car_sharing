#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vehicle.h"
#include "tariffe.h"

// Dichiarazione della funzione set_color
void set_color(int color);

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
    char line[256];
    
    while (fgets(line, sizeof(line), fp)) {
        int id;
        if (sscanf(line, "%d", &id) == 1) {
            if (id > max_id) {
                max_id = id;
            }
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
    printf("Inserisci categoria del veicolo:\n");
    printf("0: Utilitaria (%.2f euro/ora)\n", TARIFFA_UTILITARIA);
    printf("1: SUV (%.2f euro/ora)\n", TARIFFA_SUV);
    printf("2: Sportiva (%.2f euro/ora)\n", TARIFFA_SPORTIVA);
    printf("3: Moto (%.2f euro/ora)\n", TARIFFA_MOTO);
    printf("Scelta: ");
    scanf("%d", &scelta);
    
    switch (scelta) {
        case 0:
            v.tipo = UTILITARIA;
            break;
        case 1:
            v.tipo = SUV;
            break;
        case 2:
            v.tipo = SPORTIVA;
            break;
        case 3:
            v.tipo = MOTO;
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

void stampa_veicolo(veicolo v) {
    set_color(7); // Bianco
    printf("  ID: %d\n", v.id);
    printf("  Modello: %s\n", v.modello);
    printf("  Targa: %s\n", v.targa);
    
    printf("  Tipo: ");
    switch(v.tipo) {
        case UTILITARIA:
            set_color(10); // Verde
            printf("%s", "Utilitaria");
            break;
        case SUV:
            set_color(14); // Giallo
            printf("%s", "SUV");
            break;
        case SPORTIVA:
            set_color(12); // Rosso
            printf("%s", "Sportiva");
            break;
        case MOTO:
            set_color(11); // Ciano
            printf("%s", "Moto");
            break;
    }
    set_color(7); // Bianco
    printf("\n");
    
    printf("  Stato: ");
    if(v.disponibile) {
        set_color(10); // Verde
        printf("Disponibile");
    } else {
        set_color(12); // Rosso
        printf("Non disponibile");
    }
    set_color(7); // Bianco
    printf("\n");
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
        fprintf(fp, "%d %d %s %s %s %d\n",
                l->veicoli.id,
                l->veicoli.tipo,
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
    
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        veicolo v;
        char* token = strtok(line, " ");  // Legge ID
        
        if (token != NULL) {
            v.id = atoi(token);
            
            // Legge tipo veicolo
            token = strtok(NULL, " ");
            if (token != NULL) {
                v.tipo = (TipoVeicolo)atoi(token);
                
                // Legge modello (può contenere spazi)
                token = strtok(NULL, " ");
                if (token != NULL) {
                    char temp_modello[30] = "";
                    while (token != NULL) {
                        // Cerca la targa (che inizia sempre con una lettera)
                        if (strlen(token) == 7 && ((token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z'))) {
                            strcpy(v.targa, token);
                            break;
                        }
                        // Altrimenti è parte del modello
                        if (strlen(temp_modello) > 0) {
                            strcat(temp_modello, " ");
                        }
                        strcat(temp_modello, token);
                        token = strtok(NULL, " ");
                    }
                    strcpy(v.modello, temp_modello);
                    
                    // Legge posizione
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        strcpy(v.posizione, token);
                        
                        // Legge disponibilità
                        token = strtok(NULL, " ");
                        if (token != NULL) {
                            v.disponibile = atoi(token);
                            
                            // Aggiunge il veicolo alla lista
                            list nuovo = (list)malloc(sizeof(struct node));
                            if (nuovo != NULL) {
                                nuovo->veicoli = v;
                                nuovo->next = l;
                                l = nuovo;
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    return l;
}
