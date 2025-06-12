#include "f_utili.h"
#include "data_sistema.h"
#include <stdio.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "utenti.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>



// Funzione per impostare il colore del testo
void imposta_colore(int colore) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colore);
#else
    // ANSI escape codes for colors
    switch(colore) {
        case COLORE_BIANCO:  // Bianco (default)
            printf("\033[0m");
            break;
        case COLORE_VERDE:   // Verde
            printf("\033[0;32m");
            break;
        case COLORE_CIANO:   // Ciano
            printf("\033[0;36m");
            break;
        case COLORE_ROSSO:   // Rosso
            printf("\033[0;31m");
            break;
        case COLORE_MAGENTA: // Magenta
            printf("\033[0;35m");
            break;
        case COLORE_GIALLO:  // Giallo
            printf("\033[0;33m");
            break;
        default:
            printf("\033[0m");
            break;
    }
#endif
}

// Funzione per pulire il buffer di input
void svuota_buffer() {
    while (getchar() != '\n');
}

// Funzione per pulire lo schermo in modo cross-platform
void pulisci_schermo() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void salvataggio() {
    // Salva i dati prima di chiudere
    salva_lista_veicoli();
    salva_prenotazioni_su_file(ottieni_coda_prenotazioni());
    salva_utenti_file();
    
    // Libera la memoria
    pulisci_lista_veicoli();
}

void stampa_bordo_superiore() {
    imposta_colore(COLORE_CIANO);  // Ciano
    printf("=====================================\n");
    imposta_colore(COLORE_BIANCO); // Bianco
}

void stampa_bordo_inferiore() {
    imposta_colore(COLORE_CIANO);  // Ciano
    printf("=====================================\n");
    imposta_colore(COLORE_BIANCO); // Bianco
}

void stampa_separatore() {
    imposta_colore(COLORE_CIANO);  // Ciano
    printf("-------------------------------------\n");
    imposta_colore(COLORE_BIANCO); // Bianco
}

void stampa_data_sistema() {
    DataSistema data = ottieni_data_sistema();
    int giorno = ottieni_giorno_sistema(data);
    int ora = ottieni_ora_sistema(data);
    printf("Data: %s\n", ottieni_nome_giorno(giorno));
    printf("Ora: %02d:00\n", ora);
}