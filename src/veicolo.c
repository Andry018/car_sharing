#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "tariffe.h"
#include "f_utili.h"

// Definizioni private delle strutture
struct Veicolo {
    int id;
    int tipo;
    char modello[50];
    char targa[10];
    int posizione;
    int disponibilita;
};

typedef struct node {
    Veicolo v;
    struct node* next;
} node;

// Variabile statica per la lista dei veicoli
static list listaVeicoli = NULL;

// Implementazione delle funzioni di accesso alla lista
list get_lista_veicoli(void) {
    return listaVeicoli;
}

void set_lista_veicoli(list nuovaLista) {
    listaVeicoli = nuovaLista;
}

// Implementazione dei getter
int get_id_veicolo(Veicolo v) {
    return v->id;
}

int get_tipo_veicolo(Veicolo v) {
    return v->tipo;
}

const char* get_modello_veicolo(Veicolo v) {
    return v->modello;
}

const char* get_targa_veicolo(Veicolo v) {
    return v->targa;
}

int get_posizione_veicolo(Veicolo v) {
    return v->posizione;
}

int get_disponibilita_veicolo(Veicolo v) {
    return v->disponibilita;
}

// Implementazione dei setter
void set_id_veicolo(Veicolo v, int id) {
    v->id = id;
}

void set_tipo_veicolo(Veicolo v, int tipo) {
    v->tipo = tipo;
}

void set_modello_veicolo(Veicolo v, const char* modello) {
    strncpy(v->modello, modello, sizeof(v->modello) - 1);
    v->modello[sizeof(v->modello) - 1] = '\0';
}

void set_targa_veicolo(Veicolo v, const char* targa) {
    strncpy(v->targa, targa, sizeof(v->targa) - 1);
    v->targa[sizeof(v->targa) - 1] = '\0';
}

void set_posizione_veicolo(Veicolo v, int posizione) {
   v->posizione = posizione;
}

void set_disponibilita_veicolo(Veicolo v, int disponibilita) {
    v->disponibilita = disponibilita;
}

// Funzioni di gestione veicoli
Veicolo crea_veicolo(void) {
    Veicolo v = malloc(sizeof(struct Veicolo));
    if (v == NULL) {
        return NULL;
    }
    v->id = 0;
    v->tipo = 0;
    v->disponibilita = 1;
    memset(v->modello, 0, sizeof(v->modello));
    memset(v->targa, 0, sizeof(v->targa));
    v->posizione = 0; 
    return v;
}

list aggiungi_veicolo(list l) {
    Veicolo v = crea_veicolo();
    if (v == NULL) {
        return l;
    }

    // Input tipo veicolo con validazione
    int tipo_valido = 0;
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        set_color(13); // Magenta
        printf("         AGGIUNGI VEICOLO\n");
        stampa_separatore();
        set_color(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        set_color(7); // Bianco
        stampa_data_sistema();
        stampa_separatore();
        set_color(10); // Verde
        printf("     INSERIMENTO DATI VEICOLO\n");
        set_color(7); // Bianco

        printf("Tipo veicolo:\n");
        printf("0. Utilitaria\n");
        printf("1. SUV\n");
        printf("2. Sportiva\n");
        printf("3. Moto\n");
        printf("Scelta: ");
        if (scanf("%d", &v->tipo) != 1 || v->tipo < 0 || v->tipo > 3) {
            set_color(12); // Rosso
            printf("Tipo non valido. Riprova.\n");
            svuota_buffer();
            set_color(7); // Bianco
            while (getchar() != '\n'); // Pulisci buffer
            // Il ciclo riparte e il menu viene ridisegnato pulito
        } else {
            tipo_valido = 1;
            getchar(); // Consuma il newline
        }
    } while (!tipo_valido);

    // Input modello con validazione
    do {
        printf("\nModello: ");
        fgets(v->modello, sizeof(v->modello), stdin);
        v->modello[strcspn(v->modello, "\n")] = 0;
        if (strlen(v->modello) == 0) {
            printf("Il modello non può essere vuoto. Riprova.\n");
        }
    } while (strlen(v->modello) == 0);

    // Input targa con validazione
    int targa_valida = 0;
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        set_color(13); // Magenta
        printf("         AGGIUNGI VEICOLO\n");
        stampa_separatore();
        set_color(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        set_color(7); // Bianco
        stampa_data_sistema();
        stampa_separatore();
        set_color(10); // Verde
        printf("     INSERIMENTO DATI VEICOLO\n");
        set_color(7); // Bianco;

        printf("Tipo veicolo: %s\n", get_nome_tipo_veicolo(v->tipo));
        printf("Modello: %s\n", v->modello);

        printf("Targa: ");
        fgets(v->targa, sizeof(v->targa), stdin);

        // Se manca il newline, svuota il buffer
        if (strchr(v->targa, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        v->targa[strcspn(v->targa, "\n")] = 0;

        if (strlen(v->targa) == 0) {
            set_color(12); // Rosso
            printf("La targa non può essere vuota. Premi INVIO per riprovare.\n");
            set_color(7); // Bianco
            getchar(); // Attendi INVIO
        } else if (strlen(v->targa) < 7) {
            set_color(12); // Rosso
            printf("La targa inserita non è valida (deve essere di 7 caratteri). Premi INVIO per riprovare.\n");
            set_color(7); // Bianco
            getchar(); // Attendi INVIO
        } else if (strlen(v->targa) > 7) {
            set_color(12); // Rosso
            printf("La targa non può superare 7 caratteri. Premi INVIO per riprovare.\n");
            set_color(7); // Bianco
            getchar(); // Attendi INVIO
        } else {
            targa_valida = 1;
        }
    } while (!targa_valida);

    // Input posizione
    v->posizione = 0; // Inizializza a 0

    v->id = carica_ultimo_id() + 1;
    v->disponibilita = 1;

    list newNode = (list)malloc(sizeof(struct node));
    if (newNode == NULL) {
        free(v);
        return l;
    }

    newNode->v = v;
    newNode->next = l;
    return newNode;
}

list rimuovi_veicolo(list l, int id)
{
    if (l == NULL) return NULL;
    
    // Caso 1: Il veicolo da rimuovere è il primo della lista
    if (l->v != NULL && l->v->id == id)
    {
        list temp = l->next;
        free(l->v);  // Libera la memoria del veicolo
        free(l);     // Libera la memoria del nodo della lista
        return temp;
    }
    
    // Caso 2: Il veicolo da rimuovere è in una posizione successiva
    list temp = l;
    while (temp->next != NULL)
    {
        if (temp->next->v != NULL && temp->next->v->id == id)
        {
            list da_rimuovere = temp->next;
            temp->next = temp->next->next;
            free(da_rimuovere->v);  // Libera la memoria del veicolo
            free(da_rimuovere);     // Libera la memoria del nodo della lista
            return l;
        }
        temp = temp->next;
    }
    
    // Il veicolo non è stato trovato
    return l;
}

void stampa_veicolo(Veicolo v) {
    if (v == NULL) return;
    
    set_color(7); // Bianco
    printf("  ID: %d\n", v->id);
    printf("  Modello: %s\n", v->modello);
    printf("  Targa: %s\n", v->targa);
    
    set_color(10); // Verde
    printf("  Tipo: %s\n", get_nome_tipo_veicolo(v->tipo));
    
    set_color(7); // Bianco
    printf("\n");
    
    printf("  Stato: ");
    if(v->disponibilita) {
        set_color(10); // Verde
        printf("Disponibile");
    } else {
        set_color(12); // Rosso
        printf("Non disponibile");
    }

    set_color(14); // Giallo
    printf("  Posizione: %s\n", get_nome_posizione_veicolo(v->posizione)); 
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
    
    list temp = l;
    while (temp != NULL)
    {
        // Uso il carattere '|' come separatore per evitare problemi con gli spazi
        fprintf(fp, "%d|%d|%s|%s|%d|%d\n", 
            temp->v->id,
            temp->v->tipo,
            temp->v->modello,
            temp->v->targa,
            temp->v->posizione,
            temp->v->disponibilita);
        temp = temp->next;
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
        Veicolo v = malloc(sizeof(struct Veicolo));
        if (v == NULL) {
            printf("Errore nell'allocazione della memoria.\n");
            continue;
        }
        
        // Uso '|' come separatore
        char* token = strtok(line, "|");
        if (token != NULL) {
            v->id = atoi(token);
            
            token = strtok(NULL, "|");
            if (token != NULL) {
                v->tipo = atoi(token);
                
                token = strtok(NULL, "|");
                if (token != NULL) {
                    strncpy(v->modello, token, sizeof(v->modello) - 1);
                    v->modello[sizeof(v->modello) - 1] = '\0';
                    
                    token = strtok(NULL, "|");
                    if (token != NULL) {
                        strncpy(v->targa, token, sizeof(v->targa) - 1);
                        v->targa[sizeof(v->targa) - 1] = '\0';
                        
                        token = strtok(NULL, "|");
                        if (token != NULL) {
                            v->posizione = atoi(token);
                            
                            token = strtok(NULL, "|");
                            if (token != NULL) {
                                v->disponibilita = atoi(token);
                                
                                // Aggiunge il veicolo alla lista
                                list nuovo = (list)malloc(sizeof(struct node));
                                if (nuovo != NULL) {
                                    nuovo->v = v;
                                    nuovo->next = l;
                                    l = nuovo;
                                } else {
                                    free(v);  // Libera il veicolo solo se non è stato aggiunto alla lista
                                }
                            }
                        }
                    }
                }
            }
        }
        if (v != NULL && l == NULL) {  // Se il veicolo non è stato aggiunto alla lista
            free(v);
        }
    }
    fclose(fp);
    return l;
}

list get_next_node(list l) {
    return l->next;
}

Veicolo get_veicolo_da_lista(list *l) {
    if (*l == NULL) {
        return NULL;
    }
    Veicolo v = (*l)->v;
    list temp = *l;
    *l = (*l)->next;
    free(temp);     // Libera solo la memoria del nodo
    return v;       // Restituisce il veicolo senza liberarlo
}

// Funzioni di ricerca
Veicolo cerca_veicolo(list l, int id) {
    while (l != NULL) {
        if (l->v->id == id) {
            return l->v;
        }
        l = l->next;
    }
    return NULL;
}

void modifica_veicolo(list l, int id) {
    Veicolo v = cerca_veicolo(l, id);
    if (v == NULL) {
        printf("Veicolo non trovato\n");
        return;
    }

    printf("Modifica veicolo %d\n", id);
    printf("Nuovo tipo (0: Utilitaria, 1: SUV, 2: Sportiva, 3: Moto): ");
    int tipo;
    scanf("%d", &tipo);
    getchar();
    set_tipo_veicolo(v, tipo);

    printf("Nuovo modello: ");
    char modello[50];
    fgets(modello, sizeof(modello), stdin);
    modello[strcspn(modello, "\n")] = 0;
    set_modello_veicolo(v, modello);

    printf("Nuova targa: ");
    char targa[10];
    fgets(targa, sizeof(targa), stdin);
    targa[strcspn(targa, "\n")] = 0;
    set_targa_veicolo(v, targa);

    printf("Nuova posizione: (0: Deposito, 1: Posizione B, 2: Posizione C, 3: Posizione D): ");
    int posizione;
    scanf("%d", &posizione);
    getchar();
    set_posizione_veicolo(v, posizione);
}

void stampa_lista_veicoli(list l)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nLista dei veicoli:\n");
    list temp = l;
    while (temp != NULL)
    {
        stampa_veicolo(temp->v);
        stampa_separatore();
        temp = temp->next;
    }
}

void stampa_veicoli_disponibili(list l)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli disponibili:\n");
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->disponibilita)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo disponibile al momento.\n");
    }
}

void stampa_veicoli_non_disponibili(list l)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli non disponibili:\n");
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (!temp->v->disponibilita)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Tutti i veicoli sono disponibili.\n");
    }
}

void stampa_veicoli_per_tipo(list l, int tipo)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo ");
    switch(tipo) {
        case 0:
            printf("Utilitaria");
            break;
        case 1:
            printf("SUV");
            break;
        case 2:
            printf("Sportiva");
            break;
        case 3:
            printf("Moto");
            break;
    }
    printf(":\n");
    
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->tipo == tipo)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo presente.\n");
    }
}

void stampa_veicoli_per_posizione(list l, int posizione)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli nella posizione %s:\n", get_nome_posizione_veicolo(posizione));
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->posizione == posizione)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo presente in questa posizione.\n");
    }
}

void stampa_veicoli_per_modello(list l, const char* modello)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli con modello %s:\n", modello);
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (strcmp(temp->v->modello, modello) == 0)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo con questo modello presente.\n");
    }
}

void stampa_veicoli_per_targa(list l, const char* targa)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli con targa %s:\n", targa);
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (strcmp(temp->v->targa, targa) == 0)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo con questa targa presente.\n");
    }
}

void stampa_veicoli_per_id(list l, int id)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli con ID %d:\n", id);
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->id == id)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo con questo ID presente.\n");
    }
}

void stampa_veicoli_per_tipo_e_posizione(list l, int tipo, int posizione)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo %s", get_nome_tipo_veicolo(tipo));
    
    printf(" nella posizione %s:\n", get_nome_posizione_veicolo(posizione));
    
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->tipo == tipo && temp->v->posizione == posizione)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo presente in questa posizione.\n");
    }
}

void stampa_veicoli_per_tipo_e_disponibilita(list l, int tipo, bool disponibile)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo %s", get_nome_tipo_veicolo(tipo));
   
    printf(" %s:\n", disponibile ? "disponibili" : "non disponibili");
    
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->tipo == tipo && temp->v->disponibilita == disponibile)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo %s.\n", disponibile ? "disponibile" : "non disponibile");
    }
}

void stampa_veicoli_per_posizione_e_disponibilita(list l, int posizione, bool disponibile)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli nella posizione %s %s:\n", get_nome_posizione_veicolo(posizione), disponibile ? "disponibili" : "non disponibili");
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->posizione == posizione && temp->v->disponibilita == disponibile)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo %s in questa posizione.\n", disponibile ? "disponibile" : "non disponibile");
    }
}

void stampa_veicoli_per_tipo_posizione_e_disponibilita(list l, int tipo, int posizione, bool disponibile)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo %s", get_nome_tipo_veicolo(tipo));
    
    
    printf(" nella posizione %s %s:\n", get_nome_posizione_veicolo(posizione), disponibile ? "disponibili" : "non disponibili");
    
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->tipo == tipo && temp->v->posizione == posizione && temp->v->disponibilita == disponibile)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->next;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo %s in questa posizione.\n", disponibile ? "disponibile" : "non disponibile");
    }
}

// Funzione per ottenere il nome del tipo di veicolo
const char* get_nome_tipo_veicolo(int tipo) {
    switch (tipo) {
        case 0:
            return "Utilitaria";
        case 1:
            return "SUV";
        case 2:
            return "Sportiva";
        case 3:
            return "Moto";
        default:
            return "Tipo non valido";
    }
}

void carica_lista_veicoli(void) {
    listaVeicoli = carica_veicolo_file(listaVeicoli);
}

void salva_lista_veicoli(void) {
    salva_veicolo_file(listaVeicoli);
}

void pulisci_lista_veicoli(void) {
    list current = listaVeicoli;
    while (current != NULL) {
        list next = current->next;
        free(current->v);
        free(current);
        current = next;
    }
    listaVeicoli = NULL;
}
int carica_ultimo_id(){
    FILE *fp = fopen("data/veicoli.txt", "r");
    if (fp == NULL) {
        printf("Il file non esiste.\n");
        return 0; // Se il file non esiste, ritorna 0
    }
    int id = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        id++;
    }
    fclose(fp);
    return id;
}

Veicolo get_veicolo_senza_rimuovere(list l) {
    if (l == NULL) {
        return NULL;
    }
    return l->v;
}
  
const char* get_nome_posizione_veicolo(int posizione) {
    switch (posizione) {
        case 0:
            return "Deposito";
        case 1:
            return "Posizione B";
        case 2:
            return "Posizione C";
        case 3:
            return "Posizione D";
        default:
            return "Posizione sconosciuta";
    }
    
}

 list aggiungi_veicolo_test(list l, Veicolo v) {
       list nuovo = malloc(sizeof(struct node));
       if (!nuovo) return l;
       nuovo->v = v;
       nuovo->next = l;
       return nuovo;
   }