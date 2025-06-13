#include "data_sistema.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @struct DataSistema
 * @brief Rappresenta la data e l'ora correnti del sistema.
 *
 * @var DataSistema::giorno
 *   Giorno della settimana (0=Lunedì, ..., 6=Domenica).
 * @var DataSistema::ora
 *   Ora del giorno (0-23).
 */
struct DataSistema {
    int giorno;
    int ora;
} ;

// Variabile statica per mantenere la data di sistema
static DataSistema data_corrente = NULL;  // Inizializza a Lunedì 00:00

/**
 * @brief Inizializza la data di sistema.
 * @details Alloca la struttura DataSistema e la imposta a Lunedì 8:00.
 */
void inizializza_data_sistema() {
    if (data_corrente == NULL) {  // Alloca solo se non è già stato allocato
        data_corrente = (DataSistema)malloc(sizeof(struct DataSistema));
        if (data_corrente == NULL) {
            fprintf(stderr, "Errore nell'allocazione della memoria per DataSistema.\n");
            exit(EXIT_FAILURE);
        }
        // Inizializza a Lunedì alle 8:00
        data_corrente->giorno = 0;  // Lunedì
        data_corrente->ora = 8;     // 8:00
    }
}

/**
 * @brief Avanza il tempo di sistema di un numero specificato di ore.
 * @param ore Numero di ore da avanzare.
 * @note Side Effect: Modifica la data di sistema.
 */
void avanza_tempo(int ore) {
    // Validazione input
    if (ore < 0) {
        fprintf(stderr, "Errore: il numero di ore deve essere positivo\n");
        return;
    }
    if (data_corrente == NULL) {
        fprintf(stderr, "Errore: la data di sistema non è inizializzata\n");
        return;
    }

    data_corrente->ora += ore;
    
    // Gestisci il riporto delle ore
    while (data_corrente->ora >= 24) {
        data_corrente->ora -= 24;
        data_corrente->giorno++;
        
        // Gestisci il riporto dei giorni
        if (data_corrente->giorno >= 7) {
            data_corrente->giorno = 0;
        }
    }
}

/**
 * @brief Restituisce il puntatore alla data di sistema corrente.
 * @return Puntatore alla struttura DataSistema.
 */
DataSistema ottieni_data_sistema() {
    return data_corrente;
}

/**
 * @brief Converte una data in timestamp (giorno*24 + ora).
 * @param data Puntatore alla struttura DataSistema.
 * @return Il timestamp corrispondente.
 */
int converti_data_in_timestamp(DataSistema data) {
    return (data->giorno * 24) + data->ora;
}

/**
 * @brief Calcola la priorità temporale di una prenotazione rispetto alla data di sistema.
 * @param timestamp_prenotazione Il timestamp della prenotazione.
 * @return La priorità (0 per prenotazioni nel passato, valore crescente per prenotazioni future).
 */
int calcola_priorita_temporale(int timestamp_prenotazione) {
    // Calcola la differenza in ore tra la data di sistema e la prenotazione
    int timestamp_corrente = converti_data_in_timestamp(data_corrente);
    int differenza = timestamp_prenotazione - timestamp_corrente;
    
    // Se la prenotazione è nel passato, assegna priorità alta (numero basso)
    if (differenza < 0) {
        return 0;
    }
    
    // Altrimenti, la priorità aumenta con la distanza temporale
    // Più la prenotazione è lontana nel tempo, più alta è la priorità (numero più alto)
    return differenza;
}

/**
 * @brief Restituisce il nome del giorno della settimana.
 * @param giorno Numero del giorno (0-6).
 * @return Nome del giorno o "Giorno non valido".
 */
const char* ottieni_nome_giorno(int giorno) {
    static const char* giorni[] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi", "Sabato", "Domenica"};
    if (giorno >= 0 && giorno < 7) {
        return giorni[giorno];
    }
    return "Giorno non valido";
}

/**
 * @brief Restituisce il giorno dalla struttura DataSistema.
 * @param data Puntatore alla struttura DataSistema.
 * @return Giorno (0-6), oppure -1 se data è NULL.
 */
int ottieni_giorno_sistema(DataSistema data) {
    if (data == NULL) return -1;
    return data->giorno;
}

/**
 * @brief Restituisce l'ora dalla struttura DataSistema.
 * @param data Puntatore alla struttura DataSistema.
 * @return Ora (0-23), oppure -1 se data è NULL.
 */
int ottieni_ora_sistema(DataSistema data) {
    if (data == NULL) return -1;
    return data->ora;
}

/**
 * @brief Restituisce il giorno corrente del sistema.
 * @return Giorno corrente (0-6).
 */
int ottieni_giorno_corrente() {
    return data_corrente->giorno;
}

/**
 * @brief Restituisce l'ora corrente del sistema.
 * @return Ora corrente (0-23).
 */
int ottieni_ora_corrente() {
    return data_corrente->ora;
}