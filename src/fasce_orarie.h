#ifndef fasce_orarie_H
#define fasce_orarie_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazioni.h"
#include "veicolo.h"

/**
 * @brief Forward declaration per information hiding
 */
typedef struct FasciaOraria *FasciaOraria;

/**
 * @brief Forward declaration per information hiding
 */
typedef struct CalendarioVeicolo *CalendarioVeicolo;

/**
 * @brief Inizializza un nuovo calendario per un veicolo
 * 
 * @param id_veicolo ID del veicolo per cui creare il calendario
 * 
 * @pre id_veicolo deve essere un intero positivo
 * 
 * @post Se l'allocazione ha successo, viene restituito un puntatore a un nuovo calendario inizializzato
 * @post Se l'allocazione fallisce, il programma termina con errore
 * 
 * @note Side Effect: Alloca memoria per la struttura CalendarioVeicolo
 * 
 * @return CalendarioVeicolo Puntatore al nuovo calendario inizializzato
 */
CalendarioVeicolo inizializza_calendario(int id_veicolo);

/**
 * @brief Aggiorna il calendario con le prenotazioni attive
 * 
 * @param calendario Calendario da aggiornare
 * @param coda Coda delle prenotazioni da cui leggere i dati
 * 
 * @pre calendario deve essere un puntatore valido a una struttura CalendarioVeicolo
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni
 * 
 * @post Il calendario viene aggiornato con le prenotazioni attive
 * @post La disponibilità del veicolo viene aggiornata in base allo stato attuale
 * 
 * @note Side Effect: Modifica il contenuto del calendario
 * @note Side Effect: Libera la memoria del vecchio calendario
 * 
 * @return CalendarioVeicolo Puntatore al calendario aggiornato
 */
CalendarioVeicolo aggiorna_calendario(CalendarioVeicolo calendario, CodaPrenotazioni coda);

/**
 * @brief Visualizza il calendario di un veicolo
 * 
 * @param calendario Calendario da visualizzare
 * 
 * @pre calendario deve essere un puntatore valido a una struttura CalendarioVeicolo
 * 
 * @post Il calendario viene stampato su stdout in formato tabellare
 * 
 * @note Side Effect: Scrive su stdout
 */
void visualizza_calendario(CalendarioVeicolo calendario);

/**
 * @brief Verifica la disponibilità di un veicolo in una fascia oraria
 * 
 * @param calendario Calendario del veicolo
 * @param giorno_inizio Giorno di inizio (0-6)
 * @param ora_inizio Ora di inizio (0-23)
 * @param giorno_fine Giorno di fine (0-6)
 * @param ora_fine Ora di fine (0-23)
 * 
 * @pre calendario deve essere un puntatore valido
 * @pre giorno_inizio e giorno_fine devono essere compresi tra 0 e 6
 * @pre ora_inizio e ora_fine devono essere compresi tra 0 e 23
 * 
 * @post Viene restituito 1 se il veicolo è disponibile nell'intervallo specificato
 * @post Viene restituito 0 se il veicolo non è disponibile o i parametri non sono validi
 * 
 * @return int 1 se disponibile, 0 altrimenti
 */
int verifica_disponibilita(CalendarioVeicolo calendario, int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);

#endif /* fasce_orarie_H */
