#ifndef fasce_orarie_H
#define fasce_orarie_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazioni.h"
#include "veicolo.h"

typedef struct FasciaOrarioa *FasciaOraria;

typedef struct CalendarioVeicolo *CalendarioVeicolo;

// Funzione per inizializzare il calendario di un veicolo
void inizializza_calendario(CalendarioVeicolo* calendario, int id_veicolo);

// Funzione per aggiornare il calendario con le prenotazioni dal file
void aggiorna_calendario(CalendarioVeicolo* calendario, CodaPrenotazioni* coda);

// Funzione per visualizzare il calendario di un veicolo
void visualizza_calendario(CalendarioVeicolo* calendario);

// Funzione per verificare la disponibilità di un veicolo in una fascia oraria
int verifica_disponibilita(CalendarioVeicolo* calendario, int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);

// Funzione per ottenere il nome del giorno della settimana
const char* get_nome_giorno(int giorno);

int get_stato_fascia_oraria(FasciaOraria* fascia_oraria);
int get_id_prenotazione_fascia(FasciaOraria* fascia_oraria);
int get_id_veicolo_calendario(CalendarioVeicolo* calendario);
FasciaOraria* get_fascia_oraria(CalendarioVeicolo* calendario, int giorno, int ora);

void set_stato_fascia_oraria(FasciaOraria* fascia_oraria, int stato);   
void set_id_prenotazione_fascia(FasciaOraria* fascia_oraria, int id_prenotazione);
void set_id_veicolo_calendario(CalendarioVeicolo* calendario, int id_veicolo);
void set_fascia_oraria(CalendarioVeicolo* calendario, int giorno, int ora, FasciaOraria* fascia);
#endif /* fasce_orarie_H */
