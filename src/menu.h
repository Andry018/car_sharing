#ifndef MENU_H
#define MENU_H

#include "utenti.h"
#include "prenotazioni.h"
#include "veicolo.h"
#include "tariffe.h"
#include "fasce_orarie.h"

/**
 * @brief Visualizza le tariffe dei veicoli e gli sconti disponibili
 * 
 * Mostra una schermata formattata con le tariffe orarie per ogni tipo di veicolo,
 * gli sconti disponibili e, se l'utente è loggato, il numero di noleggi completati.
 * 
 * @pre current_user è un puntatore valido a una struttura Utente oppure NULL
 * @pre Le costanti di tariffa devono essere definite
 * @post Viene visualizzata una schermata formattata con le informazioni richieste
 * @post Il programma attende la pressione di INVIO
 * @sideeffect Modifica la schermata del terminale
 * @sideeffect Stampa informazioni a video
 * @sideeffect Svuota il buffer di input
 * @param current_user Puntatore all'utente corrente o NULL
 */
void visualizza_tariffe(Utente current_user);

/**
 * @brief Gestisce il menu interattivo per la gestione dei veicoli
 * 
 * Implementa un menu che permette di aggiungere, rimuovere e visualizzare veicoli.
 * Per ogni veicolo visualizzato, mostra anche la relativa tariffa oraria in base al tipo.
 * Il menu viene ripetuto finché l'utente non sceglie di uscire.
 * 
 * @pre Le funzioni di supporto devono essere implementate
 * @pre La struttura dati della lista veicoli deve essere inizializzata
 * @pre Le tariffe per ogni tipo di veicolo devono essere definite
 * @post La lista dei veicoli rimane aggiornata in memoria e su file
 * @post Il menu termina quando l'utente sceglie di uscire
 * @sideeffect Modifica la visualizzazione del terminale
 * @sideeffect Modifica la lista dei veicoli
 * @sideeffect Salva i cambiamenti su file
 */
void gestione_veicoli(void);

/**
 * @brief Gestisce l'interfaccia per le prenotazioni auto
 * 
 * Permette di creare, visualizzare, cancellare e modificare prenotazioni,
 * visualizzare tariffe e avanzare il tempo di sistema. Mostra la data di sistema
 * corrente e calcola le tariffe in base al tipo di veicolo selezionato.
 * 
 * @pre current_user deve essere un puntatore valido a una struttura Utente
 * @pre Il sistema deve aver inizializzato correttamente la coda delle prenotazioni
 * @pre Le tariffe per ogni tipo di veicolo devono essere definite
 * @post Le prenotazioni vengono salvate su file se modificate
 * @post Il sistema attende la pressione di INVIO dopo ogni operazione
 * @sideeffect Modifica la struttura dati delle prenotazioni
 * @sideeffect Scrive su file i dati aggiornati
 * @sideeffect Modifica l'output del terminale
 * @param current_user Puntatore all'utente corrente
 */
void prenota_auto(Utente current_user);

/**
 * @brief Visualizza tutte le prenotazioni presenti nella coda
 * 
 * Mostra a video tutte le prenotazioni presenti nella coda delle prenotazioni.
 * Visualizza un'intestazione con titolo e data di sistema, poi, se ci sono prenotazioni,
 * elenca ciascuna mostrando ID, dettagli e costo stimato calcolato in base al tipo di
 * veicolo e alla durata della prenotazione.
 * 
 * @pre La coda delle prenotazioni è stata inizializzata e accessibile tramite get_coda_prenotazioni()
 * @pre La lista dei veicoli è disponibile e accessibile tramite get_lista_veicoli()
 * @pre Le funzioni di stampa e calcolo (stampa_prenotazione(), calcola_tariffa_prenotazione(), stampa_data_sistema()) sono correttamente implementate
 * @pre È possibile usare set_color() per cambiare il colore del testo nel terminale
 * @post Sullo schermo viene stampato un elenco delle prenotazioni presenti, con relativi dettagli e costo stimato
 * @post Se la coda è vuota, viene stampato un messaggio di "Nessuna prenotazione presente"
 * @post La funzione non modifica strutture dati interne o esterne
 * @sideeffect Pulizia dello schermo e stampa su console
 * @sideeffect Cambio colore del testo sul terminale
 * @sideeffect Eventuale rilascio di memoria di veicoli temporanei (tramite free(v))
 * @param current_user Puntatore all'utente corrente
 */
void visualizza_prenotazioni(Utente current_user);

/**
 * @brief Visualizza la schermata di restituzione auto
 * 
 * Visualizza una schermata dedicata alla restituzione di un'auto.
 * Mostra il titolo, la data di sistema, e permette all'utente di selezionare
 * il veicolo da restituire. Gestisce la verifica della disponibilità del veicolo
 * e l'aggiornamento del suo stato.
 * 
 * @pre Le funzioni di gestione dello schermo (pulisci_schermo(), stampa_bordo_superiore(), stampa_bordo_inferiore()) sono disponibili e funzionanti
 * @pre La funzione stampa_data_sistema() è disponibile e correttamente implementata
 * @pre Le funzioni di gestione colore (set_color()) e input (svuota_buffer()) sono disponibili
 * @pre La lista dei veicoli è accessibile e contiene dati validi
 * @post Viene mostrata a video una schermata con il titolo "RESTITUISCI AUTO", la data di sistema corrente
 * @post Se l'operazione ha successo, lo stato del veicolo viene aggiornato
 * @sideeffect Pulizia e stampa su console
 * @sideeffect Cambio colore del testo nel terminale
 * @sideeffect Attesa di input utente per continuare (svuotamento buffer)
 * @sideeffect Modifica dello stato del veicolo selezionato
 */
void restituisci_auto(void);

/**
 * @brief Mostra la disponibilità dei veicoli e il calendario delle prenotazioni
 * 
 * Mostra a schermo una lista dei veicoli con il loro stato di disponibilità attuale,
 * aggiornato in base alle prenotazioni correnti. Per ogni veicolo mostra anche la
 * relativa tariffa oraria in base al tipo. Dopo aver elencato i veicoli, chiede
 * all'utente di inserire l'ID di un veicolo e mostra il calendario delle prenotazioni
 * per quel veicolo, evidenziando le fasce occupate e libere.
 * 
 * @pre Sono disponibili le funzioni per la gestione dello schermo, stampa, colori e input
 * @pre Le funzioni di gestione prenotazioni e veicoli sono implementate correttamente
 * @pre Le strutture dati CalendarioVeicolo e CodaPrenotazioni sono definite e supportano le operazioni necessarie
 * @pre Il sistema è in grado di fornire la data e ora correnti
 * @pre Le tariffe per ogni tipo di veicolo devono essere definite
 * @post A video viene mostrata una lista aggiornata dei veicoli con il loro stato di disponibilità attuale e tariffe
 * @post Viene mostrato il calendario dettagliato delle prenotazioni per il veicolo selezionato
 * @post Lo stato di disponibilità del veicolo viene ripristinato allo stato originale
 * @sideeffect Accesso e lettura di dati da file (prenotazioni)
 * @sideeffect Modifica temporanea dello stato di disponibilità nei dati veicoli (solo in memoria)
 * @sideeffect Stampa su console e cambio colore
 */
void visualizza_disponibilita(void);

/**
 * @brief Mostra il menu principale per i clienti
 * 
 * Stampa a video il menu principale riservato all'utente cliente, suddiviso in sezioni
 * (Prenotazioni, Informazioni, Account), con le relative opzioni numerate e il nome
 * dell'utente visualizzato in cima. Mostra anche la data di sistema corrente.
 * 
 * @pre current_user è un puntatore valido a una struttura Utente con i dati dell'utente attualmente connesso
 * @pre Funzione get_nome_utente(Utente*) restituisce una stringa valida con il nome dell'utente
 * @pre Sono disponibili funzioni per la gestione della grafica testuale e colori
 * @pre La funzione stampa_data_sistema() è disponibile e correttamente implementata
 * @post Viene stampato a video il menu cliente con intestazioni colorate, opzioni numerate, il nome dell'utente e la data di sistema
 * @post Nessuna modifica di dati o stato interno
 * @sideeffect Output testuale sul terminale con utilizzo di colori
 * @param current_user Puntatore all'utente corrente
 */
void mostra_menu_cliente(Utente current_user);

/**
 * @brief Mostra il menu principale per gli amministratori
 * 
 * Stampa a video il menu principale riservato all'amministratore del sistema di car sharing,
 * con varie sezioni per la gestione del sistema, il monitoraggio e le operazioni di sistema,
 * includendo il nome dell'amministratore connesso e la data di sistema corrente.
 * 
 * @pre current_user è un puntatore valido a una struttura Utente contenente i dati dell'utente amministratore connesso
 * @pre La funzione get_nome_utente(Utente*) restituisce una stringa valida col nome dell'utente
 * @pre Sono disponibili funzioni per la gestione della grafica testuale e colori
 * @pre La funzione stampa_data_sistema() è disponibile e correttamente implementata
 * @post Viene mostrato a video un menu strutturato in sezioni, con intestazioni colorate, opzioni numerate, il nome dell'amministratore e la data di sistema
 * @post Non modifica dati o stato del programma
 * @sideeffect Output testuale sul terminale con colori
 * @param current_user Puntatore all'utente corrente
 */
void mostra_menu_admin(Utente current_user);

/**
 * @brief Gestisce il sotto-menu amministrativo per le prenotazioni
 * 
 * Gestisce il sotto-menu amministrativo per le prenotazioni, permettendo di visualizzare,
 * filtrare, ordinare e modificare lo stato delle prenotazioni registrate nel sistema.
 * Mostra la data di sistema corrente e calcola le tariffe in base al tipo di veicolo
 * per ogni prenotazione visualizzata.
 * 
 * @pre Le funzioni ausiliarie (get_coda_prenotazioni(), stampa_prenotazione(), modifica_stato_prenotazione(), salva_prenotazioni_su_file(), ecc.) sono implementate correttamente e restituiscono dati coerenti
 * @pre La coda di prenotazioni contiene dati validi
 * @pre Le funzioni di gestione memoria e I/O (malloc(), free(), scanf(), printf(), svuota_buffer()) funzionano correttamente
 * @pre L'utente ha privilegi amministrativi (non verificato direttamente in questa funzione, deve essere garantito da chiamante)
 * @pre Le tariffe per ogni tipo di veicolo devono essere definite
 * @pre La funzione stampa_data_sistema() è disponibile e correttamente implementata
 * @post Eventuali modifiche allo stato delle prenotazioni vengono salvate su file
 * @post L'output video mostra liste e filtri di prenotazioni a seconda della scelta, con relative tariffe
 * @post La funzione si ripete fino alla scelta di uscita (0)
 * @sideeffect Input e output testuali tramite terminale
 * @sideeffect Allocazione e liberazione di memoria dinamica temporanea
 * @sideeffect Modifica della struttura dati delle prenotazioni se si cambia stato
 */
void gestione_prenotazioni_admin(void);

/**
 * @brief Mostra il menu iniziale del sistema
 * 
 * Visualizza il menu iniziale con il logo del sistema, un messaggio di benvenuto,
 * e le opzioni per accedere, registrarsi o uscire dal programma. Il menu è formattato
 * con bordi e separatori, utilizza colori diversi per evidenziare sezioni e testo.
 * Questa è la prima schermata che l'utente vede all'avvio del programma.
 * 
 * @pre La console o terminale deve supportare l'output testuale e i codici colore ANSI o equivalenti
 * @pre Le funzioni stampa_bordo_superiore(), stampa_bordo_inferiore(), stampa_separatore(), 
 *      set_color(int) e mostra_logo() devono essere definite e funzionanti
 * @post Sullo schermo è visibile un menu strutturato e colorato con il logo, il titolo "BENVENUTO",
 *      e le opzioni di accesso, registrazione e uscita
 * @post Nessun dato di programma viene modificato
 * @sideeffect Produce output testuale e grafico (bordo, testo colorato) a schermo tramite printf
 * @sideeffect Modifica temporaneamente il colore del testo con set_color
 */
void mostra_menu_iniziale(void);

/**
 * @brief Stampa il logo del sistema in ASCII art
 * 
 * La funzione stampa a video un logo in ASCII art che rappresenta il nome e l'identità
 * grafica del sistema di car sharing. Il logo viene mostrato in colore giallo per
 * renderlo visivamente evidente. Alla fine della stampa, il colore del testo viene
 * riportato a bianco.
 * 
 * @pre La console o terminale deve supportare la stampa a video e i codici colore
 * @pre La funzione set_color(int) deve essere definita e funzionante per modificare il colore del testo in output
 * @post Sullo schermo è visibile il logo del sistema car sharing stampato in giallo
 * @post Il colore del testo viene resettato a bianco (set_color(WHITE))
 * @post Nessuna variabile o struttura dati viene modificata
 * @sideeffect Cambia temporaneamente il colore del testo in console
 * @sideeffect Produce output testuale a schermo tramite printf
 * @sideeffect Non modifica dati globali o parametri esterni
 */
void mostra_logo(void);

/**
 * @brief Visualizza il menu di login del sistema
 * 
 * La funzione visualizza a schermo il menu di login del sistema di car sharing,
 * con le opzioni per accedere con credenziali esistenti o registrarsi come nuovo utente.
 * Il menu è formattato con bordi e separatori, utilizza colori diversi per evidenziare
 * sezioni e testo, e include il logo del sistema. Questa schermata viene mostrata
 * dopo la schermata iniziale quando l'utente sceglie di accedere o registrarsi.
 * 
 * @pre La console o terminale deve supportare l'output testuale e i codici colore ANSI o equivalenti
 * @pre Le funzioni stampa_bordo_superiore(), stampa_bordo_inferiore(), stampa_separatore(), set_color(int) e mostra_logo() devono essere definite e funzionanti
 * @post Sullo schermo è visibile un menu strutturato e colorato con il logo, il titolo "LOGIN", e le opzioni di accesso e registrazione
 * @post Nessun dato di programma viene modificato
 * @sideeffect Produce output testuale e grafico (bordo, testo colorato) a schermo tramite printf e altre funzioni di stampa
 * @sideeffect Modifica temporaneamente il colore del testo con set_color
 * @sideeffect Non modifica variabili o strutture dati globali o passate per riferimento
 */
void mostra_menu_login(void);

/**
 * @brief Gestisce il menu degli utenti per gli amministratori
 * 
 * Implementa un menu che permette agli amministratori di gestire
 * gli utenti del sistema. Mostra la data di sistema corrente e permette
 * di visualizzare, aggiungere, modificare e rimuovere utenti.
 * 
 * @pre Le funzioni di supporto devono essere implementate
 * @pre La funzione stampa_data_sistema() è disponibile e correttamente implementata
 * @post Gli utenti vengono salvati su file se modificate
 * @sideeffect Modifica la visualizzazione del terminale
 * @sideeffect Modifica gli utenti
 * @sideeffect Salva i cambiamenti su file
 */
void gestione_utenti_admin(void);

#endif // MENU_H

