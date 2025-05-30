#ifndef fasce_orarie_H
#define fasce_orarie_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazioni.h"
#include "veicolo.h"

typedef struct FasciaOraria *FasciaOraria;

typedef struct CalendarioVeicolo *CalendarioVeicolo;

/**
 * @brief Inizializza il calendario di un veicolo specifico
 * 
 * La funzione alloca e inizializza una nuova struttura CalendarioVeicolo per il veicolo identificato da id_veicolo,
 * impostando tutte le 168 fasce orarie (24 ore × 7 giorni) come disponibili.
 * 
 * @param id_veicolo Identificatore del veicolo
 * @return CalendarioVeicolo Puntatore alla nuova struttura CalendarioVeicolo inizializzata
 * @note Se l'allocazione fallisce, la funzione termina il programma con EXIT_FAILURE
 */
CalendarioVeicolo inizializza_calendario(int id_veicolo);

/**
 * @brief Aggiorna il calendario con le prenotazioni attive
 * 
 * La funzione crea un nuovo calendario inizializzandolo a tutte fasce libere e poi lo aggiorna
 * con le prenotazioni attive presenti nella coda, gestendo correttamente anche le prenotazioni multi-giorno.
 * 
 * @param calendario Puntatore al calendario da aggiornare
 * @param coda Puntatore alla coda delle prenotazioni
 * @return CalendarioVeicolo Puntatore al nuovo calendario aggiornato, NULL se i parametri non sono validi
 * @note La funzione libera la memoria del vecchio calendario
 */
CalendarioVeicolo aggiorna_calendario(CalendarioVeicolo calendario, CodaPrenotazioni coda);

/**
 * @brief Visualizza il calendario di un veicolo
 * 
 * Stampa una tabella con righe per ogni giorno (da Lunedì a Domenica) e colonne per ogni ora (0–23).
 * Ogni cella della tabella indica se una fascia oraria è occupata (X) oppure libera (spazio vuoto).
 * 
 * @param calendario Puntatore al calendario da visualizzare
 */
void visualizza_calendario(CalendarioVeicolo calendario);

/**
 * @brief Verifica la disponibilità di un veicolo in una fascia oraria
 * 
 * @param calendario Puntatore al calendario del veicolo
 * @param giorno_inizio Giorno di inizio (0-6, Lun-Dom)
 * @param ora_inizio Ora di inizio (0-23)
 * @param giorno_fine Giorno di fine (0-6, Lun-Dom)
 * @param ora_fine Ora di fine (0-23)
 * @return int 1 se la fascia è disponibile, 0 altrimenti
 */
int verifica_disponibilita(CalendarioVeicolo calendario, int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);

/**
 * @brief Ottiene lo stato di occupazione di una fascia oraria
 * 
 * @param fascia Puntatore alla fascia oraria
 * @return int 0 se libera, 1 se occupata, -1 se fascia è NULL
 */
int get_stato_fascia_oraria(FasciaOraria fascia);

/**
 * @brief Ottiene l'ID della prenotazione associata a una fascia oraria
 * 
 * @param fascia Puntatore alla fascia oraria
 * @return int ID della prenotazione, 0 se nessuna prenotazione, -1 se fascia è NULL
 */
int get_id_prenotazione_fascia(FasciaOraria fascia);

/**
 * @brief Ottiene l'ID del veicolo associato al calendario
 * 
 * @param calendario Puntatore al calendario
 * @return int ID del veicolo, -1 se calendario è NULL
 */
int get_id_veicolo_calendario(CalendarioVeicolo calendario);

/**
 * @brief Ottiene una fascia oraria specifica dal calendario
 * 
 * @param calendario Puntatore al calendario
 * @param giorno Giorno della settimana (0-6, Lun-Dom)
 * @param ora Ora del giorno (0-23)
 * @return FasciaOraria Puntatore alla fascia oraria, NULL se parametri non validi
 */
FasciaOraria get_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora);

/**
 * @brief Imposta lo stato di occupazione di una fascia oraria
 * 
 * @param fascia Puntatore alla fascia oraria
 * @param stato Nuovo stato (0=libero, 1=occupato)
 */
void set_stato_fascia_oraria(FasciaOraria fascia, int stato);   

/**
 * @brief Imposta l'ID della prenotazione per una fascia oraria
 * 
 * @param fascia Puntatore alla fascia oraria
 * @param id_prenotazione ID della prenotazione
 */
void set_id_prenotazione_fascia(FasciaOraria fascia, int id_prenotazione);

/**
 * @brief Imposta l'ID del veicolo per un calendario
 * 
 * @param calendario Puntatore al calendario
 * @param id_veicolo ID del veicolo
 */
void set_id_veicolo_calendario(CalendarioVeicolo calendario, int id_veicolo);

/**
 * @brief Imposta una fascia oraria nel calendario
 * 
 * @param calendario Puntatore al calendario
 * @param giorno Giorno della settimana (0-6, Lun-Dom)
 * @param ora Ora del giorno (0-23)
 * @param fascia Puntatore alla fascia oraria da impostare
 */
void set_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora, FasciaOraria fascia);

#endif /* fasce_orarie_H */
