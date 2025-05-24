#ifndef DATA_SISTEMA_H
#define DATA_SISTEMA_H

typedef struct DataSistema *DataSistema;

// Funzioni per la gestione della data di sistema
void inizializza_data_sistema(void);
void avanza_tempo(int ore);
DataSistema get_data_sistema(void);
int converti_data_in_timestamp(DataSistema data);
DataSistema converti_timestamp_in_data(int timestamp);
int calcola_priorita_temporale(int timestamp_prenotazione);
const char* get_nome_giorno(int giorno);

#endif /* DATA_SISTEMA_H */ 