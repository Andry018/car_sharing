#ifndef UTENTI_H
#define UTENTI_H

#define TABLE_SIZE 100

typedef struct Utente {
    int id;
    char username[30];
    char nomeCompleto[50];
    int isAdmin;
} Utente;

void inizializza_tabella_utenti();
int inserisci_utente(const char* username, const char* nomeCompleto);
Utente* cerca_utente(const char* username);
void stampa_utenti();

#endif