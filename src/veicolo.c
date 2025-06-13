/**
 * @file veicolo.c
 * @brief Implementazione delle funzioni di gestione dei veicoli per il sistema di car sharing.
 *
 * Questo file contiene le funzioni per la creazione, modifica, ricerca e gestione dei veicoli.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "veicolo.h"
#include "tariffe.h"
#include "f_utili.h"

/**
 * @struct Veicolo
 * @brief Rappresenta un veicolo nel sistema di car sharing.
 *
 * Contiene tutte le informazioni necessarie per identificare e gestire un veicolo.
 *
 * @var Veicolo::id
 * Identificativo univoco del veicolo.
 * @var Veicolo::tipo
 * Tipo del veicolo (es. utilitaria, suv, sportiva, moto).
 * @var Veicolo::modello
 * Modello del veicolo (stringa).
 * @var Veicolo::targa
 * Targa del veicolo (stringa).
 * @var Veicolo::posizione
 * Identificativo della posizione o stazione del veicolo.
 * @var Veicolo::disponibilita
 * Stato di disponibilità (1 = disponibile, 0 = non disponibile).
 */
struct Veicolo {
    int id;
    int tipo;
    char modello[50];
    char targa[10];
    int posizione;
    int disponibilita;
};

/**
 * @struct nodo
 * @brief Nodo di una lista collegata di veicoli.
 *
 * Ogni nodo contiene un veicolo e un puntatore al nodo successivo.
 *
 * @var nodo::v
 * Dati del veicolo associato al nodo.
 * @var nodo::successivo
 * Puntatore al prossimo nodo della lista.
 */
typedef struct nodo {
    Veicolo v;
    struct nodo* successivo;
} nodo;

// Variabile statica per la lista dei veicoli
static list listaVeicoli = NULL;

/**
 * @brief Restituisce la lista attuale dei veicoli.
 * @return Puntatore alla lista dei veicoli.
 */
list ottieni_lista_veicoli(void) {
    return listaVeicoli;
}

/**
 * @brief Imposta la lista dei veicoli.
 * @param nuovaLista Nuova lista da impostare.
 * @note Side Effect: Sovrascrive la lista globale dei veicoli.
 */
void imposta_lista_veicoli(list nuovaLista) {
    listaVeicoli = nuovaLista;
}

/**
 * @brief Restituisce l'ID del veicolo.
 * @param v Puntatore al veicolo.
 * @return ID del veicolo.
 * @pre v != NULL
 */
int ottieni_id_veicolo(Veicolo v) {
    return v->id;
}

/**
 * @brief Restituisce il tipo del veicolo.
 * @param v Puntatore al veicolo.
 * @return Tipo del veicolo.
 * @pre v != NULL
 */
int ottieni_tipo_veicolo(Veicolo v) {
    return v->tipo;
}

/**
 * @brief Restituisce il modello del veicolo.
 * @param v Puntatore al veicolo.
 * @return Modello del veicolo (stringa).
 * @pre v != NULL
 */
const char* ottieni_modello_veicolo(Veicolo v) {
    return v->modello;
}

/**
 * @brief Restituisce la targa del veicolo.
 * @param v Puntatore al veicolo.
 * @return Targa del veicolo (stringa).
 * @pre v != NULL
 */
const char* ottieni_targa_veicolo(Veicolo v) {
    return v->targa;
}

/**
 * @brief Restituisce la posizione del veicolo.
 * @param v Puntatore al veicolo.
 * @return Posizione del veicolo.
 * @pre v != NULL
 */
int ottieni_posizione_veicolo(Veicolo v) {
    return v->posizione;
}

/**
 * @brief Restituisce la disponibilità del veicolo.
 * @param v Puntatore al veicolo.
 * @return Disponibilità del veicolo (1 = disponibile, 0 = non disponibile).
 * @pre v != NULL
 */
int ottieni_disponibilita_veicolo(Veicolo v) {
    return v->disponibilita;
}

/**
 * @brief Imposta l'ID del veicolo.
 * @param v Puntatore al veicolo.
 * @param id Nuovo ID da impostare.
 * @pre v != NULL
 * @note Side Effect: Modifica il campo id del veicolo.
 */
void imposta_id_veicolo(Veicolo v, int id) {
    v->id = id;
}

/**
 * @brief Imposta il tipo del veicolo.
 * @param v Puntatore al veicolo.
 * @param tipo Nuovo tipo da impostare.
 * @pre v != NULL
 * @note Side Effect: Modifica il campo tipo del veicolo.
 */
void imposta_tipo_veicolo(Veicolo v, int tipo) {
    v->tipo = tipo;
}

/**
 * @brief Imposta il modello del veicolo.
 * @param v Puntatore al veicolo.
 * @param modello Nuovo modello da impostare (stringa).
 * @pre v != NULL
 * @note Side Effect: Modifica il campo modello del veicolo.
 */
void imposta_modello_veicolo(Veicolo v, const char* modello) {
    strncpy(v->modello, modello, sizeof(v->modello) - 1);
    v->modello[sizeof(v->modello) - 1] = '\0';
}

/**
 * @brief Imposta la targa del veicolo.
 * @param v Puntatore al veicolo.
 * @param targa Nuova targa da impostare (stringa).
 * @pre v != NULL
 * @note Side Effect: Modifica il campo targa del veicolo.
 */
void imposta_targa_veicolo(Veicolo v, const char* targa) {
    strncpy(v->targa, targa, sizeof(v->targa) - 1);
    v->targa[sizeof(v->targa) - 1] = '\0';
}

/**
 * @brief Imposta la posizione del veicolo.
 * @param v Puntatore al veicolo.
 * @param posizione Nuova posizione da impostare.
 * @pre v != NULL
 * @note Side Effect: Modifica il campo posizione del veicolo.
 */
void imposta_posizione_veicolo(Veicolo v, int posizione) {
   v->posizione = posizione;
}

/**
 * @brief Imposta la disponibilità del veicolo.
 * @param v Puntatore al veicolo.
 * @param disponibilita Nuovo stato di disponibilità.
 * @pre v != NULL
 * @note Side Effect: Modifica il campo disponibilita del veicolo.
 */
void imposta_disponibilita_veicolo(Veicolo v, int disponibilita) {
    v->disponibilita = disponibilita;
}

/**
 * @brief Crea un nuovo veicolo con valori di default.
 * @return Puntatore al nuovo veicolo, oppure NULL in caso di errore.
 * @note Side Effect: Alloca memoria per un nuovo veicolo.
 */
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

/**
 * @brief Aggiunge un nuovo veicolo alla lista.
 * @param l Lista dei veicoli.
 * @return Nuova lista con il veicolo aggiunto.
 * @note Side Effect: Alloca memoria per il nuovo veicolo e nodo.
 */
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
        imposta_colore(13); // Magenta
        printf("         AGGIUNGI VEICOLO\n");
        stampa_separatore();
        imposta_colore(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        imposta_colore(7); // Bianco
        stampa_data_sistema();
        stampa_separatore();
        imposta_colore(10); // Verde
        printf("     INSERIMENTO DATI VEICOLO\n");
        imposta_colore(7); // Bianco

        printf("Tipo veicolo:\n");
        printf("0. Utilitaria\n");
        printf("1. SUV\n");
        printf("2. Sportiva\n");
        printf("3. Moto\n");
        printf("Scelta: ");
        if (scanf("%d", &v->tipo) != 1 || v->tipo < 0 || v->tipo > 3) {
            imposta_colore(12); // Rosso
            printf("Tipo non valido. Riprova.\n");
            svuota_buffer();
            imposta_colore(7); // Bianco
            while (getchar() != '\n'); // Pulisci buffer
            // Il ciclo riparte e il menu viene ridisegnato pulito
        } else {
            tipo_valido = 1;
            getchar(); // Consuma la nuova linea
        }
    } while (!tipo_valido);

    // Input modello con validazione
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        imposta_colore(13); // Magenta
        printf("         AGGIUNGI VEICOLO\n");
        stampa_separatore();
        imposta_colore(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        imposta_colore(7); // Bianco
        stampa_data_sistema();
        stampa_separatore();
        imposta_colore(10); // Verde
        printf("     INSERIMENTO DATI VEICOLO\n");
        imposta_colore(7); // Bianco;

        printf("Tipo veicolo: %s\n", ottieni_nome_tipo_veicolo(v->tipo));
        printf("Modello: ");
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
        imposta_colore(13); // Magenta
        printf("         AGGIUNGI VEICOLO\n");
        stampa_separatore();
        imposta_colore(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        imposta_colore(7); // Bianco
        stampa_data_sistema();
        stampa_separatore();
        imposta_colore(10); // Verde
        printf("     INSERIMENTO DATI VEICOLO\n");
        imposta_colore(7); // Bianco;

        printf("Tipo veicolo: %s\n", ottieni_nome_tipo_veicolo(v->tipo));
        printf("Modello: %s\n", v->modello);

        printf("Targa: ");
        fgets(v->targa, sizeof(v->targa), stdin);

        // Se manca la nuova linea , svuota il buffer
        if (strchr(v->targa, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        v->targa[strcspn(v->targa, "\n")] = 0;

        if (strlen(v->targa) == 0) {
            imposta_colore(12); // Rosso
            printf("La targa non può essere vuota. Premi INVIO per riprovare.\n");
            imposta_colore(7); // Bianco
            getchar(); // Attendi INVIO
        } else if (strlen(v->targa) < 7) {
            imposta_colore(12); // Rosso
            printf("La targa inserita non è valida (deve essere di 7 caratteri). Premi INVIO per riprovare.\n");
            imposta_colore(7); // Bianco
            getchar(); // Attendi INVIO
        } else if (strlen(v->targa) > 7) {
            imposta_colore(12); // Rosso
            printf("La targa non può superare 7 caratteri. Premi INVIO per riprovare.\n");
            imposta_colore(7); // Bianco
            getchar(); // Attendi INVIO
        } else {
            targa_valida = 1;
        }
    } while (!targa_valida);

    // Input posizione
    v->posizione = 0; // Inizializza a 0

    v->id = carica_ultimo_id() + 1;
    v->disponibilita = 1;

    list nuovo_nodo = (list)malloc(sizeof(struct nodo));
    if (nuovo_nodo == NULL) {
        free(v);
        return l;
    }

    nuovo_nodo->v = v;
    nuovo_nodo->successivo = l;
    return nuovo_nodo;
}

/**
 * @brief Rimuove un veicolo dalla lista dato il suo ID.
 * @param l Lista dei veicoli.
 * @param id ID del veicolo da rimuovere.
 * @return Nuova lista senza il veicolo rimosso.
 * @note Side Effect: Libera la memoria del veicolo e del nodo rimosso.
 */
list rimuovi_veicolo(list l, int id)
{
    if (l == NULL) return NULL;
    
    // Caso 1: Il veicolo da rimuovere è il primo della lista
    if (l->v != NULL && l->v->id == id)
    {
        list temp = l->successivo;
        free(l->v);  // Libera la memoria del veicolo
        free(l);     // Libera la memoria del nodo della lista
        return temp;
    }
    
    // Caso 2: Il veicolo da rimuovere è in una posizione successiva
    list temp = l;
    while (temp->successivo != NULL)
    {
        if (temp->successivo->v != NULL && temp->successivo->v->id == id)
        {
            list da_rimuovere = temp->successivo;
            temp->successivo = temp->successivo->successivo;
            free(da_rimuovere->v);  // Libera la memoria del veicolo
            free(da_rimuovere);     // Libera la memoria del nodo della lista
            return l;
        }
        temp = temp->successivo;
    }
    
    // Il veicolo non è stato trovato
    return l;
}

/**
 * @brief Stampa le informazioni di un veicolo.
 * @param v Puntatore al veicolo da stampare.
 * @pre v != NULL
 */
void stampa_veicolo(Veicolo v) {
    if (v == NULL) return;
    
    imposta_colore(7); // Bianco
    printf("  ID: %d\n", v->id);
    printf("  Modello: %s\n", v->modello);
    printf("  Targa: %s\n", v->targa);
    
    imposta_colore(10); // Verde
    printf("  Tipo: %s\n", ottieni_nome_tipo_veicolo(v->tipo));
    
    imposta_colore(7); // Bianco
    printf("\n");
    
    printf("  Stato: ");
    if(v->disponibilita) {
        imposta_colore(10); // Verde
        printf("Disponibile");
    } else {
        imposta_colore(12); // Rosso
        printf("Non disponibile");
    }

    imposta_colore(14); // Giallo
    printf("  Posizione: %s\n", ottieni_nome_posizione_veicolo(v->posizione)); 
    imposta_colore(7); // Bianco
    printf("\n");
}

/**
 * @brief Salva la lista dei veicoli su file.
 * @param l Lista dei veicoli da salvare.
 * @note Side Effect: Sovrascrive il file data/veicoli.txt.
 */
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
        temp = temp->successivo;
    }
    fclose(fp);
    printf("Veicoli salvati nel file data/veicoli.txt\n");
}

/**
 * @brief Carica la lista dei veicoli da file.
 * @param l Lista dei veicoli esistente (può essere NULL).
 * @return Lista aggiornata con i veicoli caricati.
 * @note Side Effect: Alloca memoria per ogni veicolo e nodo caricato.
 */
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
                                list nuovo = (list)malloc(sizeof(struct nodo));
                                if (nuovo != NULL) {
                                    nuovo->v = v;
                                    nuovo->successivo = l;
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

/**
 * @brief Restituisce il nodo successivo nella lista.
 * @param l Nodo corrente.
 * @return Nodo successivo.
 * @pre l != NULL
 */
list ottieni_successivo_nodo(list l) {
    return l->successivo;
}

/**
 * @brief Estrae il veicolo dal primo nodo della lista e libera il nodo.
 * @param l Puntatore alla lista.
 * @return Puntatore al veicolo estratto.
 * @note Side Effect: La lista viene aggiornata e il nodo rimosso viene liberato.
 * @pre *l != NULL
 */
Veicolo ottieni_veicolo_da_lista(list *l) {
    if (*l == NULL) {
        return NULL;
    }
    Veicolo v = (*l)->v;
    list temp = *l;
    *l = (*l)->successivo;
    free(temp);     // Libera solo la memoria del nodo
    return v;       // Restituisce il veicolo senza liberarlo
}

/**
 * @brief Cerca un veicolo nella lista tramite ID.
 * @param l Lista dei veicoli.
 * @param id ID del veicolo da cercare.
 * @return Puntatore al veicolo trovato, oppure NULL.
 */
Veicolo cerca_veicolo(list l, int id) {
    while (l != NULL) {
        if (l->v->id == id) {
            return l->v;
        }
        l = l->successivo;
    }
    return NULL;
}

/**
 * @brief Modifica i dati di un veicolo dato il suo ID.
 * @param l Lista dei veicoli.
 * @param id ID del veicolo da modificare.
 * @note Side Effect: Modifica i dati del veicolo nella lista.
 */
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
    imposta_tipo_veicolo(v, tipo);

    printf("Nuovo modello: ");
    char modello[50];
    fgets(modello, sizeof(modello), stdin);
    modello[strcspn(modello, "\n")] = 0;
    imposta_modello_veicolo(v, modello);

    printf("Nuova targa: ");
    char targa[10];
    fgets(targa, sizeof(targa), stdin);
    targa[strcspn(targa, "\n")] = 0;
    imposta_targa_veicolo(v, targa);

    printf("Nuova posizione: (0: Deposito, 1: Posizione B, 2: Posizione C, 3: Posizione D): ");
    int posizione;
    scanf("%d", &posizione);
    getchar();
    imposta_posizione_veicolo(v, posizione);
}

/**
 * @brief Stampa tutti i veicoli presenti nella lista.
 * @param l Lista dei veicoli.
 */
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
        temp = temp->successivo;
    }
}

/**
 * @brief Stampa tutti i veicoli disponibili.
 * @param l Lista dei veicoli.
 */
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo disponibile al momento.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli non disponibili.
 * @param l Lista dei veicoli.
 */
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Tutti i veicoli sono disponibili.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli di un certo tipo.
 * @param l Lista dei veicoli.
 * @param tipo Tipo di veicolo da filtrare.
 */
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo presente.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli in una certa posizione.
 * @param l Lista dei veicoli.
 * @param posizione Posizione da filtrare.
 */
void stampa_veicoli_per_posizione(list l, int posizione)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli nella posizione %s:\n", ottieni_nome_posizione_veicolo(posizione));
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->posizione == posizione)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo presente in questa posizione.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli di un certo modello.
 * @param l Lista dei veicoli.
 * @param modello Modello da filtrare (stringa).
 */
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo con questo modello presente.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli con una certa targa.
 * @param l Lista dei veicoli.
 * @param targa Targa da filtrare (stringa).
 */
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo con questa targa presente.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli con un certo ID.
 * @param l Lista dei veicoli.
 * @param id ID da filtrare.
 */
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo con questo ID presente.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli di un certo tipo e posizione.
 * @param l Lista dei veicoli.
 * @param tipo Tipo di veicolo.
 * @param posizione Posizione del veicolo.
 */
void stampa_veicoli_per_tipo_e_posizione(list l, int tipo, int posizione)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo %s", ottieni_nome_tipo_veicolo(tipo));
    
    printf(" nella posizione %s:\n", ottieni_nome_posizione_veicolo(posizione));
    
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->tipo == tipo && temp->v->posizione == posizione)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo presente in questa posizione.\n");
    }
}

/**
 * @brief Stampa tutti i veicoli di un certo tipo e disponibilità.
 * @param l Lista dei veicoli.
 * @param tipo Tipo di veicolo.
 * @param disponibile Stato di disponibilità.
 */
void stampa_veicoli_per_tipo_e_disponibilita(list l, int tipo, bool disponibile)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo %s", ottieni_nome_tipo_veicolo(tipo));
   
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
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo %s.\n", disponibile ? "disponibile" : "non disponibile");
    }
}

/**
 * @brief Stampa tutti i veicoli in una certa posizione e disponibilità.
 * @param l Lista dei veicoli.
 * @param posizione Posizione del veicolo.
 * @param disponibile Stato di disponibilità.
 */
void stampa_veicoli_per_posizione_e_disponibilita(list l, int posizione, bool disponibile)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli nella posizione %s %s:\n", ottieni_nome_posizione_veicolo(posizione), disponibile ? "disponibili" : "non disponibili");
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->posizione == posizione && temp->v->disponibilita == disponibile)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo %s in questa posizione.\n", disponibile ? "disponibile" : "non disponibile");
    }
}

/**
 * @brief Stampa tutti i veicoli di un certo tipo, posizione e disponibilità.
 * @param l Lista dei veicoli.
 * @param tipo Tipo di veicolo.
 * @param posizione Posizione del veicolo.
 * @param disponibile Stato di disponibilità.
 */
void stampa_veicoli_per_tipo_posizione_e_disponibilita(list l, int tipo, int posizione, bool disponibile)
{
    if (l == NULL)
    {
        printf("La lista dei veicoli è vuota.\n");
        return;
    }
    
    printf("\nVeicoli di tipo %s", ottieni_nome_tipo_veicolo(tipo));
    
    
    printf(" nella posizione %s %s:\n", ottieni_nome_posizione_veicolo(posizione), disponibile ? "disponibili" : "non disponibili");
    
    list temp = l;
    bool trovato = false;
    while (temp != NULL)
    {
        if (temp->v->tipo == tipo && temp->v->posizione == posizione && temp->v->disponibilita == disponibile)
        {
            stampa_veicolo(temp->v);
            trovato = true;
        }
        temp = temp->successivo;
    }
    
    if (!trovato)
    {
        printf("Nessun veicolo di questo tipo %s in questa posizione.\n", disponibile ? "disponibile" : "non disponibile");
    }
}

/**
 * @brief Restituisce il nome del tipo di veicolo.
 * @param tipo Codice numerico del tipo.
 * @return Nome del tipo di veicolo (stringa).
 */
const char* ottieni_nome_tipo_veicolo(int tipo) {
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

/**
 * @brief Carica la lista dei veicoli dalla memoria di massa.
 * @note Side Effect: Sovrascrive la lista globale dei veicoli.
 */
void carica_lista_veicoli(void) {
    listaVeicoli = carica_veicolo_file(listaVeicoli);
}

/**
 * @brief Salva la lista dei veicoli sulla memoria di massa.
 * @note Side Effect: Sovrascrive il file data/veicoli.txt.
 */
void salva_lista_veicoli(void) {
    salva_veicolo_file(listaVeicoli);
}

/**
 * @brief Libera tutta la memoria occupata dalla lista dei veicoli.
 * @note Side Effect: La lista globale viene azzerata e la memoria liberata.
 */
void pulisci_lista_veicoli(void) {
    list current = listaVeicoli;
    while (current != NULL) {
        list successivo = current->successivo;
        free(current->v);
        free(current);
        current = successivo;
    }
    listaVeicoli = NULL;
}

/**
 * @brief Restituisce l'ultimo ID utilizzato per i veicoli.
 * @return Ultimo ID utilizzato.
 */
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

/**
 * @brief Restituisce il veicolo associato a un nodo senza rimuoverlo dalla lista.
 * @param l Nodo della lista.
 * @return Puntatore al veicolo.
 * @pre l != NULL
 */
Veicolo ottieni_veicolo_senza_rimuovere(list l) {
    if (l == NULL) {
        return NULL;
    }
    return l->v;
}
  
/**
 * @brief Restituisce il nome della posizione del veicolo.
 * @param posizione Codice numerico della posizione.
 * @return Nome della posizione (stringa).
 */
const char* ottieni_nome_posizione_veicolo(int posizione) {
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
