#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utenti.h"
#include "hash.h"

struct Utente {
    int id;
    char username[30];
    char nome_completo[50];
    char password[MAX_PASSWORD_LENGTH];  // Campo per la password
    int isAdmin;
} ;


static Utente tabellaUtenti[TABLE_SIZE];
static int id_counter = 0;

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

void inizializza_tabella_utenti(void) {
    for (int index = 0; index < TABLE_SIZE; index++) {
        tabellaUtenti[index] = NULL;
    }
    printf("Tabella utenti inizializzata.\n");
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
    int max_id = carica_ultimo_id_utente();
    printf("Tentativo di apertura del file utenti.txt...\n");
    FILE* file = fopen("data/utenti.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file utenti.txt. Tentativo di creazione...\n");
        // Se il file non esiste, crealo con l'utente admin
        file = fopen("data/utenti.txt", "w");
        if (file == NULL) {
            printf("Errore nella creazione del file utenti.txt. Verifica i permessi della directory.\n");
            return 0;
        }
        
        // Crea l'utente admin
        if (fprintf(file, "0 Admin Administrator 1\n") < 0) {
            printf("Errore nella scrittura del file utenti.txt\n");
            fclose(file);
            return 0;
        }
        fclose(file);
        
        // Riapri il file in lettura
        file = fopen("data/utenti.txt", "r");
        if (file == NULL) {
            printf("Errore nella riapertura del file utenti.txt\n");
            return 0;
        }
        
        // Inizializza la tabella con l'admin
        unsigned int index = hash_djb2("Admin") % TABLE_SIZE;
        if (tabellaUtenti[index] == NULL) {
            tabellaUtenti[index] = malloc(sizeof(struct Utente));
            if (tabellaUtenti[index] != NULL) {
                tabellaUtenti[index]->id = 0;
                strcpy(tabellaUtenti[index]->username, "Admin");
                strcpy(tabellaUtenti[index]->nome_completo, "Administrator");
                tabellaUtenti[index]->isAdmin = 1;
                printf("File utenti.txt creato con l'utente Admin.\n");
                fclose(file);
                return 1;
            }
        }
        fclose(file);
        return 0;
    }

    printf("File utenti.txt aperto con successo. Lettura in corso...\n");
    char line[256];
    int success = 1;
    int count = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        // Salta le righe vuote
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
            continue;
        }

        char username[30] = {0};
        char nome_completo[50] = {0};
        int id = -1, isAdmin = -1;
        
        // Leggi l'ID e l'username
        char* token = strtok(line, " ");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: ID mancante\n", line_number);
            continue;
        }
        id = atoi(token);
        
        // Leggi l'username
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: username mancante\n", line_number);
            continue;
        }
        strncpy(username, token, sizeof(username) - 1);
        
        // Leggi il nome completo (può contenere spazi)
        token = strtok(NULL, "\n");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: nome completo mancante\n", line_number);
            continue;
        }
        
        // Estrai isAdmin dal nome completo
        char* last_space = strrchr(token, ' ');
        if (last_space == NULL) {
            printf("Errore nel formato della riga %d: isAdmin mancante\n", line_number);
            continue;
        }
        isAdmin = atoi(last_space + 1);
        *last_space = '\0';  // Termina il nome completo prima dell'isAdmin
        
        strncpy(nome_completo, token, sizeof(nome_completo) - 1);
        
        // Verifica che tutti i campi siano validi
        if (id < 0 || strlen(username) == 0 || strlen(nome_completo) == 0 || isAdmin < 0) {
            printf("Errore nel formato della riga %d: campi non validi\n", line_number);
            continue;
        }
        
        unsigned int index = hash_djb2(username) % TABLE_SIZE;
        
        // Se lo slot è vuoto, alloca nuova memoria
        if (tabellaUtenti[index] == NULL) {
            tabellaUtenti[index] = malloc(sizeof(struct Utente));
        }
        
        if (tabellaUtenti[index] != NULL) {
            tabellaUtenti[index]->id = id;
            strcpy(tabellaUtenti[index]->username, username);
            strcpy(tabellaUtenti[index]->nome_completo, nome_completo);
            tabellaUtenti[index]->isAdmin = isAdmin;
            count++;
            printf("Caricato utente: %s (ID: %d)\n", username, id);
        } else {
            printf("Errore nell'allocazione della memoria per l'utente %s\n", username);
            success = 0;
        }
        if(count > 0) {
            id_counter = max_id + 1;
        } else {
            id_counter = 1;  // Inizializza il contatore se non ci sono utenti
        }
    }
    
    fclose(file);
    
    if (count == 0) {
        printf("Nessun utente trovato nel file. Creazione utente admin...\n");
        // Se non ci sono utenti, crea l'admin
        unsigned int index = hash_djb2("Admin") % TABLE_SIZE;
        if (tabellaUtenti[index] == NULL) {
            tabellaUtenti[index] = malloc(sizeof(struct Utente));
            if (tabellaUtenti[index] != NULL) {
                tabellaUtenti[index]->id = 0;
                strcpy(tabellaUtenti[index]->username, "Admin");
                strcpy(tabellaUtenti[index]->nome_completo, "Administrator");
                tabellaUtenti[index]->isAdmin = 1;
                salva_utenti_file();  // Salva l'admin nel file
                return 1;
            }
        }
        return 0;
    }
    
    if (success) {
        printf("Caricati %d utenti dal file data/utenti.txt\n", count);
    } else {
        printf("Si sono verificati errori durante il caricamento degli utenti\n");
    }
    return success;
}

int inserisci_utente(const char* username, const char* nome_completo) {
    int idx = hash_djb2(username) % TABLE_SIZE;
    if (tabellaUtenti[idx] == NULL) {
        tabellaUtenti[idx] = malloc(sizeof(struct Utente));
        if (tabellaUtenti[idx] == NULL) {
            return 0;
        }
    }
    
    // Se stiamo inserendo l'admin, usa ID 0
    if (strcmp(username, "Admin") == 0) {
        id_counter = 0;
    }
    
    tabellaUtenti[idx]->id = id_counter++;
    strcpy(tabellaUtenti[idx]->username, username);
    strcpy(tabellaUtenti[idx]->nome_completo, nome_completo);
    tabellaUtenti[idx]->isAdmin = (strcmp(username, "Admin") == 0) ? 1 : 0;
    return 1;
}

Utente cerca_utente(const char* username) {
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
Utente cerca_utente_per_id(int id) {
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

int get_id_utente(Utente u) {
    if (u == NULL) {
        return -1;  // Utente non valido
    }
    return u->id;  // Restituisce l'ID dell'utente
}

const char* get_nome_utente(Utente u) {
    if (u == NULL) {
        return NULL;  // Utente non valido
    }
    return u->nome_completo;  // Restituisce il nome completo dell'utente
}

const char* get_username_utente(Utente u) {
    if (u == NULL) {
        return NULL;  // Utente non valido
    }
    return u->username;  // Restituisce l'username dell'utente
}   

const char* get_password_utente(const char* username) {
   Utente utente = cerca_utente(username);
    if (utente != NULL) {
        return utente->password;
    }
    free(utente);
    return NULL;  // Utente non trovato
}   

int get_isAdmin_utente(Utente u) {
    if (u == NULL) {
        return -1;  // Utente non valido
    }
    return u->isAdmin;  // Restituisce lo stato di amministratore dell'utente
}   

void set_id_utente(int id, Utente u) {
    if (u == NULL) {
        printf("Utente non valido!\n");
        return;
    }
    u->id = id;  // Imposta l'ID dell'utente     
}

void set_nome_utente(const char* nome_completo, Utente u) {
    if (u == NULL) {
        printf("Utente non valido!\n");
        return;
    }
    strncpy(u->nome_completo, nome_completo, sizeof(u->nome_completo) - 1);
    u->nome_completo[sizeof(u->nome_completo) - 1] = '\0';  // Assicura che la stringa sia terminata correttamente
}

void set_username_utente(const char* new_username, Utente u) {
    if (u == NULL) {
        printf("Utente non valido!\n");
        return;
    }
    if (cerca_utente(new_username) != NULL) {
        printf("Username già esistente!\n");
        return;  // Username già in uso
    }
    strcpy(u->username, new_username);  // Imposta il nuovo username
    
   
}

void set_password_utente(const char* username, Utente u) {
    if (u == NULL) {
        printf("Utente non valido!\n");
        return;
    }
    
    char hashed_password[MAX_PASSWORD_LENGTH];
    hash_password(username, hashed_password);
    
    // Imposta la password hashata
    strncpy(u->password, hashed_password, sizeof(u->password) - 1);
    u->password[sizeof(u->password) - 1] = '\0';  // Assicura che la stringa sia terminata correttamente
}
 
int verifica_password(const char* password, Utente u) {
    if (u == NULL) {
        return 0;  // Utente non valido
    }
    
    char hashed_password[MAX_PASSWORD_LENGTH];
    hash_password(password, hashed_password);
    
    // Confronta la password hashata con quella memorizzata
    if (strcmp(u->password, hashed_password) == 0) {
        return 1;  // Password corretta
    }
    
    return 0;  // Password errata
}

void hash_password(const char* input, char* output) {
    hash_djb2(input);
    unsigned long hash = hash_djb2(input);
    snprintf(output, MAX_PASSWORD_LENGTH, "%lu", hash);
}
