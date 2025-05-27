#include "fasce_orarie.h"
#include "data_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include "prenotazioni.h"

// Struttura per rappresentare una fascia oraria
struct FasciaOraria {
    int occupato;          // 0 = libero, 1 = occupato
    int id_prenotazione;   // ID della prenotazione che occupa questa fascia
};

// Struttura per rappresentare il calendario di un veicolo
struct CalendarioVeicolo {
    int id_veicolo;
    FasciaOraria calendario[7][24];  // [giorno][ora]
};

// Funzione per inizializzare il calendario di un veicolo
CalendarioVeicolo inizializza_calendario(int id_veicolo) {
   CalendarioVeicolo nuovo_calendario= (CalendarioVeicolo)malloc(sizeof(struct CalendarioVeicolo));
    if (nuovo_calendario == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria per il calendario del veicolo.\n");
        exit(EXIT_FAILURE);
    }
    
    nuovo_calendario->id_veicolo = id_veicolo;
    
    // Inizializza tutte le fasce orarie come libere
    for (int giorno = 0; giorno < 7; giorno++) {
        for (int ora = 0; ora < 24; ora++) {
            nuovo_calendario->calendario[giorno][ora]->occupato = 0;
            nuovo_calendario->calendario[giorno][ora]->id_prenotazione = 0;
        }
    }
    return nuovo_calendario;
}

// Funzione per aggiornare il calendario con le prenotazioni dal file
void aggiorna_calendario(CalendarioVeicolo calendario, CodaPrenotazioni coda) {
    if (calendario == NULL || coda == NULL) return;
    
    // Prima inizializza il calendario
    inizializza_calendario( calendario->id_veicolo);
    
    // Poi aggiorna con le prenotazioni attive
    for (int i = 0; i < get_dimensione_coda(coda); i++) {
        Prenotazione p = get_prenotazione_in_coda(coda, i);
        
        // Aggiorna solo se la prenotazione è per questo veicolo e non è cancellata
        if (get_id_prenotazione(p)== calendario->id_veicolo && get_stato_prenotazione(p) != 0) {
            int giorno_inizio = estrai_giorno(get_giorno_ora_inizio(p));
            int ora_inizio = estrai_ora(get_giorno_ora_inizio(p));
            int giorno_fine = estrai_giorno(get_giorno_ora_fine(p));
            int ora_fine = estrai_ora(get_giorno_ora_inizio(p));
            
            // Gestione prenotazioni multi-giorno
            if (giorno_inizio == giorno_fine) {
                // Prenotazione nello stesso giorno
                for (int ora = ora_inizio; ora < ora_fine; ora++) {
                   calendario->calendario[giorno_inizio][ora]->occupato = 1;
                   calendario->calendario[giorno_inizio][ora]->id_prenotazione = get_id_prenotazione(p);
                }
            } else {
                // Prenotazione su più giorni
                // Primo giorno: da ora_inizio fino alla fine del giorno
                for (int ora = ora_inizio; ora < 24; ora++) {
                    calendario->calendario[giorno_inizio][ora]->occupato = 1;
                    calendario->calendario[giorno_inizio][ora]->id_prenotazione = get_id_prenotazione(p);
                }
                
                // Giorni intermedi: tutto il giorno
                for (int giorno = giorno_inizio + 1; giorno < giorno_fine; giorno++) {
                    for (int ora = 0; ora < 24; ora++) {
                        calendario->calendario[giorno][ora]->occupato = 1;
                        calendario->calendario[giorno][ora]->id_prenotazione = get_id_prenotazione(p);
                    }
                }
                
                // Ultimo giorno: dall'inizio fino a ora_fine
                for (int ora = 0; ora < ora_fine; ora++) {
                    calendario->calendario[giorno_fine][ora]->occupato = 1;
                    calendario->calendario[giorno_fine][ora]->id_prenotazione = get_id_prenotazione(p);
                }
            }
        }
    }
}

// Funzione per visualizzare il calendario di un veicolo
void visualizza_calendario(CalendarioVeicolo calendario) {
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
            if (calendario->calendario[giorno][ora]->occupato) {
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
int verifica_disponibilita(CalendarioVeicolo calendario, int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine) {
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
            if (calendario->calendario[giorno_inizio][ora]->occupato) {
                return 0;  // Non disponibile
            }
        }
    } else {
        // Prenotazione su più giorni
        // Verifica primo giorno
        for (int ora = ora_inizio; ora < 24; ora++) {
            if (calendario->calendario[giorno_inizio][ora]->occupato) {
                return 0;
            }
        }
        
        // Verifica giorni intermedi
        for (int giorno = giorno_inizio + 1; giorno < giorno_fine; giorno++) {
            for (int ora = 0; ora < 24; ora++) {
                if (calendario->calendario[giorno][ora]->occupato) {
                    return 0;
                }
            }
        }
        
        // Verifica ultimo giorno
        for (int ora = 0; ora < ora_fine; ora++) {
            if (calendario->calendario[giorno_fine][ora]->occupato) {
                return 0;
            }
        }
    }
    
    return 1;  // Disponibile
}

int get_stato_fascia_oraria(FasciaOraria fascia) {
    if (fascia == NULL) return -1;
    return fascia->occupato;
}

int get_id_prenotazione_fascia(FasciaOraria fascia) {
    if (fascia == NULL) return -1;
    return fascia->id_prenotazione;
}

int get_id_veicolo_calendario(CalendarioVeicolo calendario) {
    if (calendario == NULL) return -1;
    return calendario->id_veicolo;
}

FasciaOraria* get_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora) {
    if (calendario == NULL) return NULL;
    if (giorno < 0 || giorno > 6) return NULL;
    if (ora < 0 || ora > 23) return NULL;
    return &calendario->calendario[giorno][ora];
}

void set_stato_fascia_oraria(FasciaOraria fascia, int stato) {
    if (fascia == NULL) return;
    fascia->occupato = stato;
}

void set_id_prenotazione_fascia(FasciaOraria fascia, int id_prenotazione) {
    if (fascia == NULL) return;
    fascia->id_prenotazione = id_prenotazione;
}

void set_id_veicolo_calendario(CalendarioVeicolo calendario, int id_veicolo) {
    if (calendario == NULL) return;
    calendario->id_veicolo = id_veicolo;
}

void set_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora, FasciaOraria fascia) {
    if (calendario == NULL || fascia == NULL) return;
    if (giorno < 0 || giorno > 6) return;
    if (ora < 0 || ora > 23) return;
    
    calendario->calendario[giorno][ora] = fascia;
}


