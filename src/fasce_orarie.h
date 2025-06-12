#ifndef fasce_orarie_H
#define fasce_orarie_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazioni.h"
#include "veicolo.h"

typedef struct FasciaOraria *FasciaOraria;

typedef struct CalendarioVeicolo *CalendarioVeicolo;

// Funzione per inizializzare il calendario di un veicolo
CalendarioVeicolo inizializza_calendario(int id_veicolo);

// Funzione per aggiornare il calendario con le prenotazioni dal file
CalendarioVeicolo aggiorna_calendario(CalendarioVeicolo calendario, CodaPrenotazioni coda);

// Funzione per visualizzare il calendario di un veicolo
void visualizza_calendario(CalendarioVeicolo calendario);

// Funzione per verificare la disponibilità di un veicolo in una fascia oraria
int verifica_disponibilita(CalendarioVeicolo calendario, int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);


int ottieni_stato_fascia_oraria(FasciaOraria fascia);
int ottieni_id_prenotazione_fascia(FasciaOraria fascia);
int ottieni_id_veicolo_calendario(CalendarioVeicolo calendario);
FasciaOraria ottieni_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora);

void imposta_stato_fascia_oraria(FasciaOraria fascia, int stato);   
void imposta_id_prenotazione_fascia(FasciaOraria fascia, int id_prenotazione);
void imposta_id_veicolo_calendario(CalendarioVeicolo calendario, int id_veicolo);
void imposta_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora, FasciaOraria fascia);
#endif /* fasce_orarie_H */
