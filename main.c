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

// Funzione per impostare il colore del testo
void setColor(int color) {
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
void svuotaBuffer() {
    while (getchar() != '\n');
}

// Funzione per pulire lo schermo in modo cross-platform
void PulisciSchermo() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void gestioneVeicoli() {
    int scelta;
    
    do {
        PulisciSchermo();
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
        svuotaBuffer();

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
                svuotaBuffer();
                break;
            }
            case 4:
                salvaListaVeicoli();
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            case 5:
                caricaListaVeicoli();
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            case 0:
                break;
            default:
                setColor(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                setColor(7); // Bianco
                svuotaBuffer();
        }
    } while(scelta != 0);
}

void prenotaAuto() {
    int scelta;
    static CodaPrenotazioni* coda_prenotazioni = NULL;
    
    // Inizializza la coda delle prenotazioni se non esiste
    if (coda_prenotazioni == NULL) {
        coda_prenotazioni = inizializza_coda();
        if (coda_prenotazioni == NULL) {
            setColor(12); // Rosso
            printf("Errore nell'inizializzazione della coda prenotazioni!\n");
            setColor(7); // Bianco
            printf("Premi INVIO per tornare al menu...");
            svuotaBuffer();
            return;
        }
    }
    
    do {
        PulisciSchermo();
        setColor(10); // Verde
        printf("=====================================\n");
        printf("       PRENOTAZIONE AUTO\n");
        printf("=====================================\n");
        setColor(7); // Bianco
        
        printf("1. Nuova prenotazione\n");
        printf("2. Visualizza prenotazioni attive\n");
        printf("3. Cancella prenotazione\n");
        printf("4. Modifica stato prenotazione\n");
        printf("5. Salva prenotazioni su file\n");
        printf("0. Torna al menu principale\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuotaBuffer();

        switch(scelta) {
            case 1: {
                int id_utente, id_veicolo, giorno, ora_inizio, ora_fine, priorita;
                
                // Visualizza veicoli disponibili
                printf("\nVeicoli disponibili:\n");
                list temp = getListaVeicoli();
                while(temp != NULL) {
                    stampaVeicolo(temp->veicoli);
                    printf("-------------------\n");
                    temp = temp->next;
                }
                
                printf("\nInserisci i dati della prenotazione:\n");
                printf("ID Utente: ");
                scanf("%d", &id_utente);
                printf("ID Veicolo: ");
                scanf("%d", &id_veicolo);
                printf("Giorno (0-6, Lun-Dom): ");
                scanf("%d", &giorno);
                printf("Ora inizio (0-23): ");
                scanf("%d", &ora_inizio);
                printf("Ora fine (0-23): ");
                scanf("%d", &ora_fine);
                printf("Priorità (più bassa = più prioritaria): ");
                scanf("%d", &priorita);
                svuotaBuffer();
                
                Prenotazione nuova = crea_prenotazione(id_utente, id_veicolo, giorno, 
                                                     ora_inizio, ora_fine, priorita);
                
                int risultato = aggiungi_prenotazione(coda_prenotazioni, nuova);
                if (risultato == 0) {
                    setColor(10); // Verde
                    printf("\nPrenotazione aggiunta con successo!\n");
                } else if (risultato == -2) {
                    setColor(12); // Rosso
                    printf("\nErrore: Fascia oraria non valida!\n");
                } else {
                    setColor(12); // Rosso
                    printf("\nErrore nell'aggiunta della prenotazione!\n");
                }
                setColor(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            }
            case 2: {
                printf("\nPrenotazioni attive:\n");
                printf("-------------------\n");
                
                // Pulisci la coda esistente prima di caricare dal file
                pulisci_coda(coda_prenotazioni);
                
                // Carica le prenotazioni dal file
                caricaPrenotazioniDaFile(coda_prenotazioni);
                
                // Crea una coda temporanea per non perdere le prenotazioni
                CodaPrenotazioni* temp = inizializza_coda();
                if (temp == NULL) {
                    setColor(12); // Rosso
                    printf("Errore nella visualizzazione delle prenotazioni!\n");
                    setColor(7); // Bianco
                    break;
                }
                
                // Estrai e mostra tutte le prenotazioni
                while (coda_prenotazioni->dimensione > 0) {
                    Prenotazione p = rimuovi_prenotazione(coda_prenotazioni);
                    stampa_prenotazione(p);
                    printf("-------------------\n");
                    
                    // Reinserisci nella coda temporanea
                    aggiungi_prenotazione(temp, p);
                }
                
                // Ripristina la coda originale
                while (temp->dimensione > 0) {
                    Prenotazione p = rimuovi_prenotazione(temp);
                    aggiungi_prenotazione(coda_prenotazioni, p);
                }
                
                distruggi_coda(temp);
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            }
            case 3: {
                int id_prenotazione;
                printf("\nInserisci l'ID della prenotazione da cancellare: ");
                scanf("%d", &id_prenotazione);
                svuotaBuffer();
                
                Prenotazione* p = cerca_prenotazione(coda_prenotazioni, id_prenotazione);
                if (p != NULL) {
                    p->stato = CANCELLATA;
                    setColor(10); // Verde
                    printf("Prenotazione cancellata con successo!\n");
                } else {
                    setColor(12); // Rosso
                    printf("Prenotazione non trovata!\n");
                }
                setColor(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            }
            case 4: {
                int id_prenotazione, nuovo_stato;
                printf("\nInserisci l'ID della prenotazione: ");
                scanf("%d", &id_prenotazione);
                printf("Nuovo stato (0=In attesa, 1=Confermata, 2=Completata, 3=Cancellata): ");
                scanf("%d", &nuovo_stato);
                svuotaBuffer();
                
                int risultato = modifica_stato_prenotazione(coda_prenotazioni, id_prenotazione, nuovo_stato);
                if (risultato == 0) {
                    setColor(10); // Verde
                    printf("Stato modificato con successo!\n");
                } else {
                    setColor(12); // Rosso
                    printf("Errore nella modifica dello stato!\n");
                }
                setColor(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            }
            case 5:
                salvaPrenotazioniSuFile(coda_prenotazioni);
                printf("Prenotazioni salvate su file.\n");
                printf("Premi INVIO per continuare...");
                svuotaBuffer();
                break;
            case 0:
                break;
            default:
                setColor(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                setColor(7); // Bianco
                svuotaBuffer();
        }
    } while(scelta != 0);
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
    svuotaBuffer();
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
    svuotaBuffer();
}

void visualizzaDisponibilita() {
    int id_veicolo;
    CalendarioVeicolo calendario;
    CodaPrenotazioni* coda_prenotazioni = NULL;
    
    PulisciSchermo();
    setColor(11); // Ciano
    printf("=====================================\n");
    printf("       VISUALIZZA DISPONIBILITA\n");
    printf("=====================================\n");
    setColor(7); // Bianco
    
    // Visualizza lista veicoli disponibili
    printf("\nVeicoli disponibili:\n");
    list temp = getListaVeicoli();
    while(temp != NULL) {
        stampaVeicolo(temp->veicoli);
        printf("-------------------\n");
        temp = temp->next;
    }
    
    // Chiedi l'ID del veicolo
    printf("\nInserisci l'ID del veicolo per visualizzare la disponibilita: ");
    scanf("%d", &id_veicolo);
    svuotaBuffer();
    
    // Inizializza la coda delle prenotazioni se non esiste
    if (coda_prenotazioni == NULL) {
        coda_prenotazioni = inizializza_coda();
        if (coda_prenotazioni == NULL) {
            setColor(12); // Rosso
            printf("Errore nell'inizializzazione della coda prenotazioni!\n");
            setColor(7); // Bianco
            printf("Premi INVIO per tornare al menu...");
            svuotaBuffer();
            return;
        }
    }
    
    // Carica le prenotazioni dal file
    caricaPrenotazioniDaFile(coda_prenotazioni);
    
    // Inizializza e aggiorna il calendario
    inizializza_calendario(&calendario, id_veicolo);
    aggiorna_calendario(&calendario, coda_prenotazioni);
    
    // Visualizza il calendario
    visualizza_calendario(&calendario);
    
    printf("\nPremi INVIO per tornare al menu...");
    svuotaBuffer();
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
        PulisciSchermo();
        
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
        printf("5. Visualizza disponibilita\n");
        printf("0. Esci\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuotaBuffer();

        switch (scelta) {
            case 1:
                PulisciSchermo();
                prenotaAuto();
                break;
            case 2:
                PulisciSchermo();
                visualizzaPrenotazioni();
                break;
            case 3:
                PulisciSchermo();
                restituisciAuto();
                break;
            case 4:
                PulisciSchermo();
                gestioneVeicoli();
                break;
            case 5:
                PulisciSchermo();
                visualizzaDisponibilita();
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
                svuotaBuffer();
                break;
        }
    }

    return 0;
}
