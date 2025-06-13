/**
 * @file utenti.c
 * @brief Gestione degli utenti per il sistema di car sharing.
 *
 * Questo file contiene le funzioni per la creazione, ricerca, modifica, validazione e rimozione degli utenti.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utenti.h"
#include "hash.h"
#include <ctype.h>
#include "prenotazioni.h"

/**
 * @struct Utente
 * @brief Rappresenta un utente del sistema.
 *
 * @var Utente::id
 * Identificativo univoco dell'utente.
 * @var Utente::nome_utente
 * Nome utente per l'accesso.
 * @var Utente::nome_completo
 * Nome completo dell'utente.
 * @var Utente::password
 * Password hashata dell'utente.
 * @var Utente::isamministratore
 * Flag che indica se l'utente è amministratore (1) o normale (0).
 */
struct Utente {
    int id;
    char nome_utente[30];
    char nome_completo[50];
    char password[MAX_PASSWORD_LENGTH];
    int isamministratore;
};

static Utente tabellaUtenti[TABLE_SIZE];
static int id_counter = 1;

/**
 * @brief Carica l'ultimo ID utente dal file.
 * @return L'ultimo ID trovato, oppure 0 se il file non esiste.
 */
int carica_ultimo_id_utente() {
    FILE* file = fopen("data/utenti.txt", "r");
    if (file == NULL) {
        return 0;  // Ritorna 0 se il file non esiste
    }
    
    int max_id = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        int id;
        char nome_utente[30];
        if (sscanf(line, "%d %s", &id, nome_utente) >= 2) {
            // Ignora l'amministratore (ID 0) nel conteggio del max_id
            if (id > max_id && strcmp(nome_utente, "amministratore") != 0) {
                max_id = id;
            }
        }
    }
    fclose(file);
    return max_id;
}

/**
 * @brief Inizializza la tabella degli utenti a NULL.
 * @note Side Effect: Modifica la tabella globale degli utenti.
 */
void inizializza_tabella_utenti(void) {
    for (int indice = 0; indice < TABLE_SIZE; indice++) {
        tabellaUtenti[indice] = NULL;
    }
    printf("Tabella utenti inizializzata.\n");
}

/**
 * @brief Salva tutti gli utenti su file.
 * @note Side Effect: Sovrascrive il file data/utenti.txt.
 */
void salva_utenti_file() {
    FILE* file = fopen("data/utenti.txt", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file utenti.txt\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL) {
            fprintf(file, "%d %s %s %s %d\n", 
                   tabellaUtenti[i]->id, 
                   tabellaUtenti[i]->nome_utente, 
                   tabellaUtenti[i]->password,
                   tabellaUtenti[i]->nome_completo,
                   tabellaUtenti[i]->isamministratore);
        }
    }
    fclose(file);
    printf("Utenti salvati nel file data/utenti.txt\n");
}

/**
 * @brief Carica gli utenti dal file e li inserisce nella tabella.
 * @return 1 se il caricamento è riuscito, 0 altrimenti.
 * @note Side Effect: Modifica la tabella globale degli utenti.
 */
int carica_utenti_file() {
    int max_id = carica_ultimo_id_utente();
    printf("Tentativo di apertura del file utenti.txt...\n");
    FILE* file = fopen("data/utenti.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file utenti.txt. Tentativo di creazione...\n");
        // Se il file non esiste, crealo con l'utente amministratore
        file = fopen("data/utenti.txt", "w");
        if (file == NULL) {
            printf("Errore nella creazione del file utenti.txt. Verifica i permessi della directory.\n");
            return 0;
        }
        
        // Crea l'utente amministratore
        char amministratore_password_hash[MAX_PASSWORD_LENGTH];
        hash_password("amministratore", amministratore_password_hash);
        if (fprintf(file, "0 amministratore %s amministratore 1\n", amministratore_password_hash) < 0) {
            printf("Errore nella scrittura del file utenti.txt\n");
            fclose(file);
            return 0;
        }
       // fclose(file);
        
        // Riapri il file in lettura
        file = fopen("data/utenti.txt", "r");
        if (file == NULL) {
            printf("Errore nella riapertura del file utenti.txt\n");
            return 0;
        }
        
        // Inizializza la tabella con l'amministratore
        unsigned int indice = hash_djb2("amministratore") % TABLE_SIZE;
        if (tabellaUtenti[indice] == NULL) {
            tabellaUtenti[indice] = malloc(sizeof(struct Utente));
            if (tabellaUtenti[indice] != NULL) {
                tabellaUtenti[indice]->id = 0;
                strcpy(tabellaUtenti[indice]->nome_utente, "amministratore");
                char amministratore_password_hash[MAX_PASSWORD_LENGTH];
                hash_password("amministratore", amministratore_password_hash);
                strcpy(tabellaUtenti[indice]->password, amministratore_password_hash);   
                strcpy(tabellaUtenti[indice]->nome_completo, "amministratore");
                tabellaUtenti[indice]->isamministratore = 1;
                printf("File utenti.txt creato con l'utente amministratore.\n");
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

        char nome_utente[30] = {0};
        char nome_completo[50] = {0};
        char password[MAX_PASSWORD_LENGTH] = {0};
        int id = -1, isamministratore = -1;
        
        // Leggi l'ID e il nome utente
        char* token = strtok(line, " ");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: ID mancante\n", line_number);
            continue;
        }
        id = atoi(token);
        
        // Leggi il nome utente
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: nome_utente mancante\n", line_number);
            continue;
        }
        strncpy(nome_utente, token, sizeof(nome_utente) - 1);

        // Leggi la password
        token = strtok(NULL, " ");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: password mancante\n", line_number);
            continue;
        }
        strncpy(password, token, sizeof(password) - 1);
        
        // Leggi il nome completo (può contenere spazi)
        token = strtok(NULL, "\n");
        if (token == NULL) {
            printf("Errore nel formato della riga %d: nome completo mancante\n", line_number);
            continue;
        }
        
        // Estrai isamministratore dal nome completo
        char* last_space = strrchr(token, ' ');
        if (last_space == NULL) {
            printf("Errore nel formato della riga %d: isamministratore mancante\n", line_number);
            continue;
        }
        isamministratore = atoi(last_space + 1);
        *last_space = '\0';  // Termina il nome completo prima dell'isamministratore
        
        strncpy(nome_completo, token, sizeof(nome_completo) - 1);
        
        
        // Verifica che tutti i campi siano validi
        if (id < 0 || strlen(nome_utente) == 0 || strlen(nome_completo) == 0 || isamministratore < 0) {
            printf("Errore nel formato della riga %d: campi non validi\n", line_number);
            continue;
        }
        
        unsigned int indice = hash_djb2(nome_utente) % TABLE_SIZE;
        
        // Se lo slot è vuoto, alloca nuova memoria
        if (tabellaUtenti[indice] == NULL) {
            tabellaUtenti[indice] = malloc(sizeof(struct Utente));
        }
        
        if (tabellaUtenti[indice] != NULL) {
            tabellaUtenti[indice]->id = id;
            strcpy(tabellaUtenti[indice]->nome_utente, nome_utente);
            strcpy(tabellaUtenti[indice]->password, password);  
            strcpy(tabellaUtenti[indice]->nome_completo, nome_completo);
            tabellaUtenti[indice]->isamministratore = isamministratore;
            count++;
            printf("Caricato utente: %s (ID: %d)\n", nome_utente, id);
        } else {
            printf("Errore nell'allocazione della memoria per l'utente %s\n", nome_utente);
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
        printf("Nessun utente trovato nel file. Creazione utente amministratore...\n");
        // Se non ci sono utenti, crea l'amministratore
        unsigned int indice = hash_djb2("amministratore") % TABLE_SIZE;
        if (tabellaUtenti[indice] == NULL) {
            tabellaUtenti[indice] = malloc(sizeof(struct Utente));
            if (tabellaUtenti[indice] != NULL) {
                tabellaUtenti[indice]->id = 0;
                strcpy(tabellaUtenti[indice]->nome_utente, "amministratore");
                strcpy(tabellaUtenti[indice]->password, "amministratore"); 
                strcpy(tabellaUtenti[indice]->nome_completo, "amministratore");
                tabellaUtenti[indice]->isamministratore = 1;
                salva_utenti_file();  // Salva l'amministratore nel file
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

/**
 * @brief Inserisce un nuovo utente nella tabella.
 * @param nome_utente Nome utente.
 * @param nome_completo Nome completo dell'utente.
 * @param password Password hashata.
 * @return 1 se inserimento riuscito, 0 altrimenti.
 * @note Side Effect: Modifica la tabella globale degli utenti.
 */
int inserisci_utente(const char* nome_utente, const char* nome_completo, const char* password) {
    int idx = hash_djb2(nome_utente) % TABLE_SIZE;
    if (tabellaUtenti[idx] == NULL) {
        tabellaUtenti[idx] = malloc(sizeof(struct Utente));
        if (tabellaUtenti[idx] == NULL) {
            return 0;
        }
    }
    
    // Se stiamo inserendo l'amministratore, usa ID 0
    if (strcmp(nome_utente, "amministratore") == 0) {
        id_counter = 0;
    }
    
    tabellaUtenti[idx]->id = id_counter++;
    strcpy(tabellaUtenti[idx]->nome_utente, nome_utente);
    strcpy(tabellaUtenti[idx]->nome_completo, nome_completo);
    strcpy(tabellaUtenti[idx]->password, password); // Salva la password hashata
    tabellaUtenti[idx]->isamministratore = (strcmp(nome_utente, "amministratore") == 0) ? 1 : 0;
    return 1;
}

/**
 * @brief Cerca un utente tramite nome utente.
 * @param nome_utente Nome utente da cercare.
 * @return Puntatore all'utente trovato, oppure NULL.
 */
Utente cerca_utente(const char* nome_utente) {
    unsigned int indice = hash_djb2(nome_utente) % TABLE_SIZE;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (indice + i) % TABLE_SIZE;
        if (tabellaUtenti[idx] == NULL)
            return NULL;

        if (strcmp(tabellaUtenti[idx]->nome_utente, nome_utente) == 0)
            return tabellaUtenti[idx];
    }
    return NULL;
}

/**
 * @brief Cerca un utente tramite ID.
 * @param id ID da cercare.
 * @return Puntatore all'utente trovato, oppure NULL.
 */
Utente cerca_utente_per_id(int id) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL && tabellaUtenti[i]->id == id) {
            return tabellaUtenti[i];
        }
    }
    return NULL;
}

/**
 * @brief Stampa tutti gli utenti presenti nella tabella.
 */
void stampa_utenti() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL) {
            printf("ID: %d | nome_utente: %s | Nome: %s | amministratore: %s\n",
                   tabellaUtenti[i]->id,
                   tabellaUtenti[i]->nome_utente,
                   tabellaUtenti[i]->nome_completo,
                   tabellaUtenti[i]->isamministratore ? "Si" : "No");
        }
    }
}

/**
 * @brief Restituisce l'ID dell'utente.
 * @param u Puntatore all'utente.
 * @return ID dell'utente, oppure -1 se non valido.
 * @pre u != NULL
 */
int ottieni_id_utente(Utente u) {
    if (u == NULL) {
        return -1;  // Utente non valido
    }
    return u->id;  // Restituisce l'ID dell'utente
}

/**
 * @brief Restituisce il nome completo dell'utente.
 * @param u Puntatore all'utente.
 * @return Nome completo, oppure NULL se non valido.
 * @pre u != NULL
 */
const char* ottieni_nome_completo_utente(Utente u) {
    if (u == NULL) {
        return NULL;  // Utente non valido
    }
    return u->nome_completo;  // Restituisce il nome completo dell'utente
}

/**
 * @brief Restituisce lo stato di amministratore dell'utente.
 * @param u Puntatore all'utente.
 * @return 1 se amministratore, 0 se normale, -1 se non valido.
 * @pre u != NULL
 */
int ottieni_isamministratore_utente(Utente u) {
    if (u == NULL) {
        return -1;  // Utente non valido
    }
    return u->isamministratore;  // Restituisce lo stato di amministratore dell'utente
}

/**
 * @brief Verifica se la password fornita corrisponde a quella dell'utente.
 * @param password Password in chiaro da verificare.
 * @param u Puntatore all'utente.
 * @return 1 se la password è corretta, 0 altrimenti.
 * @pre u != NULL
 */
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

/**
 * @brief Calcola l'hash della password.
 * @param input Stringa di input.
 * @param output Buffer di output per l'hash.
 */
void hash_password(const char* input, char* output) {
    unsigned long hash = hash_djb2(input);
    snprintf(output, MAX_PASSWORD_LENGTH, "%lu", hash);
}

/**
 * @brief Valida il nome utente.
 * @param nome_utente Nome utente da validare.
 * @return 1 se valido, 0 altrimenti.
 */
int valida_nome_utente(const char* nome_utente) {
    if (strlen(nome_utente) < 3 || strlen(nome_utente) > 29) {
        return 0;
    }
    
    // Verifica che contenga solo caratteri alfanumerici e underscore
    for (int i = 0; nome_utente[i]; i++) {
        if (!isalnum(nome_utente[i]) && nome_utente[i] != '_') {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Valida il nome completo.
 * @param nome Nome completo da validare.
 * @return 1 se valido, 0 altrimenti.
 */
int valida_nome_completo(const char* nome) {
    if (strlen(nome) < 3 || strlen(nome) > 49) {
        return 0;
    }
    
    // Verifica che contenga solo lettere, spazi e alcuni caratteri speciali
    for (int i = 0; nome[i]; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ' && nome[i] != '\'' && nome[i] != '-') {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Rimuove un utente dato il suo ID.
 * @param id ID dell'utente da rimuovere.
 * @return 1 se rimosso con successo, 0 altrimenti.
 * @note Side Effect: Modifica la tabella utenti e rimuove le prenotazioni associate.
 */
int rimuovi_utente(int id) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (tabellaUtenti[i] != NULL && tabellaUtenti[i]->id == id) {
            // Elimina tutte le prenotazioni dell'utente
            CodaPrenotazioni coda = ottieni_coda_prenotazioni();
            rimuovi_prenotazioni_utente(coda, id);
            salva_prenotazioni_su_file(coda); 

            free(tabellaUtenti[i]);
            tabellaUtenti[i] = NULL;
            return 1;
        }
    }
    return 0;
}
