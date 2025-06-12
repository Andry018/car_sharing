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
    CodaPrenotazioni coda = ottieni_coda_prenotazioni();
    if (coda != NULL) {
        rimuovi_prenotazioni_scadute(coda);
        aggiorna_priorita_prenotazioni(coda);
        salva_prenotazioni_su_file(coda);
    }
    
    int scelta;
    int stato = 0; // momentaneo
    char utente_corrente[30] = "";
    
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
                    
                    imposta_colore(13); // Magenta
                    printf("             LOGIN\n");
                    stampa_separatore();
                    
                    Utente temp_utente = NULL;
                    char nome_utente[30];
                    do {
                        imposta_colore(7); // Bianco
                        printf("Nome Utente: ");
                        fgets(nome_utente, sizeof(nome_utente), stdin);
                        strtok(nome_utente, "\n"); // Rimuovi nuova linea
                        
                        if (!valida_nome_utente(nome_utente)) {
                            imposta_colore(12); // Rosso
                            printf("Nome utente non valido! Deve contenere solo caratteri alfanumerici\n");
                            printf("e trattino basso, lunghezza tra 3 e 29 caratteri.\n");
                            imposta_colore(7); // Bianco
                        }
                    } while (!valida_nome_utente(nome_utente));
                    
                    temp_utente = cerca_utente(nome_utente);
                    if (temp_utente == NULL) {
                        imposta_colore(12); // Rosso
                        printf("\nErrore: Utente non trovato!\n");
                        printf("Premi INVIO per tornare al menu principale...");
                        imposta_colore(7); // Bianco
                        svuota_buffer();
                    } else {
                        char password[MAX_PASSWORD_LENGTH];
                        imposta_colore(7); // Bianco
                        printf("Password: ");
                        fgets(password, sizeof(password), stdin);
                        strtok(password, "\n");

                        if (verifica_password(password, temp_utente)) {
                            imposta_colore(10); // Verde
                            printf("\nAccesso effettuato con successo!\n");
                            printf("Benvenuto/a, %s!\n", ottieni_nome_utente(temp_utente));
                            stato = 1;
                            strncpy(utente_corrente, nome_utente, sizeof(utente_corrente));
                            salva_utenti_file();
                            printf("\nPremi INVIO per continuare...");
                            imposta_colore(7); // Bianco
                            svuota_buffer();
                        } else {
                            imposta_colore(12); // Rosso
                            printf("\nPassword errata!\n");
                            printf("Premi INVIO per tornare al menu principale...");
                            imposta_colore(7); // Bianco
                            svuota_buffer();
                        }
                    }
                    break;
                }
                case 2: { // Registrazione
                    pulisci_schermo();
                    stampa_bordo_superiore();
                    
                    imposta_colore(13); // Magenta
                    printf("          REGISTRAZIONE\n");
                    stampa_separatore();
                    
                    char nome_completo[50];
                    char nome_utente[30];
                    
                    // Input e validazione nome completo
                    do {
                        imposta_colore(7); // Bianco
                        printf("Nome completo: ");
                        fgets(nome_completo, sizeof(nome_completo), stdin);
                        strtok(nome_completo, "\n");
                        
                        if (!valida_nome_completo(nome_completo)) {
                            imposta_colore(12); // Rosso
                            printf("Nome non valido! Usa solo lettere, spazi, apostrofi e trattini.\n");
                            printf("Lunghezza tra 3 e 49 caratteri.\n");
                            imposta_colore(7); // Bianco
                        }
                    } while (!valida_nome_completo(nome_completo));
                    
                    // Input e validazione nome utente
                    do {
                        imposta_colore(7); // Bianco
                        printf("Nome Utente: ");
                        fgets(nome_utente, sizeof(nome_utente), stdin);
                        strtok(nome_utente, "\n");
                        
                        if (!valida_nome_utente(nome_utente)) {
                            imposta_colore(12); // Rosso
                            printf("Nome Utente non valido! Usa solo caratteri alfanumerici e underscore.\n");
                            printf("Lunghezza tra 3 e 29 caratteri.\n");
                            imposta_colore(7); // Bianco
                        } else if (cerca_utente(nome_utente) != NULL) {
                            imposta_colore(12); // Rosso
                            printf("Nome Utente già in uso! Scegline un altro.\n");
                            imposta_colore(7); // Bianco
                            continue;
                        }
                    } while (!valida_nome_utente(nome_utente) || 
                            cerca_utente(nome_utente) != NULL);
                    
                    char password[MAX_PASSWORD_LENGTH];
                    do {
                        imposta_colore(7); // Bianco
                        printf("Password: ");
                        fgets(password, sizeof(password), stdin);
                        strtok(password, "\n");
                        if (strlen(password) < 4) {
                            imposta_colore(12); // Rosso
                            printf("Password troppo corta! Minimo 4 caratteri.\n");
                            imposta_colore(7); // Bianco
                        }
                    } while (strlen(password) < 4);

                    char hashed[MAX_PASSWORD_LENGTH];
                    hash_password(password, hashed);

                    if (inserisci_utente(nome_utente, nome_completo, hashed)) {
                        imposta_colore(10); // Verde
                        printf("\nRegistrazione completata con successo!\n");
                        stato = 1;
                        strncpy(utente_corrente, nome_utente, sizeof(utente_corrente));
                        salva_utenti_file();  // Salvo gli utenti dopo la registrazione
                    } else {
                        imposta_colore(12); // Rosso
                        printf("\nErrore: Registrazione fallita.\n");
                    }
                    
                    printf("\nPremi INVIO per continuare...");
                    imposta_colore(7); // Bianco
                    svuota_buffer();
                    break;
                }
                case 0: // Uscita
                    imposta_colore(12); // Rosso
                    printf("\nChiusura del programma...\n");
                    salvataggio();
                    imposta_colore(7); // Bianco
                    return 0;
                default:
                    imposta_colore(12); // Rosso
                    printf("\nScelta non valida! Premi INVIO per riprovare...");
                    imposta_colore(7); // Bianco
                    svuota_buffer();
                    break;
            }
        } else {
            pulisci_schermo();
            
            if (ottieni_isamministratore_utente(cerca_utente(utente_corrente))) {
                mostra_menu_amministratore(cerca_utente(utente_corrente));
            } else {
                mostra_menu_cliente(cerca_utente(utente_corrente));
            }
            
            printf("Scelta: ");
            if(scanf("%d", &scelta) != 1) {
                scelta = -999;
            }
            svuota_buffer();

            if (ottieni_isamministratore_utente(cerca_utente(utente_corrente))) {
                // Menu amministratore
                switch (scelta) {
                    case 1:
                        pulisci_schermo();
                        gestione_veicoli();
                        break;
                    case 2:
                        pulisci_schermo();
                        gestione_prenotazioni_amministratore();
                        break;
                    case 3:
                        pulisci_schermo();
                        gestione_utenti_amministratore();
                        break;
                    case 4:
                        pulisci_schermo();
                        visualizza_prenotazioni(cerca_utente(utente_corrente));
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
                        CodaPrenotazioni coda = ottieni_coda_prenotazioni();
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
                        utente_corrente[0] = '\0';
                        break;
                    case 0:
                        imposta_colore(12); // Rosso
                        printf("\nSalvataggio dei dati e chiusura del programma...\n");
                        salvataggio();
                        imposta_colore(7); // Bianco
                        return 0;
                    default:
                        imposta_colore(12); // Rosso
                        printf("\nScelta non valida. Premi INVIO per riprovare...");
                        imposta_colore(7); // Bianco
                        svuota_buffer();
                        break;
                }
            } else {
                // Menu Cliente
                switch (scelta) {
                    case 1:
                        pulisci_schermo();
                        prenota_auto(cerca_utente(utente_corrente));
                        break;
                    case 2:
                        pulisci_schermo();
                        visualizza_prenotazioni(cerca_utente(utente_corrente));
                        break;
                    case 3:
                        pulisci_schermo();
                        visualizza_disponibilita();
                        break;
                    case 4:
                        pulisci_schermo();
                        visualizza_tariffe(cerca_utente(utente_corrente));
                        break;
                    case 5:
                        stato = 0;  // Torna al menu di login
                        utente_corrente[0] = '\0';
                        break;
                    case 0:
                        imposta_colore(12); // Rosso
                        printf("\nSalvataggio dei dati e chiusura del programma...\n");
                        salvataggio();
                        imposta_colore(7); // Bianco
                        return 0;
                    default:
                        imposta_colore(12); // Rosso
                        printf("\nScelta non valida. Premi INVIO per riprovare...");
                        imposta_colore(7); // Bianco
                        svuota_buffer();
                        break;
                }
            }
        }
    }

    return 0;
}
