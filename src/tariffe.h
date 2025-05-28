#ifndef TARIFFE_H
#define TARIFFE_H



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