#include "f_utili.h"
#include "data_sistema.h"
#include <stdio.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "utenti.h"
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

// Funzione per impostare il colore del testo
void set_color(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    // ANSI escape codes for colors
    switch(color) {
        case WHITE:  // Bianco (default)
            printf("\033[0m");
            break;
        case GREEN: // Verde
            printf("\033[0;32m");
            break;
        case CYAN: // Ciano
            printf("\033[0;36m");
            break;
        case RED: // Rosso
            printf("\033[0;31m");
            break;
        case MAGENTA: // Magenta
            printf("\033[0;35m");
            break;
        case YELLOW: // Giallo
            printf("\033[0;33m");
            break;
        default:
            printf("\033[0m");
            break;
    }
#endif
}

// Funzione per pulire il buffer di input
void svuota_buffer(void) {
    int c;
    // Leggi tutti i caratteri fino al newline o EOF
    while ((c = getchar()) != '\n' && c != EOF) {
        // Continua a leggere finché non troviamo un newline o EOF
    }
    
    // Se abbiamo raggiunto EOF, pulisci anche il flag di errore
    if (c == EOF) {
        clearerr(stdin);
    }
}

// Funzione per pulire lo schermo in modo cross-platform
void pulisci_schermo(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void salvataggio(void) {
    // Salva i dati prima di chiudere
    salva_lista_veicoli();
    salva_prenotazioni_su_file(get_coda_prenotazioni());
    salva_utenti_file();
    
    // Libera la memoria
    pulisci_lista_veicoli();
}

void stampa_bordo_superiore(void) {
    set_color(CYAN);
    printf("=====================================\n");
    set_color(WHITE);
}

void stampa_bordo_inferiore(void) {
    set_color(CYAN);
    printf("=====================================\n");
    set_color(WHITE);
}

void stampa_separatore(void) {
    set_color(CYAN);
    printf("-------------------------------------\n");
    set_color(WHITE);
}

void stampa_data_sistema(void) {
    DataSistema data = get_data_sistema();
    int giorno = get_giorno_sistema(data);
    int ora = get_ora_sistema(data);
    
    set_color(CYAN);
    printf("Data sistema: %s ", get_nome_giorno(giorno));
    printf("%02d:00\n", ora);
    set_color(WHITE);
}