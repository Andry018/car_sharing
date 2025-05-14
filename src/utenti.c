#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utenti.h"
#include "hash.h"

static Utente* tabellaUtenti[TABLE_SIZE];

void inizializza_tabella_utenti() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabellaUtenti[i] = NULL;
    }
}

int inserisci_utente(const char* username, const char* nomeCompleto) {
    unsigned int index = hash_djb2(username) % TABLE_SIZE;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (index + i) % TABLE_SIZE;

        if (tabellaUtenti[idx] == NULL) {
            tabellaUtenti[idx] = malloc(sizeof(Utente));
            strcpy(tabellaUtenti[idx]->username, username);
            strcpy(tabellaUtenti[idx]->nomeCompleto, nomeCompleto);
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
            printf("Username: %s | Nome: %s\n",
                   tabellaUtenti[i]->username,
                   tabellaUtenti[i]->nomeCompleto);
        }
    }
}