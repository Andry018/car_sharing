#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "vehicle.h"
#include "prenotazioni.h"
#include "fasceorarie.h"
#include "utenti.h"

// COMMIT BUONO
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

void gestione_veicoli() {
    int scelta;
    
    do {
        pulisci_schermo();
        set_color(14); // Giallo
        printf("=====================================\n");
        printf("       GESTIONE VEICOLI\n");
        printf("=====================================\n");
        set_color(7); // Bianco
        
        printf("1. Aggiungi veicolo\n");
        printf("2. Rimuovi veicolo\n");
        printf("3. Visualizza tutti i veicoli\n");
        printf("0. Torna al menu principale\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuota_buffer();

        switch(scelta) {
            case 1:
                set_lista_veicoli(aggiungi_veicolo(get_lista_veicoli()));
                salva_lista_veicoli(); // Salva automaticamente dopo l'aggiunta
                break;
            case 2:
                set_lista_veicoli(rimuovi_veicolo(get_lista_veicoli()));
                salva_lista_veicoli(); // Salva automaticamente dopo la rimozione
                break;
            case 3: {
                list temp = get_lista_veicoli();
                while(temp != NULL) {
                    stampa_veicolo(temp->veicoli);
                    printf("-------------------\n");
                    temp = temp->next;
                }
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 0:
                break;
            default:
                set_color(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                set_color(7); // Bianco
                svuota_buffer();
        }
    } while(scelta != 0);
}

void prenota_auto() {
    int scelta;
    static CodaPrenotazioni* coda_prenotazioni = NULL;
    
    // Inizializza la coda delle prenotazioni se non esiste
    if (coda_prenotazioni == NULL) {
        coda_prenotazioni = inizializza_coda();
        if (coda_prenotazioni == NULL) {
            set_color(12); // Rosso
            printf("Errore nell'inizializzazione della coda prenotazioni!\n");
            set_color(7); // Bianco
            printf("Premi INVIO per tornare al menu...");
            svuota_buffer();
            return;
        }
    }
    
    do {
        pulisci_schermo();
        set_color(10); // Verde
        printf("=====================================\n");
        printf("       PRENOTAZIONE AUTO\n");
        printf("=====================================\n");
        set_color(7); // Bianco
        
        printf("1. Nuova prenotazione\n");
        printf("2. Visualizza prenotazioni attive\n");
        printf("3. Cancella prenotazione\n");
        printf("4. Modifica stato prenotazione\n");
        printf("0. Torna al menu principale\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuota_buffer();

        switch(scelta) {
            case 1: {
                int id_utente, id_veicolo, giorno_inizio, ora_inizio, giorno_fine, ora_fine, priorita;
                
                // Visualizza veicoli disponibili
                printf("\nVeicoli disponibili:\n");
                list temp = get_lista_veicoli();
                while(temp != NULL) {
                    stampa_veicolo(temp->veicoli);
                    printf("-------------------\n");
                    temp = temp->next;
                }
                
                printf("\nInserisci i dati della prenotazione:\n");
                printf("ID Utente: ");
                scanf("%d", &id_utente);
                printf("ID Veicolo: ");
                scanf("%d", &id_veicolo);
                printf("Giorno inizio (0-6, Lun-Dom): ");
                scanf("%d", &giorno_inizio);
                printf("Ora inizio (0-23): ");
                scanf("%d", &ora_inizio);
                printf("Giorno fine (0-6, Lun-Dom): ");
                scanf("%d", &giorno_fine);
                printf("Ora fine (0-23): ");
                scanf("%d", &ora_fine);
                printf("Priorità (piu' bassa = piu' prioritaria): ");
                scanf("%d", &priorita);
                svuota_buffer();
                
                Prenotazione nuova = crea_prenotazione(id_utente, id_veicolo, 
                                                     giorno_inizio, ora_inizio,
                                                     giorno_fine, ora_fine, 
                                                     priorita);
                
                int risultato = aggiungi_prenotazione(coda_prenotazioni, nuova);
                salva_prenotazioni_su_file(coda_prenotazioni); 
                if (risultato == 0) {
                    set_color(10); // Verde
                    printf("\nPrenotazione aggiunta con successo!\n");
                } else if (risultato == -2) {
                    set_color(12); // Rosso
                    printf("\nErrore: Fascia oraria non valida!\n");
                } else {
                    set_color(12); // Rosso
                    printf("\nErrore nell'aggiunta della prenotazione!\n");
                }
                set_color(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 2: {
                printf("\nPrenotazioni attive:\n");
                for (int i = 0; i < coda_prenotazioni->dimensione; i++) {
                    stampa_prenotazione(coda_prenotazioni->heap[i]);
                    printf("-------------------\n");
                }
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 3: {
                int id_prenotazione;
                printf("\nInserisci l'ID della prenotazione da cancellare: ");
                scanf("%d", &id_prenotazione);
                svuota_buffer();
                
                Prenotazione* prenotazione = cerca_prenotazione(coda_prenotazioni, id_prenotazione);
                if (prenotazione != NULL) {
                    prenotazione->stato = CANCELLATA;
                    set_color(10); // Verde
                    printf("\nPrenotazione cancellata con successo!\n");
                } else {
                    set_color(12); // Rosso
                    printf("\nPrenotazione non trovata!\n");
                }
                set_color(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 4: {
                int id_prenotazione, nuovo_stato;
                printf("\nInserisci l'ID della prenotazione da modificare: ");
                scanf("%d", &id_prenotazione);
                printf("Nuovo stato (0=In attesa, 1=Confermata, 2=Completata, 3=Cancellata): ");
                scanf("%d", &nuovo_stato);
                svuota_buffer();
                
                int risultato = modifica_stato_prenotazione(coda_prenotazioni, id_prenotazione, nuovo_stato);
                if (risultato == 0) {
                    set_color(10); // Verde
                    printf("\nStato della prenotazione modificato con successo!\n");
                } else {
                    set_color(12); // Rosso
                    printf("\nErrore nella modifica dello stato!\n");
                }
                set_color(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 0:
                break;
            default:
                set_color(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                set_color(7); // Bianco
                svuota_buffer();
        }
    } while(scelta != 0);
}

void visualizza_prenotazioni() {
    set_color(11); // Ciano
    printf("=====================================\n");
    printf("       Visualizza Prenotazioni\n");
    printf("=====================================\n");
    set_color(7); // Bianco
    
    // TODO: Implementare la visualizzazione delle prenotazioni
    printf("Funzionalità in sviluppo...\n");
    printf("Premi INVIO per tornare al menu...");
    svuota_buffer();
}

void restituisci_auto() {
    set_color(14); // Giallo
    printf("=====================================\n");
    printf("       Restituisci Auto\n");
    printf("=====================================\n");
    set_color(7); // Bianco
    
    // TODO: Implementare la logica di restituzione
    printf("Funzionalità in sviluppo...\n");
    printf("Premi INVIO per tornare al menu...");
    svuota_buffer();
}

void visualizza_disponibilita() {
    int id_veicolo;
    CalendarioVeicolo calendario;
    CodaPrenotazioni* coda_prenotazioni = NULL;
    
    pulisci_schermo();
    set_color(11); // Ciano
    printf("=====================================\n");
    printf("       VISUALIZZA DISPONIBILITA\n");
    printf("=====================================\n");
    set_color(7); // Bianco
    
    // Visualizza lista veicoli disponibili
    printf("\nVeicoli disponibili:\n");
    list temp = get_lista_veicoli();
    while(temp != NULL) {
        stampa_veicolo(temp->veicoli);
        printf("-------------------\n");
        temp = temp->next;
    }
    
    // Chiedi l'ID del veicolo
    printf("\nInserisci l'ID del veicolo per visualizzare la disponibilita: ");
    scanf("%d", &id_veicolo);
    svuota_buffer();
    
    // Inizializza la coda delle prenotazioni se non esiste
    if (coda_prenotazioni == NULL) {
        coda_prenotazioni = inizializza_coda();
        if (coda_prenotazioni == NULL) {
            set_color(12); // Rosso
            printf("Errore nell'inizializzazione della coda prenotazioni!\n");
            set_color(7); // Bianco
            printf("Premi INVIO per tornare al menu...");
            svuota_buffer();
            return;
        }
    }
    
    // Carica le prenotazioni dal file
    carica_prenotazioni_da_file(coda_prenotazioni);
    
    // Inizializza e aggiorna il calendario
    inizializza_calendario(&calendario, id_veicolo);
    aggiorna_calendario(&calendario, coda_prenotazioni);
    
    // Visualizza il calendario
    visualizza_calendario(&calendario);
    
    printf("\nPremi INVIO per tornare al menu...");
    svuota_buffer();
}

void cleanup() {
    // Salva i dati prima di chiudere
    salva_lista_veicoli();
    
    // Libera la memoria
    pulisci_lista_veicoli();
}

int main() {
    int scelta;
    int stato = 0; // momentaneo
    
    // Carica i veicoli all'avvio
    carica_lista_veicoli();

  while (1) {
        pulisci_schermo();

        if (stato == 0) {
            set_color(13); //Magenta
            printf("=====================================\n");
            printf("        Sei un nuovo utente?\n");
            printf("=====================================\n");
            printf("1. Si, voglio registrarmi\n");
            printf("2. No, voglio accedere\n");
            printf("0. Esci\n");
            printf("-------------------------------------\n");  
            printf("Scelta: ");
            scanf("%d", &scelta);
            svuota_buffer();
            switch (scelta) {
                case 1:
                    pulisci_schermo();
                    Utente* nuovo_utente = malloc(sizeof(Utente));
                    if (nuovo_utente == NULL) {
                        set_color(12); // Rosso
                        printf("Errore: Memoria insufficiente per il nuovo utente.\n");
                        set_color(7); // Bianco
                        return 1;
                    }
                    printf("Inserisci il tuo nome completo: ");
                    fgets(nuovo_utente->nome_completo, sizeof(nuovo_utente->nome_completo), stdin); 
                    strtok(nuovo_utente->nome_completo, "\n"); // Rimuovi newline
                    printf("Inserisci il tuo username: ");
                    fgets(nuovo_utente->username, sizeof(nuovo_utente->username), stdin);
                    strtok(nuovo_utente->username, "\n"); // Rimuovi newline
                    nuovo_utente->isAdmin = 0; // Default: non admin
                    if (inserisci_utente(nuovo_utente->username, nuovo_utente->nome_completo) == 1) {
                        set_color(10); // Verde
                        printf("Registrazione completata con successo!\n");
                    } else {
                        set_color(12); // Rosso
                        printf("Errore: Registrazione fallita.\n");
                    }
                    stato=1;
                    break;
                case 2:
                    pulisci_schermo();
                    printf("Inserisci il tuo username: ");
                    char username[30];
                    fgets(username, sizeof(username), stdin);
                    strtok(username, "\n"); // Rimuovi newline
                    Utente* utente = cerca_utente(username);
                    if (utente == NULL) {
                        set_color(12); // Rosso
                        printf("Errore: Utente non trovato.\n");
                        stato=0;
                    } else {
                        set_color(10); // Verde
                        printf("Accesso effettuato con successo!\n");
                        printf("Benvenuto, %s!\n", utente->nome_completo);
                        stato=1;
                    }
                    stato=1;
                    break;       
        } 
        pulisci_schermo();
        
        
        
        set_color(13); // Magenta
        printf("=====================================\n");
        printf("       SISTEMA DI CAR SHARING\n");
        printf("=====================================\n");
        set_color(7); // Bianco

        // Opzioni del menu
        printf("1. Prenota un'auto\n");
        printf("2. Visualizza prenotazioni\n");
        printf("3. Restituisci auto\n");
        printf("4. Gestione Veicoli\n");
        printf("5. Visualizza disponibilita\n");
        printf("0. Esci\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuota_buffer();

        switch (scelta) {
            case 1:
                pulisci_schermo();
                prenota_auto();
                break;
            case 2:
                pulisci_schermo();
                visualizza_prenotazioni();
                break;
            case 3:
                pulisci_schermo();
                restituisci_auto();
                break;
            case 4:
                pulisci_schermo();
                gestione_veicoli();
                break;
            case 5:
                pulisci_schermo();
                visualizza_disponibilita();
                break;
            case 0:
                set_color(12); // Rosso
                printf("\nSalvataggio dei dati e chiusura del programma...\n");
                cleanup(); // Salva e pulisce prima di chiudere
                set_color(7); // Bianco
                return 0;
            default:
                set_color(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                set_color(7); // Bianco
                svuota_buffer();
                break;
        }
    }

    return 0;
}
}
