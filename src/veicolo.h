#ifndef veicolo_C
#define veicolo_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tariffe.h"

// Forward declarations per information hiding
typedef struct Veicolo* Veicolo;
typedef struct nodo* list;

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
 * @note Side Effect: Nessuno
 * 
 * @note Questa funzione è di sola lettura e non modifica lo stato del sistema
 */
list ottieni_lista_veicoli(void);

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
 * @note Side Effect: Modifica lo stato globale: aggiorna la variabile listaVeicoli
 */
void imposta_lista_veicoli(list nuovaLista);

//------------------------------------------------------------------------------
/**
 * @brief Salva su file la lista dei veicoli mantenuta nella variabile globale listaVeicoli
 * 
 * @pre listaVeicoli deve essere correttamente inizializzata (Può essere anche NULL, se salva_veicolo_file lo gestisce come lista vuota)
 * @pre La funzione salva_veicolo_file(list) deve essere implementata correttamente e sapere come serializzare la struttura list
 * 
 * @post I dati contenuti in listaVeicoli vengono scritti su un file, in un formato stabilito da salva_veicolo_file
 * 
 * @note Side Effect: Scrittura su file tramite salva_veicolo_file
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
 * @note Side Effect: Lettura da file tramite carica_veicolo_file
 * @note Side Effect: Modifica della variabile listaVeicoli
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
 * @pre La struttura dei nodi deve essere coerente (ogni nodo punta al successivo con il campo successivo)
 * 
 * @post Tutta la memoria dinamica associata a listaVeicoli viene liberata
 * @post La variabile listaVeicoli risulta vuota, ovvero NULL
 * 
 * @note Side Effect: Deallocazione della memoria dinamica associata alla lista
 * @note Side Effect: Modifica della variabile globale listaVeicoli
 * @note Side Effect: Dopo la chiamata, ogni puntatore precedentemente ottenuto da listaVeicoli sarà dangling (non più valido)
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
 * @note Side Effect: Modifica di una variabile static int id interna, che mantiene stato tra chiamate successive
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
 * @pre La struttura struct nodo deve essere definita correttamente, con almeno:
 *      - un campo veicolo veicoli
 *      - un campo struct nodo* successivo
 * @pre La funzione crea_veicolo() deve essere disponibile e funzionante
 * 
 * @post Restituisce un nuovo puntatore alla lista, con il nuovo nodo in testa
 * @post Se malloc fallisce, la lista originale viene restituita invariata
 * 
 * @note Side Effect: Nessuno
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
 * @note Side Effect: Libera memoria con free() se trova l'elemento
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
 * - Il tipo del veicolo (con coloree associato)
 * - La posizione del veicolo (Deposito, Posizione B, Posizione C, Posizione D)
 * - Lo stato di disponibilità (con coloree associato)
 * 
 * @param v Il veicolo da stampare
 * 
 * @pre Il parametro v è un veicolo valido, ovvero:
 *      - id è un intero assegnato
 *      - modello e targa sono stringhe ben terminate
 *      - tipo è uno dei valori previsti (UTILITARIA, SUV, SPORTIVA, MOTO)
 *      - posizione è uno dei valori previsti (0=Deposito, 1=Posizione B, 2=Posizione C, 3=Posizione D)
 * @pre La funzione imposta_colore(int) è disponibile e funzionante
 * 
 * @post Le informazioni del veicolo sono stampate a schermo in formato leggibile e con evidenziazione a colorei
 * @post Lo stato del programma non viene modificato
 * 
 * @note Side Effect: Output su console
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
 * @note Side Effect: Scrittura su file: data/veicoli.txt
 * @note Side Effect: Apertura e chiusura file
 * @note Side Effect: Output su console con printf
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
 * @note Side Effect: Lettura da file: data/veicoli.txt
 * @note Side Effect: Allocazione dinamica per ogni nodo veicolo (malloc)
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
 * @note Side Effect: Nessuno
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
 * @note Side Effect: Nessuno
 * 
 * @return int L'ID del veicolo
 */
int ottieni_id_veicolo(Veicolo v);

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
 * @note Side Effect: Nessuno
 * 
 * @return int Il tipo del veicolo
 */
int ottieni_tipo_veicolo(Veicolo v);

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
 * @note Side Effect: Nessuno
 * 
 * @return const char* Il modello del veicolo
 */
const char* ottieni_modello_veicolo(Veicolo v);

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
 * @note Side Effect: Nessuno
 * 
 * @return int La posizione del veicolo
 */
int ottieni_posizione_veicolo(Veicolo v);

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
 * @note Side Effect: Nessuno
 * 
 * @return int La disponibilità del veicolo (1 = disponibile, 0 = non disponibile)
 */
int ottieni_disponibilita_veicolo(Veicolo v);

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
 * @note Side Effect: Modifica diretta del campo id nella struttura
 */
void imposta_id_veicolo(Veicolo v, int id);

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
 * @note Side Effect: Modifica diretta del campo tipo nella struttura
 */
void imposta_tipo_veicolo(Veicolo v, int tipo);

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
 * @note Side Effect: Scrive su v->modello
 */
void imposta_modello_veicolo(Veicolo v, const char* modello);

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
 * @note Side Effect: Scrive su v->targa
 */
void imposta_targa_veicolo(Veicolo v, const char* targa);

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
 * @note Side Effect: Scrive su v->posizione
 */
void imposta_posizione_veicolo(Veicolo v, int posizione);

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
 * @note Side Effect: Modifica il campo disponibilita della struttura
 */
void imposta_disponibilita_veicolo(Veicolo v, int disponibilita);

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
 * @note Side Effect: Nessuno
 * 
 * @return Veicolo Il veicolo trovato o NULL se non esiste
 */
Veicolo cerca_veicolo(list l, int id);

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
 * @note Side Effect: Output su standard output (console)
 */
void stampa_lista_veicoli(list l);


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
 * @note Side Effect: Output su standard output (console)
 */
void stampa_veicoli_per_tipo(list l, int tipo);
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
 * @note Side Effect: Nessuno
 * 
 * @return const char* Il nome del tipo di veicolo
 */
const char* ottieni_nome_tipo_veicolo(int tipo);

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
 * @note Side Effect: Nessuno
 * 
 * @return const char* Il nome della posizione del veicolo
 */
const char* ottieni_nome_posizione_veicolo(int posizione);

list ottieni_successivo_nodo(list l);
Veicolo ottieni_veicolo_senza_rimuovere(list l);


#endif
