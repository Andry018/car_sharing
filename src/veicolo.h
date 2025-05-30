#ifndef veicolo_C
#define veicolo_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tariffe.h"

// Forward declarations per information hiding
typedef struct Veicolo* Veicolo;
typedef struct node* list;

// Funzioni di accesso alla lista
/**
 * @brief Restituisce il valore corrente della variabile listaVeicoli
 * 
 * @return listaVeicoli Riferimento alla lista dei veicoli attualmente memorizzata nel sistema
 * 
 * @pre La variabile listaVeicoli deve essere inizializzata correttamente prima della chiamata alla funzione
 * 
 * @post La funzione restituisce un riferimento alla lista dei veicoli attualmente memorizzata nel sistema
 * @post Nessuna modifica viene effettuata su listaVeicoli o su altri dati del programma
 * 
 * @sideeffect Nessuno
 * 
 * @note Questa funzione è di sola lettura e non modifica lo stato del sistema
 */
list get_lista_veicoli(void);

//------------------------------------------------------------------------------
/**
 * @brief Aggiorna il contenuto della variabile listaVeicoli assegnandole il valore passato tramite il parametro nuovaLista
 * 
 * @param nuovaLista Il nuovo valore da assegnare a listaVeicoli
 * 
 * @pre Il parametro nuovaLista deve essere un valore valido per il tipo list
 * @pre Se listaVeicoli conteneva già una lista precedente allocata dinamicamente, è responsabilità del chiamante liberare la memoria associata prima della sovrascrittura (se necessario)
 * 
 * @post La variabile listaVeicoli assume il valore nuovaLista
 * @post Eventuali riferimenti precedenti a listaVeicoli non sono più validi, a meno che non siano stati gestiti
 * 
 * @sideeffect Modifica lo stato globale: aggiorna la variabile listaVeicoli
 */
void set_lista_veicoli(list nuovaLista);

//------------------------------------------------------------------------------
/**
 * @brief Salva su file la lista dei veicoli mantenuta nella variabile globale listaVeicoli
 * 
 * @pre listaVeicoli deve essere correttamente inizializzata (Può essere anche NULL, se salva_veicolo_file lo gestisce come lista vuota)
 * @pre La funzione salva_veicolo_file(list) deve essere implementata correttamente e sapere come serializzare la struttura list
 * 
 * @post I dati contenuti in listaVeicoli vengono scritti su un file, in un formato stabilito da salva_veicolo_file
 * 
 * @sideeffect Scrittura su file tramite salva_veicolo_file
 */
void salva_lista_veicoli(void);

//------------------------------------------------------------------------------
/**
 * @brief Carica la lista dei veicoli da file
 * 
 * La funzione chiama carica_veicolo_file(listaVeicoli), che legge i dati da file.
 * Il risultato è assegnato alla variabile listaVeicoli, aggiornandola.
 * 
 * @pre La funzione carica_veicolo_file(list) deve essere correttamente implementata:
 *      - deve leggere i dati dal file previsto
 *      - restituire una nuova lista coerente
 * @pre Il file deve essere accessibile in lettura e contenere dati ben formati
 * @pre Se carica_veicolo_file() non libera la memoria della vecchia lista, allora è compito del chiamante farlo prima dell'assegnazione
 * 
 * @post La variabile globale listaVeicoli punta a una nuova lista allocata dinamicamente e popolata con i dati letti dal file
 * @post La lista precedente viene eventualmente persa se non gestita
 * 
 * @sideeffect Lettura da file tramite carica_veicolo_file
 * @sideeffect Modifica della variabile listaVeicoli
 */
void carica_lista_veicoli(void);

//------------------------------------------------------------------------------
/**
 * @brief Libera la memoria associata alla lista dei veicoli
 * 
 * La funzione libera uno ad uno tutti i nodi della lista dei veicoli puntata dalla variabile globale listaVeicoli,
 * evitando perdite di memoria. Alla fine, listaVeicoli sarà NULL.
 * 
 * @pre La variabile globale listaVeicoli deve essere inizializzata (può anche essere NULL)
 * @pre I nodi della lista sono stati allocati dinamicamente con malloc o funzioni equivalenti
 * @pre La struttura dei nodi deve essere coerente (ogni nodo punta al successivo con il campo next)
 * 
 * @post Tutta la memoria dinamica associata a listaVeicoli viene liberata
 * @post La variabile listaVeicoli risulta vuota, ovvero NULL
 * 
 * @sideeffect Deallocazione della memoria dinamica associata alla lista
 * @sideeffect Modifica della variabile globale listaVeicoli
 * @sideeffect Dopo la chiamata, ogni puntatore precedentemente ottenuto da listaVeicoli sarà dangling (non più valido)
 */
void pulisci_lista_veicoli(void);

// Funzioni di gestione veicoli
//------------------------------------------------------------------------------
/**
 * @brief Crea un nuovo veicolo con dati inseriti dall'utente
 * 
 * La funzione:
 * 1. Genera un ID univoco per il veicolo
 * 2. Chiede all'utente di inserire tipo, modello e targa
 * 3. Restituisce la struttura veicolo compilata
 * 
 * @pre La struttura veicolo è definita correttamente e contiene:
 *      - int id, int tipo, char modello[30], char targa[8], int disponibile
 * @pre La funzione carica_ultimo_id() è disponibile e restituisce l'ultimo ID usato
 * @pre Sono definiti i tipi di veicolo: UTILITARIA, SUV, SPORTIVA, MOTO
 * @pre Sono definite le costanti TARIFFA_UTILITARIA, ecc.
 * @pre L'ambiente di esecuzione consente input/output via terminale (scanf, printf, fgets)
 * 
 * @post Restituisce un oggetto veicolo correttamente inizializzato
 * @post L'ID del veicolo è univoco e crescente
 * @post Il veicolo ha tipo, modello, targa e posizione correttamente assegnati
 * 
 * @sideeffect Modifica di una variabile static int id interna, che mantiene stato tra chiamate successive
 * 
 * @return Veicolo Il nuovo veicolo creato
 */
Veicolo crea_veicolo(void);

//------------------------------------------------------------------------------
/**
 * @brief Aggiunge un nuovo veicolo alla lista
 * 
 * La funzione:
 * 1. Alloca un nuovo nodo
 * 2. Crea un nuovo veicolo tramite crea_veicolo()
 * 3. Inserisce il nuovo nodo in testa alla lista l
 * 4. Restituisce il puntatore alla nuova lista
 * 
 * @param l La lista a cui aggiungere il veicolo (può essere NULL)
 * 
 * @pre Il parametro l può essere NULL o una lista valida di veicoli
 * @pre La struttura struct node deve essere definita correttamente, con almeno:
 *      - un campo veicolo veicoli
 *      - un campo struct node* next
 * @pre La funzione crea_veicolo() deve essere disponibile e funzionante
 * 
 * @post Restituisce un nuovo puntatore alla lista, con il nuovo nodo in testa
 * @post Se malloc fallisce, la lista originale viene restituita invariata
 * 
 * @sideeffect Nessuno
 * 
 * @return list La nuova lista con il veicolo aggiunto
 */
list aggiungi_veicolo(list l);

//------------------------------------------------------------------------------
/**
 * @brief Rimuove un veicolo dalla lista
 * 
 * La funzione:
 * 1. Richiede all'utente l'ID di un veicolo da rimuovere
 * 2. Cerca il nodo corrispondente nella lista l
 * 3. Se lo trova, lo rimuove e libera la memoria
 * 4. Restituisce la nuova lista aggiornata
 * 
 * @param l La lista da cui rimuovere il veicolo
 * @param id L'ID del veicolo da rimuovere
 * 
 * @pre La lista l è valida (può essere anche NULL)
 * @pre Ogni nodo della lista contiene un campo veicolo veicoli con almeno int id
 * @pre La lista è ben formata (non contiene cicli, puntatori invalidi, ecc.)
 * @pre Input da tastiera disponibile per leggere l'ID
 * 
 * @post Se esiste un veicolo con l'ID fornito, viene rimosso e la memoria associata viene liberata
 * @post Se non esiste, la lista resta invariata e viene mostrato un messaggio di errore
 * @post La lista restituita è valida e coerente
 * 
 * @sideeffect Libera memoria con free() se trova l'elemento
 * 
 * @return list La nuova lista con il veicolo rimosso
 */
list rimuovi_veicolo(list l, int id);

//------------------------------------------------------------------------------
/**
 * @brief Stampa le informazioni di un veicolo
 * 
 * La funzione stampa in output:
 * - L'ID del veicolo
 * - Il modello
 * - La targa
 * - Il tipo del veicolo (con colore associato)
 * - La posizione del veicolo (Deposito, Posizione B, Posizione C, Posizione D)
 * - Lo stato di disponibilità (con colore associato)
 * 
 * @param v Il veicolo da stampare
 * 
 * @pre Il parametro v è un veicolo valido, ovvero:
 *      - id è un intero assegnato
 *      - modello e targa sono stringhe ben terminate
 *      - tipo è uno dei valori previsti (UTILITARIA, SUV, SPORTIVA, MOTO)
 *      - posizione è uno dei valori previsti (0=Deposito, 1=Posizione B, 2=Posizione C, 3=Posizione D)
 * @pre La funzione set_color(int) è disponibile e funzionante
 * 
 * @post Le informazioni del veicolo sono stampate a schermo in formato leggibile e con evidenziazione a colori
 * @post Lo stato del programma non viene modificato
 * 
 * @sideeffect Output su console
 */
void stampa_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Salva la lista dei veicoli su file
 * 
 * La funzione salva i dati dei veicoli contenuti nella lista l nel file "data/veicoli.txt"
 * in modalità sovrascrittura ("w"). Ogni veicolo viene scritto su una riga con i seguenti campi:
 * id tipo modello targa disponibile
 * 
 * @param l La lista dei veicoli da salvare
 * 
 * @pre l può essere NULL (in tal caso, il file viene comunque aperto e poi chiuso vuoto)
 * @pre La directory data/ esiste e l'applicazione ha i permessi di scrittura al file veicoli.txt
 * @pre I campi modello, targa di ciascun veicolo sono stringhe ben terminate
 * 
 * @post I dati della lista l sono scritti nel file data/veicoli.txt, sovrascrivendo eventuali contenuti precedenti
 * @post Il file è chiuso correttamente al termine
 * @post Un messaggio di conferma viene stampato su console in caso di successo
 * 
 * @sideeffect Scrittura su file: data/veicoli.txt
 * @sideeffect Apertura e chiusura file
 * @sideeffect Output su console con printf
 */
void salva_veicolo_file(list l);

//------------------------------------------------------------------------------
/**
 * @brief Carica la lista dei veicoli da file
 * 
 * La funzione apre il file data/veicoli.txt, legge ogni riga rappresentante un veicolo,
 * ricostruisce i dati e li inserisce in testa alla lista l. La lista risultante viene restituita.
 * 
 * @param l La lista a cui aggiungere i veicoli letti (può essere NULL)
 * 
 * @pre Il file data/veicoli.txt deve esistere e contenere righe ben formate con il seguente ordine:
 *      id tipo modello targa disponibile
 * @pre Il campo modello può contenere spazi, ma viene letto correttamente finché la targa ha esattamente 7 caratteri
 *      e inizia con una lettera
 * @pre La lista l può essere NULL (in questo caso la funzione crea una nuova lista da zero)
 * 
 * @post Il contenuto del file viene caricato in memoria come lista di veicoli
 * @post I nuovi elementi vengono aggiunti in testa alla lista l
 * @post La lista risultante viene restituita
 * 
 * @sideeffect Lettura da file: data/veicoli.txt
 * @sideeffect Allocazione dinamica per ogni nodo veicolo (malloc)
 * 
 * @return list La lista con i veicoli caricati dal file
 */
list carica_veicolo_file(list l);

//------------------------------------------------------------------------------
/**
 * @brief Carica l'ultimo ID utilizzato dal file dei veicoli
 * 
 * La funzione apre il file data/veicoli.txt, legge tutte le righe e restituisce il valore massimo
 * del campo id trovato nel file. Se il file non esiste o è vuoto, restituisce 0.
 * 
 * @pre Il file data/veicoli.txt, se esiste, deve contenere righe in cui l'id è il primo campo
 *      e rappresenta un intero valido
 * @pre Ogni riga deve iniziare con un intero (%d) che rappresenta l'ID del veicolo
 * 
 * @post Restituisce l'id massimo tra quelli trovati nel file
 * @post Se il file non esiste, viene restituito 0
 * 
 * @sideeffect Nessuno
 * 
 * @return int L'ultimo ID utilizzato o 0 se il file non esiste
 */
int carica_ultimo_id(void);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce l'identificativo del veicolo
 * 
 * @param v Il veicolo di cui ottenere l'ID
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * 
 * @post id = v->id
 * 
 * @sideeffect Nessuno
 * 
 * @return int L'ID del veicolo
 */
int get_id_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce il tipo del veicolo
 * 
 * Restituisce il tipo del veicolo v, ad esempio auto, scooter, bici, ecc. (codificato come intero).
 * 
 * @param v Il veicolo di cui ottenere il tipo
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * 
 * @post tipo = v->tipo
 * 
 * @sideeffect Nessuno
 * 
 * @return int Il tipo del veicolo
 */
int get_tipo_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce il modello del veicolo
 * 
 * Restituisce una stringa costante contenente il modello del veicolo v.
 * 
 * @param v Il veicolo di cui ottenere il modello
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * 
 * @post modello = v->modello
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* Il modello del veicolo
 */
const char* get_modello_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce la targa del veicolo
 * 
 * Restituisce una stringa costante contenente la targa del veicolo v.
 * 
 * @param v Il veicolo di cui ottenere la targa
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * 
 * @post targa = v->targa
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* La targa del veicolo
 */
const char* get_targa_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce la posizione del veicolo
 * 
 * Restituisce una stringa con la posizione attuale del veicolo v.
 * 
 * @param v Il veicolo di cui ottenere la posizione
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * 
 * @post posizione = v->posizione
 * 
 * @sideeffect Nessuno
 * 
 * @return int La posizione del veicolo
 */
int get_posizione_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce la disponibilità del veicolo
 * 
 * Restituisce un intero che indica se il veicolo è disponibile (1) o meno (0).
 * 
 * @param v Il veicolo di cui ottenere la disponibilità
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * 
 * @post disponibilita = v->disponibilita
 * 
 * @sideeffect Nessuno
 * 
 * @return int La disponibilità del veicolo (1 = disponibile, 0 = non disponibile)
 */
int get_disponibilita_veicolo(Veicolo v);

//------------------------------------------------------------------------------
/**
 * @brief Imposta l'ID del veicolo
 * 
 * Imposta l'ID del veicolo v al valore specificato.
 * 
 * @param v Il veicolo da modificare
 * @param id Il nuovo ID da assegnare
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * @pre id è un intero non negativo
 * 
 * @post v->id = id
 * 
 * @sideeffect Modifica diretta del campo id nella struttura
 */
void set_id_veicolo(Veicolo v, int id);

//------------------------------------------------------------------------------
/**
 * @brief Imposta il tipo del veicolo
 * 
 * Imposta il tipo del veicolo v al valore tipo (auto, bici, ecc.).
 * 
 * @param v Il veicolo da modificare
 * @param tipo Il nuovo tipo da assegnare
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * @pre tipo è un intero valido secondo la codifica dei tipi veicolo
 * 
 * @post v->tipo = tipo
 * 
 * @sideeffect Modifica diretta del campo tipo nella struttura
 */
void set_tipo_veicolo(Veicolo v, int tipo);

//------------------------------------------------------------------------------
/**
 * @brief Imposta il modello del veicolo
 * 
 * Imposta il campo modello del veicolo v alla stringa passata come parametro.
 * 
 * @param v Il veicolo da modificare
 * @param modello Il nuovo modello da assegnare
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * @pre modello è una stringa valida (non NULL)
 * 
 * @post Il campo v->modello conterrà una copia sicura di modello, troncata se necessario
 *       alla dimensione massima consentita
 * 
 * @sideeffect Scrive su v->modello
 */
void set_modello_veicolo(Veicolo v, const char* modello);

//------------------------------------------------------------------------------
/**
 * @brief Imposta la targa del veicolo
 * 
 * Imposta il campo targa del veicolo v alla stringa fornita.
 * 
 * @param v Il veicolo da modificare
 * @param targa La nuova targa da assegnare
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * @pre targa è una stringa valida
 * 
 * @post Il campo v->targa conterrà una copia sicura di targa, troncata se necessario
 * 
 * @sideeffect Scrive su v->targa
 */
void set_targa_veicolo(Veicolo v, const char* targa);

//------------------------------------------------------------------------------
/**
 * @brief Imposta la posizione del veicolo
 * 
 * Imposta la posizione corrente del veicolo alla stringa specificata.
 * 
 * @param v Il veicolo da modificare
 * @param posizione La nuova posizione da assegnare
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * @pre posizione è una stringa valida
 * 
 * @post Il campo v->posizione conterrà una copia sicura di posizione, troncata se necessario
 * 
 * @sideeffect Scrive su v->posizione
 */
void set_posizione_veicolo(Veicolo v, int posizione);

//------------------------------------------------------------------------------
/**
 * @brief Imposta la disponibilità del veicolo
 * 
 * Imposta il campo disponibilita del veicolo v.
 * 
 * @param v Il veicolo da modificare
 * @param disponibilita Il nuovo stato di disponibilità
 * 
 * @pre v è un puntatore valido a una struttura Veicolo
 * @pre disponibilita è un intero valido (es. 0 o 1)
 * 
 * @post v->disponibilita = disponibilita
 * 
 * @sideeffect Modifica il campo disponibilita della struttura
 */
void set_disponibilita_veicolo(Veicolo v, int disponibilita);

// Funzioni di ricerca
//------------------------------------------------------------------------------
/**
 * @brief Cerca un veicolo nella lista per ID
 * 
 * Cerca nella lista l un veicolo con id uguale a quello passato come parametro.
 * 
 * @param l La lista in cui cercare
 * @param id L'ID del veicolo da cercare
 * 
 * @pre l è una lista di tipo list, eventualmente vuota
 * @pre id è un intero valido
 * 
 * @post Se esiste un nodo nella lista con v->id == id, viene restituito quel Veicolo
 * @post Altrimenti, viene restituito NULL
 * 
 * @sideeffect Nessuno
 * 
 * @return Veicolo Il veicolo trovato o NULL se non esiste
 */
Veicolo cerca_veicolo(list l, int id);

//------------------------------------------------------------------------------
/**
 * @brief Modifica i dati di un veicolo
 * 
 * Cerca un veicolo con l'id fornito nella lista l e consente di modificarne i campi
 * (tipo, modello, targa, posizione) tramite input da tastiera.
 * 
 * @param l La lista dei veicoli
 * @param id L'identificatore del veicolo da modificare
 * 
 * @pre l è una lista valida di veicoli
 * @pre id è l'identificatore del veicolo da modificare
 * @pre L'input dell'utente deve essere conforme alle attese (intero per tipo, stringhe per gli altri)
 * 
 * @post Se il veicolo con id è presente nella lista, i suoi campi vengono aggiornati con i nuovi valori
 * @post Se il veicolo non esiste, stampa un messaggio di errore e non modifica nulla
 * 
 * @sideeffect Modifica i dati di un veicolo nella lista
 * @sideeffect Stampa messaggi e legge input da console
 */
void modifica_veicolo(list l, int id);

// Funzioni di stampa
//------------------------------------------------------------------------------
/**
 * @brief Stampa tutti i veicoli nella lista
 * 
 * Stampa a video tutti i veicoli contenuti nella lista l.
 * 
 * @param l La lista dei veicoli da stampare
 * 
 * @pre l è una lista valida (può anche essere NULL)
 * 
 * @post Se la lista è vuota, stampa un messaggio corrispondente
 * @post Se contiene elementi, stampa ciascun veicolo con stampa_veicolo
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_lista_veicoli(list l);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli disponibili
 * 
 * Stampa a video solo i veicoli disponibili (disponibilita == true) presenti nella lista l.
 * 
 * @param l La lista dei veicoli
 * 
 * @pre l è una lista valida
 * 
 * @post Se la lista è vuota, stampa che non ci sono veicoli
 * @post Se ci sono veicoli disponibili, li stampa
 * @post Se nessun veicolo è disponibile, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_disponibili(list l);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli non disponibili
 * 
 * Stampa tutti i veicoli non disponibili (disponibilita == false) presenti nella lista l.
 * 
 * @param l La lista dei veicoli
 * 
 * @pre l è una lista valida (può anche essere NULL)
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se ci sono veicoli non disponibili, li stampa tramite stampa_veicolo
 * @post Se tutti i veicoli sono disponibili, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_non_disponibili(list l);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli di un tipo specifico
 * 
 * Stampa tutti i veicoli di un dato tipo presenti nella lista l.
 * 
 * @param l La lista dei veicoli
 * @param tipo Il tipo di veicolo da cercare (0=Utilitaria, 1=SUV, 2=Sportiva, 3=Moto)
 * 
 * @pre l è una lista valida
 * @pre tipo è un intero compreso tra 0 e 3 (inclusi)
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se ci sono veicoli con v->tipo == tipo, vengono stampati
 * @post Se non ci sono veicoli del tipo richiesto, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_tipo(list l, int tipo);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli in una posizione specifica
 * 
 * Stampa tutti i veicoli presenti nella posizione indicata dall'intero posizione.
 * 
 * @param l La lista dei veicoli
 * @param posizione La posizione da cercare (0=Deposito, 1=Posizione B, 2=Posizione C, 3=Posizione D)
 * 
 * @pre l è una lista valida
 * @pre posizione è un intero compreso tra 0 e 3 (inclusi)
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se ci sono veicoli con v->posizione == posizione, vengono stampati
 * @post Se non ci sono veicoli in quella posizione, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_posizione(list l, int posizione);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli di un modello specifico
 * 
 * Stampa i veicoli della lista l il cui modello è esattamente uguale alla stringa modello.
 * 
 * @param l La lista dei veicoli
 * @param modello Il modello da cercare
 * 
 * @pre l è una lista valida (può anche essere NULL)
 * @pre modello è una stringa valida e non NULL
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se ci sono veicoli con strcmp(v->modello, modello) == 0, li stampa
 * @post Se non ci sono corrispondenze, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_modello(list l, const char* modello);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli con una targa specifica
 * 
 * Stampa i veicoli della lista l la cui targa corrisponde esattamente alla stringa targa.
 * 
 * @param l La lista dei veicoli
 * @param targa La targa da cercare
 * 
 * @pre l è una lista valida
 * @pre targa è una stringa valida e non NULL
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se ci sono veicoli con strcmp(v->targa, targa) == 0, li stampa
 * @post Se non ci sono corrispondenze, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_targa(list l, const char* targa);

//------------------------------------------------------------------------------
/**
 * @brief Stampa un veicolo specifico per ID
 * 
 * Stampa il veicolo della lista l il cui id è uguale al valore intero specificato.
 * 
 * @param l La lista dei veicoli
 * @param id L'ID del veicolo da cercare
 * 
 * @pre l è una lista valida
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se c'è un veicolo con v->id == id, lo stampa
 * @post Se non ci sono veicoli con quell'id, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_id(list l, int id);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli per tipo e posizione
 * 
 * Stampa i veicoli della lista l che sono contemporaneamente del tipo specificato (tipo)
 * e si trovano nella posizione specificata (posizione).
 * 
 * @param l La lista dei veicoli
 * @param tipo Il tipo di veicolo da cercare
 * @param posizione La posizione da cercare (0=Deposito, 1=Posizione B, 2=Posizione C, 3=Posizione D)
 * 
 * @pre l è una lista valida (può anche essere NULL)
 * @pre tipo è un intero compreso tra 0 e 3 (inclusi), rappresentante il tipo di veicolo
 * @pre posizione è un intero compreso tra 0 e 3 (inclusi)
 * 
 * @post Se la lista è vuota, stampa un messaggio che lo indica
 * @post Se ci sono veicoli con v->tipo == tipo e v->posizione == posizione, li stampa
 * @post Se non ci sono corrispondenze, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_tipo_e_posizione(list l, int tipo, int posizione);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli per tipo e disponibilità
 * 
 * Stampa i veicoli della lista l che sono di un certo tipo (tipo) e che sono disponibili
 * o meno, a seconda del valore di disponibile.
 * 
 * @param l La lista dei veicoli
 * @param tipo Il tipo di veicolo da cercare
 * @param disponibile Lo stato di disponibilità da cercare
 * 
 * @pre l è una lista valida
 * @pre tipo è un intero valido (0-3)
 * @pre disponibile è un booleano: true per cercare veicoli disponibili, false per quelli non disponibili
 * 
 * @post Se la lista è vuota, stampa un messaggio
 * @post Se esistono veicoli con v->tipo == tipo e v->disponibilita == disponibile, li stampa
 * @post Altrimenti, stampa che non esistono veicoli di quel tipo con la disponibilità richiesta
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_tipo_e_disponibilita(list l, int tipo, bool disponibile);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli per posizione e disponibilità
 * 
 * Stampa i veicoli della lista l che si trovano in una certa posizione (posizione) e che
 * sono disponibili o meno in base a disponibile.
 * 
 * @param l La lista dei veicoli
 * @param posizione La posizione da cercare (0=Deposito, 1=Posizione B, 2=Posizione C, 3=Posizione D)
 * @param disponibile Lo stato di disponibilità da cercare
 * 
 * @pre l è una lista valida
 * @pre posizione è un intero compreso tra 0 e 3 (inclusi)
 * @pre disponibile è un booleano
 * 
 * @post Se la lista è vuota, stampa un messaggio
 * @post Se esistono veicoli con v->posizione == posizione e v->disponibilita == disponibile, li stampa
 * @post Se non ci sono veicoli corrispondenti, stampa un messaggio
 * 
 * @sideeffect Output su standard output (console)
 */
void stampa_veicoli_per_posizione_e_disponibilita(list l, int posizione, bool disponibile);

//------------------------------------------------------------------------------
/**
 * @brief Stampa i veicoli per tipo, posizione e disponibilità
 * 
 * Stampa tutti i veicoli della lista l che sono:
 * - del tipo tipo
 * - si trovano nella posizione posizione
 * - hanno lo stato di disponibilità disponibile
 * 
 * @param l La lista dei veicoli
 * @param tipo Il tipo di veicolo da cercare
 * @param posizione La posizione da cercare (0=Deposito, 1=Posizione B, 2=Posizione C, 3=Posizione D)
 * @param disponibile Lo stato di disponibilità da cercare
 * 
 * @pre l è una lista valida (può anche essere NULL)
 * @pre tipo ∈ {0, 1, 2, 3} corrisponde a tipi validi: Utilitaria, SUV, Sportiva, Moto
 * @pre posizione è un intero compreso tra 0 e 3 (inclusi)
 * @pre disponibile è un booleano (true o false)
 * 
 * @post Se la lista è vuota, stampa un messaggio informativo
 * @post Se ci sono veicoli che soddisfano tutte e tre le condizioni, li stampa
 * @post Se nessun veicolo soddisfa tutte le condizioni, stampa un messaggio specifico
 * 
 * @sideeffect Output su standard output (console)
 * @sideeffect Messaggi dinamici che indicano il tipo, la posizione e la disponibilità selezionata
 */
void stampa_veicoli_per_tipo_posizione_e_disponibilita(list l, int tipo, int posizione, bool disponibile);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce il nome del tipo di veicolo
 * 
 * Restituisce una stringa letterale che rappresenta il nome del tipo di veicolo
 * corrispondente all'intero tipo.
 * 
 * @param tipo Il tipo di veicolo da convertire in stringa
 * 
 * @pre tipo è un intero che può essere:
 *      - 0: "Utilitaria"
 *      - 1: "SUV"
 *      - 2: "Sportiva"
 *      - 3: "Moto"
 *      - qualsiasi altro valore produce "Tipo non valido"
 * 
 * @post Restituisce un puntatore a una stringa costante che rappresenta il tipo del veicolo
 * @post Non alloca memoria dinamica
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* Il nome del tipo di veicolo
 */
const char* get_nome_tipo_veicolo(int tipo);

//------------------------------------------------------------------------------
/**
 * @brief Restituisce il nome della posizione del veicolo
 * 
 * Restituisce una stringa letterale che rappresenta il nome della posizione del veicolo
 * corrispondente all'intero posizione.
 * 
 * @param posizione La posizione del veicolo da convertire in stringa
 * 
 * @pre posizione è un intero che può essere:
 *      - 0: "Deposito"
 *      - 1: "Posizione B"
 *      - 2: "Posizione C"
 *      - 3: "Posizione D"
 *      - qualsiasi altro valore produce "Posizione non valida"
 * 
 * @post Restituisce un puntatore a una stringa costante che rappresenta la posizione del veicolo
 * @post Non alloca memoria dinamica
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* Il nome della posizione del veicolo
 */
const char* get_nome_posizione_veicolo(int posizione);

#endif
