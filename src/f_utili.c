#include "f_utili.h"
#include "data_sistema.h"
#include <stdio.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "utenti.h"
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
 * @brief Imposta il colore del testo nella console.
 * @param colore Il codice colore da impostare.
 * @note Side Effect: Modifica l'aspetto del testo nella console.
 */
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

/**
 * @brief Svuota il buffer di input.
 * @note Side Effect: Consuma i caratteri dal buffer di input.
 */
void svuota_buffer() {
    while (getchar() != '\n');
}

/**
 * @brief Pulisce lo schermo della console.
 * @note Side Effect: Modifica l'output della console.
 */
void pulisci_schermo() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief Salva i dati e libera la memoria.
 * @note Side Effect: Modifica i file di salvataggio e libera la memoria allocata.
 */
void salvataggio() {
    // Salva i dati prima di chiudere
    salva_lista_veicoli();
    salva_prenotazioni_su_file(ottieni_coda_prenotazioni());
    salva_utenti_file();
    
    // Libera la memoria
    pulisci_lista_veicoli();
}

/**
 * @brief Stampa il bordo superiore.
 * @note Side Effect: Modifica l'output della console.
 */
void stampa_bordo_superiore() {
    imposta_colore(COLORE_CIANO);  // Ciano
    printf("=====================================\n");
    imposta_colore(COLORE_BIANCO); // Bianco
}

/**
 * @brief Stampa il bordo inferiore.
 * @note Side Effect: Modifica l'output della console.
 */
void stampa_bordo_inferiore() {
    imposta_colore(COLORE_CIANO);  // Ciano
    printf("=====================================\n");
    imposta_colore(COLORE_BIANCO); // Bianco
}

/**
 * @brief Stampa un separatore orizzontale.
 * @note Side Effect: Modifica l'output della console.
 */
void stampa_separatore() {
    imposta_colore(COLORE_CIANO);  // Ciano
    printf("-------------------------------------\n");
    imposta_colore(COLORE_BIANCO); // Bianco
}

/**
 * @brief Stampa la data e l'ora di sistema.
 * @note Side Effect: Modifica l'output della console.
 */
void stampa_data_sistema() {
    DataSistema data = ottieni_data_sistema();
    int giorno = ottieni_giorno_sistema(data);
    int ora = ottieni_ora_sistema(data);
    printf("Data: %s\n", ottieni_nome_giorno(giorno));
    printf("Ora: %02d:00\n", ora);
}
