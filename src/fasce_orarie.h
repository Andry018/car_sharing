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
 * @sideeffect Alloca memoria per la struttura CalendarioVeicolo
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
 * @sideeffect Modifica il contenuto del calendario
 * @sideeffect Libera la memoria del vecchio calendario
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
 * @sideeffect Scrive su stdout
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

/**
 * @brief Ottiene lo stato di occupazione di una fascia oraria
 * 
 * @param fascia Fascia oraria da controllare
 * 
 * @pre fascia deve essere un puntatore valido
 * 
 * @post Viene restituito 1 se la fascia è occupata, 0 se libera, -1 se fascia è NULL
 * 
 * @return int Stato della fascia oraria
 */
int ottieni_stato_fascia_oraria(FasciaOraria fascia);

/**
 * @brief Ottiene l'ID della prenotazione associata a una fascia oraria
 * 
 * @param fascia Fascia oraria da controllare
 * 
 * @pre fascia deve essere un puntatore valido
 * 
 * @post Viene restituito l'ID della prenotazione o -1 se fascia è NULL
 * 
 * @return int ID della prenotazione
 */
int ottieni_id_prenotazione_fascia(FasciaOraria fascia);

/**
 * @brief Ottiene l'ID del veicolo associato al calendario
 * 
 * @param calendario Calendario da controllare
 * 
 * @pre calendario deve essere un puntatore valido
 * 
 * @post Viene restituito l'ID del veicolo o -1 se calendario è NULL
 * 
 * @return int ID del veicolo
 */
int ottieni_id_veicolo_calendario(CalendarioVeicolo calendario);

/**
 * @brief Ottiene una fascia oraria specifica dal calendario
 * 
 * @param calendario Calendario da cui ottenere la fascia
 * @param giorno Giorno della fascia (0-6)
 * @param ora Ora della fascia (0-23)
 * 
 * @pre calendario deve essere un puntatore valido
 * @pre giorno deve essere compreso tra 0 e 6
 * @pre ora deve essere compresa tra 0 e 23
 * 
 * @post Viene restituito un puntatore alla fascia oraria richiesta
 * @post Viene restituito NULL se i parametri non sono validi
 * 
 * @return FasciaOraria Puntatore alla fascia oraria
 */
FasciaOraria ottieni_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora);

/**
 * @brief Imposta lo stato di occupazione di una fascia oraria
 * 
 * @param fascia Fascia oraria da modificare
 * @param stato Nuovo stato (0 = libero, 1 = occupato)
 * 
 * @pre fascia deve essere un puntatore valido
 * 
 * @post Lo stato della fascia viene aggiornato
 */
void imposta_stato_fascia_oraria(FasciaOraria fascia, int stato);

/**
 * @brief Imposta l'ID della prenotazione per una fascia oraria
 * 
 * @param fascia Fascia oraria da modificare
 * @param id_prenotazione ID della prenotazione da associare
 * 
 * @pre fascia deve essere un puntatore valido
 * 
 * @post L'ID della prenotazione viene aggiornato
 */
void imposta_id_prenotazione_fascia(FasciaOraria fascia, int id_prenotazione);

/**
 * @brief Imposta l'ID del veicolo per un calendario
 * 
 * @param calendario Calendario da modificare
 * @param id_veicolo ID del veicolo da associare
 * 
 * @pre calendario deve essere un puntatore valido
 * 
 * @post L'ID del veicolo viene aggiornato
 */
void imposta_id_veicolo_calendario(CalendarioVeicolo calendario, int id_veicolo);

/**
 * @brief Imposta una fascia oraria nel calendario
 * 
 * @param calendario Calendario da modificare
 * @param giorno Giorno della fascia (0-6)
 * @param ora Ora della fascia (0-23)
 * @param fascia Nuova fascia oraria da impostare
 * 
 * @pre calendario e fascia devono essere puntatori validi
 * @pre giorno deve essere compreso tra 0 e 6
 * @pre ora deve essere compresa tra 0 e 23
 * 
 * @post La fascia oraria specificata viene aggiornata
 */
void imposta_fascia_oraria(CalendarioVeicolo calendario, int giorno, int ora, FasciaOraria fascia);

#endif /* fasce_orarie_H */
