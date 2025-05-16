#include "tariffe.h"
#include <stdio.h>
#include <stdlib.h>

// Funzione per ottenere la tariffa oraria in base al tipo di veicolo
double get_tariffa_oraria(TipoVeicolo tipo) {
    switch (tipo) {
        case UTILITARIA:
            return TARIFFA_UTILITARIA;
        case SUV:
            return TARIFFA_SUV;
        case SPORTIVA:
            return TARIFFA_SPORTIVA;
        case MOTO:
            return TARIFFA_MOTO;
        default:
            return 0.0; // In caso di tipo non valido
    }
}

// Funzione per ottenere il nome del tipo di veicolo
const char* get_nome_tipo_veicolo(TipoVeicolo tipo) {
    switch (tipo) {
        case UTILITARIA:
            return "Utilitaria";
        case SUV:
            return "SUV";
        case SPORTIVA:
            return "Sportiva";
        case MOTO:
            return "Moto";
        default:
            return "Tipo non valido";
    }
}

// Funzione per applicare lo sconto fedeltà
double applica_sconto_fedelta(double tariffa_base, int numero_noleggi) {
    if (numero_noleggi > NOLEGGI_PER_SCONTO) {
        return tariffa_base * (1.0 - SCONTO_FEDELTA);
    }
    return tariffa_base;
}

// Funzione per calcolare il numero di ore gratuite
int calcola_ore_gratuite(int ore_totali) {
    return ore_totali / (ORE_PER_PACCHETTO + 1); // Una ora gratis ogni 5 ore
}

// Funzione per applicare lo sconto pacchetto ore
double applica_sconto_pacchetto_ore(double tariffa_base, int ore_totali) {
    int ore_gratuite = calcola_ore_gratuite(ore_totali);
    int ore_da_pagare = ore_totali - ore_gratuite;
    return tariffa_base * ore_da_pagare;
}

// Funzione per calcolare la tariffa totale dato il tipo di veicolo e le ore totali
double calcola_tariffa(TipoVeicolo tipo, int ore_totali) {
    double tariffa_oraria = get_tariffa_oraria(tipo);
    return tariffa_oraria * ore_totali;
}

// Funzione per calcolare la tariffa di una prenotazione
double calcola_tariffa_prenotazione(TipoVeicolo tipo, int giorno_ora_inizio, int giorno_ora_fine) {
    // Estrai il giorno e l'ora dall'intero che li rappresenta
    int giorno_inizio = giorno_ora_inizio / 100;
    int ora_inizio = giorno_ora_inizio % 100;
    int giorno_fine = giorno_ora_fine / 100;
    int ora_fine = giorno_ora_fine % 100;
    
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
    
    return calcola_tariffa(tipo, ore_totali);
}

// Funzione per stampare le informazioni sugli sconti disponibili
void stampa_info_sconti(void) {
    printf("\nSconti disponibili:\n");
    printf("1. Sconto fedelta':\n");
    printf("   - %.0f%% di sconto dopo %d noleggi\n", SCONTO_FEDELTA * 100, NOLEGGI_PER_SCONTO);
    printf("\n2. Pacchetti orari:\n");
    printf("   - 1 ora gratuita ogni %d ore di noleggio\n", ORE_PER_PACCHETTO);
    printf("   Esempio: noleggio di 6 ore = paghi 5 ore\n");
    printf("           noleggio di 12 ore = paghi 10 ore\n");
} 

