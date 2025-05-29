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
void set_color(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    // ANSI escape codes for colors
    switch(color) {
        case 7:  // Bianco (default)
            printf("\033[0m");
            break;
        case 10: // Verde
            printf("\033[0;32m");
            break;
        case 11: // Ciano
            printf("\033[0;36m");
            break;
        case 12: // Rosso
            printf("\033[0;31m");
            break;
        case 13: // Magenta
            printf("\033[0;35m");
            break;
        case 14: // Giallo
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
    salva_prenotazioni_su_file(get_coda_prenotazioni());
    salva_utenti_file();
    
    // Libera la memoria
    pulisci_lista_veicoli();
}

void stampa_bordo_superiore() {
    set_color(11);  // Ciano
    printf("=====================================\n");
    set_color(7);   // Bianco
}

void stampa_bordo_inferiore() {
    set_color(11);  // Ciano
    printf("=====================================\n");
    set_color(7);   // Bianco
}

void stampa_separatore() {
    set_color(11);  // Ciano
    printf("-------------------------------------\n");
    set_color(7);   // Bianco
}

void stampa_data_sistema() {
    DataSistema data = get_data_sistema();
    int giorno = get_giorno_sistema(data);
    int ora = get_ora_sistema(data);
    printf("Data: %s\n", get_nome_giorno(giorno));
    printf("Ora: %02d:00\n", ora);
}