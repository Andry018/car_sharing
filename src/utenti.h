#ifndef UTENTI_H
#define UTENTI_H

#define TABLE_SIZE 100

typedef struct {
    int id;
    char username[30];
    char nome_completo[50];
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

#endif // UTENTI_H