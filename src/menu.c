#include "menu.h"
#include <ctype.h>
#include "veicolo.h"  // Aggiungiamo l'include per la definizione di struct Veicolo
#include "f_utili.h"

/**
 * @brief Gestisce le operazioni relative ai veicoli.
 * @details Permette di aggiungere, rimuovere e visualizzare i veicoli nel sistema.
 * Questa funzione è accessibile solo agli amministratori.
 */
void gestione_veicoli() {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        
        imposta_colore(COLORE_MAGENTA);
        printf("         GESTIONE VEICOLI\n");
        
        stampa_separatore();
        
        // Sezione Operazioni
        imposta_colore(COLORE_GIALLO);
        printf("           OPERAZIONI\n");
        imposta_colore(COLORE_BIANCO);
        printf("1. Aggiungi veicolo\n");
        printf("2. Rimuovi veicolo\n");
        printf("3. Visualizza tutti i veicoli\n");
        
        stampa_separatore();
        
        // Sezione Navigazione
        imposta_colore(COLORE_ROSSO);
        printf("           NAVIGAZIONE\n");
        imposta_colore(COLORE_BIANCO);
        printf("0. Torna al menu principale\n");
        
        stampa_bordo_inferiore();
        printf("Scelta: ");
        if(scanf("%d", &scelta) != 1) {
            scelta = -999;
            svuota_buffer();
            imposta_colore(COLORE_ROSSO);
            printf("\nErrore: Inserisci un numero valido!\n");
            imposta_colore(COLORE_BIANCO);
            printf("Premi INVIO per riprovare...");
            svuota_buffer();
            continue;
        }
        svuota_buffer();

        switch(scelta) {
            case 1: {
                pulisci_schermo();
                stampa_bordo_superiore();
                
                imposta_colore(COLORE_MAGENTA);
                printf("         AGGIUNGI VEICOLO\n");
                
                stampa_separatore();
                
                // Mostra la data di sistema corrente
                imposta_colore(COLORE_GIALLO);
                printf("         DATA DI SISTEMA\n");
                imposta_colore(COLORE_BIANCO);
                stampa_data_sistema();
                
                stampa_separatore();
                
                // Sezione Input
                imposta_colore(COLORE_VERDE);
                printf("     INSERIMENTO DATI VEICOLO\n");
                imposta_colore(COLORE_BIANCO);
                
                Veicolo v = crea_veicolo();
                if (v == NULL) {
                    imposta_colore(COLORE_ROSSO);
                    printf("Errore nell'allocazione della memoria!\n");
                    imposta_colore(COLORE_BIANCO);
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }

                imposta_id_veicolo(v, carica_ultimo_id() + 1);
                imposta_disponibilita_veicolo(v, 1);

                // Aggiungi il veicolo alla lista
                list nuova_lista = aggiungi_veicolo(ottieni_lista_veicoli());
                if (nuova_lista == NULL) {
                    free(v);
                    imposta_colore(COLORE_ROSSO);
                    printf("Errore nell'aggiunta del veicolo!\n");
                    imposta_colore(COLORE_BIANCO);
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }

                imposta_lista_veicoli(nuova_lista);
                salva_lista_veicoli();

                imposta_colore(COLORE_VERDE);
                printf("\nVeicolo aggiunto con successo!\n");
                imposta_colore(COLORE_BIANCO);
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 2: {
                pulisci_schermo();
                stampa_bordo_superiore();
                
                imposta_colore(COLORE_MAGENTA);
                printf("         RIMUOVI VEICOLO\n");
                
                stampa_separatore();
                
                // Mostra la data di sistema corrente
                imposta_colore(COLORE_GIALLO);
                printf("         DATA DI SISTEMA\n");
                imposta_colore(COLORE_BIANCO);
                stampa_data_sistema();
                
                stampa_separatore();
                
                // Sezione Input
                imposta_colore(COLORE_VERDE);
                printf("     RIMUOVI VEICOLO\n");
                imposta_colore(COLORE_BIANCO);
                
                // Visualizza veicoli disponibili
                list temp = ottieni_lista_veicoli();
                bool trovato = false;
                while(temp != NULL) {
                    Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                    if (!v) {
                        temp = ottieni_successivo_nodo(temp);
                        continue;
                    }
                    stampa_veicolo(v);
                    trovato = true;
                    if (ottieni_successivo_nodo(temp) != NULL) {
                        stampa_separatore();
                    }
                    temp = ottieni_successivo_nodo(temp);
                }
                
                if (!trovato) {
                    imposta_colore(COLORE_ROSSO);
                    printf("  Nessun veicolo disponibile\n");
                    imposta_colore(COLORE_BIANCO);
                    stampa_bordo_inferiore();
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                stampa_separatore();
                
                int id;
                bool id_valido = false;
                do {
                    printf("Inserisci l'ID del veicolo da rimuovere: ");
                    if(scanf("%d", &id) != 1) {
                        svuota_buffer();
                        imposta_colore(COLORE_ROSSO);
                        printf("Errore: Inserisci un numero valido!\n");
                        imposta_colore(COLORE_BIANCO);
                        printf("Premi INVIO per riprovare...");
                        svuota_buffer();
                        continue;
                    }
                    svuota_buffer();
                    
                    // Verifica che il veicolo esista
                    list temp2 = ottieni_lista_veicoli();
                    bool veicolo_trovato = false;
                    while(temp2 != NULL) {
                        Veicolo v = ottieni_veicolo_senza_rimuovere(temp2);
                        if (!v) {
                            temp2 = ottieni_successivo_nodo(temp2);
                            continue;
                        }
                        if (ottieni_id_veicolo(v) == id) {
                            veicolo_trovato = true;
                            break;
                        }
                        temp2 = ottieni_successivo_nodo(temp2);
                    }
                    
                    if (!veicolo_trovato) {
                        imposta_colore(COLORE_ROSSO);
                        printf("Errore: Veicolo non trovato!\n");
                        imposta_colore(COLORE_BIANCO);
                        printf("Premi INVIO per riprovare...");
                        svuota_buffer();
                        continue;
                    }
                    
                    id_valido = true;
                } while (!id_valido);
                
                list nuova_lista = rimuovi_veicolo(ottieni_lista_veicoli(), id);
                imposta_lista_veicoli(nuova_lista);
                salva_lista_veicoli();
                imposta_colore(COLORE_VERDE);
                printf("\nVeicolo rimosso con successo!\n");
                imposta_colore(COLORE_BIANCO);
                stampa_bordo_inferiore();
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 3: {
                pulisci_schermo();
                stampa_bordo_superiore();
                
                imposta_colore(COLORE_MAGENTA);
                printf("       ELENCO DEI VEICOLI\n");
                
                stampa_separatore();
                
                list temp = ottieni_lista_veicoli();
                if (temp == NULL) {
                    imposta_colore(COLORE_ROSSO);
                    printf("  Nessun veicolo disponibile\n");
                    imposta_colore(COLORE_BIANCO);
                } else {
                    while(temp != NULL) {
                        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                        if (!v) {
                            temp = ottieni_successivo_nodo(temp);
                            continue;
                        }
                       
                        if (ottieni_disponibilita_veicolo(v) == 1) {
                            stampa_veicolo(v);
                            int tipo = ottieni_tipo_veicolo(v);
                            printf("Tariffa oraria: %.2f euro\n", ottieni_tariffa_oraria(tipo));
                        }
                        temp = ottieni_successivo_nodo(temp);
                    }
                }
                
                stampa_bordo_inferiore();
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                free(temp);
                svuota_buffer();
                break;
            }
            case 0:{
                printf("\nTornando al menu principale...\n");
                break;
            }
            default:
                imposta_colore(COLORE_ROSSO);
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                imposta_colore(COLORE_BIANCO);
                svuota_buffer();
        }
        //svuota_buffer();
        
    } while(scelta != 0);
}

/**
 * @brief Gestisce il processo di prenotazione di un veicolo.
 * @param utente_corrente L'utente che effettua la prenotazione.
 * @details Permette all'utente di selezionare un veicolo, scegliere data e ora di inizio e fine prenotazione, e confermare la prenotazione.
 */
void prenota_auto(Utente utente_corrente) {
    int scelta;
    CodaPrenotazioni coda_prenotazioni = ottieni_coda_prenotazioni();
    
    if (coda_prenotazioni == NULL) {
        imposta_colore(COLORE_ROSSO);
        printf("Errore nel sistema di prenotazioni!\n");
        imposta_colore(COLORE_BIANCO);
        printf("Premi INVIO per tornare al menu...");
        svuota_buffer();
        return;
    }
    
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        
        imposta_colore(COLORE_MAGENTA);
        printf("         GESTIONE PRENOTAZIONI\n");
        
        // Mostra la data di sistema corrente
        stampa_separatore();
        imposta_colore(COLORE_GIALLO);
        printf("         DATA DI SISTEMA\n");
        imposta_colore(COLORE_BIANCO);
        stampa_data_sistema();
        
        stampa_separatore();
        
        // Sezione Prenotazioni
        imposta_colore(COLORE_VERDE);
        printf("          PRENOTAZIONI\n");
        imposta_colore(COLORE_BIANCO);
        printf("1. Nuova prenotazione\n");
        printf("2. Visualizza prenotazioni\n");
        printf("3. Cancella prenotazione\n");
        //printf("4. Modifica stato prenotazione\n");
        
        stampa_separatore();
        
        // Sezione Informazioni
        imposta_colore(COLORE_GIALLO);
        printf("          INFORMAZIONI\n");
        imposta_colore(COLORE_BIANCO);
        printf("4. Visualizza tariffe\n");
        printf("5. Avanza tempo sistema\n");
        
        stampa_separatore();
        
        // Sezione Navigazione
        imposta_colore(COLORE_ROSSO);
        printf("           NAVIGAZIONE\n");
        imposta_colore(COLORE_BIANCO);
        printf("0. Torna al menu principale\n");
        
        stampa_bordo_inferiore();
        printf("Scelta: ");
        if(scanf("%d", &scelta) != 1) {
            scelta = -999;
        }
        svuota_buffer();

        switch(scelta) {
            case 1: {
                int id_veicolo, giorno_inizio, ora_inizio, giorno_fine, ora_fine;
                list temp;
                bool id_valido = false;
                Veicolo veicolo_selezionato = NULL;
                do {
                    pulisci_schermo();
                    stampa_bordo_superiore();
                    
                    imposta_colore(COLORE_MAGENTA);
                    printf("         NUOVA PRENOTAZIONE\n");
                    
                    stampa_separatore();
                    
                    // Mostra la data di sistema corrente
                    imposta_colore(COLORE_GIALLO);
                    printf("         DATA DI SISTEMA\n");
                    imposta_colore(COLORE_BIANCO);
                    stampa_data_sistema();
                    
                    stampa_separatore();
                    
                    // Visualizza veicoli disponibili con tariffe
                    imposta_colore(COLORE_VERDE);
                    printf("     VEICOLI DISPONIBILI\n");
                    imposta_colore(COLORE_BIANCO);
                    temp = ottieni_lista_veicoli();
                    bool trovato = false;
                    while(temp != NULL) {
                        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                        if (!v) continue;
                        if (ottieni_disponibilita_veicolo(v) == 1) {  // Mostra solo i veicoli disponibili
                            stampa_veicolo(v);
                            int tipo = ottieni_tipo_veicolo(v);
                            printf("Tariffa oraria: %.2f euro\n", ottieni_tariffa_oraria(tipo));
                            trovato = true;
                            if(ottieni_id_veicolo(v)!=1){
                                stampa_separatore();
                            }
                        }
                        temp = ottieni_successivo_nodo(temp);
                    }
                    
                    if (!trovato) {
                        imposta_colore(COLORE_ROSSO);
                        printf("Nessun veicolo disponibile al momento.\n");
                        imposta_colore(COLORE_BIANCO);
                        printf("Premi INVIO per tornare al menu...");
                        svuota_buffer();
                        return;
                    }
                    
                    stampa_separatore();
                    
                    printf("ID Veicolo: ");
                    if(scanf("%d", &id_veicolo) != 1) {
                        svuota_buffer();
                        imposta_colore(COLORE_ROSSO);
                        printf("Errore: Inserisci un numero valido!\n");
                        imposta_colore(COLORE_BIANCO);
                        printf("Premi INVIO per riprovare...");
                        svuota_buffer();
                        continue;
                    }
                    svuota_buffer();
                    
                    // Trova il veicolo per mostrare il costo
                    temp = ottieni_lista_veicoli();
                    veicolo_selezionato = NULL;  // Reset della variabile
                    while(temp != NULL) {
                        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                        if (!v) continue;
                        int id = ottieni_id_veicolo(v);
                        if (id == id_veicolo) {
                            veicolo_selezionato = v;
                            break;
                        }
                        temp = ottieni_successivo_nodo(temp);
                    }
                    
                    if(veicolo_selezionato == NULL) {
                        imposta_colore(COLORE_ROSSO);
                        printf("Errore: Veicolo non trovato!\n");
                        imposta_colore(COLORE_BIANCO);
                        printf("Premi INVIO per riprovare...");
                        svuota_buffer();
                    } else {
                        id_valido = true;
                    }
                } while (!id_valido);
                
                int tipo = ottieni_tipo_veicolo(veicolo_selezionato);
                
                stampa_bordo_inferiore();
                
                // Input giorno e ora inizio
                bool data_inizio_valida = false;
                bool data_fine_valida = false;
                int giorno_ora_inizio = 0;
                int giorno_ora_fine = 0;

                do {
                    // Input data inizio
                    do {
                        pulisci_schermo();
                        stampa_bordo_superiore();
                        
                        imposta_colore(COLORE_MAGENTA);
                        printf("         NUOVA PRENOTAZIONE\n");
                        
                        stampa_separatore();
                        
                        // Mostra la data di sistema corrente
                        imposta_colore(COLORE_GIALLO);
                        printf("         DATA DI SISTEMA\n");
                        imposta_colore(COLORE_BIANCO);
                        stampa_data_sistema();
                        
                        stampa_separatore();
                        
                        // Mostra il veicolo selezionato
                        imposta_colore(COLORE_VERDE);
                        printf("     VEICOLO SELEZIONATO\n");
                        imposta_colore(COLORE_BIANCO);
                        stampa_veicolo(veicolo_selezionato);
                        printf("Tariffa oraria: %.2f euro\n", ottieni_tariffa_oraria(tipo));
                        
                        stampa_separatore();
                        
                        printf("Giorno inizio (0-6, Lun-Dom): ");
                        if(scanf("%d", &giorno_inizio) != 1) {
                            svuota_buffer();
                            imposta_colore(COLORE_ROSSO);
                            printf("Errore: Inserisci un numero valido!\n");
                            imposta_colore(COLORE_BIANCO);
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        svuota_buffer();
                        
                        if(giorno_inizio < 0 || giorno_inizio > 6) {
                            imposta_colore(COLORE_ROSSO);
                            printf("Errore: Giorno non valido!\n");
                            imposta_colore(COLORE_BIANCO);
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        
                        printf("Ora inizio (0-23): ");
                        if(scanf("%d", &ora_inizio) != 1) {
                            svuota_buffer();
                            imposta_colore(COLORE_ROSSO);
                            printf("Errore: Inserisci un numero valido!\n");
                            imposta_colore(COLORE_BIANCO);
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        svuota_buffer();
                        
                        if(ora_inizio < 0 || ora_inizio > 23) {
                            imposta_colore(COLORE_ROSSO);
                            printf("Errore: Ora non valida!\n");
                            imposta_colore(COLORE_BIANCO);
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        
                        // Converti le date in timestamp
                        giorno_ora_inizio = giorno_inizio * 24 + ora_inizio;
                        
                        // Valida subito se la data di inizio è nel passato
                        int validazione_inizio = valida_data_prenotazione(giorno_ora_inizio, giorno_ora_fine);
                        if (validazione_inizio == -1) {
                            imposta_colore(COLORE_ROSSO);
                            printf("\nErrore: Non puoi prenotare nel passato!\n");
                            imposta_colore(COLORE_BIANCO);
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        
                        data_inizio_valida = true;
                    } while (!data_inizio_valida);

                    // Input data fine
                    do {
                        pulisci_schermo();
                        stampa_bordo_superiore();
                        
                        imposta_colore(COLORE_MAGENTA);
                        printf("         NUOVA PRENOTAZIONE\n");
                        
                        stampa_separatore();
                        
                        // Mostra la data di sistema corrente
                        imposta_colore(COLORE_GIALLO);
                        printf("         DATA DI SISTEMA\n");
                        imposta_colore(COLORE_BIANCO);
                        stampa_data_sistema();
                        
                        stampa_separatore();
                        
                        // Mostra il veicolo selezionato
                        imposta_colore(10); // Verde
                        printf("     VEICOLO SELEZIONATO\n");
                        imposta_colore(7); // Bianco
                        stampa_veicolo(veicolo_selezionato);
                        printf("Tariffa oraria: %.2f euro\n", ottieni_tariffa_oraria(tipo));
                        
                        stampa_separatore();
                        
                        // Mostra data inizio già inserita
                        imposta_colore(14); // Giallo
                        printf("     DATA INIZIO INSERITA\n");
                        imposta_colore(7); // Bianco
                        printf("Giorno: %s\n", ottieni_nome_giorno(giorno_inizio));
                        printf("Ora: %02d:00\n", ora_inizio);
                        
                        stampa_separatore();
                        
                        printf("Giorno fine (0-6, Lun-Dom): ");
                        if(scanf("%d", &giorno_fine) != 1) {
                            svuota_buffer();
                            imposta_colore(12); // Rosso
                            printf("Errore: Inserisci un numero valido!\n");
                            imposta_colore(7); // Bianco
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        svuota_buffer();
                        
                        if(giorno_fine < 0 || giorno_fine > 6) {
                            imposta_colore(12); // Rosso
                            printf("Errore: Giorno non valido!\n");
                            imposta_colore(7); // Bianco
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        
                        printf("Ora fine (0-23): ");
                        if(scanf("%d", &ora_fine) != 1) {
                            svuota_buffer();
                            imposta_colore(12); // Rosso
                            printf("Errore: Inserisci un numero valido!\n");
                            imposta_colore(7); // Bianco
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        svuota_buffer();
                        
                        if(ora_fine < 0 || ora_fine > 23) {
                            imposta_colore(12); // Rosso
                            printf("Errore: Ora non valida!\n");
                            imposta_colore(7); // Bianco
                            printf("Premi INVIO per riprovare...");
                            svuota_buffer();
                            continue;
                        }
                        
                        // Converti le date in timestamp
                        giorno_ora_fine = giorno_fine * 24 + ora_fine;
                        
                        data_fine_valida = true;
                    } while (!data_fine_valida);

                    // Valida le date
                    int validazione = valida_data_prenotazione(giorno_ora_inizio, giorno_ora_fine);
                    if (validazione != 0) {
                        imposta_colore(12); // Rosso
                        if (validazione == -1) {
                            printf("\nErrore: Non puoi prenotare nel passato!\n");
                        } else {
                            printf("\nErrore: La data di fine deve essere successiva alla data di inizio!\n");
                        }
                        imposta_colore(7); // Bianco
                        printf("Premi INVIO per riprovare...");
                        svuota_buffer();
                        data_inizio_valida = false; // Forza il ritorno all'input della data di inizio
                        data_fine_valida = false;   // Resetta anche la validazione della data di fine
                        continue;
                    }
                    
                    break; // Se arriva qui, entrambe date sono giuste
                } while (true);
                
                stampa_bordo_inferiore();

                // Richiesta posizione di riconsegna
                printf("\nDove vuoi lasciare il veicolo?\n");
                for (int i = 0; i <= 3; i++) {
                    printf("%d. %s\n", i, ottieni_nome_posizione_veicolo(i));
                }
                int posizione_riconsegna;
                do {
                    printf("Scegli la posizione di riconsegna (0-3): ");
                    if (scanf("%d", &posizione_riconsegna) != 1 || posizione_riconsegna < 0 || posizione_riconsegna > 3) {
                        imposta_colore(12); // Rosso
                        printf("Scelta non valida!\n");
                        imposta_colore(7); // Bianco
                        svuota_buffer();
                    } else {
                        svuota_buffer();
                        break;
                    }
                } while (1);

                
                
                // Verifica sovrapposizioni
                if (verifica_sovrapposizioni(coda_prenotazioni, id_veicolo, giorno_ora_inizio, giorno_ora_fine) == 1) {
                    imposta_colore(12); // Rosso
                    printf("\nErrore: Esiste gia' una prenotazione per questo veicolo in questo periodo!\n");
                    imposta_colore(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    data_inizio_valida = false; // Forza il ritorno all'input della data di inizio
                    data_fine_valida = false;   // Resetta anche la validazione della data di fine
                    continue;
                }
                
                // Calcola e mostra il costo stimato
                double costo_base = calcola_tariffa_prenotazione(ottieni_coda_prenotazioni(), tipo, giorno_ora_inizio, giorno_ora_fine, ottieni_id_utente(utente_corrente));
                
                // Calcola il numero di prenotazioni dell'utente per lo sconto fedeltà
                int num_prenotazioni = conta_prenotazioni_completate(coda_prenotazioni, ottieni_id_utente(utente_corrente));
                
                // Applica lo sconto fedeltà se applicabile
                double costo_finale = applica_sconto_fedelta(costo_base, num_prenotazioni);
                
                imposta_colore(14); // Giallo
                printf("\nRiepilogo prenotazione:\n");
                printf("Veicolo: %s (ID: %d)\n", ottieni_modello_veicolo(veicolo_selezionato), ottieni_id_veicolo(veicolo_selezionato));
                printf("Tariffa oraria: %.2f euro\n", ottieni_tariffa_oraria(tipo));
                printf("Data inizio: %s ore %02d:00\n", ottieni_nome_giorno(giorno_inizio), ora_inizio);
                printf("Data fine: %s ore %02d:00\n", ottieni_nome_giorno(giorno_fine), ora_fine);
                printf("Costo base: %.2f euro\n", costo_base);
                printf("Hai scelto di lasciare il veicolo in: %s\n", ottieni_nome_posizione_veicolo(posizione_riconsegna));
                
                if (costo_finale < costo_base) {
                    printf("Sconto fedeltà applicato: %.2f euro\n", costo_base - costo_finale);
                    printf("Costo finale: %.2f euro\n", costo_finale);
                }
                
                if (num_prenotazioni < 10) {
                    printf("\nNota: Ti mancano %d noleggi per ottenere lo sconto fedeltà!\n", 
                           10 - num_prenotazioni);
                }
                
                imposta_colore(7); // Bianco
                
                printf("Confermi la prenotazione? (1: Si, 0: No): ");
                int conferma;
                if(scanf("%d", &conferma) != 1) {
                    svuota_buffer();
                    imposta_colore(12); // Rosso
                    printf("Errore: Inserisci un numero valido!\n");
                    imposta_colore(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    data_inizio_valida = false; // Forza il ritorno all'input della data di inizio
                    data_fine_valida = false;   // Resetta anche la validazione della data di fine
                    continue;
                }
                svuota_buffer();
                
                if(!conferma) {
                    printf("Prenotazione annullata.\n");
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    data_inizio_valida = false; // Forza il ritorno all'input della data di inizio
                    data_fine_valida = false;   // Resetta anche la validazione della data di fine
                    continue;
                }
                
                // La priorità viene calcolata automaticamente in base al tempo
                Prenotazione nuova = crea_prenotazione(ottieni_id_utente(utente_corrente), id_veicolo, 
                                                     giorno_inizio, ora_inizio,
                                                     giorno_fine, ora_fine, 
                                                     -1,
                                                    posizione_riconsegna);  // -1 indica di usare la priorità automatica
                
                if (nuova == NULL) {
                    imposta_colore(12); // Rosso
                    printf("\nErrore nella creazione della prenotazione!\n");
                    imposta_colore(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                int risultato = aggiungi_prenotazione(coda_prenotazioni, nuova);
                free(nuova);  // Libera la memoria dopo l'uso
                
                if (risultato == 0) {
                    imposta_colore(10); // Verde
                    salva_prenotazioni_su_file(coda_prenotazioni);
                    printf("\nPrenotazione aggiunta con successo!\n");
                    printf("Costo totale: %.2f euro\n", costo_finale);
                } else if (risultato == -2) {
                    imposta_colore(12); // Rosso
                    printf("\nErrore: Fascia oraria non valida!\n");
                } else {
                    imposta_colore(12); // Rosso
                    printf("\nErrore nell'aggiunta della prenotazione!\n");
                }
                imposta_colore(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 2: {
                printf("\nPrenotazioni attive:\n");
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                    stampa_prenotazione(p);
                    
                    // Trova il veicolo per mostrare il costo
                    list temp = ottieni_lista_veicoli();
                    while(temp != NULL) {
                        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                        if (!v) continue;
                        int id = ottieni_id_veicolo(v);
                        if (id == ottieni_id_veicolo_prenotazione(p)) {
                            int tipo = ottieni_tipo_veicolo(v);
                            double costo = calcola_tariffa_prenotazione(ottieni_coda_prenotazioni(), tipo, ottieni_giorno_ora_inizio(p), ottieni_giorno_ora_fine(p), ottieni_id_utente(utente_corrente));
                            printf("Costo stimato: %.2f euro\n", costo);
                            break;
                        }
                        temp = ottieni_successivo_nodo(temp);
                    }
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
                
                Prenotazione prenotazione = cerca_prenotazione(coda_prenotazioni, id_prenotazione);
                if (prenotazione != NULL) {
                    // Verifica che l'utente possa cancellare questa prenotazione
                    if (ottieni_isamministratore_utente(utente_corrente) || ottieni_id_utente_prenotazione(prenotazione) == ottieni_id_utente(utente_corrente)) {
                        imposta_stato_prenotazione(3, prenotazione);
                        salva_prenotazioni_su_file(coda_prenotazioni);
                        imposta_colore(10); // Verde
                        printf("\nPrenotazione cancellata con successo!\n");
                    } else {
                        imposta_colore(12); // Rosso
                        printf("\nNon hai i permessi per cancellare questa prenotazione!\n");
                    }
                } else {
                    imposta_colore(12); // Rosso
                    printf("\nPrenotazione non trovata!\n");
                }
                imposta_colore(7); // Bianco
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            
            case 4:
                visualizza_tariffe(utente_corrente);
                break;
            case 5: {
                pulisci_schermo();
                int ore;
                printf("Inserisci il numero di ore da avanzare: ");
                scanf("%d", &ore);
                svuota_buffer();
                
                avanza_tempo(ore);
                CodaPrenotazioni coda = ottieni_coda_prenotazioni();
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
            case 0:
                break;
            default:
                imposta_colore(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                imposta_colore(7); // Bianco
                svuota_buffer();
        }
    } while(scelta != 0);
}

/**
 * @brief Visualizza le prenotazioni dell'utente corrente.
 * @param utente_corrente L'utente di cui visualizzare le prenotazioni.
 * @details Mostra tutte le prenotazioni attive dell'utente, con dettagli come veicolo, date, stato e costo stimato.
 */
void visualizza_prenotazioni(Utente utente_corrente) {
    pulisci_schermo();
    stampa_bordo_superiore();
    imposta_colore(13); // Magenta
    printf("       ELENCO PRENOTAZIONI\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    imposta_colore(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    imposta_colore(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    CodaPrenotazioni coda = ottieni_coda_prenotazioni();
    int id_utente = ottieni_id_utente(utente_corrente);
    int is_amministratore = ottieni_isamministratore_utente(utente_corrente);

    if (coda == NULL || ottieni_dimensione_coda(coda) == 0) {
        imposta_colore(12); // Rosso
        printf("  Nessuna prenotazione presente\n");
        imposta_colore(7); // Bianco
    } else if (is_amministratore) {
        for (int i = 0; i < ottieni_dimensione_coda(coda); i++) {
            Prenotazione p = ottieni_prenotazione_in_coda(coda, i);
            stampa_prenotazione(p);
            
            // Trova il veicolo per mostrare il costo
            list temp = ottieni_lista_veicoli();
            while(temp != NULL) {
                Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                if (!v) {
                    temp = ottieni_successivo_nodo(temp);
                    continue;
                }
                if (ottieni_id_veicolo(v) == ottieni_id_veicolo_prenotazione(p)) {
                    int tipo = ottieni_tipo_veicolo(v);
                    double costo = calcola_tariffa_prenotazione(ottieni_coda_prenotazioni(), tipo, ottieni_giorno_ora_inizio(p), ottieni_giorno_ora_fine(p), ottieni_id_utente(utente_corrente));
                    int completate_prima = conta_prenotazioni_completate_prima_di(coda, ottieni_id_utente_prenotazione(p), ottieni_id_prenotazione(p));
                    costo = applica_sconto_fedelta(costo, completate_prima);
                    printf("Costo stimato: %.2f euro\n", costo);
                    break;
                }
                temp = ottieni_successivo_nodo(temp);
            }
            
            if (i < ottieni_dimensione_coda(coda) - 1) {
                stampa_separatore();
            }
        }
    } else {
        int trovate = 0;
        for(int i = 0; i < ottieni_dimensione_coda(coda); i++) {
            Prenotazione p = ottieni_prenotazione_in_coda(coda, i);
            if (!p) continue;
            if(ottieni_id_utente_prenotazione(p) != id_utente) continue;
            trovate++;
                                   
            // Intestazione prenotazione
            imposta_colore(14); // Giallo
            printf("  Prenotazione #%d\n", trovate);
            imposta_colore(7); // Bianco
            
            // Dettagli prenotazione
            stampa_prenotazione(p);
            
            // Trova il veicolo per mostrare il costo
            list temp = ottieni_lista_veicoli();
            while(temp != NULL) {
                Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                if (!v) {
                    temp = ottieni_successivo_nodo(temp);
                    continue;
                }
                if (ottieni_id_veicolo(v) == ottieni_id_veicolo_prenotazione(p)) {
                    int tipo = ottieni_tipo_veicolo(v);
                    double costo = calcola_tariffa_prenotazione(ottieni_coda_prenotazioni(), tipo, ottieni_giorno_ora_inizio(p), ottieni_giorno_ora_fine(p), ottieni_id_utente(utente_corrente));
                    int completate_prima = conta_prenotazioni_completate_prima_di(coda, ottieni_id_utente_prenotazione(p), ottieni_id_prenotazione(p));
                    costo = applica_sconto_fedelta(costo, completate_prima);
                    printf("Costo stimato: %.2f euro\n", costo);
                    break;
                }
                temp = ottieni_successivo_nodo(temp);
            }
            
            if (i < ottieni_dimensione_coda(coda) - 1) {
                stampa_separatore();
            }
        }
        if(trovate == 0) {
            imposta_colore(12); // Rosso
            printf("  Nessuna prenotazione trovata per l'utente corrente\n");
            imposta_colore(7); // Bianco
        }
    }   
    
    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}

/**
 * @brief Visualizza la disponibilità dei veicoli.
 * @details Mostra lo stato di disponibilità di tutti i veicoli nel sistema e permette di visualizzare il calendario di un veicolo specifico.
 */
void visualizza_disponibilita(void) {
    list veicoli = ottieni_lista_veicoli();
    if (veicoli == NULL) {
        pulisci_schermo();
        stampa_bordo_superiore();
        imposta_colore(12); // Rosso
        printf("  Nessun veicolo disponibile\n");
        imposta_colore(7); // Bianco
        stampa_bordo_inferiore();
        printf("Premi INVIO per continuare...");
        svuota_buffer();
        return;
    }
    
    pulisci_schermo();
    stampa_bordo_superiore();
    
    imposta_colore(13); // Magenta
    printf("     VISUALIZZA DISPONIBILITA'\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    imposta_colore(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    imposta_colore(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    // Visualizza tutti i veicoli
    imposta_colore(10); // Verde
    printf("     ELENCO VEICOLI\n");
    imposta_colore(7); // Bianco
    
    list temp = veicoli;
    bool trovato = false;
    while(temp != NULL) {
        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
        if (!v) {
            temp = ottieni_successivo_nodo(temp);
            continue;
        }
         // Aggiorna il calendario e la disponibilità 
        CalendarioVeicolo calendario = inizializza_calendario(ottieni_id_veicolo(v));
        CodaPrenotazioni coda = ottieni_coda_prenotazioni();
        CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, coda);
        free(nuovo_calendario);
        
        stampa_veicolo(v);
        trovato = true;
        
        if (ottieni_successivo_nodo(temp) != NULL) {
            stampa_separatore();
        }
        temp = ottieni_successivo_nodo(temp);
    }
    
    if (!trovato) {
        imposta_colore(12); // Rosso
        printf("  Nessun veicolo disponibile\n");
        imposta_colore(7); // Bianco
    }
    
    stampa_separatore();
    
    // Sezione Input
    imposta_colore(14); // Giallo
    printf("     VISUALIZZA CALENDARIO\n");
    imposta_colore(7); // Bianco
    
    int id_veicolo;
    bool id_valido = false;
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        
        imposta_colore(13); // Magenta
        printf("     VISUALIZZA DISPONIBILITA'\n");
        
        stampa_separatore();
        
        // Mostra la data di sistema corrente
        imposta_colore(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        imposta_colore(7); // Bianco
        stampa_data_sistema();
        
        stampa_separatore();
        
        // Visualizza tutti i veicoli
        imposta_colore(10); // Verde
        printf("     ELENCO VEICOLI\n");
        imposta_colore(7); // Bianco
        
        list temp2 = veicoli;
        bool trovato = false;
        while(temp2 != NULL) {
            Veicolo v = ottieni_veicolo_senza_rimuovere(temp2);
            if (!v) {
                temp2 = ottieni_successivo_nodo(temp2);
                continue;
            }
            
            stampa_veicolo(v);
            trovato = true;
            
            if (ottieni_successivo_nodo(temp2) != NULL) {
                stampa_separatore();
            }
            temp2 = ottieni_successivo_nodo(temp2);
        }
        
        if (!trovato) {
            imposta_colore(12); // Rosso
            printf("  Nessun veicolo disponibile\n");
            imposta_colore(7); // Bianco
        }
        
        stampa_separatore();
        
        // Sezione Input
        imposta_colore(14); // Giallo
        printf("     VISUALIZZA CALENDARIO\n");
        imposta_colore(7); // Bianco
        
        printf("Inserisci l'ID del veicolo per visualizzare il calendario (0 per uscire): ");
        if (scanf("%d", &id_veicolo) != 1) {
            svuota_buffer();
            imposta_colore(12); // Rosso
            printf("Errore: Inserisci un numero valido!\n");
            imposta_colore(7); // Bianco
            printf("Premi INVIO per riprovare...");
            svuota_buffer();
            continue;
        }
        svuota_buffer();
        
        if (id_veicolo == 0) {
            id_valido = true;
            break;
        }
        
        // Verifica che il veicolo esista
        list temp3 = ottieni_lista_veicoli();
        bool veicolo_trovato = false;
        while(temp3 != NULL) {
            Veicolo v = ottieni_veicolo_senza_rimuovere(temp3);
            if (!v) {
                temp3 = ottieni_successivo_nodo(temp3);
                continue;
            }
            if (ottieni_id_veicolo(v) == id_veicolo) {
                veicolo_trovato = true;
                break;
            }
            temp3 = ottieni_successivo_nodo(temp3);
        }
        
        if (!veicolo_trovato) {
            imposta_colore(12); // Rosso
            printf("Errore: Veicolo non trovato!\n");
            imposta_colore(7); // Bianco
            printf("Premi INVIO per riprovare...");
            svuota_buffer();
            continue;
        }
        
        id_valido = true;
    } while (!id_valido);
    
    if (id_veicolo == 0) {
        stampa_bordo_inferiore();
        printf("Premi INVIO per continuare...");
        svuota_buffer();
        return;
    }
    
    // Inizializza e aggiorna il calendario
    CalendarioVeicolo calendario = inizializza_calendario(id_veicolo);
    if (calendario == NULL) {
        imposta_colore(12); // Rosso
        printf("  Errore nell'inizializzazione del calendario!\n");
        imposta_colore(7); // Bianco
        stampa_bordo_inferiore();
        printf("Premi INVIO per continuare...");
        svuota_buffer();
        return;
    }
    
    CodaPrenotazioni coda_prenotazioni = ottieni_coda_prenotazioni();
    CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, coda_prenotazioni);
    
    stampa_separatore();
    
    // Visualizza il calendario
    imposta_colore(14); // Giallo
    printf("         CALENDARIO VEICOLO\n");
    imposta_colore(7); // Bianco
    visualizza_calendario(nuovo_calendario);
    free(nuovo_calendario); // Libera la memoria del calendario
    
    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}

/**
 * @brief Visualizza le tariffe dei veicoli e gli sconti disponibili.
 * @param utente_corrente L'utente corrente per mostrare eventuali sconti fedeltà.
 * @details Mostra le tariffe orarie per ogni tipo di veicolo e gli sconti disponibili. Se l'utente è loggato, mostra anche il suo stato fedeltà.
 */
void visualizza_tariffe(Utente utente_corrente) {
    pulisci_schermo();
    stampa_bordo_superiore();
    
    imposta_colore(13); // Magenta
    printf("          TARIFFE VEICOLI\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    imposta_colore(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    imposta_colore(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    // Sezione tariffe
    imposta_colore(10); // Verde
    printf("      TARIFFE ORARIE VEICOLI\n");
    printf("1. Utilitaria: %.2f euro/ora\n", ottieni_tariffa_oraria(0));
    printf("2. SUV: %.2f euro/ora\n", ottieni_tariffa_oraria(1));
    printf("3. Sportiva: %.2f euro/ora\n", ottieni_tariffa_oraria(2));
    printf("4. Moto: %.2f euro/ora\n", ottieni_tariffa_oraria(3));
    
    stampa_separatore();

    // Sezione sconti
    imposta_colore(14); // Giallo
    printf("         SCONTI DISPONIBILI\n");
    imposta_colore(7); // Bianco
    stampa_info_sconti();

    // Mostra il numero di noleggi completati dell'utente corrente
    if (utente_corrente != NULL) {
        stampa_separatore();
        imposta_colore(10); // Verde
        printf("     STATO FEDELTA' UTENTE\n");
        imposta_colore(7); // Bianco
        
        int noleggi_completati = conta_prenotazioni_completate(ottieni_coda_prenotazioni(), ottieni_id_utente(utente_corrente));
        printf("Noleggi completati: %d\n", noleggi_completati);
        
        if (noleggi_completati < 10) {
            printf("Ti mancano %d noleggi per ottenere lo sconto fedeltà!\n", 10 - noleggi_completati);
        } else {
            imposta_colore(10); // Verde
            printf("Hai ottenuto lo sconto fedeltà!\n");
            imposta_colore(7); // Bianco
        }
    }

    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}



/**
 * @brief Mostra il menu principale per gli utenti clienti.
 * @param utente_corrente L'utente cliente loggato.
 * @details Visualizza le opzioni disponibili per gli utenti clienti, inclusa la gestione delle prenotazioni e la visualizzazione delle informazioni.
 */
void mostra_menu_cliente(Utente utente_corrente) {
    stampa_bordo_superiore();
    
    imposta_colore(13);  // Magenta
    printf("        SISTEMA DI CAR SHARING\n");
    printf("        Benvenuto/a, %s\n", ottieni_nome_completo_utente(utente_corrente));
    
    stampa_separatore();
    
    // Sezione Prenotazioni
    imposta_colore(14);  // Giallo
    printf("           PRENOTAZIONI\n");
    imposta_colore(7);   // Bianco
    printf("1. Prenota un'auto\n");
    printf("2. Visualizza le mie prenotazioni\n");
    
    stampa_separatore();
    
    // Sezione Informazioni
    imposta_colore(10);  // Verde
    printf("           INFORMAZIONI\n");
    imposta_colore(7);   // Bianco
    printf("3. Visualizza disponibilita'\n");
    printf("4. Visualizza tariffe\n");
    
    stampa_separatore();
    
    // Sezione Account
    imposta_colore(12);  // Rosso
    printf("             ACCOUNT\n");
    imposta_colore(7);   // Bianco
    printf("5. Logout\n");
    printf("0. Esci\n");
    
    stampa_bordo_inferiore();
}

/**
 * @brief Mostra il menu principale per gli amministratori.
 * @param utente_corrente L'amministratore loggato.
 * @details Visualizza le opzioni disponibili per gli amministratori, inclusa la gestione di veicoli, prenotazioni e utenti.
 */
void mostra_menu_amministratore(Utente utente_corrente) {
    stampa_bordo_superiore();
    
    imposta_colore(13);  // Magenta
    printf("      SISTEMA DI CAR SHARING\n");
    printf("      PANNELLO AMMINISTRATORE\n");
    printf("      Benvenuto/a, %s\n", ottieni_nome_completo_utente(utente_corrente));
    
    stampa_separatore();
    
    // Sezione Gestione Sistema
    imposta_colore(14);  // Giallo
    printf("        GESTIONE SISTEMA\n");
    imposta_colore(7);   // Bianco
    printf("1. Gestione Veicoli\n");
    printf("2. Gestione Prenotazioni\n");
    printf("3. Gestione Utenti\n"); // <-- Spostato qui
    
    stampa_separatore();
    
    // Sezione Monitoraggio
    imposta_colore(10);  // Verde
    printf("          MONITORAGGIO\n");
    imposta_colore(7);   // Bianco
    printf("4. Visualizza prenotazioni\n");
    //printf("3. Gestione Utenti\n");
    printf("5. Visualizza disponibilita'\n");
    
    stampa_separatore();
    
    // Sezione Sistema
    imposta_colore(12);  // Rosso
    printf("            SISTEMA\n");
    imposta_colore(7);   // Bianco
    printf("6. Avanza tempo sistema\n");
    printf("7. Logout\n");
    printf("0. Esci\n");
    
    stampa_bordo_inferiore();
}

/**
 * @brief Gestisce le operazioni di amministrazione delle prenotazioni.
 * @details Permette agli amministratori di visualizzare, filtrare e modificare le prenotazioni nel sistema.
 */
void gestione_prenotazioni_amministratore(void) {
    int scelta;
    CodaPrenotazioni coda_prenotazioni = ottieni_coda_prenotazioni();
    
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        
        imposta_colore(13); // Magenta
        printf("    GESTIONE PRENOTAZIONI (amministratore)\n");
        
        stampa_separatore();
        
        // Mostra la data di sistema corrente
        imposta_colore(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        imposta_colore(7); // Bianco
        stampa_data_sistema();
        
        stampa_separatore();
        
        // Sezione Operazioni
        imposta_colore(10); // Verde
        printf("           OPERAZIONI\n");
        imposta_colore(7); // Bianco
        printf("1. Visualizza tutte le prenotazioni\n");
        printf("2. Filtra prenotazioni per utente\n");
        printf("3. Filtra prenotazioni per veicolo\n");
        printf("4. Filtra prenotazioni per stato\n");
        printf("5. Modifica stato prenotazione\n");
        printf("6. Visualizza prenotazioni in ordine di data\n");
        printf("7. Visualizza prenotazioni in ordine di priorita'\n");
        
        stampa_separatore();
        
        // Sezione Navigazione
        imposta_colore(12); // Rosso
        printf("           NAVIGAZIONE\n");
        imposta_colore(7); // Bianco
        printf("0. Torna al menu principale\n");
        
        stampa_bordo_inferiore();
        printf("Scelta: ");
        if(scanf("%d", &scelta) != 1) {
            scelta = -999;
        }

        svuota_buffer();

        switch(scelta) {
            case 1: {
                pulisci_schermo();
                stampa_bordo_superiore();
                
                imposta_colore(13); // Magenta
                printf("       ELENCO PRENOTAZIONI\n");
                
                stampa_separatore();
                
                if (coda_prenotazioni == NULL || ottieni_dimensione_coda(coda_prenotazioni) == 0) {
                    imposta_colore(12); // Rosso
                    printf("  Nessuna prenotazione presente\n");
                    imposta_colore(7); // Bianco
                } else {
                    for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                        Prenotazione p = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                        if (!p) continue;
                        
                        imposta_colore(14); // Giallo
                        printf("  Prenotazione #%d\n", ottieni_id_prenotazione(p));
                        imposta_colore(7); // Bianco
                        
                        stampa_prenotazione(p);
                        
                        // Trova il veicolo per mostrare il costo
                        list temp = ottieni_lista_veicoli();
                        while(temp != NULL) {
                            Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                            if (!v) {
                                temp = ottieni_successivo_nodo(temp);
                                continue;
                            }
                            if (ottieni_id_veicolo(v) == ottieni_id_veicolo_prenotazione(p)) {
                                int tipo = ottieni_tipo_veicolo(v);
                                double costo = calcola_tariffa_prenotazione(ottieni_coda_prenotazioni(), tipo, ottieni_giorno_ora_inizio(p), ottieni_giorno_ora_fine(p), ottieni_id_prenotazione(p));
                                int completate_prima = conta_prenotazioni_completate_prima_di(coda_prenotazioni, ottieni_id_utente_prenotazione(p), ottieni_id_prenotazione(p));
                                costo = applica_sconto_fedelta(costo, completate_prima);
                                printf("Costo stimato: %.2f euro\n", costo);
                                break;
                            }
                            temp = ottieni_successivo_nodo(temp);
                        }
                        
                        if (i < ottieni_dimensione_coda(coda_prenotazioni) - 1) {
                            stampa_separatore();
                        }
                    }
                }
                
                stampa_bordo_inferiore();
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 2: {
                // Mostra la lista degli utenti
                pulisci_schermo();
                stampa_bordo_superiore();
                imposta_colore(13); // Magenta
                printf("      ELENCO UTENTI\n");
                stampa_separatore();
                stampa_utenti(); // Funzione già esistente
                stampa_bordo_inferiore();

                int id_utente;
                printf("Inserisci l'ID dell'utente: ");
                scanf("%d", &id_utente);
                svuota_buffer();

                pulisci_schermo();
                stampa_bordo_superiore();
                imposta_colore(13); // Magenta
                printf("  PRENOTAZIONI UTENTE #%d\n", id_utente);
                stampa_separatore();

                int trovate = 0;
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                    if (!p) continue;
                    if (ottieni_id_utente_prenotazione(p) == id_utente) {
                        trovate++;
                        imposta_colore(14); // Giallo
                        printf("  Prenotazione #%d\n", ottieni_id_prenotazione(p));
                        imposta_colore(7); // Bianco
                        
                        stampa_prenotazione(p);
                        
                        // Trova il veicolo per mostrare il costo
                        list temp = ottieni_lista_veicoli();
                        while(temp != NULL) {
                            Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
                            if (!v) {
                                temp = ottieni_successivo_nodo(temp);
                                continue;
                            }
                            if (ottieni_id_veicolo(v) == ottieni_id_veicolo_prenotazione(p)) {
                                int tipo = ottieni_tipo_veicolo(v);
                                double costo = calcola_tariffa_prenotazione(ottieni_coda_prenotazioni(), tipo, ottieni_giorno_ora_inizio(p), ottieni_giorno_ora_fine(p), ottieni_id_utente_prenotazione(p));
                                int completate_prima = conta_prenotazioni_completate_prima_di(coda_prenotazioni, ottieni_id_utente_prenotazione(p), ottieni_id_prenotazione(p));
                                costo = applica_sconto_fedelta(costo, completate_prima);
                                printf("Costo stimato: %.2f euro\n", costo);
                                break;
                            }
                            temp = ottieni_successivo_nodo(temp);
                        }
                        
                        if (i < ottieni_dimensione_coda(coda_prenotazioni) - 1) {
                            stampa_separatore();
                        }
                    }
                }
                
                if (trovate == 0) {
                    imposta_colore(12); // Rosso
                    printf("  Nessuna prenotazione trovata per questo utente\n");
                    imposta_colore(7); // Bianco
                }
                
                stampa_bordo_inferiore();
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 3: {
                // Mostra la lista dei veicoli
                pulisci_schermo();
                stampa_bordo_superiore();
                imposta_colore(13); // Magenta
                printf("      ELENCO VEICOLI\n");
                stampa_separatore();
                stampa_lista_veicoli(ottieni_lista_veicoli()); 
                stampa_bordo_inferiore();

                int id_veicolo;
                printf("Inserisci l'ID del veicolo: ");
                scanf("%d", &id_veicolo);
                svuota_buffer();
                
                printf("\nPrenotazioni del veicolo %d:\n", id_veicolo);
                int trovate = 0;
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                    if (ottieni_id_veicolo_prenotazione(p) == id_veicolo) {
                        trovate++;
                        printf("\n--- Prenotazione %d ---\n", trovate);
                        stampa_prenotazione(p);
                        printf("------------------------\n");
                    }
                }
                if (trovate == 0) {
                    printf("Nessuna prenotazione trovata per questo veicolo.\n");
                }
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 4: {
                int stato;
                printf("Seleziona lo stato (0=In attesa, 1=Confermata, 2=Completata, 3=Cancellata): ");
                scanf("%d", &stato);
                svuota_buffer();
                
                printf("\nPrenotazioni con stato %d:\n", stato);
                int trovate = 0;
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                    if ((int)ottieni_stato_prenotazione(p) == stato) {
                        trovate++;
                        printf("\n--- Prenotazione %d ---\n", trovate);
                        stampa_prenotazione(p);
                        printf("------------------------\n");
                    }
                }
                if (trovate == 0) {
                    printf("Nessuna prenotazione trovata con questo stato.\n");
                }
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 5: {
                pulisci_schermo();
                stampa_bordo_superiore();
                
                imposta_colore(13); // Magenta
                printf("    MODIFICA STATO PRENOTAZIONE\n");
                
                stampa_separatore();
                
                // Mostra la data di sistema corrente
                imposta_colore(14); // Giallo
                printf("         DATA DI SISTEMA\n");
                imposta_colore(7); // Bianco
                stampa_data_sistema();
                
                stampa_separatore();
                
                // Visualizza tutte le prenotazioni
                imposta_colore(10); // Verde
                printf("     ELENCO PRENOTAZIONI\n");
                imposta_colore(7); // Bianco
                
                if (coda_prenotazioni == NULL || ottieni_dimensione_coda(coda_prenotazioni) == 0) {
                    imposta_colore(12); // Rosso
                    printf("  Nessuna prenotazione presente\n");
                    imposta_colore(7); // Bianco
                } else {
                    for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                        Prenotazione p = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                        if (!p) continue;
                        
                        imposta_colore(14); // Giallo
                        printf("  Prenotazione #%d\n", ottieni_id_prenotazione(p));
                        imposta_colore(7); // Bianco
                        
                        stampa_prenotazione(p);
                        
                        if (i < ottieni_dimensione_coda(coda_prenotazioni) - 1) {
                            stampa_separatore();
                        }
                    }
                }
                
                stampa_separatore();
                
                // Sezione Input
                imposta_colore(14); // Giallo
                printf("     MODIFICA STATO\n");
                imposta_colore(7); // Bianco
                
                int id_prenotazione, nuovo_stato;
                printf("Inserisci l'ID della prenotazione da modificare: ");
                scanf("%d", &id_prenotazione);
                printf("Nuovo stato (0=In attesa, 1=Confermata, 2=Completata, 3=Cancellata): ");
                scanf("%d", &nuovo_stato);
                svuota_buffer();
                
                if (modifica_stato_prenotazione(coda_prenotazioni, id_prenotazione, nuovo_stato) == 0) {
                    salva_prenotazioni_su_file(coda_prenotazioni);
                    imposta_colore(10); // Verde
                    printf("\nStato della prenotazione modificato con successo!\n");
                } else {
                    imposta_colore(12); // Rosso
                    printf("\nErrore: prenotazione non trovata.\n");
                }
                imposta_colore(7); // Bianco
                stampa_bordo_inferiore();
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 6: {
                // Creiamo un array temporaneo per ordinare le prenotazioni per data
                Prenotazione* temp = malloc(sizeof(Prenotazione) * ottieni_dimensione_coda(coda_prenotazioni));
                if (temp == NULL) {
                    printf("Errore di allocazione memoria.\n");
                    break;
                }
                
                // Copiamo le prenotazioni nell'array temporaneo
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    temp[i] = ottieni_prenotazione_in_coda(coda_prenotazioni, i);
                }
                
                // Ordiniamo per data di inizio (bubble sort)
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni) - 1; i++) {
                    for (int j = 0; j < ottieni_dimensione_coda(coda_prenotazioni) - i - 1; j++) {
                        if (ottieni_ora_inizio(temp[j]) > ottieni_ora_inizio(temp[j + 1])) {
                            Prenotazione t = temp[j];
                            temp[j] = temp[j + 1];
                            temp[j + 1] = t;
                        }
                    }
                }
                
                // Stampiamo le prenotazioni ordinate
                printf("\nPrenotazioni ordinate per data:\n");
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    printf("\n--- Prenotazione %d ---\n", i + 1);
                    stampa_prenotazione(temp[i]);
                    printf("------------------------\n");
                }
                
                free(temp);
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 7: {
                // Le prenotazioni sono già ordinate per priorità nell'heap
                printf("\nPrenotazioni ordinate per priorita':\n");
                for (int i = 0; i < ottieni_dimensione_coda(coda_prenotazioni); i++) {
                    printf("\n--- Prenotazione %d ---\n", i + 1);
                    stampa_prenotazione(ottieni_prenotazione_in_coda(coda_prenotazioni, i));
                    printf("------------------------\n");
                }
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 0:
                break;
            default:
                imposta_colore(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                imposta_colore(7); // Bianco
                svuota_buffer();
                break;
        }
    } while (scelta != 0);
}

/**
 * @brief Gestisce le operazioni di amministrazione degli utenti.
 * @details Permette agli amministratori di visualizzare e gestire gli utenti del sistema, inclusa la possibilità di rimuovere utenti.
 */
void gestione_utenti_amministratore() {
    int scelta;
    do {
        pulisci_schermo();
        stampa_bordo_superiore();

        imposta_colore(13); // Magenta
        printf("      GESTIONE UTENTI\n");
        stampa_separatore();
        imposta_colore(10); // Verde
        printf("1. Visualizza tutti gli utenti\n");
        printf("2. Cancella utente\n");
        printf("0. Torna al menu amministratore\n");
        stampa_bordo_inferiore();
        printf("Scelta: ");
        if(scanf("%d", &scelta) != 1) {
            scelta = -999;
        }
        svuota_buffer();

        switch(scelta) {
            case 1:
                pulisci_schermo();
                stampa_bordo_superiore();
                imposta_colore(13); // Magenta
                printf("      ELENCO UTENTI\n");
                stampa_separatore();
                stampa_utenti(); // Funzione già esistente
                stampa_bordo_inferiore();
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            case 2: {
                // Mostra la lista degli utenti prima di chiedere quale eliminare
                pulisci_schermo();
                stampa_bordo_superiore();
                imposta_colore(13); // Magenta
                printf("      ELENCO UTENTI\n");
                stampa_separatore();
                stampa_utenti(); // Funzione già esistente che mostra tutti gli utenti
                stampa_bordo_inferiore();

                int id;
                printf("Inserisci l'ID dell'utente da cancellare: ");
                if(scanf("%d", &id) != 1) {
                    svuota_buffer();
                    imposta_colore(12); // Rosso
                    printf("Errore: Inserisci un numero valido!\n");
                    imposta_colore(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                svuota_buffer();
                if (id == 0) {
                    imposta_colore(12); // Rosso
                    printf("Non puoi cancellare l'utente amministratore!\n");
                    imposta_colore(7); // Bianco
                } else if (rimuovi_utente(id)) {
                    imposta_colore(10); // Verde
                    printf("Utente cancellato con successo!\n");
                    salva_utenti_file();
                } else {
                    imposta_colore(12); // Rosso
                    printf("Utente non trovato!\n");
                }
                printf("Premi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 0:
                break;
            default:
                imposta_colore(12); // Rosso
                printf("Scelta non valida. Premi INVIO per riprovare...");
                imposta_colore(7); // Bianco
                svuota_buffer();
        }
    } while(scelta != 0);
}

/**
 * @brief Visualizza il logo ASCII del sistema.
 * @details Stampa il logo ASCII del sistema di car sharing.
 */
void mostra_logo() {
    imposta_colore(14); // Giallo
    printf("\n");
printf("_________                    _________.__                    .__                 \n");
printf("\\_   ___ \\ _____  _______   /   _____/|  |__  _____  _______ |__|  ____    ____  \n");
printf("/    \\  \\/ \\__  \\ \\_  __ \\  \\_____  \\ |  |  \\ \\__  \\ \\_  __ \\|  | /    \\  / ___\\ \n");
printf("\\     \\____ / __ \\_|  | \\/  /        \\|   Y  \\ / __ \\_|  | \\/|  ||   |  \\/ /_/  >\n");
printf(" \\______  /(____  /|__|    /_______  /|___|  /(____  /|__|   |__||___|  /\\___  / \n");
printf("        \\/      \\/                 \\/      \\/      \\/                 \\//_____/  \n");


    printf("\n");
    imposta_colore(7); // Bianco
}

/**
 * @brief Mostra il menu di login.
 * @details Visualizza le opzioni per accedere o registrarsi al sistema.
 */
void mostra_menu_login() {
    stampa_bordo_superiore();
    
    mostra_logo();
    
    stampa_separatore();
    
    imposta_colore(13); // Magenta
    printf("             BENVENUTO/A\n");
    stampa_separatore();
    
    imposta_colore(10); // Verde
    printf("           ACCESSO\n");
    imposta_colore(7); // Bianco
    printf("1. Accedi\n");
    printf("2. Registrati\n");
    
    stampa_separatore();
    
    imposta_colore(12); // Rosso
    printf("           SISTEMA\n");
    imposta_colore(7); // Bianco
    printf("0. Esci\n");
    
    stampa_bordo_inferiore();
}

