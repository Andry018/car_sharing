#ifndef TARIFFE_H
#define TARIFFE_H

/**
 * @brief Calcola il costo totale della prenotazione in base al tipo di veicolo e all'intervallo di tempo
 * 
 * La funzione calcola il costo totale della prenotazione in base al tipo di veicolo e all'intervallo di tempo
 * (giorno e ora di inizio/fine), tenendo conto della durata effettiva in ore e applicando eventuali sconti.
 * 
 * @pre tipo deve essere un codice valido per un veicolo esistente (0-3)
 * @pre giorno_ora_inizio e giorno_ora_fine devono essere nel formato ggoo dove gg ∈ [0, 6] e oo ∈ [0, 23]
 * @pre giorno_ora_inizio deve essere minore di giorno_ora_fine
 * 
 * @post Viene restituito il costo totale calcolato, considerando:
 *       - Tariffa oraria base del tipo di veicolo
 *       - Durata effettiva in ore
 *       - Eventuali sconti applicabili
 * 
 * @sideeffect Nessun effetto collaterale
 * 
 * @param tipo Codice valido per un veicolo esistente
 * @param giorno_ora_inizio Intero nel formato ggoo dove gg ∈ [0, 6] e oo ∈ [0, 23]
 * @param giorno_ora_fine Intero nel formato ggoo dove gg ∈ [0, 6] e oo ∈ [0, 23]
 * @return double Costo della prenotazione per l'intervallo specificato
 */
double calcola_tariffa_prenotazione(int tipo, int giorno_ora_inizio, int giorno_ora_fine);

/**
 * @brief Restituisce la tariffa oraria associata al tipo di veicolo specificato
 * 
 * @pre tipo deve essere un intero compreso tra 0 e 3
 * 
 * @post Viene restituita la tariffa oraria costante associata al tipo di veicolo
 * @post Se tipo non è valido, viene restituito 0.0
 * 
 * @sideeffect Nessun effetto collaterale
 * 
 * @param tipo Intero che rappresenta un codice valido per un veicolo (0 = Utilitaria, 1 = SUV, 2 = Sportiva, 3 = Moto)
 * @return double Tariffa oraria costante associata al tipo di veicolo, 0.0 se tipo non è valido
 */
double get_tariffa_oraria(int tipo);

/**
 * @brief Applica uno sconto fedeltà alla tariffa base se il numero di noleggi supera una soglia predefinita
 * 
 * @pre tariffa_base deve essere un valore non negativo
 * @pre numero_noleggi deve essere un intero non negativo
 * 
 * @post Se numero_noleggi ≥ NOLEGGI_PER_SCONTO, viene applicato lo sconto fedeltà
 * @post Se numero_noleggi < NOLEGGI_PER_SCONTO, viene restituita la tariffa base
 * 
 * @sideeffect Nessun effetto collaterale
 * 
 * @param tariffa_base Valore base della tariffa (≥ 0)
 * @param numero_noleggi Numero di noleggi completati (≥ 0)
 * @return double Tariffa scontata se numero_noleggi ≥ NOLEGGI_PER_SCONTO, altrimenti tariffa_base
 */
double applica_sconto_fedelta(double tariffa_base, int numero_noleggi);

/**
 * @brief Calcola il costo totale applicando una promozione per pacchetti di ore
 * 
 * La funzione calcola il costo totale applicando una promozione che prevede 1 ora gratuita
 * ogni certo numero di ore prenotate.
 * 
 * @pre tariffa_base deve essere un valore non negativo
 * @pre ore_totali deve essere un intero non negativo
 * 
 * @post Viene restituito il costo totale considerando le ore gratuite della promozione
 * @post Il costo viene calcolato come: tariffa_base * (ore_totali - ore_gratuite)
 * 
 * @sideeffect Nessun effetto collaterale
 * 
 * @param tariffa_base Valore base della tariffa (≥ 0)
 * @param ore_totali Numero totale di ore prenotate (≥ 0)
 * @return double Costo calcolato considerando le ore gratuite
 */
double applica_sconto_pacchetto_ore(double tariffa_base, int ore_totali);

/**
 * @brief Determina quante ore gratuite spettano in base alla promozione
 * 
 * La funzione determina quante ore gratuite spettano in base a una promozione che regala
 * 1 ora ogni pacchetto di ORE_PER_PACCHETTO + 1 ore totali.
 * 
 * @pre ore_totali deve essere un intero non negativo
 * 
 * @post Viene restituito il numero di ore gratuite spettanti
 * @post Il numero di ore gratuite è calcolato come: ore_totali / (ORE_PER_PACCHETTO + 1)
 * 
 * @sideeffect Nessun effetto collaterale
 * 
 * @param ore_totali Numero totale di ore prenotate (≥ 0)
 * @return int Numero di ore gratuite spettanti
 */
int calcola_ore_gratuite(int ore_totali);

/**
 * @brief Stampa informazioni sugli sconti disponibili nel sistema
 * 
 * La funzione stampa a video informazioni descrittive sugli sconti disponibili nel sistema
 * di noleggio, inclusi lo sconto fedeltà e le offerte sui pacchetti orari.
 * 
 * @pre La console deve supportare l'output testuale
 * 
 * @post Vengono stampate a video le informazioni sugli sconti disponibili
 * 
 * @sideeffect Modifica l'output del terminale
 */
void stampa_info_sconti(void);

#endif // TARIFFE_H 