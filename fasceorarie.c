#include "fasceorarie.h"

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
            for (int ora = p.ora_inizio; ora < p.ora_fine; ora++) {
                calendario->calendario[p.giorno_settimana][ora].occupato = 1;
                calendario->calendario[p.giorno_settimana][ora].id_prenotazione = p.id_prenotazione;
            }
        }
    }
}

// Funzione per ottenere il nome del giorno della settimana
const char* get_nome_giorno(int giorno) {
    switch (giorno) {
        case 0: return "Lunedi";
        case 1: return "Martedi";
        case 2: return "Mercoledi";
        case 3: return "Giovedi";
        case 4: return "Venerdi";
        case 5: return "Sabato";
        case 6: return "Domenica";
        default: return "Giorno non valido";
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
    }
    printf("==========================================\n");
    printf("Legenda: X = Occupato, Spazio vuoto = Libero\n");
}

// Funzione per verificare la disponibilità di un veicolo in una fascia oraria
int verifica_disponibilita(CalendarioVeicolo* calendario, int giorno, int ora_inizio, int ora_fine) {
    if (calendario == NULL) return 0;
    if (giorno < 0 || giorno > 6) return 0;
    if (ora_inizio < 0 || ora_inizio > 23) return 0;
    if (ora_fine < 0 || ora_fine > 23) return 0;
    if (ora_inizio >= ora_fine) return 0;
    
    // Verifica se tutte le ore nella fascia richiesta sono libere
    for (int ora = ora_inizio; ora < ora_fine; ora++) {
        if (calendario->calendario[giorno][ora].occupato) {
            return 0;  // Non disponibile
        }
    }
    
    return 1;  // Disponibile
}
