#include "menu.h"
#include <ctype.h>




#include "f_utili.h"



void gestione_veicoli() {
    int scelta;
    
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        
        set_color(13); // Magenta
        printf("         GESTIONE VEICOLI\n");
        
        stampa_separatore();
        
        // Sezione Operazioni
        set_color(14); // Giallo
        printf("           OPERAZIONI\n");
        set_color(7); // Bianco
        printf("1. Aggiungi veicolo\n");
        printf("2. Rimuovi veicolo\n");
        printf("3. Visualizza tutti i veicoli\n");
        
        stampa_separatore();
        
        // Sezione Navigazione
        set_color(12); // Rosso
        printf("           NAVIGAZIONE\n");
        set_color(7); // Bianco
        printf("0. Torna al menu principale\n");
        
        stampa_bordo_inferiore();
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuota_buffer();

        switch(scelta) {
            case 1:
                set_lista_veicoli(aggiungi_veicolo(get_lista_veicoli()));
                salva_lista_veicoli();
                break;
            case 2:
                set_lista_veicoli(rimuovi_veicolo(get_lista_veicoli()));
                salva_lista_veicoli();
                break;
            case 3: {
                pulisci_schermo();
                stampa_bordo_superiore();
                
                set_color(13); // Magenta
                printf("       ELENCO DEI VEICOLI\n");
                
                stampa_separatore();
                
                list temp = get_lista_veicoli();
                if (temp == NULL) {
                    set_color(12); // Rosso
                    printf("  Nessun veicolo disponibile\n");
                    set_color(7); // Bianco
                } else {
                    while(temp != NULL) {
                        Veicolo v = get_veicolo_da_lista(&temp);
                        if (!v) continue;
                       
                        if (get_disponibilita_veicolo(v) == 0) {
                            stampa_veicolo(v);
                            int tipo = get_tipo_veicolo(v);
                            printf("Tariffa oraria: %.2f euro\n", get_tariffa_oraria(tipo));
                        }
                        free(v);
                        temp = get_next_node(temp);
                    }
                }
                
                stampa_bordo_inferiore();
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

void prenota_auto(Utente current_user) {
    int scelta;
    CodaPrenotazioni coda_prenotazioni = get_coda_prenotazioni();
    
    if (coda_prenotazioni == NULL) {
        set_color(12); // Rosso
        printf("Errore nel sistema di prenotazioni!\n");
        set_color(7); // Bianco
        printf("Premi INVIO per tornare al menu...");
        svuota_buffer();
        return;
    }
    
    do {
        pulisci_schermo();
        stampa_bordo_superiore();
        
        set_color(13); // Magenta
        printf("         GESTIONE PRENOTAZIONI\n");
        
        // Mostra la data di sistema corrente
        stampa_separatore();
        set_color(14); // Giallo
        printf("         DATA DI SISTEMA\n");
        set_color(7); // Bianco
        stampa_data_sistema();
        
        stampa_separatore();
        
        // Sezione Prenotazioni
        set_color(10); // Verde
        printf("          PRENOTAZIONI\n");
        set_color(7); // Bianco
        printf("1. Nuova prenotazione\n");
        printf("2. Visualizza prenotazioni\n");
        printf("3. Cancella prenotazione\n");
        printf("4. Modifica stato prenotazione\n");
        
        stampa_separatore();
        
        // Sezione Informazioni
        set_color(14); // Giallo
        printf("          INFORMAZIONI\n");
        set_color(7); // Bianco
        printf("5. Visualizza tariffe\n");
        printf("6. Avanza tempo sistema\n");
        
        stampa_separatore();
        
        // Sezione Navigazione
        set_color(12); // Rosso
        printf("           NAVIGAZIONE\n");
        set_color(7); // Bianco
        printf("0. Torna al menu principale\n");
        
        stampa_bordo_inferiore();
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuota_buffer();

        switch(scelta) {
            case 1: {
                int id_utente, id_veicolo, giorno_inizio, ora_inizio, giorno_fine, ora_fine;
                
                // Visualizza veicoli disponibili con tariffe
                printf("\nVeicoli disponibili:\n");
                list temp = get_lista_veicoli();
                while(temp != NULL) {
                    Veicolo v = get_veicolo_da_lista(&temp);
                    if (!v) continue;
                    if (get_disponibilita_veicolo(v) == 0) {
                        stampa_veicolo(v);
                        int tipo = get_tipo_veicolo(v);
                        printf("Tariffa oraria: %.2f euro\n", get_tariffa_oraria(tipo));
                    }
                    free(v);
                    temp = get_next_node(temp);
                }
                
                // Mostra informazioni sugli sconti disponibili
                set_color(10); // Verde
                stampa_info_sconti();
                set_color(7); // Bianco
                
                printf("\nInserisci i dati della prenotazione:\n");
                
                // Gestione ID utente in base ai permessi
                if (get_isAdmin_utente(get_username_utente(current_user)) == 0) {
                    do {
                        printf("ID Utente (0 per usare il tuo ID): ");
                        scanf("%d", &id_utente);
                        if (id_utente == 0) {
                             set_id_utente(id_utente, current_user);
                            break;
                        }
                        
                        // Verifica che l'utente esista
                        Utente utente_prenotazione = cerca_utente_per_id(id_utente);
                        if (utente_prenotazione == NULL) {
                            set_color(12); // Rosso
                            printf("Errore: Nessun utente trovato con ID %d\n", id_utente);
                            printf("Inserisci un ID valido o 0 per usare il tuo ID\n");
                            set_color(7); // Bianco
                        } else {
                            printf("Prenotazione per: %s\n", get_nome_utente(utente_prenotazione));
                            break;
                        }
                    } while (1);
                } else {
                    id_utente = get_id_utente(get_username_utente(current_user));
                    printf("ID Utente: %d (il tuo ID)\n", id_utente);
                }

                printf("ID Veicolo: ");
                scanf("%d", &id_veicolo);
                
                // Trova il veicolo per mostrare il costo orario
                temp = get_lista_veicoli();
                Veicolo veicolo_selezionato = NULL;
                while(temp != NULL) {
                    Veicolo v = get_veicolo_da_lista(&temp);
                    if (!v) continue;
                    int id = get_id_veicolo(v);
                    if (id == id_veicolo) {
                        veicolo_selezionato = v;
                        break;
                    }
                    free(v);
                    temp = get_next_node(temp);
                }
                
                if(veicolo_selezionato == NULL) {
                    set_color(12); // Rosso
                    printf("Errore: Veicolo non trovato!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                int id = get_id_veicolo(veicolo_selezionato);
                int tipo = get_tipo_veicolo(veicolo_selezionato);
                
                printf("Giorno inizio (0-6, Lun-Dom): ");
                scanf("%d", &giorno_inizio);

                if(giorno_inizio < 0 || giorno_inizio > 6) {
                    set_color(12); // Rosso
                    printf("Errore: Giorno non valido!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }

                printf("Ora inizio (0-23): ");
                scanf("%d", &ora_inizio);

                if(ora_inizio < 0 || ora_inizio > 23) {
                    set_color(12); // Rosso
                    printf("Errore: Ora non valida!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }




                printf("Giorno fine (0-6, Lun-Dom): ");
                scanf("%d", &giorno_fine);

                if(giorno_fine < 0 || giorno_fine > 6) {
                    set_color(12); // Rosso
                    printf("Errore: Giorno non valido!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }



                printf("Ora fine (0-23): ");
                scanf("%d", &ora_fine);

                if(ora_fine < 0 || ora_fine > 23) {
                    set_color(12); // Rosso
                    printf("Errore: Ora non valida!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }


                // Converti le date in timestamp
                int giorno_ora_inizio = giorno_inizio * 24 + ora_inizio;
                int giorno_ora_fine = giorno_fine * 24 + ora_fine;
                
                // Valida le date
                int validazione = valida_data_prenotazione(giorno_ora_inizio, giorno_ora_fine);
                if (validazione != 0) {
                    set_color(12); // Rosso
                    if (validazione == -1) {
                        printf("\nErrore: Non puoi prenotare nel passato!\n");
                    } else {
                        printf("\nErrore: La data di fine deve essere successiva alla data di inizio!\n");
                    }
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                // Verifica sovrapposizioni
                if (verifica_sovrapposizioni(coda_prenotazioni, id_veicolo, giorno_ora_inizio, giorno_ora_fine) == 1) {
                    set_color(12); // Rosso
                    printf("\nErrore: Esiste gia' una prenotazione per questo veicolo in questo periodo!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                // Calcola e mostra il costo stimato
                double costo_base = calcola_tariffa_prenotazione(tipo, giorno_ora_inizio, giorno_ora_fine);
                
                // Calcola il numero di prenotazioni dell'utente per lo sconto fedeltà
                int num_prenotazioni = conta_prenotazioni_completate(coda_prenotazioni, id_utente);
                
                
                // Applica lo sconto fedeltà se applicabile
                double costo_finale = applica_sconto_fedelta(costo_base, num_prenotazioni);
                
                set_color(14); // Giallo
                printf("\nRiepilogo prenotazione:\n");
                printf("Veicolo: %s (ID: %d)\n", get_modello_veicolo(veicolo_selezionato), id);
                printf("Tariffa oraria: %.2f euro\n", get_tariffa_oraria(tipo));
                printf("Data inizio: %s ore %02d:00\n", get_nome_giorno(giorno_inizio), ora_inizio);
                printf("Data fine: %s ore %02d:00\n", get_nome_giorno(giorno_fine), ora_fine);
                printf("Costo base: %.2f euro\n", costo_base);
                
                if (costo_finale < costo_base) {
                    printf("Sconto fedelta' applicato: %.2f euro\n", costo_base - costo_finale);
                    printf("Costo finale: %.2f euro\n", costo_finale);
                }
                
                if (num_prenotazioni < NOLEGGI_PER_SCONTO) {
                    printf("\nNota: Ti mancano %d noleggi per ottenere lo sconto fedelta'!\n", 
                           NOLEGGI_PER_SCONTO - num_prenotazioni);
                }
                
                set_color(7); // Bianco
                
                printf("Confermi la prenotazione? (1: Si, 0: No): ");
                int conferma;
                scanf("%d", &conferma);
                if(!conferma) {
                    printf("Prenotazione annullata.\n");
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                // La priorità viene calcolata automaticamente in base al tempo
                Prenotazione nuova = crea_prenotazione(id_utente, id_veicolo, 
                                                     giorno_inizio, ora_inizio,
                                                     giorno_fine, ora_fine, 
                                                     -1);  // -1 indica di usare la priorità automatica
                
                if (nuova == NULL) {
                    set_color(12); // Rosso
                    printf("\nErrore nella creazione della prenotazione!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }
                
                int risultato = aggiungi_prenotazione(coda_prenotazioni, nuova);
                free(nuova);  // Libera la memoria dopo l'uso
                
                if (risultato == 0) {
                    set_color(10); // Verde
                    salva_prenotazioni_su_file(coda_prenotazioni);
                    printf("\nPrenotazione aggiunta con successo!\n");
                    printf("Costo totale: %.2f euro\n", costo_finale);
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
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = get_prenotazione_in_coda(coda_prenotazioni, i);
                    stampa_prenotazione(p);
                    
                    // Trova il veicolo per mostrare il costo
                    list temp = get_lista_veicoli();
                    while(temp != NULL) {
                        Veicolo v = get_veicolo_da_lista(&temp);
                        if (!v) continue;
                        int id = get_id_veicolo(v);
                        if (id == get_id_veicolo_prenotazione(p)) {
                            int tipo = get_tipo_veicolo(v);
                            double costo = calcola_tariffa_prenotazione(tipo, get_ora_inizio(p), get_ora_fine(p));
                            printf("Costo stimato: %.2f euro\n", costo);
                            break;
                        }
                        free(v);
                        temp = get_next_node(temp);
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
                    if (get_isAdmin_utente(get_username_utente(current_user)) || get_id_utente_prenotazione(prenotazione) == get_id_utente(get_username_utente(current_user))) {
                        set_stato_prenotazione(3, prenotazione);
                        salva_prenotazioni_su_file(coda_prenotazioni);
                        set_color(10); // Verde
                        printf("\nPrenotazione cancellata con successo!\n");
                    } else {
                        set_color(12); // Rosso
                        printf("\nNon hai i permessi per cancellare questa prenotazione!\n");
                    }
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
                // Solo gli admin possono modificare lo stato delle prenotazioni
                if (!get_isAdmin_utente(get_username_utente(current_user))) {
                    set_color(12); // Rosso
                    printf("\nSolo gli amministratori possono modificare lo stato delle prenotazioni!\n");
                    set_color(7); // Bianco
                    printf("Premi INVIO per continuare...");
                    svuota_buffer();
                    break;
                }

                int id_prenotazione, nuovo_stato;
                printf("\nInserisci l'ID della prenotazione da modificare: ");
                scanf("%d", &id_prenotazione);
                printf("Nuovo stato (0=In attesa, 1=Confermata, 2=Completata, 3=Cancellata): ");
                scanf("%d", &nuovo_stato);
                svuota_buffer();
                
                int risultato = modifica_stato_prenotazione(coda_prenotazioni, id_prenotazione, nuovo_stato);
                if (risultato == 0) {
                    salva_prenotazioni_su_file(coda_prenotazioni);
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
            case 5:
                visualizza_tariffe(current_user);
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
                set_color(12); // Rosso
                printf("\nScelta non valida. Premi INVIO per riprovare...");
                set_color(7); // Bianco
                svuota_buffer();
        }
    } while(scelta != 0);
}

void visualizza_prenotazioni() {
    pulisci_schermo();
    stampa_bordo_superiore();
    
    set_color(13); // Magenta
    printf("       ELENCO PRENOTAZIONI\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    set_color(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    set_color(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    CodaPrenotazioni coda = get_coda_prenotazioni();
    if (coda == NULL || get_dimensione_coda(coda) == 0) {
        set_color(12); // Rosso
        printf("  Nessuna prenotazione presente\n");
        set_color(7); // Bianco
    } else {
        for (int i = 0; i <get_dimensione_coda(coda); i++) {
            Prenotazione p = get_prenotazione_in_coda(coda, i);
            
            // Intestazione prenotazione
            set_color(14); // Giallo
            printf("  Prenotazione #%d\n", get_id_prenotazione(p));
            set_color(7); // Bianco
            
            // Dettagli prenotazione
            stampa_prenotazione(p);
            
            // Trova il veicolo per mostrare il costo
            list temp = get_lista_veicoli();
            while(temp != NULL) {
                Veicolo v = get_veicolo_da_lista(&temp);
                if (!v) continue;
                int id = get_id_veicolo(v);
                if (id == get_id_veicolo_prenotazione(p)) {
                    int tipo = get_tipo_veicolo(v);
                    double costo = calcola_tariffa_prenotazione(tipo, get_ora_inizio(p), get_ora_fine(p));
                    printf("Costo stimato: %.2f euro\n", costo);
                    break;
                }
                free(v);
                temp = get_next_node(temp);
            }
            
            if (i <get_dimensione_coda(coda) - 1) {
                stampa_separatore();
            }
        }
    }
    
    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}

void restituisci_auto() {
    pulisci_schermo();
    stampa_bordo_superiore();
    
    set_color(13); // Magenta
    printf("         RESTITUISCI AUTO\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    set_color(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    set_color(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    // TODO: Implementare la logica di restituzione
    set_color(12); // Rosso
    printf("  Funzionalita' in sviluppo...\n");
    set_color(7); // Bianco
    
    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}

void visualizza_disponibilita() {
    list veicoli = get_lista_veicoli();
    int id_veicolo=get_id_veicolo(get_veicolo_da_lista(&veicoli));
    CalendarioVeicolo calendario=inizializza_calendario(id_veicolo);
    CodaPrenotazioni coda_prenotazioni = NULL;
    
    pulisci_schermo();
    stampa_bordo_superiore();
    
    set_color(13); // Magenta
    printf("     VISUALIZZA DISPONIBILITA'\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    set_color(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    set_color(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    // Inizializza la coda delle prenotazioni
    coda_prenotazioni = inizializza_coda();
    if (coda_prenotazioni == NULL) {
        set_color(12); // Rosso
        printf("  Errore: Inizializzazione fallita\n");
        set_color(7); // Bianco
        stampa_bordo_inferiore();
        printf("Premi INVIO per continuare...");
        svuota_buffer();
        return;
    }
    
    // Carica le prenotazioni dal file
    carica_prenotazioni_da_file(coda_prenotazioni);
    
    // Visualizza lista veicoli con stato attuale
    set_color(10); // Verde
    printf("       VEICOLI E STATO ATTUALE\n");
    set_color(7); // Bianco
    
    list temp = get_lista_veicoli();
    if (temp == NULL) {
        set_color(12); // Rosso
        printf("  Nessun veicolo disponibile\n");
        set_color(7); // Bianco
    } else {
        while(temp != NULL) {
            // Inizializza e aggiorna il calendario per questo veicolo
            Veicolo v = get_veicolo_da_lista(&temp);
            if (!v) continue;
            int id = get_id_veicolo(v);
            CalendarioVeicolo cal_temp=inizializza_calendario(id);
            aggiorna_calendario(cal_temp, coda_prenotazioni);
           
            
            // Controlla se il veicolo è attualmente occupato
            int occupato_ora = get_disponibilita_veicolo(v);
            
            // Salva il valore originale di disponibile
            int disponibile_orig = get_disponibilita_veicolo(v);
            
            // Imposta temporaneamente disponibile in base all'occupazione attuale
            set_disponibilita_veicolo(v,!occupato_ora);
            
            // Stampa il veicolo
            stampa_veicolo(v);
            
            // Ripristina il valore originale di disponibile
            set_disponibilita_veicolo(v, disponibile_orig);
            
            if (get_next_node(temp) != NULL) {
                stampa_separatore();
            }
            free(v);
            temp = get_next_node(temp);
        }
    }
    
    stampa_separatore();
    
    // Chiedi l'ID del veicolo
    printf("Inserisci l'ID del veicolo: ");
    scanf("%d", &id_veicolo);
    svuota_buffer();
    
    // Inizializza e aggiorna il calendario
    aggiorna_calendario(calendario, coda_prenotazioni);
    
    stampa_separatore();
    
    // Visualizza il calendario
    set_color(14); // Giallo
    printf("         CALENDARIO VEICOLO\n");
    set_color(7); // Bianco
    visualizza_calendario(calendario);
    
    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}

void visualizza_tariffe(Utente current_user) {
    pulisci_schermo();
    stampa_bordo_superiore();
    
    set_color(13); // Magenta
    printf("          TARIFFE VEICOLI\n");
    
    stampa_separatore();
    
    // Mostra la data di sistema corrente
    set_color(14); // Giallo
    printf("         DATA DI SISTEMA\n");
    set_color(7); // Bianco
    stampa_data_sistema();
    
    stampa_separatore();
    
    // Sezione tariffe
    set_color(10); // Verde
    printf("      TARIFFE ORARIE VEICOLI\n");
    printf("1. Utilitaria: %.2f euro/ora\n", TARIFFA_UTILITARIA);
    printf("2. SUV: %.2f euro/ora\n", TARIFFA_SUV);
    printf("3. Sportiva: %.2f euro/ora\n", TARIFFA_SPORTIVA);
    printf("4. Moto: %.2f euro/ora\n", TARIFFA_MOTO);
    
    stampa_separatore();

    set_color(14); // Giallo
    printf("         SCONTI DISPONIBILI'\n");
    stampa_info_sconti();
    set_color(7); // Bianco

    // Mostra il numero di noleggi completati dell'utente corrente
    if (current_user != NULL) {
        int noleggi_completati = conta_prenotazioni_completate(get_coda_prenotazioni(), get_id_utente(get_username_utente(current_user)));
        printf("\nNoleggi completati: %d\n", noleggi_completati);
    }

    stampa_bordo_inferiore();
    printf("Premi INVIO per continuare...");
    svuota_buffer();
}



void mostra_menu_cliente(Utente current_user) {
    stampa_bordo_superiore();
    
    set_color(13);  // Magenta
    printf("        SISTEMA DI CAR SHARING\n");
    printf("        Benvenuto, %s\n", get_nome_utente(current_user));
    
    stampa_separatore();
    
    // Sezione Prenotazioni
    set_color(14);  // Giallo
    printf("           PRENOTAZIONI\n");
    set_color(7);   // Bianco
    printf("1. Prenota un'auto\n");
    printf("2. Visualizza le mie prenotazioni\n");
    
    stampa_separatore();
    
    // Sezione Informazioni
    set_color(10);  // Verde
    printf("           INFORMAZIONI\n");
    set_color(7);   // Bianco
    printf("3. Visualizza disponibilita'\n");
    printf("4. Visualizza tariffe\n");
    
    stampa_separatore();
    
    // Sezione Account
    set_color(12);  // Rosso
    printf("             ACCOUNT\n");
    set_color(7);   // Bianco
    printf("5. Logout\n");
    printf("0. Esci\n");
    
    stampa_bordo_inferiore();
}

void mostra_menu_admin(Utente current_user) {
    stampa_bordo_superiore();
    
    set_color(13);  // Magenta
    printf("      SISTEMA DI CAR SHARING\n");
    printf("      PANNELLO AMMINISTRATORE\n");
    printf("      Benvenuto, %s\n", get_nome_utente(current_user));
    
    stampa_separatore();
    
    // Sezione Gestione Sistema
    set_color(14);  // Giallo
    printf("        GESTIONE SISTEMA\n");
    set_color(7);   // Bianco
    printf("1. Gestione Veicoli\n");
    printf("2. Gestione Prenotazioni\n");
    
    stampa_separatore();
    
    // Sezione Monitoraggio
    set_color(10);  // Verde
    printf("          MONITORAGGIO\n");
    set_color(7);   // Bianco
    printf("3. Visualizza prenotazioni\n");
    printf("4. Gestione Utenti\n");
    printf("5. Visualizza disponibilita'\n");
    
    stampa_separatore();
    
    // Sezione Sistema
    set_color(12);  // Rosso
    printf("            SISTEMA\n");
    set_color(7);   // Bianco
    printf("6. Avanza tempo sistema\n");
    printf("7. Logout\n");
    printf("0. Esci\n");
    
    stampa_bordo_inferiore();
}

void gestione_prenotazioni_admin() {
    int scelta;
    CodaPrenotazioni coda_prenotazioni = get_coda_prenotazioni();
    
    do {
        pulisci_schermo();
        set_color(14); // Giallo
        printf("=====================================\n");
        printf("    GESTIONE PRENOTAZIONI (ADMIN)\n");
        printf("=====================================\n");
        set_color(7); // Bianco
        
        // Mostra la data di sistema corrente
        stampa_data_sistema();
        printf("\n");
        
        printf("1. Visualizza tutte le prenotazioni\n");
        printf("2. Filtra prenotazioni per utente\n");
        printf("3. Filtra prenotazioni per veicolo\n");
        printf("4. Filtra prenotazioni per stato\n");
        printf("5. Modifica stato prenotazione\n");
        printf("6. Visualizza prenotazioni in ordine di data\n");
        printf("7. Visualizza prenotazioni in ordine di priorita'\n");
        printf("0. Torna al menu principale\n");
        printf("-------------------------------------\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        svuota_buffer();

        switch(scelta) {
            case 1: {
                printf("\nElenco di tutte le prenotazioni:\n");
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = get_prenotazione_in_coda(coda_prenotazioni, i);
                    printf("\n--- Prenotazione %d ---\n", i + 1);
                    stampa_prenotazione(p);
                    
                    // Trova il veicolo per mostrare il costo
                    list temp = get_lista_veicoli();
                    while(temp != NULL) {
                        Veicolo v = get_veicolo_da_lista(&temp);
                        if (!v) continue;
                        int id = get_id_veicolo(v);
                        if (id == get_id_veicolo_prenotazione(p)) {
                            int tipo = get_tipo_veicolo(v);
                            double costo = calcola_tariffa_prenotazione(tipo, get_ora_inizio(p), get_ora_fine(p));
                            printf("Costo: %.2f euro\n", costo);
                            break;
                        }
                        free(v);
                        temp = get_next_node(temp);
                    }
                    printf("------------------------\n");
                }
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 2: {
                int id_utente;
                printf("Inserisci l'ID dell'utente: ");
                scanf("%d", &id_utente);
                svuota_buffer();
                
                printf("\nPrenotazioni dell'utente %d:\n", id_utente);
                int trovate = 0;
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = get_prenotazione_in_coda(coda_prenotazioni, i);
                    if (get_id_utente_prenotazione(p) == id_utente) {
                        trovate++;
                        printf("\n--- Prenotazione %d ---\n", trovate);
                        stampa_prenotazione(p);
                        printf("------------------------\n");
                    }
                }
                if (trovate == 0) {
                    printf("Nessuna prenotazione trovata per questo utente.\n");
                }
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 3: {
                int id_veicolo;
                printf("Inserisci l'ID del veicolo: ");
                scanf("%d", &id_veicolo);
                svuota_buffer();
                
                printf("\nPrenotazioni del veicolo %d:\n", id_veicolo);
                int trovate = 0;
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = get_prenotazione_in_coda(coda_prenotazioni, i);
                    if (get_id_veicolo_prenotazione(p) == id_veicolo) {
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
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    Prenotazione p = get_prenotazione_in_coda(coda_prenotazioni, i);
                    if ((int)get_stato_prenotazione(p) == stato) {
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
                int id_prenotazione, nuovo_stato;
                printf("Inserisci l'ID della prenotazione da modificare: ");
                scanf("%d", &id_prenotazione);
                printf("Nuovo stato (0=In attesa, 1=Confermata, 2=Completata, 3=Cancellata): ");
                scanf("%d", &nuovo_stato);
                svuota_buffer();
                
                if (modifica_stato_prenotazione(coda_prenotazioni, id_prenotazione, nuovo_stato) == 0) {
                    salva_prenotazioni_su_file(coda_prenotazioni);
                    printf("\nStato della prenotazione modificato con successo!\n");
                } else {
                    printf("\nErrore: prenotazione non trovata.\n");
                }
                printf("\nPremi INVIO per continuare...");
                svuota_buffer();
                break;
            }
            case 6: {
                // Creiamo un array temporaneo per ordinare le prenotazioni per data
                Prenotazione* temp = malloc(sizeof(Prenotazione) * get_dimensione_coda(coda_prenotazioni));
                if (temp == NULL) {
                    printf("Errore di allocazione memoria.\n");
                    break;
                }
                
                // Copiamo le prenotazioni nell'array temporaneo
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    temp[i] = get_prenotazione_in_coda(coda_prenotazioni, i);
                }
                
                // Ordiniamo per data di inizio (bubble sort)
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni) - 1; i++) {
                    for (int j = 0; j < get_dimensione_coda(coda_prenotazioni) - i - 1; j++) {
                        if (get_ora_inizio(temp[j]) > get_ora_inizio(temp[j + 1])) {
                            Prenotazione t = temp[j];
                            temp[j] = temp[j + 1];
                            temp[j + 1] = t;
                        }
                    }
                }
                
                // Stampiamo le prenotazioni ordinate
                printf("\nPrenotazioni ordinate per data:\n");
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
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
                for (int i = 0; i < get_dimensione_coda(coda_prenotazioni); i++) {
                    printf("\n--- Prenotazione %d ---\n", i + 1);
                    stampa_prenotazione(get_prenotazione_in_coda(coda_prenotazioni, i));
                    printf("------------------------\n");
                }
                printf("\nPremi INVIO per continuare...");
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
                break;
        }
    } while (scelta != 0);
}

void mostra_logo() {
    set_color(14); // Giallo
    printf("\n");
printf("_________                    _________.__                    .__                 \n");
printf("\\_   ___ \\ _____  _______   /   _____/|  |__  _____  _______ |__|  ____    ____  \n");
printf("/    \\  \\/ \\__  \\ \\_  __ \\  \\_____  \\ |  |  \\ \\__  \\ \\_  __ \\|  | /    \\  / ___\\ \n");
printf("\\     \\____ / __ \\_|  | \\/  /        \\|   Y  \\ / __ \\_|  | \\/|  ||   |  \\/ /_/  >\n");
printf(" \\______  /(____  /|__|    /_______  /|___|  /(____  /|__|   |__||___|  /\\___  / \n");
printf("        \\/      \\/                 \\/      \\/      \\/                 \\//_____/  \n");


    printf("\n");
    set_color(7); // Bianco
}

void mostra_menu_login() {
    stampa_bordo_superiore();
    
    mostra_logo();
    
    stampa_separatore();
    
    set_color(13); // Magenta
    printf("             BENVENUTO\n");
    stampa_separatore();
    
    set_color(10); // Verde
    printf("           ACCESSO\n");
    set_color(7); // Bianco
    printf("1. Accedi\n");
    printf("2. Registrati\n");
    
    stampa_separatore();
    
    set_color(12); // Rosso
    printf("           SISTEMA\n");
    set_color(7); // Bianco
    printf("0. Esci\n");
    
    stampa_bordo_inferiore();
}

int valida_username(const char* username) {
    if (strlen(username) < 3 || strlen(username) > 29) {
        return 0;
    }
    
    // Verifica che contenga solo caratteri alfanumerici e underscore
    for (int i = 0; username[i]; i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            return 0;
        }
    }
    return 1;
}

int valida_nome_completo(const char* nome) {
    if (strlen(nome) < 3 || strlen(nome) > 49) {
        return 0;
    }
    
    // Verifica che contenga solo lettere, spazi e alcuni caratteri speciali
    for (int i = 0; nome[i]; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ' && nome[i] != '\'' && nome[i] != '-') {
            return 0;
        }
    }
    return 1;
}
