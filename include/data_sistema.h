#ifndef DATA_SISTEMA_H
#define DATA_SISTEMA_H

typedef struct DataSistema *DataSistema;

// Basic system time functions
void inizializza_data_sistema();
void avanza_tempo(int ore);
DataSistema get_data_sistema();

// Conversion functions
int converti_data_in_timestamp(DataSistema data);
DataSistema converti_timestamp_in_data(int timestamp);

// Priority calculation
int calcola_priorita_temporale(int timestamp_prenotazione);

// Day name utility
const char* get_nome_giorno(int giorno);

// Getter functions for DataSistema struct fields
int get_giorno_sistema(DataSistema* data);
int get_ora_sistema(DataSistema* data);

// Helper functions for current system time
int get_giorno_corrente();
int get_ora_corrente();
int get_timestamp_corrente();

#endif // DATA_SISTEMA_H 