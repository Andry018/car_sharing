#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utenti.h"
#include "hash.h"

static Utente* tabellaUtenti[TABLE_SIZE];

int carica_ultimo_id_utente() {
    FILE* file = fopen("data/utenti.txt", "r");
    if (file == NULL) {
        return 0;
    }
    
    int max_id = 0;
    int id;
    char username[30];
    char nome_completo[50];
    
    while (fscanf(file, "%d %s %s", &id, username, nome_completo) == 3) {
        if (id > max_id) {
            max_id = id;
        }
    }
    fclose(file);
    return max_id;
}

void inizializza_tabella_utenti() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabellaUtenti[i] = NULL;
    }
}

void salva_utenti_file() {
    FILE* file = fopen("data/utenti.txt", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file utenti.txt\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL) {
            fprintf(file, "%d %s %s %d\n", 
                   tabellaUtenti[i]->id, 
                   tabellaUtenti[i]->username, 
                   tabellaUtenti[i]->nome_completo,
                   tabellaUtenti[i]->isAdmin);
        }
    }
    fclose(file);
    printf("Utenti salvati nel file data/utenti.txt\n");
}

int carica_utenti_file() {
    FILE* file = fopen("data/utenti.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file utenti.txt\n");
        return 0;
    }
    int id;
    char username[30];
    char nome_completo[50];
    int isAdmin;
    int success = 1;

    while (fscanf(file, "%d %s %s %d", &id, username, nome_completo, &isAdmin) == 4) {
        if (!inserisci_utente(username, nome_completo)) {
            printf("Errore nell'inserimento dell'utente %s\n", username);
            success = 0;
        }
    }
    fclose(file);
    
    if (success) {
        printf("Utenti caricati dal file data/utenti.txt\n");
    } else {
        printf("Si sono verificati errori durante il caricamento degli utenti\n");
    }
    return success;
}

int inserisci_utente(const char* username, const char* nome_completo) {
    static int id_counter = 0;
    if (id_counter == 0) {
        id_counter = carica_ultimo_id_utente();
    }
    
    unsigned int index = hash_djb2(username) % TABLE_SIZE;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (index + i) % TABLE_SIZE;

        if (tabellaUtenti[idx] == NULL) {
            tabellaUtenti[idx] = malloc(sizeof(Utente));
            if (tabellaUtenti[idx] == NULL) {
                return 0;
            }
            id_counter++;
            tabellaUtenti[idx]->id = id_counter;
            strcpy(tabellaUtenti[idx]->username, username);
            strcpy(tabellaUtenti[idx]->nome_completo, nome_completo);
            tabellaUtenti[idx]->isAdmin = 0;  // Default: non admin
            return 1;
        }
    }
    return 0;
}

Utente* cerca_utente(const char* username) {
    unsigned int index = hash_djb2(username) % TABLE_SIZE;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (index + i) % TABLE_SIZE;
        if (tabellaUtenti[idx] == NULL)
            return NULL;

        if (strcmp(tabellaUtenti[idx]->username, username) == 0)
            return tabellaUtenti[idx];
    }
    return NULL;
}

void stampa_utenti() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL) {
            printf("ID: %d | Username: %s | Nome: %s | Admin: %s\n",
                   tabellaUtenti[i]->id,
                   tabellaUtenti[i]->username,
                   tabellaUtenti[i]->nome_completo,
                   tabellaUtenti[i]->isAdmin ? "Sì" : "No");
        }
    }
}