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
int get_giorno_sistema(DataSistema data);
int get_ora_sistema(DataSistema data); 
int get_ora_corrente(void);
int get_giorno_corrente(void);
int get_timestamp_corrente(void);
void distruggi_data_sistema(void);

#endif /* DATA_SISTEMA_H */ 