#include "tariffe.h"
#include "veicolo.h"
#include "prenotazioni.h"
#include "utenti.h"
#include <stdio.h>
#include <stdlib.h>

// Definizione delle tariffe orarie per tipo di veicolo (in euro)
#define TARIFFA_UTILITARIA 5.0
#define TARIFFA_SUV 8.0
#define TARIFFA_SPORTIVA 12.50
#define TARIFFA_MOTO 4.0

// Definizione degli sconti
#define SCONTO_FEDELTA 0.10  // 10% di sconto dopo 10 noleggi
#define NOLEGGI_PER_SCONTO 10  // Numero di noleggi necessari per lo sconto fedeltà
#define ORE_PER_PACCHETTO 5  // Numero di ore dopo le quali si ottiene un'ora gratuita

/**
 * @brief Ottiene la tariffa oraria base per un tipo di veicolo.
 * @param tipo Il tipo di veicolo (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * @return La tariffa oraria in euro per il tipo di veicolo, 0.0 se tipo non valido.
 */
double ottieni_tariffa_oraria(int tipo) {
    switch (tipo) {
        case 0:
            return TARIFFA_UTILITARIA;
        case 1:
            return TARIFFA_SUV;
        case 2:
            return TARIFFA_SPORTIVA;
        case 3:
            return TARIFFA_MOTO;
        default:
            return 0.0; // In caso di tipo non valido
    }
}

/**
 * @brief Applica lo sconto fedeltà a una tariffa.
 * Applica uno sconto del 10% se l'utente ha completato 10 noleggi.
 * @param tariffa_base La tariffa base a cui applicare lo sconto.
 * @param noleggi_completati Il numero di noleggi completati dall'utente.
 * @return La tariffa con lo sconto applicato se applicabile.
 */
double applica_sconto_fedelta(double tariffa_base, int noleggi_completati) {
    if (noleggi_completati == NOLEGGI_PER_SCONTO) {
        return tariffa_base * (1.0 - SCONTO_FEDELTA);
    } else {
        return tariffa_base;
    }
}

/**
 * @brief Calcola il numero di ore gratuite per un pacchetto.
 * Calcola quante ore gratuite spettano in base al numero totale di ore noleggiate.
 * @param ore_totali Il numero totale di ore di noleggio.
 * @return Il numero di ore gratuite (1 ogni 5 ore).
 */
int calcola_ore_gratuite(int ore_totali) {
    return ore_totali / (ORE_PER_PACCHETTO + 1); // Una ora gratis ogni 5 ore
}

/**
 * @brief Applica lo sconto pacchetto ore a una tariffa.
 * Applica lo sconto "1 ora gratis ogni 5 ore" alla tariffa base.
 * @param tariffa_base La tariffa oraria base.
 * @param ore_totali Il numero totale di ore di noleggio.
 * @return La tariffa con lo sconto pacchetto ore applicato.
 */
double applica_sconto_pacchetto_ore(double tariffa_base, int ore_totali) {
    int ore_gratuite = calcola_ore_gratuite(ore_totali);
    int ore_da_pagare = ore_totali - ore_gratuite;
    return tariffa_base * ore_da_pagare;
}

/**
 * @brief Calcola la tariffa totale per un noleggio.
 * Calcola la tariffa totale in base al tipo di veicolo e al numero di ore di noleggio,
 * applicando gli sconti per pacchetti orari (1 ora gratis ogni 5 ore).
 * @param tipo Il tipo di veicolo (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * @param ore_totali Il numero totale di ore di noleggio
 * @return La tariffa totale in euro
 */
double calcola_tariffa(int tipo, int ore_totali) {
    double tariffa_oraria = ottieni_tariffa_oraria(tipo);
    // Applica lo sconto pacchetto ore (1 ora gratis ogni 5 ore)
    return applica_sconto_pacchetto_ore(tariffa_oraria, ore_totali);
}

/**
 * @brief Calcola la tariffa per una prenotazione specifica.
 * Calcola la tariffa totale per una prenotazione considerando il tipo di veicolo
 * e l'intervallo di tempo tra inizio e fine prenotazione.
 * @param coda La coda delle prenotazioni.
 * @param tipo Il tipo di veicolo (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * @param giorno_ora_inizio L'ora di inizio prenotazione (formato: giorno*100 + ora)
 * @param giorno_ora_fine L'ora di fine prenotazione (formato: giorno*100 + ora)
 * @param id_utente ID dell'utente che effettua la prenotazione.
 * @return La tariffa totale in euro.
 */
double calcola_tariffa_prenotazione(CodaPrenotazioni coda, int tipo, int giorno_ora_inizio, int giorno_ora_fine, int id_utente) {
    // Estrai il giorno e l'ora dall'intero che li rappresenta
    int giorno_inizio = estrai_giorno(giorno_ora_inizio);
    int ora_inizio = estrai_ora(giorno_ora_inizio);
    int giorno_fine = estrai_giorno(giorno_ora_fine);
    int ora_fine = estrai_ora(giorno_ora_fine);
    
    // Calcola il numero totale di ore
    int ore_totali = 0;
    
    if (giorno_inizio == giorno_fine) {
        // Prenotazione nello stesso giorno
        ore_totali = ora_fine - ora_inizio;
    } else {
        // Prenotazione su più giorni
        // Ore del primo giorno
        ore_totali += (24 - ora_inizio);
        
        // Ore dei giorni intermedi
        ore_totali += (giorno_fine - giorno_inizio - 1) * 24;
        
        // Ore dell'ultimo giorno
        ore_totali += ora_fine;
    }
    
    double tariffa_base = calcola_tariffa(tipo, ore_totali);

    // --- SCONTO FEDELTA ---
    int noleggi_completati = conta_prenotazioni_completate(coda, id_utente);
    double tariffa_finale = applica_sconto_fedelta(tariffa_base, noleggi_completati);

    return tariffa_finale;
}

/**
 * @brief Stampa le informazioni sugli sconti disponibili.
 * Stampa a video le informazioni dettagliate sugli sconti disponibili:
 * - Sconto fedeltà (10% dopo 10 noleggi)
 * - Pacchetti orari (1 ora gratis ogni 5 ore)
 */
void stampa_info_sconti(void) {
    printf("\nSconti disponibili:\n");
    printf("1. Sconto fedelta':\n");
    printf("   - %.0f%% di sconto dopo %d noleggi\n", SCONTO_FEDELTA * 100, NOLEGGI_PER_SCONTO);
    printf("\n2. Pacchetti orari:\n");
    printf("   - 1 ora gratuita ogni %d ore di noleggio\n", ORE_PER_PACCHETTO);
    printf("   Esempio: noleggio di 6 ore = paghi 5 ore\n");
    printf("           noleggio di 12 ore = paghi 10 ore\n");
}

