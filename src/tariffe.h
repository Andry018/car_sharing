#ifndef TARIFFE_H
#define TARIFFE_H

/**
 * @brief Calcola la tariffa totale per un noleggio
 * 
 * Calcola la tariffa totale in base al tipo di veicolo e al numero di ore di noleggio,
 * applicando gli sconti per pacchetti orari (1 ora gratis ogni 5 ore).
 * 
 * @param tipo Il tipo di veicolo (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * @param ore_totali Il numero totale di ore di noleggio
 * 
 * @pre tipo deve essere un intero compreso tra 0 e 3
 * @pre ore_totali deve essere un intero positivo
 * 
 * @post Restituisce la tariffa totale calcolata in euro
 * 
 * @sideeffect Nessuno
 * 
 * @return double La tariffa totale in euro
 */
double calcola_tariffa(int tipo, int ore_totali);

/**
 * @brief Calcola la tariffa per una prenotazione specifica
 * 
 * Calcola la tariffa totale per una prenotazione considerando il tipo di veicolo
 * e l'intervallo di tempo tra inizio e fine prenotazione.
 * 
 * @param tipo Il tipo di veicolo (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * @param giorno_ora_inizio L'ora di inizio prenotazione (formato: giorno*100 + ora)
 * @param giorno_ora_fine L'ora di fine prenotazione (formato: giorno*100 + ora)
 * 
 * @pre tipo deve essere un intero compreso tra 0 e 3
 * @pre giorno_ora_inizio e giorno_ora_fine devono essere interi positivi
 * @pre giorno_ora_fine deve essere maggiore di giorno_ora_inizio
 * 
 * @post Restituisce la tariffa totale calcolata in euro
 * 
 * @sideeffect Nessuno
 * 
 * @return double La tariffa totale in euro
 */
double calcola_tariffa_prenotazione(int tipo, int giorno_ora_inizio, int giorno_ora_fine);

/**
 * @brief Ottiene la tariffa oraria base per un tipo di veicolo
 * 
 * Restituisce la tariffa oraria base per il tipo di veicolo specificato.
 * 
 * @param tipo Il tipo di veicolo (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * 
 * @pre tipo deve essere un intero compreso tra 0 e 3
 * 
 * @post Restituisce la tariffa oraria in euro per il tipo di veicolo
 * 
 * @sideeffect Nessuno
 * 
 * @return double La tariffa oraria in euro
 */
double ottieni_tariffa_oraria(int tipo);

/**
 * @brief Applica lo sconto fedeltà a una tariffa
 * 
 * Applica uno sconto del 10% se l'utente ha completato 10 noleggi.
 * 
 * @param tariffa_base La tariffa base a cui applicare lo sconto
 * @param noleggi_completati Il numero di noleggi completati dall'utente
 * 
 * @pre tariffa_base deve essere un valore positivo
 * @pre noleggi_completati deve essere un intero non negativo
 * 
 * @post Restituisce la tariffa con lo sconto applicato se applicabile
 * 
 * @sideeffect Nessuno
 * 
 * @return double La tariffa con lo sconto applicato
 */
double applica_sconto_fedelta(double tariffa_base, int noleggi_completati);

/**
 * @brief Applica lo sconto pacchetto ore a una tariffa
 * 
 * Applica lo sconto "1 ora gratis ogni 5 ore" alla tariffa base.
 * 
 * @param tariffa_base La tariffa oraria base
 * @param ore_totali Il numero totale di ore di noleggio
 * 
 * @pre tariffa_base deve essere un valore positivo
 * @pre ore_totali deve essere un intero positivo
 * 
 * @post Restituisce la tariffa con lo sconto pacchetto ore applicato
 * 
 * @sideeffect Nessuno
 * 
 * @return double La tariffa con lo sconto applicato
 */
double applica_sconto_pacchetto_ore(double tariffa_base, int ore_totali);

/**
 * @brief Calcola il numero di ore gratuite per un pacchetto
 * 
 * Calcola quante ore gratuite spettano in base al numero totale di ore noleggiate.
 * 
 * @param ore_totali Il numero totale di ore di noleggio
 * 
 * @pre ore_totali deve essere un intero positivo
 * 
 * @post Restituisce il numero di ore gratuite (1 ogni 5 ore)
 * 
 * @sideeffect Nessuno
 * 
 * @return int Il numero di ore gratuite
 */
int calcola_ore_gratuite(int ore_totali);

/**
 * @brief Stampa le informazioni sugli sconti disponibili
 * 
 * Stampa a video le informazioni dettagliate sugli sconti disponibili:
 * - Sconto fedeltà (10% dopo 10 noleggi)
 * - Pacchetti orari (1 ora gratis ogni 5 ore)
 * 
 * @pre Nessuna
 * 
 * @post Le informazioni sugli sconti vengono stampate su stdout
 * 
 * @sideeffect Output su console
 */
void stampa_info_sconti(void);

#endif // TARIFFE_H 