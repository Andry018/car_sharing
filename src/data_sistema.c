#include "data_sistema.h"
#include <stdio.h>
#include <stdlib.h>

// Struttura per rappresentare la data e ora del sistema
struct DataSistema {
    int giorno;     // 0-6 (Lunedì-Domenica)
    int ora;        // 0-23
} ;

// Variabile statica per mantenere la data di sistema
static DataSistema data_corrente = NULL;  // Inizializza a Lunedì 00:00

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

void avanza_tempo(int ore) {
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

DataSistema ottieni_data_sistema() {
    return data_corrente;
}

int converti_data_in_timestamp(DataSistema data) {
    return (data->giorno * 24) + data->ora;
}

DataSistema converti_timestamp_in_data(int timestamp) {
    DataSistema data=ottieni_data_sistema();
    if (data == NULL) {
        data = (DataSistema)malloc(sizeof(struct DataSistema));
        if (data == NULL) {
            fprintf(stderr, "Errore nell'allocazione della memoria per DataSistema.\n");
            exit(EXIT_FAILURE);
        }
    }
    
    data->giorno = timestamp / 24;
    data->ora = timestamp % 24;
    
    return data;
}

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

const char* ottieni_nome_giorno(int giorno) {
    static const char* giorni[] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi", "Sabato", "Domenica"};
    if (giorno >= 0 && giorno < 7) {
        return giorni[giorno];
    }
    return "Giorno non valido";
}

// Getter functions for DataSistema struct fields
int ottieni_giorno_sistema(DataSistema data) {
    if (data == NULL) return -1;
    return data->giorno;
}

int ottieni_ora_sistema(DataSistema data) {
    if (data == NULL) return -1;
    return data->ora;
}

// Helper function to get current system day
int ottieni_giorno_corrente() {
    return data_corrente->giorno;
}

// Helper function to get current system hour
int ottieni_ora_corrente() {
    return data_corrente->ora;
}

// Helper function to get current system timestamp
int ottieni_timestamp_corrente() {
    return converti_data_in_timestamp(data_corrente);
} 

void distruggi_data_sistema() {
    if (data_corrente != NULL) {
        free(data_corrente);
        data_corrente = NULL;  // Imposta a NULL per evitare dangling pointer
    }
}