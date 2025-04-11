#include <stdio.h>
#include <stdlib.h>

// Funzioni placeholder
void prenotaAuto() {
    printf("Funzione: Prenota auto\n");
    printf("Premi INVIO per tornare al menu...");
    getchar(); getchar();
}

void visualizzaPrenotazioni() {
    printf("Funzione: Visualizza prenotazioni\n");
    printf("Premi INVIO per tornare al menu...");
    getchar(); getchar();
}

void restituisciAuto() {
    printf("Funzione: Restituisci auto\n");
    printf("Premi INVIO per tornare al menu...");
    getchar(); getchar();
}

int main() {
    int scelta;

    while (1) {
        system("cls"); // "cls" se sei su Windows

        printf("=== SISTEMA DI CAR SHARING ===\n");
        printf("1. Prenota un'auto\n");
        printf("2. Visualizza prenotazioni\n");
        printf("3. Restituisci auto\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

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
                printf("Chiusura del programma...\n");
                return 0;
            default:
                printf("Scelta non valida. Premi INVIO per riprovare...");
                getchar(); getchar();
                break;
        }
    }

    return 0;
}
