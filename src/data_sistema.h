#ifndef DATA_SISTEMA_H
#define DATA_SISTEMA_H

typedef struct DataSistema *DataSistema;

/**
 * @brief Inizializza la data di sistema
 * 
 * Alloca e inizializza la struttura DataSistema con i valori di default:
 * - Giorno: Lunedì (0)
 * - Ora: 8:00
 * 
 * @pre Nessuna
 * 
 * @post La data di sistema è inizializzata
 * @post Se l'allocazione fallisce, il programma termina
 * 
 * @sideeffect Alloca memoria per la struttura DataSistema
 */
void inizializza_data_sistema(void);

/**
 * @brief Avanza il tempo di sistema di un numero specificato di ore
 * 
 * Incrementa l'ora di sistema e gestisce automaticamente il riporto
 * delle ore e dei giorni della settimana.
 * 
 * @param ore Il numero di ore da avanzare
 * 
 * @pre ore deve essere un intero positivo
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Il tempo di sistema viene avanzato di 'ore' ore
 * @post Il giorno viene aggiornato se necessario (riporto dopo 24 ore)
 * 
 * @sideeffect Modifica la data di sistema
 */
void avanza_tempo(int ore);

/**
 * @brief Ottiene il puntatore alla data di sistema corrente
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Restituisce il puntatore alla struttura DataSistema corrente
 * 
 * @sideeffect Nessuno
 * 
 * @return DataSistema Il puntatore alla data di sistema
 */
DataSistema ottieni_data_sistema(void);

/**
 * @brief Converte una data in timestamp
 * 
 * Converte una data in un timestamp numerico (giorno*24 + ora)
 * 
 * @param data La data da convertire
 * 
 * @pre data deve essere un puntatore valido
 * 
 * @post Restituisce il timestamp corrispondente alla data
 * 
 * @sideeffect Nessuno
 * 
 * @return int Il timestamp (giorno*24 + ora)
 */
int converti_data_in_timestamp(DataSistema data);

/**
 * @brief Converte un timestamp in data
 * 
 * Converte un timestamp numerico in una struttura DataSistema
 * 
 * @param timestamp Il timestamp da convertire
 * 
 * @pre timestamp deve essere un intero non negativo
 * 
 * @post Restituisce una nuova struttura DataSistema con la data convertita
 * 
 * @sideeffect Alloca memoria per la nuova struttura DataSistema
 * 
 * @return DataSistema La data convertita
 */
DataSistema converti_timestamp_in_data(int timestamp);

/**
 * @brief Calcola la priorità temporale di una prenotazione
 * 
 * Calcola la priorità di una prenotazione basata sulla differenza
 * temporale con la data di sistema corrente.
 * 
 * @param timestamp_prenotazione Il timestamp della prenotazione
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Restituisce la priorità (0 per prenotazioni nel passato,
 *       valore crescente per prenotazioni future)
 * 
 * @sideeffect Nessuno
 * 
 * @return int La priorità della prenotazione
 */
int calcola_priorita_temporale(int timestamp_prenotazione);

/**
 * @brief Ottiene il nome del giorno della settimana
 * 
 * @param giorno Il numero del giorno (0-6, Lun-Dom)
 * 
 * @pre giorno deve essere un intero compreso tra 0 e 6
 * 
 * @post Restituisce il nome del giorno o "Giorno non valido"
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* Il nome del giorno
 */
const char* ottieni_nome_giorno(int giorno);

/**
 * @brief Ottiene il giorno da una struttura DataSistema
 * 
 * @param data La struttura DataSistema
 * 
 * @pre data deve essere un puntatore valido
 * 
 * @post Restituisce il giorno (0-6) o -1 se data è NULL
 * 
 * @sideeffect Nessuno
 * 
 * @return int Il giorno della settimana
 */
int ottieni_giorno_sistema(DataSistema data);

/**
 * @brief Ottiene l'ora da una struttura DataSistema
 * 
 * @param data La struttura DataSistema
 * 
 * @pre data deve essere un puntatore valido
 * 
 * @post Restituisce l'ora (0-23) o -1 se data è NULL
 * 
 * @sideeffect Nessuno
 * 
 * @return int L'ora del giorno
 */
int ottieni_ora_sistema(DataSistema data);

/**
 * @brief Ottiene l'ora corrente del sistema
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Restituisce l'ora corrente (0-23)
 * 
 * @sideeffect Nessuno
 * 
 * @return int L'ora corrente
 */
int ottieni_ora_corrente(void);

/**
 * @brief Ottiene il giorno corrente del sistema
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Restituisce il giorno corrente (0-6)
 * 
 * @sideeffect Nessuno
 * 
 * @return int Il giorno corrente
 */
int ottieni_giorno_corrente(void);

/**
 * @brief Ottiene il timestamp corrente del sistema
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Restituisce il timestamp corrente (giorno*24 + ora)
 * 
 * @sideeffect Nessuno
 * 
 * @return int Il timestamp corrente
 */
int ottieni_timestamp_corrente(void);

/**
 * @brief Libera la memoria allocata per la data di sistema
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post La memoria viene liberata
 * @post Il puntatore alla data di sistema viene impostato a NULL
 * 
 * @sideeffect Libera la memoria allocata
 */
void distruggi_data_sistema(void);

#endif /* DATA_SISTEMA_H */ 