#ifndef DATA_SISTEMA_H
#define DATA_SISTEMA_H

typedef struct DataSistema *DataSistema;

/**
 * @brief Inizializza la data e l'ora del sistema
 * 
 * Inizializza la data e l'ora del sistema impostandole a Lunedì alle 8:00.
 * Se la struttura dati non è già allocata, provvede ad allocarla.
 * 
 * @pre La memoria deve essere disponibile per l'allocazione
 * @post data_corrente è allocato se non lo era già
 * @post data_corrente->giorno è impostato a 0 (Lunedì)
 * @post data_corrente->ora è impostato a 8 (8:00)
 * @sideeffect Alloca memoria se necessario
 * @sideeffect Modifica i campi giorno e ora nella struttura puntata da data_corrente
 * @sideeffect In caso di errore di allocazione, termina il programma
 */
void inizializza_data_sistema(void);

/**
 * @brief Avanza l'orario del sistema
 * 
 * Avanza l'orario del sistema di un numero di ore specificato, aggiornando giorno e ora
 * con rollover appropriati.
 * 
 * @pre ore è un intero maggiore o uguale a 0
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post data_corrente->ora è incrementato di ore, con rollover a 0 dopo 23
 * @post Se l'ora supera le 23, il giorno viene incrementato di conseguenza, con rollover a 0 dopo il sesto giorno (domenica)
 * @sideeffect Modifica diretta dei campi giorno e ora nella struttura puntata da data_corrente
 * @param ore Numero di ore da avanzare
 */
void avanza_tempo(int ore);

/**
 * @brief Restituisce la data e l'ora correnti del sistema
 * 
 * Restituisce la data e l'ora correnti del sistema.
 * 
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post Restituisce il valore corrente della struttura DataSistema puntata da data_corrente
 * @return Puntatore alla struttura DataSistema corrente
 */
DataSistema get_data_sistema(void);

/**
 * @brief Converte una data in timestamp
 * 
 * Converte una data (giorno e ora) in un timestamp unico, espresso in ore totali
 * dall'inizio della settimana.
 * 
 * @pre data è un puntatore valido a una struttura DataSistema con campi giorno e ora
 * @pre giorno è compreso tra 0 e 6 (inclusi)
 * @pre ora è compreso tra 0 e 23 (inclusi)
 * @post Restituisce un intero pari a data->giorno * 24 + data->ora
 * @param data Puntatore alla struttura DataSistema da convertire
 * @return Timestamp in ore dall'inizio della settimana
 */
int converti_data_in_timestamp(DataSistema data);

/**
 * @brief Converte un timestamp in una struttura DataSistema
 * 
 * Converte un timestamp (numero totale di ore dall'inizio della settimana) in una
 * struttura DataSistema con giorno e ora.
 * 
 * @pre timestamp è un intero non negativo
 * @post Restituisce una struttura DataSistema tale che:
 *       - giorno = timestamp / 24
 *       - ora = timestamp % 24
 * @param timestamp Numero di ore dall'inizio della settimana
 * @return Puntatore alla struttura DataSistema convertita
 */
DataSistema converti_timestamp_in_data(int timestamp);

/**
 * @brief Calcola la priorità temporale di una prenotazione
 * 
 * Calcola la priorità temporale di una prenotazione rispetto alla data e ora
 * correnti del sistema.
 * 
 * @pre timestamp_prenotazione è un intero non negativo
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post Se differenza < 0, restituisce 0 (priorità massima)
 * @post Altrimenti, restituisce differenza (più grande è, più bassa è la priorità)
 * @param timestamp_prenotazione Timestamp della prenotazione
 * @return Valore della priorità (0 per massima priorità, altrimenti differenza temporale)
 */
int calcola_priorita_temporale(int timestamp_prenotazione);

/**
 * @brief Restituisce il nome del giorno della settimana
 * 
 * Restituisce il nome del giorno della settimana corrispondente all'intero giorno.
 * 
 * @pre giorno è un intero compreso tra 0 e 6 (0 = Lunedì, ..., 6 = Domenica)
 * @post Se giorno è valido, restituisce il nome del giorno corrispondente come stringa costante
 * @post Altrimenti, restituisce la stringa "Giorno non valido"
 * @param giorno Numero del giorno (0-6)
 * @return Nome del giorno come stringa costante
 */
const char* get_nome_giorno(int giorno);

/**
 * @brief Restituisce il giorno dalla struttura DataSistema
 * 
 * Restituisce il giorno contenuto nella struttura DataSistema passata come parametro.
 * 
 * @pre data è un puntatore valido a una struttura DataSistema oppure NULL
 * @post Se data è valido, restituisce il valore di data->giorno
 * @post Se data è NULL, restituisce -1
 * @param data Puntatore alla struttura DataSistema
 * @return Giorno della settimana (0-6) o -1 se data è NULL
 */
int get_giorno_sistema(DataSistema data);

/**
 * @brief Restituisce l'ora dalla struttura DataSistema
 * 
 * Restituisce l'ora contenuta nella struttura DataSistema passata come parametro.
 * 
 * @pre data è un puntatore valido a una struttura DataSistema oppure NULL
 * @post Se data è valido, restituisce il valore di data->ora
 * @post Se data è NULL, restituisce -1
 * @param data Puntatore alla struttura DataSistema
 * @return Ora del giorno (0-23) o -1 se data è NULL
 */
int get_ora_sistema(DataSistema data);

/**
 * @brief Restituisce l'ora corrente del sistema
 * 
 * Restituisce l'ora corrente del sistema.
 * 
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post Restituisce il valore di data_corrente->ora
 * @return Ora corrente (0-23)
 */
int get_ora_corrente(void);

/**
 * @brief Restituisce il giorno corrente del sistema
 * 
 * Restituisce il giorno corrente del sistema.
 * 
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post Restituisce il valore di data_corrente->giorno
 * @return Giorno corrente (0-6)
 */
int get_giorno_corrente(void);

/**
 * @brief Restituisce il timestamp corrente del sistema
 * 
 * Restituisce il timestamp corrente del sistema, cioè il numero totale di ore
 * trascorse dall'inizio della settimana.
 * 
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post Restituisce il risultato di converti_data_in_timestamp(data_corrente)
 * @return Timestamp corrente in ore dall'inizio della settimana
 */
int get_timestamp_corrente(void);

/**
 * @brief Libera la memoria allocata per la data del sistema
 * 
 * Libera la memoria allocata per la struttura data_corrente.
 * 
 * @pre data_corrente è un puntatore valido a una struttura DataSistema
 * @post La memoria puntata da data_corrente è stata liberata
 * @post data_corrente è impostato a NULL
 * @sideeffect Libera la memoria allocata
 */
void distruggi_data_sistema(void);

#endif /* DATA_SISTEMA_H */ 