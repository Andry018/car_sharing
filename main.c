#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "vehicle.h"

// Funzione per impostare il colore del testo
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Funzione per pulire il buffer di input
void clearInputBuffer() {
    while (getchar() != '\n');
}

void gestioneVeicoli() {
    int scelta;
    
    do {
        system("cls");
        setColor(14); // Giallo
        printf("=====================================\n");
        printf("       GESTIONE VEICOLI\n");
        printf("=====================================\n");
        setColor(7); // Bianco
        
        printf("1. Aggiungi veicolo\n");
        printf("2. Rimuovi veicolo\n");
        printf("3. Visualizza tutti i veicoli\n");
        printf("4. Salva veicoli su file\n");
        printf("5. Carica veicoli da file\n");
        printf("0. Torna al menu principale\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        clearInputBuffer();

        switch(scelta) {
            case 1:
                setListaVeicoli(aggiungiVeicolo(getListaVeicoli()));
                salvaListaVeicoli(); // Salva automaticamente dopo l'aggiunta
                break;
            case 2:
                setListaVeicoli(rimuoviVeicolo(getListaVeicoli()));
                salvaListaVeicoli(); // Salva automaticamente dopo la rimozione
                break;
            case 3: {
                list temp = getListaVeicoli();
                while(temp != NULL) {
                    stampaVeicolo(temp->veicoli);
                    printf("-------------------\n");
                    temp = temp->next;
                }
                printf("Premi INVIO per continuare...");
                clearInputBuffer();
                break;
            }
            case 4:
                salvaListaVeicoli();
                printf("Premi INVIO per continuare...");
                clearInputBuffer();
                break;
            case 5:
                caricaListaVeicoli();
                printf("Premi INVIO per continuare...");
                clearInputBuffer();
                break;
            case 0:
                break;
            default:
                setColor(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                setColor(7); // Bianco
                clearInputBuffer();
        }
    } while(scelta != 0);
}

void prenotaAuto() {
    setColor(10); // Verde
    printf("=====================================\n");
    printf("       Prenota Auto\n");
    printf("=====================================\n");
    setColor(7); // Bianco
    
    // TODO: Implementare la logica di prenotazione usando i veicoli disponibili
    printf("Funzionalità in sviluppo...\n");
    printf("Premi INVIO per tornare al menu...");
    clearInputBuffer();
}

void visualizzaPrenotazioni() {
    setColor(11); // Ciano
    printf("=====================================\n");
    printf("       Visualizza Prenotazioni\n");
    printf("=====================================\n");
    setColor(7); // Bianco
    
    // TODO: Implementare la visualizzazione delle prenotazioni
    printf("Funzionalità in sviluppo...\n");
    printf("Premi INVIO per tornare al menu...");
    clearInputBuffer();
}

void restituisciAuto() {
    setColor(14); // Giallo
    printf("=====================================\n");
    printf("       Restituisci Auto\n");
    printf("=====================================\n");
    setColor(7); // Bianco
    
    // TODO: Implementare la logica di restituzione
    printf("Funzionalità in sviluppo...\n");
    printf("Premi INVIO per tornare al menu...");
    clearInputBuffer();
}

void cleanup() {
    // Salva i dati prima di chiudere
    salvaListaVeicoli();
    
    // Libera la memoria
    pulisciListaVeicoli();
}

int main() {
    int scelta;
    
    // Carica i veicoli all'avvio
   caricaListaVeicoli();

    while (1) {
        system("cls");
        
        setColor(13); // Magenta
        printf("=====================================\n");
        printf("       SISTEMA DI CAR SHARING\n");
        printf("=====================================\n");
        setColor(7); // Bianco

        // Opzioni del menu
        printf("1. Prenota un'auto\n");
        printf("2. Visualizza prenotazioni\n");
        printf("3. Restituisci auto\n");
        printf("4. Gestione Veicoli\n");
        printf("0. Esci\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        clearInputBuffer();

        switch (scelta) {
            case 1:
                system("cls");
                prenotaAuto();
                break;
            case 2:
                system("cls");
                visualizzaPrenotazioni();
                break;
            case 3:
                system("cls");
                restituisciAuto();
                break;
            case 4:
                system("cls");
                gestioneVeicoli();
                break;
            case 0:
                setColor(12); // Rosso
                printf("\nSalvataggio dei dati e chiusura del programma...\n");
                cleanup(); // Salva e pulisce prima di chiudere
                setColor(7); // Bianco
                return 0;
            default:
                setColor(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                setColor(7); // Bianco
                clearInputBuffer();
                break;
        }
    }

    return 0;
}
