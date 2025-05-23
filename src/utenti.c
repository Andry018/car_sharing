#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utenti.h"
#include "hash.h"

static Utente* tabellaUtenti[TABLE_SIZE];

int carica_ultimo_id_utente() {
    FILE* file = fopen("data/utenti.txt", "r");
    if (file == NULL) {
        return 0;  // Ritorna 0 se il file non esiste
    }
    
    int max_id = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        int id;
        char username[30];
        if (sscanf(line, "%d %s", &id, username) >= 2) {
            // Ignora l'admin (ID 0) nel conteggio del max_id
            if (id > max_id && strcmp(username, "Admin") != 0) {
                max_id = id;
            }
        }
    }
    fclose(file);
    return max_id;
}

void inizializza_tabella_utenti() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabellaUtenti[i] = NULL;
    }
    
    // Verifica se l'admin esiste già nel file
    FILE* file = fopen("data/utenti.txt", "r");
    int admin_exists = 0;
    
    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char username[30];
            if (sscanf(line, "%*d %s", username) == 1 && strcmp(username, "Admin") == 0) {
                admin_exists = 1;
                break;
            }
        }
        fclose(file);
    }
    
    // Crea automaticamente l'utente admin se non esiste
    if (!admin_exists) {
        unsigned int index = hash_djb2("Admin") % TABLE_SIZE;
        tabellaUtenti[index] = malloc(sizeof(Utente));
        if (tabellaUtenti[index] != NULL) {
            tabellaUtenti[index]->id = 0;  // ID 0 per l'admin
            strcpy(tabellaUtenti[index]->username, "Admin");
            strcpy(tabellaUtenti[index]->nome_completo, "Administrator");
            tabellaUtenti[index]->isAdmin = 1;
            
            // Salva l'admin nel file
            FILE* write_file;
            if (admin_exists == 0 && file == NULL) {
                // Se il file non esiste, crealo
                write_file = fopen("data/utenti.txt", "w");
            } else {
                // Altrimenti aggiungi in append
                write_file = fopen("data/utenti.txt", "a");
            }
            
            if (write_file != NULL) {
                fprintf(write_file, "%d %s %s %d\n", 
                        tabellaUtenti[index]->id,
                        tabellaUtenti[index]->username,
                        tabellaUtenti[index]->nome_completo,
                        tabellaUtenti[index]->isAdmin);
                fclose(write_file);
                printf("Utente Admin creato con successo.\n");
            }
        }
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

    char line[256];
    int success = 1;

    while (fgets(line, sizeof(line), file)) {
        char username[30];
        char nome_completo[50];
        char* token = strtok(line, " ");  // Legge ID
        
        if (token != NULL) {
            token = strtok(NULL, " ");  // Legge username
            
            if (token != NULL) {
                strcpy(username, token);
                token = strtok(NULL, "\n");  // Legge il resto della linea fino a \n
                
                if (token != NULL) {
                    // Trova l'ultimo numero nella stringa (isAdmin)
                    char* last_space = strrchr(token, ' ');
                    if (last_space != NULL) {
                        *last_space = '\0';  // Termina la stringa prima dell'isAdmin
                        // Rimuovi spazi iniziali dal nome completo
                        while (*token == ' ') token++;
                        strcpy(nome_completo, token);
                        
                        if (!inserisci_utente(username, nome_completo)) {
                            printf("Errore nell'inserimento dell'utente %s\n", username);
                            success = 0;
                        }
                    }
                }
            }
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
        // Se non ci sono altri utenti oltre all'admin, parti da 1
        if (id_counter == 0) {
            id_counter = 1;
        }
    }
    
    // Se stiamo inserendo l'admin, usa ID 0
    if (strcmp(username, "Admin") == 0) {
        id_counter = 0;
    }
    
    unsigned int index = hash_djb2(username) % TABLE_SIZE;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (index + i) % TABLE_SIZE;

        if (tabellaUtenti[idx] == NULL) {
            tabellaUtenti[idx] = malloc(sizeof(Utente));
            if (tabellaUtenti[idx] == NULL) {
                return 0;
            }
            
            // Se non è l'admin, incrementa l'ID
            if (strcmp(username, "Admin") != 0) {
                tabellaUtenti[idx]->id = id_counter++;
            } else {
                tabellaUtenti[idx]->id = 0;  // Admin sempre con ID 0
            }
            
            strcpy(tabellaUtenti[idx]->username, username);
            strcpy(tabellaUtenti[idx]->nome_completo, nome_completo);
            tabellaUtenti[idx]->isAdmin = (strcmp(username, "Admin") == 0) ? 1 : 0;
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

// Funzione per cercare un utente per ID
Utente* cerca_utente_per_id(int id) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL && tabellaUtenti[i]->id == id) {
            return tabellaUtenti[i];
        }
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