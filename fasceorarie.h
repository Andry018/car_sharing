#ifndef FASCEORARIE_H
#define FASCEORARIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazioni.h"
#include "vehicle.h"

// Struttura per rappresentare una fascia oraria
typedef struct {
    int occupato;          // 0 = libero, 1 = occupato
    int id_prenotazione;   // ID della prenotazione che occupa questa fascia
} FasciaOraria;

// Struttura per rappresentare il calendario di un veicolo
typedef struct {
    int id_veicolo;
    FasciaOraria calendario[7][24];  // [giorno][ora]
} CalendarioVeicolo;

// Funzione per inizializzare il calendario di un veicolo
void inizializza_calendario(CalendarioVeicolo* calendario, int id_veicolo);

// Funzione per aggiornare il calendario con le prenotazioni dal file
void aggiorna_calendario(CalendarioVeicolo* calendario, CodaPrenotazioni* coda);

// Funzione per visualizzare il calendario di un veicolo
void visualizza_calendario(CalendarioVeicolo* calendario);

// Funzione per verificare la disponibilità di un veicolo in una fascia oraria
int verifica_disponibilita(CalendarioVeicolo* calendario, int giorno, int ora_inizio, int ora_fine);

// Funzione per ottenere il nome del giorno della settimana
const char* get_nome_giorno(int giorno);

#endif /* FASCEORARIE_H */
