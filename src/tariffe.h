#ifndef TARIFFE_H
#define TARIFFE_H

// Definizione delle tariffe orarie per tipo di veicolo (in euro)
#define TARIFFA_UTILITARIA 5.0
#define TARIFFA_SUV 8.0
#define TARIFFA_SPORTIVA 12.50
#define TARIFFA_MOTO 4.0

// Definizione degli sconti
#define SCONTO_FEDELTA 0.10  // 10% di sconto dopo 10 noleggi
#define NOLEGGI_PER_SCONTO 10  // Numero di noleggi necessari per lo sconto fedeltà
#define ORE_PER_PACCHETTO 5  // Numero di ore dopo le quali si ottiene un'ora gratuita


typedef struct Tariffa *Tariffa;

// Funzioni per il calcolo delle tariffe
double calcola_tariffa(int tipo, int ore_totali);
double calcola_tariffa_prenotazione(int tipo, int giorno_ora_inizio, int giorno_ora_fine);

double get_tariffa_oraria(int tipo);

// Nuove funzioni per gli sconti
double applica_sconto_fedelta(double tariffa_base, int numero_noleggi);
double applica_sconto_pacchetto_ore(double tariffa_base, int ore_totali);
int calcola_ore_gratuite(int ore_totali);
void stampa_info_sconti(void);

#endif // TARIFFE_H 