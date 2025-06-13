#include "fasce_orarie.h"
#include "data_sistema.h"
#include <stdio.h>
#include <stdlib.h>
#include "prenotazioni.h"

/**
 * @struct FasciaOraria
 * @brief Rappresenta una singola fascia oraria nel calendario di un veicolo.
 *
 * @var FasciaOraria::occupato
 *   Indica se la fascia è occupata (1) o libera (0).
 * @var FasciaOraria::id_prenotazione
 *   ID della prenotazione che occupa questa fascia (0 se libera).
 */
struct FasciaOraria {
    int occupato;
    int id_prenotazione;
};

/**
 * @struct CalendarioVeicolo
 * @brief Rappresenta il calendario settimanale di un veicolo.
 *
 * @var CalendarioVeicolo::id_veicolo
 *   Identificativo del veicolo.
 * @var CalendarioVeicolo::calendario
 *   Matrice [7][24] di FasciaOraria per ogni giorno e ora della settimana.
 */
struct CalendarioVeicolo {
    int id_veicolo;
    struct FasciaOraria calendario[7][24];
};

/**
 * @brief Inizializza un nuovo calendario per un veicolo
 * @param id_veicolo ID del veicolo per cui creare il calendario
 * @return Puntatore al nuovo calendario inizializzato
 */
CalendarioVeicolo inizializza_calendario(int id_veicolo) {
    CalendarioVeicolo nuovo_calendario = (CalendarioVeicolo)malloc(sizeof(struct CalendarioVeicolo));
    if (nuovo_calendario == NULL) {
        fprintf(stderr, "Errore nell'allocazione della memoria per il calendario del veicolo.\n");
        exit(EXIT_FAILURE);
    }
    
    nuovo_calendario->id_veicolo = id_veicolo;
    
    // Inizializza tutte le fasce orarie come libere
    for (int giorno = 0; giorno < 7; giorno++) {
        for (int ora = 0; ora < 24; ora++) {
            nuovo_calendario->calendario[giorno][ora].occupato = 0;
            nuovo_calendario->calendario[giorno][ora].id_prenotazione = 0;
        }
    }
    return nuovo_calendario;
}

/**
 * @brief Aggiorna il calendario con le prenotazioni attive
 * @param calendario Calendario da aggiornare
 * @param coda Coda delle prenotazioni da cui leggere i dati
 * @return Puntatore al calendario aggiornato
 */
CalendarioVeicolo aggiorna_calendario(CalendarioVeicolo calendario, CodaPrenotazioni coda) {
    if (calendario == NULL || coda == NULL) {
        return NULL;
    }
    
    // Prima inizializza il calendario
    CalendarioVeicolo nuovo_calendario = inizializza_calendario(calendario->id_veicolo);
    int dimensione = ottieni_dimensione_coda(coda);
    // Poi aggiorna con le prenotazioni attive
    for (int i = 0; i < dimensione; i++) {
        Prenotazione p = ottieni_prenotazione_in_coda(coda, i);
        int id_v_prenotazione = ottieni_id_veicolo_prenotazione(p);
        int stato_prenotazione = ottieni_stato_prenotazione(p);
        // Aggiorna solo se la prenotazione è per questo veicolo ed è confermata
        if (id_v_prenotazione == calendario->id_veicolo && stato_prenotazione != 0 && stato_prenotazione != 2 && stato_prenotazione != 3) {
            int giorno_inizio = estrai_giorno(ottieni_giorno_ora_inizio(p));
            int ora_inizio = estrai_ora(ottieni_giorno_ora_inizio(p));
            int giorno_fine = estrai_giorno(ottieni_giorno_ora_fine(p));
            int ora_fine = estrai_ora(ottieni_giorno_ora_fine(p));
            
            // Gestione prenotazioni multi-giorno
            if (giorno_inizio == giorno_fine) {
                // Prenotazione nello stesso giorno
                for (int ora = ora_inizio; ora < ora_fine; ora++) {
                    nuovo_calendario->calendario[giorno_inizio][ora].occupato = 1;
                    nuovo_calendario->calendario[giorno_inizio][ora].id_prenotazione = ottieni_id_prenotazione(p);
                }
            } else {
                // Prenotazione su più giorni
                // Primo giorno: da ora_inizio fino alla fine del giorno
                for (int ora = ora_inizio; ora < 24; ora++) {
                    nuovo_calendario->calendario[giorno_inizio][ora].occupato = 1;
                    nuovo_calendario->calendario[giorno_inizio][ora].id_prenotazione = ottieni_id_prenotazione(p);
                }
                
                // Giorni intermedi: tutto il giorno
                for (int giorno = giorno_inizio + 1; giorno < giorno_fine; giorno++) {
                    for (int ora = 0; ora < 24; ora++) {
                        nuovo_calendario->calendario[giorno][ora].occupato = 1;
                        nuovo_calendario->calendario[giorno][ora].id_prenotazione = ottieni_id_prenotazione(p);
                    }
                }
                
                // Ultimo giorno: dall'inizio fino a ora_fine
                for (int ora = 0; ora < ora_fine; ora++) {
                    nuovo_calendario->calendario[giorno_fine][ora].occupato = 1;
                    nuovo_calendario->calendario[giorno_fine][ora].id_prenotazione = ottieni_id_prenotazione(p);
                }
            }
        }
    }
    free(calendario); // Libera la memoria del vecchio calendario

    // Dopo aver aggiornato il calendario:
    DataSistema data_attuale = ottieni_data_sistema();
    int giorno_attuale = ottieni_giorno_sistema(data_attuale);
    int ora_attuale = ottieni_ora_sistema(data_attuale);

    // Se la fascia oraria attuale è occupata, imposta il veicolo come non disponibile
    if (nuovo_calendario->calendario[giorno_attuale][ora_attuale].occupato) {
        // Cerca il veicolo nella lista globale e imposta disponibilità a 0
        Veicolo v = cerca_veicolo(ottieni_lista_veicoli(), nuovo_calendario->id_veicolo);
        if (v) {
            imposta_disponibilita_veicolo(v, 0);
        }
    } else {
        // Altrimenti, imposta disponibile
        Veicolo v = cerca_veicolo(ottieni_lista_veicoli(), nuovo_calendario->id_veicolo);
        if (v) {
            imposta_disponibilita_veicolo(v, 1);
        }
    }

    return nuovo_calendario;
}

/**
 * @brief Visualizza il calendario di un veicolo
 * @param calendario Calendario da visualizzare
 */
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
        printf("%-10s  ||", ottieni_nome_giorno(giorno));
        
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

/**
 * @brief Verifica la disponibilità di un veicolo in una fascia oraria
 * @param calendario Calendario del veicolo
 * @param giorno_inizio Giorno di inizio (0-6)
 * @param ora_inizio Ora di inizio (0-23)
 * @param giorno_fine Giorno di fine (0-6)
 * @param ora_fine Ora di fine (0-23)
 * @return 1 se disponibile, 0 altrimenti
 */
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


