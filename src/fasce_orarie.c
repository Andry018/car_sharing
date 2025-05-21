#include "fasce_orarie.h"
#include "data_sistema.h"
#include <stdio.h>
#include <stdlib.h>

// Funzione per inizializzare il calendario di un veicolo
void inizializza_calendario(CalendarioVeicolo* calendario, int id_veicolo) {
    if (calendario == NULL) return;
    
    calendario->id_veicolo = id_veicolo;
    
    // Inizializza tutte le fasce orarie come libere
    for (int giorno = 0; giorno < 7; giorno++) {
        for (int ora = 0; ora < 24; ora++) {
            calendario->calendario[giorno][ora].occupato = 0;
            calendario->calendario[giorno][ora].id_prenotazione = 0;
        }
    }
}

// Funzione per aggiornare il calendario con le prenotazioni dal file
void aggiorna_calendario(CalendarioVeicolo* calendario, CodaPrenotazioni* coda) {
    if (calendario == NULL || coda == NULL) return;
    
    // Prima inizializza il calendario
    inizializza_calendario(calendario, calendario->id_veicolo);
    
    // Poi aggiorna con le prenotazioni attive
    for (int i = 0; i < coda->dimensione; i++) {
        Prenotazione p = coda->heap[i];
        
        // Aggiorna solo se la prenotazione è per questo veicolo e non è cancellata
        if (p.id_veicolo == calendario->id_veicolo && p.stato != CANCELLATA) {
            int giorno_inizio = estrai_giorno(p.giorno_ora_inizio);
            int ora_inizio = estrai_ora(p.giorno_ora_inizio);
            int giorno_fine = estrai_giorno(p.giorno_ora_fine);
            int ora_fine = estrai_ora(p.giorno_ora_fine);
            
            // Gestione prenotazioni multi-giorno
            if (giorno_inizio == giorno_fine) {
                // Prenotazione nello stesso giorno
                for (int ora = ora_inizio; ora < ora_fine; ora++) {
                    calendario->calendario[giorno_inizio][ora].occupato = 1;
                    calendario->calendario[giorno_inizio][ora].id_prenotazione = p.id_prenotazione;
                }
            } else {
                // Prenotazione su più giorni
                // Primo giorno: da ora_inizio fino alla fine del giorno
                for (int ora = ora_inizio; ora < 24; ora++) {
                    calendario->calendario[giorno_inizio][ora].occupato = 1;
                    calendario->calendario[giorno_inizio][ora].id_prenotazione = p.id_prenotazione;
                }
                
                // Giorni intermedi: tutto il giorno
                for (int giorno = giorno_inizio + 1; giorno < giorno_fine; giorno++) {
                    for (int ora = 0; ora < 24; ora++) {
                        calendario->calendario[giorno][ora].occupato = 1;
                        calendario->calendario[giorno][ora].id_prenotazione = p.id_prenotazione;
                    }
                }
                
                // Ultimo giorno: dall'inizio fino a ora_fine
                for (int ora = 0; ora < ora_fine; ora++) {
                    calendario->calendario[giorno_fine][ora].occupato = 1;
                    calendario->calendario[giorno_fine][ora].id_prenotazione = p.id_prenotazione;
                }
            }
        }
    }
}

// Funzione per visualizzare il calendario di un veicolo
void visualizza_calendario(CalendarioVeicolo* calendario) {
    if (calendario == NULL) return;
    
    printf("\nCalendario per il veicolo ID: %d\n", calendario->id_veicolo);
    printf("==========================================\n");
    printf("Giorno/Ora  ");
    for (int ora = 0; ora <= 24; ora++) {
        if(ora == 0){
            printf("%02d ", ora);
        } else {
            printf("  %02d ", ora);
        }
    }
    printf("\n");
    
    // Stampa il calendario giorno per giorno
    for (int giorno = 0; giorno < 7; giorno++) {
        printf("%-10s  ||", get_nome_giorno(giorno));
        
        for (int ora = 0; ora < 24; ora++) {
            if (calendario->calendario[giorno][ora].occupato) {
                printf(" X ||");  // X indica occupato
            } else {
                printf("   ||");  // Spazio vuoto indica libero
            }
        }
        printf("\n");
        printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    printf("Legenda: X = Occupato, Spazio vuoto = Libero\n");
}

// Funzione per verificare la disponibilità di un veicolo in una fascia oraria
int verifica_disponibilita(CalendarioVeicolo* calendario, int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine) {
    if (calendario == NULL) return 0;
    if (giorno_inizio < 0 || giorno_inizio > 6) return 0;
    if (giorno_fine < 0 || giorno_fine > 6) return 0;
    if (ora_inizio < 0 || ora_inizio > 23) return 0;
    if (ora_fine < 0 || ora_fine > 23) return 0;
    if (giorno_inizio > giorno_fine) return 0;
    if (giorno_inizio == giorno_fine && ora_inizio >= ora_fine) return 0;
    
    // Verifica disponibilità per prenotazioni multi-giorno
    if (giorno_inizio == giorno_fine) {
        // Prenotazione nello stesso giorno
        for (int ora = ora_inizio; ora < ora_fine; ora++) {
            if (calendario->calendario[giorno_inizio][ora].occupato) {
                return 0;  // Non disponibile
            }
        }
    } else {
        // Prenotazione su più giorni
        // Verifica primo giorno
        for (int ora = ora_inizio; ora < 24; ora++) {
            if (calendario->calendario[giorno_inizio][ora].occupato) {
                return 0;
            }
        }
        
        // Verifica giorni intermedi
        for (int giorno = giorno_inizio + 1; giorno < giorno_fine; giorno++) {
            for (int ora = 0; ora < 24; ora++) {
                if (calendario->calendario[giorno][ora].occupato) {
                    return 0;
                }
            }
        }
        
        // Verifica ultimo giorno
        for (int ora = 0; ora < ora_fine; ora++) {
            if (calendario->calendario[giorno_fine][ora].occupato) {
                return 0;
            }
        }
    }
    
    return 1;  // Disponibile
}
