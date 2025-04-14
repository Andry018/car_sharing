#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Funzione per impostare il colore del testo
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Funzione per pulire il buffer di input
void clearInputBuffer() {
    while (getchar() != '\n');
}


void prenotaAuto() {
    setColor(10); // Verde
    printf("\nFunzione: Prenota auto\n");
    setColor(7); // Bianco
    printf("Premi INVIO per tornare al menu...");
    clearInputBuffer();
}

void visualizzaPrenotazioni() {
    setColor(11); // Ciano
    printf("\nFunzione: Visualizza prenotazioni\n");
    setColor(7); // Bianco
    printf("Premi INVIO per tornare al menu...");
    clearInputBuffer();
}

void restituisciAuto() {
    setColor(14); // Giallo
    printf("\nFunzione: Restituisci auto\n");
    setColor(7); // Bianco
    printf("Premi INVIO per tornare al menu...");
    clearInputBuffer();
}

int main() {
    int scelta;

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
            case 0:
                setColor(12); // Rosso
                printf("\nChiusura del programma...\n");
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
