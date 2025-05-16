#ifndef UTENTI_H
#define UTENTI_H

#define TABLE_SIZE 100
#define MAX_PASSWORD_LENGTH 64

typedef struct {
    int id;
    char username[30];
    char nome_completo[50];
    char password[MAX_PASSWORD_LENGTH];  // Campo per la password
    int isAdmin;
} Utente;

// Function declarations
int carica_ultimo_id_utente();
void inizializza_tabella_utenti();
void salva_utenti_file();
int carica_utenti_file();
int inserisci_utente(const char* username, const char* nome_completo);
Utente* cerca_utente(const char* username);
Utente* cerca_utente_per_id(int id);
void stampa_utenti();
int verifica_password(const char* username, const char* password);
void hash_password(const char* input, char* output);

#endif // UTENTI_H