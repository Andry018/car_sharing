#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "veicolo.h"
#include "prenotazioni.h"
#include "fasce_orarie.h"
#include "utenti.h"
#include "tariffe.h"
#include "menu.h"
#include "f_utili.h"





int main() {
    // Inizializza la data di sistema
    inizializza_data_sistema();
    
    // Inizializza la coda delle prenotazioni
    carica_prenotazioni();
    
    // Aggiorna le prenotazioni scadute
    CodaPrenotazioni* coda = get_coda_prenotazioni();
    if (coda != NULL) {
        rimuovi_prenotazioni_scadute(coda);
        aggiorna_priorita_prenotazioni(coda);
        salva_prenotazioni_su_file(coda);
    }
    
    int scelta;
    int stato = 0; // momentaneo
    Utente* current_user = NULL;  // Aggiungiamo un puntatore all'utente corrente
    
    // Carica i veicoli all'avvio
    carica_lista_veicoli();
    
    // Inizializza e carica gli utenti
    inizializza_tabella_utenti();
    carica_utenti_file();

    while (1) {
        pulisci_schermo();

        if (stato == 0) {
            mostra_menu_login();
            printf("Scelta: ");
            scanf("%d", &scelta);
            svuota_buffer();
            
            switch (scelta) {
                case 1: { // Login
                    pulisci_schermo();
                    stampa_bordo_superiore();
                    
                    set_color(13); // Magenta
                    printf("             LOGIN\n");
                    stampa_separatore();
                    
                    char username[30];
                    do {
                        set_color(7); // Bianco
                        printf("Username: ");
                        fgets(username, sizeof(username), stdin);
                        strtok(username, "\n"); // Rimuovi newline
                        
                        if (!valida_username(username)) {
                            set_color(12); // Rosso
                            printf("Username non valido! Deve contenere solo caratteri alfanumerici\n");
                            printf("e underscore, lunghezza tra 3 e 29 caratteri.\n");
                            set_color(7); // Bianco
                        }
                    } while (!valida_username(username));
                    
                    current_user = cerca_utente(username);
                    if (current_user == NULL) {
                        set_color(12); // Rosso
                        printf("\nErrore: Utente non trovato!\n");
                        printf("Premi INVIO per tornare al menu principale...");
                        set_color(7); // Bianco
                        svuota_buffer();
                    } else {
                        set_color(10); // Verde
                        printf("\nAccesso effettuato con successo!\n");
                        printf("Benvenuto, %s!\n", current_user->nome_completo);
                        stato = 1;
                        printf("\nPremi INVIO per continuare...");
                        set_color(7); // Bianco
                        svuota_buffer();
                    }
                    break;
                }
                case 2: { // Registrazione
                    pulisci_schermo();
                    stampa_bordo_superiore();
                    
                    set_color(13); // Magenta
                    printf("          REGISTRAZIONE\n");
                    stampa_separatore();
                    
                    Utente* nuovo_utente = malloc(sizeof(Utente));
                    if (nuovo_utente == NULL) {
                        set_color(12); // Rosso
                        printf("Errore: Memoria insufficiente.\n");
                        set_color(7); // Bianco
                        return 1;
                    }
                    
                    // Input e validazione nome completo
                    do {
                        set_color(7); // Bianco
                        printf("Nome completo: ");
                        fgets(nuovo_utente->nome_completo, sizeof(nuovo_utente->nome_completo), stdin);
                        strtok(nuovo_utente->nome_completo, "\n");
                        
                        if (!valida_nome_completo(nuovo_utente->nome_completo)) {
                            set_color(12); // Rosso
                            printf("Nome non valido! Usa solo lettere, spazi, apostrofi e trattini.\n");
                            printf("Lunghezza tra 3 e 49 caratteri.\n");
                            set_color(7); // Bianco
                        }
                    } while (!valida_nome_completo(nuovo_utente->nome_completo));
                    
                    // Input e validazione username
                    do {
                        set_color(7); // Bianco
                        printf("Username: ");
                        fgets(nuovo_utente->username, sizeof(nuovo_utente->username), stdin);
                        strtok(nuovo_utente->username, "\n");
                        
                        if (!valida_username(nuovo_utente->username)) {
                            set_color(12); // Rosso
                            printf("Username non valido! Usa solo caratteri alfanumerici e underscore.\n");
                            printf("Lunghezza tra 3 e 29 caratteri.\n");
                            set_color(7); // Bianco
                        } else if (cerca_utente(nuovo_utente->username) != NULL) {
                            set_color(12); // Rosso
                            printf("Username già in uso! Scegline un altro.\n");
                            set_color(7); // Bianco
                            continue;
                        }
                    } while (!valida_username(nuovo_utente->username) || 
                            cerca_utente(nuovo_utente->username) != NULL);
                    
                    nuovo_utente->isAdmin = 0; // Default: non admin
                    
                    if (inserisci_utente(nuovo_utente->username, nuovo_utente->nome_completo)) {
                        set_color(10); // Verde
                        printf("\nRegistrazione completata con successo!\n");
                        current_user = cerca_utente(nuovo_utente->username);
                        stato = 1;
                    } else {
                        set_color(12); // Rosso
                        printf("\nErrore: Registrazione fallita.\n");
                    }
                    
                    free(nuovo_utente);
                    salva_utenti_file();
                    
                    printf("\nPremi INVIO per continuare...");
                    set_color(7); // Bianco
                    svuota_buffer();
                    break;
                }
                case 0: // Uscita
                    set_color(12); // Rosso
                    printf("\nChiusura del programma...\n");
                    salvataggio();
                    set_color(7); // Bianco
                    return 0;
                default:
                    set_color(12); // Rosso
                    printf("\nScelta non valida! Premi INVIO per riprovare...");
                    set_color(7); // Bianco
                    svuota_buffer();
                    break;
            }
        } else {
            pulisci_schermo();
            
            if (current_user->isAdmin) {
                mostra_menu_admin(current_user);
            } else {
                mostra_menu_cliente(current_user);
            }
            
            printf("Scelta: ");
            scanf("%d", &scelta);
            svuota_buffer();

            if (current_user->isAdmin) {
                // Menu Admin
                switch (scelta) {
                    case 1:
                        pulisci_schermo();
                        gestione_veicoli();
                        break;
                    case 2:
                        pulisci_schermo();
                        gestione_prenotazioni_admin();
                        break;
                    case 3:
                        pulisci_schermo();
                        visualizza_prenotazioni();
                        break;
                    case 4:
                        pulisci_schermo();
                        // TODO: Implementare gestione_utenti();
                        printf("Funzionalita' in sviluppo...\n");
                        printf("Premi INVIO per continuare...");
                        svuota_buffer();
                        break;
                    case 5:
                        pulisci_schermo();
                        visualizza_disponibilita();
                        break;
                    case 6: {
                        pulisci_schermo();
                        int ore;
                        printf("Inserisci il numero di ore da avanzare: ");
                        scanf("%d", &ore);
                        svuota_buffer();
                        
                        avanza_tempo(ore);
                        CodaPrenotazioni* coda = get_coda_prenotazioni();
                        if (coda != NULL) {
                            rimuovi_prenotazioni_scadute(coda);
                            aggiorna_priorita_prenotazioni(coda);
                            salva_prenotazioni_su_file(coda);
                        }
                        
                        printf("Tempo sistema avanzato.\n");
                        stampa_data_sistema();
                        printf("Premi INVIO per continuare...");
                        svuota_buffer();
                        break;
                    }
                    case 7:
                        stato = 0;  // Torna al menu di login
                        current_user = NULL;
                        break;
                    case 0:
                        set_color(12); // Rosso
                        printf("\nSalvataggio dei dati e chiusura del programma...\n");
                        salvataggio();
                        set_color(7); // Bianco
                        return 0;
                    default:
                        set_color(12); // Rosso
                        printf("\nScelta non valida. Premi INVIO per riprovare...");
                        set_color(7); // Bianco
                        svuota_buffer();
                        break;
                }
            } else {
                // Menu Cliente
                switch (scelta) {
                    case 1:
                        pulisci_schermo();
                        prenota_auto(current_user);
                        break;
                    case 2:
                        pulisci_schermo();
                        visualizza_prenotazioni();
                        break;
                    case 3:
                        pulisci_schermo();
                        visualizza_disponibilita();
                        break;
                    case 4:
                        pulisci_schermo();
                        visualizza_tariffe(current_user);
                        break;
                    case 5:
                        stato = 0;  // Torna al menu di login
                        current_user = NULL;
                        break;
                    case 0:
                        set_color(12); // Rosso
                        printf("\nSalvataggio dei dati e chiusura del programma...\n");
                        salvataggio();
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
        }
    }

    return 0;
}
