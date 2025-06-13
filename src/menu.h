#ifndef MENU_H
#define MENU_H

#include "utenti.h"
#include "prenotazioni.h"
#include "veicolo.h"
#include "tariffe.h"
#include "fasce_orarie.h"

/**
 * @brief Visualizza le tariffe dei veicoli e gli sconti disponibili
 * @param utente_corrente L'utente corrente per mostrare eventuali sconti fedeltà
 * @details Mostra le tariffe orarie per ogni tipo di veicolo e gli sconti disponibili.
 * Se l'utente è loggato, mostra anche il suo stato fedeltà.
 */
/**
 * @brief Visualizza le tariffe dei veicoli e gli sconti disponibili
 * @param utente_corrente L'utente corrente per mostrare eventuali sconti fedeltà
 * @details Mostra le tariffe orarie per ogni tipo di veicolo e gli sconti disponibili.
 * Se l'utente è loggato, mostra anche il suo stato fedeltà.
 */
void visualizza_tariffe(Utente utente_corrente);

/**
 * @brief Gestisce le operazioni relative ai veicoli
 * @details Permette di aggiungere, rimuovere e visualizzare i veicoli nel sistema.
 * Questa funzione è accessibile solo agli amministratori.
 */

/**
 * @brief Gestisce le operazioni relative ai veicoli
 * @details Permette di aggiungere, rimuovere e visualizzare i veicoli nel sistema.
 * Questa funzione è accessibile solo agli amministratori.
 */
void gestione_veicoli(void);

/**
 * @brief Gestisce il processo di prenotazione di un veicolo
 * @param utente_corrente L'utente che effettua la prenotazione
 * @details Permette all'utente di selezionare un veicolo, scegliere data e ora
 * di inizio e fine prenotazione, e confermare la prenotazione.
 */

/**
 * @brief Gestisce il processo di prenotazione di un veicolo
 * @param utente_corrente L'utente che effettua la prenotazione
 * @details Permette all'utente di selezionare un veicolo, scegliere data e ora
 * di inizio e fine prenotazione, e confermare la prenotazione.
 */
void prenota_auto(Utente utente_corrente);

/**
 * @brief Visualizza le prenotazioni dell'utente corrente
 * @param utente_corrente L'utente di cui visualizzare le prenotazioni
 * @details Mostra tutte le prenotazioni attive dell'utente, con dettagli
 * come veicolo, date, stato e costo stimato.
 */

/**
 * @brief Visualizza le prenotazioni dell'utente corrente
 * @param utente_corrente L'utente di cui visualizzare le prenotazioni
 * @details Mostra tutte le prenotazioni attive dell'utente, con dettagli
 * come veicolo, date, stato e costo stimato.
 */
void visualizza_prenotazioni(Utente utente_corrente);


/**
 * @brief Visualizza la disponibilità dei veicoli
 * @details Mostra lo stato di disponibilità di tutti i veicoli nel sistema
 * e permette di visualizzare il calendario di un veicolo specifico.
 */

/**
 * @brief Visualizza la disponibilità dei veicoli
 * @details Mostra lo stato di disponibilità di tutti i veicoli nel sistema
 * e permette di visualizzare il calendario di un veicolo specifico.
 */
void visualizza_disponibilita(void);

/**
 * @brief Mostra il menu principale per gli utenti clienti
 * @param utente_corrente L'utente cliente loggato
 * @details Visualizza le opzioni disponibili per gli utenti clienti,
 * inclusa la gestione delle prenotazioni e la visualizzazione delle informazioni.
 */
/**
 * @brief Mostra il menu principale per gli utenti clienti
 * @param utente_corrente L'utente cliente loggato
 * @details Visualizza le opzioni disponibili per gli utenti clienti,
 * inclusa la gestione delle prenotazioni e la visualizzazione delle informazioni.
 */
void mostra_menu_cliente(Utente utente_corrente);

/**
 * @brief Mostra il menu principale per gli amministratori
 * @param utente_corrente L'amministratore loggato
 * @details Visualizza le opzioni disponibili per gli amministratori,
 * inclusa la gestione di veicoli, prenotazioni e utenti.
 */
void mostra_menu_amministratore(Utente utente_corrente);

/**
 * @brief Gestisce le operazioni di amministrazione delle prenotazioni
 * @details Permette agli amministratori di visualizzare, filtrare e modificare
 * le prenotazioni nel sistema.
 */
void gestione_prenotazioni_amministratore(void);

/**
 * @brief Mostra il menu iniziale del sistema
 * @details Visualizza il logo e le opzioni di accesso al sistema.
 */
void mostra_menu_iniziale();

/**
 * @brief Visualizza il logo ASCII del sistema
 * @details Stampa il logo ASCII del sistema di car sharing.
 */

/**
 * @brief Visualizza il logo ASCII del sistema
 * @details Stampa il logo ASCII del sistema di car sharing.
 */
void mostra_logo();

/**
 * @brief Mostra il menu di login
 * @details Visualizza le opzioni per accedere o registrarsi al sistema.
 */

/**
 * @brief Mostra il menu di login
 * @details Visualizza le opzioni per accedere o registrarsi al sistema.
 */
void mostra_menu_login();

/**
 * @brief Gestisce le operazioni di amministrazione degli utenti
 * @details Permette agli amministratori di visualizzare e gestire gli utenti
 * del sistema, inclusa la possibilità di rimuovere utenti.
 */
void gestione_utenti_amministratore(void);

#endif // MENU_H

