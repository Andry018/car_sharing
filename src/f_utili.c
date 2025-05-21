#include "f_utili.h"
#include <stdio.h>
#include "veicolo.h"
#include "prenotazioni.h"



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