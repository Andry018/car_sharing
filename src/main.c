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
    CodaPrenotazioni coda = get_coda_prenotazioni();
    if (coda != NULL) {
        rimuovi_prenotazioni_scadute(coda);
        aggiorna_priorita_prenotazioni(coda);
        salva_prenotazioni_su_file(coda);
    }
    
    int scelta;
    int stato = 0; // momentaneo
    char current_username[30] = "";
    
    // Carica i veicoli all'avvio
    carica_lista_veicoli();
    
    // Inizializza e carica gli utenti
    inizializza_tabella_utenti();
    if (!carica_utenti_file()) {
        printf("Errore nel caricamento degli utenti. Il programma potrebbe non funzionare correttamente.\n");
        printf("Premi INVIO per continuare...");
        svuota_buffer();
    }

    while (1) {
        pulisci_schermo();

        if (stato == 0) {
            mostra_menu_login();
            printf("Scelta: ");
            if(scanf("%d", &scelta) != 1) {
                scelta = -999;
            }
            svuota_buffer();
            
            switch (scelta) {
                case 1: { // Login
                    pulisci_schermo();
                    stampa_bordo_superiore();
                    
                    set_color(LIGHT_MAGENTA); // Magenta
                    printf("             LOGIN\n");
                    stampa_separatore();
                    
                    Utente temp_utente = NULL;
                    char username[30];
                    int username_valido = 0;
                    while (!username_valido) {
                        set_color(WHITE); // Bianco
                        printf("Username: ");
                        if (fgets(username, sizeof(username), stdin) == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Errore nella lettura dell'input!\n");
                            set_color(WHITE); // Bianco
                            continue;
                        }
                        
                        // Verifica se l'input è troppo lungo
                        if (strchr(username, '\n') == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Input troppo lungo! Massimo %zu caratteri.\n", sizeof(username) - 1);
                            set_color(WHITE); // Bianco
                            svuota_buffer();
                            continue;
                        }
                        
                        strtok(username, "\n"); // Rimuovi newline
                        
                        if (!valida_username(username)) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Username non valido! Deve contenere solo caratteri alfanumerici\n");
                            printf("e underscore, lunghezza tra 3 e 29 caratteri.\n");
                            set_color(WHITE); // Bianco
                        } else {
                            username_valido = 1;
                        }
                    }
                    
                    temp_utente = cerca_utente(username);
                    if (temp_utente == NULL) {
                        set_color(LIGHT_RED); // Rosso
                        printf("\nErrore: Utente non trovato!\n");
                        printf("Premi INVIO per tornare al menu principale...");
                        set_color(WHITE); // Bianco
                        svuota_buffer();
                    } else {
                        char password[MAX_PASSWORD_LENGTH];
                        int password_valida = 0;
                        while (!password_valida) {
                            set_color(WHITE); // Bianco
                            printf("Password: ");
                            if (fgets(password, sizeof(password), stdin) == NULL) {
                                set_color(LIGHT_RED); // Rosso
                                printf("Errore nella lettura dell'input!\n");
                                set_color(WHITE); // Bianco
                                continue;
                            }
                            
                            // Verifica se l'input è troppo lungo
                            if (strchr(password, '\n') == NULL) {
                                set_color(LIGHT_RED); // Rosso
                                printf("Input troppo lungo! Massimo %zu caratteri.\n", sizeof(password) - 1);
                                set_color(WHITE); // Bianco
                                svuota_buffer();
                                continue;
                            }
                            
                            strtok(password, "\n"); // Rimuovi newline
                            password_valida = 1;
                        }

                        if (verifica_password(password, temp_utente)) {
                            set_color(LIGHT_GREEN); // Verde
                            printf("\nAccesso effettuato con successo!\n");
                            printf("Benvenuto/a, %s!\n", get_nome_utente(username));
                            stato = 1;
                            strncpy(current_username, username, sizeof(current_username));
                            salva_utenti_file();
                            printf("\nPremi INVIO per continuare...");
                            set_color(WHITE); // Bianco
                            svuota_buffer();
                        } else {
                            set_color(LIGHT_RED); // Rosso
                            printf("\nPassword errata!\n");
                            printf("Premi INVIO per tornare al menu principale...");
                            set_color(WHITE); // Bianco
                            svuota_buffer();
                        }
                    }
                    break;
                }
                case 2: { // Registrazione
                    pulisci_schermo();
                    stampa_bordo_superiore();
                    
                    set_color(LIGHT_MAGENTA); // Magenta
                    printf("          REGISTRAZIONE\n");
                    stampa_separatore();
                    
                    char nome_completo[50];
                    char username[30];
                    
                    // Input e validazione nome completo
                    int nome_valido = 0;
                    while (!nome_valido) {
                        set_color(WHITE); // Bianco
                        printf("Nome completo: ");
                        if (fgets(nome_completo, sizeof(nome_completo), stdin) == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Errore nella lettura dell'input!\n");
                            set_color(WHITE); // Bianco
                            continue;
                        }
                        
                        // Verifica se l'input è troppo lungo
                        if (strchr(nome_completo, '\n') == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Input troppo lungo! Massimo %zu caratteri.\n", sizeof(nome_completo) - 1);
                            set_color(WHITE); // Bianco
                            svuota_buffer();
                            continue;
                        }
                        
                        strtok(nome_completo, "\n"); // Rimuovi newline
                        
                        if (!valida_nome_completo(nome_completo)) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Nome non valido! Usa solo lettere, spazi, apostrofi e trattini.\n");
                            printf("Lunghezza tra 3 e 49 caratteri.\n");
                            set_color(WHITE); // Bianco
                        } else {
                            nome_valido = 1;
                        }
                    }
                    
                    // Input e validazione username
                    int username_valido = 0;
                    while (!username_valido) {
                        set_color(WHITE); // Bianco
                        printf("Username: ");
                        if (fgets(username, sizeof(username), stdin) == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Errore nella lettura dell'input!\n");
                            set_color(WHITE); // Bianco
                            continue;
                        }
                        
                        // Verifica se l'input è troppo lungo
                        if (strchr(username, '\n') == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Input troppo lungo! Massimo %zu caratteri.\n", sizeof(username) - 1);
                            set_color(WHITE); // Bianco
                            svuota_buffer();
                            continue;
                        }
                        
                        strtok(username, "\n"); // Rimuovi newline
                        
                        if (!valida_username(username)) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Username non valido! Deve contenere solo caratteri alfanumerici\n");
                            printf("e underscore, lunghezza tra 3 e 29 caratteri.\n");
                            set_color(WHITE); // Bianco
                        } else if (cerca_utente(username) != NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Username già in uso! Scegline un altro.\n");
                            set_color(WHITE); // Bianco
                        } else {
                            username_valido = 1;
                        }
                    }
                    
                    // Input password
                    char password[MAX_PASSWORD_LENGTH];
                    int password_valida = 0;
                    while (!password_valida) {
                        set_color(WHITE); // Bianco
                        printf("Password: ");
                        if (fgets(password, sizeof(password), stdin) == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Errore nella lettura dell'input!\n");
                            set_color(WHITE); // Bianco
                            continue;
                        }
                        
                        // Verifica se l'input è troppo lungo
                        if (strchr(password, '\n') == NULL) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Input troppo lungo! Massimo %zu caratteri.\n", sizeof(password) - 1);
                            set_color(WHITE); // Bianco
                            svuota_buffer();
                            continue;
                        }
                        
                        strtok(password, "\n"); // Rimuovi newline
                        
                        if (strlen(password) < 4) {
                            set_color(LIGHT_RED); // Rosso
                            printf("Password troppo corta! Minimo 4 caratteri.\n");
                            set_color(WHITE); // Bianco
                        } else {
                            password_valida = 1;
                        }
                    }

                    char hashed[MAX_PASSWORD_LENGTH];
                    hash_password(password, hashed);

                    if (inserisci_utente(username, nome_completo, hashed)) {
                        set_color(LIGHT_GREEN); // Verde
                        printf("\nRegistrazione completata con successo!\n");
                        stato = 1;
                        strncpy(current_username, username, sizeof(current_username));
                        salva_utenti_file();  // Salvo gli utenti dopo la registrazione
                    } else {
                        set_color(LIGHT_RED); // Rosso
                        printf("\nErrore: Registrazione fallita.\n");
                    }
                    
                    printf("\nPremi INVIO per continuare...");
                    set_color(WHITE); // Bianco
                    svuota_buffer();
                    break;
                }
                case 0: // Uscita
                    set_color(LIGHT_RED); // Rosso
                    printf("\nChiusura del programma...\n");
                    salvataggio();
                    set_color(WHITE); // Bianco
                    return 0;
                default:
                    set_color(LIGHT_RED); // Rosso
                    printf("\nScelta non valida! Premi INVIO per riprovare...");
                    set_color(WHITE); // Bianco
                    svuota_buffer();
                    break;
            }
        } else {
            pulisci_schermo();
            
            if (get_isAdmin_utente(cerca_utente(current_username))) {
                mostra_menu_admin(cerca_utente(current_username));
            } else {
                mostra_menu_cliente(cerca_utente(current_username));
            }
            
            printf("Scelta: ");
            if(scanf("%d", &scelta) != 1) {
                scelta = -999;
            }
            svuota_buffer();

            if (get_isAdmin_utente(cerca_utente(current_username))) {
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
                        gestione_utenti_admin();
                        break;
                    case 4:
                        pulisci_schermo();
                        visualizza_prenotazioni(cerca_utente(current_username));
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
                        CodaPrenotazioni coda = get_coda_prenotazioni();
                        if (coda != NULL) {
                            rimuovi_prenotazioni_scadute(coda);
                            salva_lista_veicoli();
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
                        current_username[0] = '\0';
                        break;
                    case 0:
                        set_color(LIGHT_RED); // Rosso
                        printf("\nSalvataggio dei dati e chiusura del programma...\n");
                        salvataggio();
                        set_color(WHITE); // Bianco
                        return 0;
                    default:
                        set_color(LIGHT_RED); // Rosso
                        printf("\nScelta non valida. Premi INVIO per riprovare...");
                        set_color(WHITE); // Bianco
                        svuota_buffer();
                        break;
                }
            } else {
                // Menu Cliente
                switch (scelta) {
                    case 1:
                        pulisci_schermo();
                        prenota_auto(cerca_utente(current_username));
                        break;
                    case 2:
                        pulisci_schermo();
                        visualizza_prenotazioni(cerca_utente(current_username));
                        break;
                    case 3:
                        pulisci_schermo();
                        visualizza_disponibilita();
                        break;
                    case 4:
                        pulisci_schermo();
                        visualizza_tariffe(cerca_utente(current_username));
                        break;
                    case 5:
                        stato = 0;  // Torna al menu di login
                        current_username[0] = '\0';
                        break;
                    case 0:
                        set_color(LIGHT_RED); // Rosso
                        printf("\nSalvataggio dei dati e chiusura del programma...\n");
                        salvataggio();
                        set_color(WHITE); // Bianco
                        return 0;
                    default:
                        set_color(LIGHT_RED); // Rosso
                        printf("\nScelta non valida. Premi INVIO per riprovare...");
                        set_color(WHITE); // Bianco
                        svuota_buffer();
                        break;
                }
            }
        }
    }

    return 0;
}
