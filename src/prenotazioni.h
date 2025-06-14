#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include "data_sistema.h"
#include <stdbool.h>


// Forward declarations per information hiding
typedef struct Prenotazione *Prenotazione;
typedef struct CodaPrenotazioni *CodaPrenotazioni;

/**
 * @brief Converte giorno e ora in un timestamp univoco
 * 
 * La funzione restituisce un valore intero (timestamp) che rappresenta un momento temporale univoco 
 * nell'arco della settimana, calcolato a partire da un giorno e un'ora.
 * 
 * @param giorno Il giorno della settimana (0-6)
 * @param ora L'ora del giorno (0-23)
 * 
 * @pre giorno deve essere un intero compreso tra 0 e 6 (inclusi)
 * @pre ora deve essere un intero compreso tra 0 e 23 (inclusi)
 * 
 * @post Viene restituito un valore intero non negativo pari a giorno * 24 + ora
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Il timestamp calcolato
 */
int converti_in_timestamp(int giorno, int ora);

/**
 * @brief Estrae il giorno da un timestamp
 * 
 * La funzione restituisce il giorno della settimana (0-6) a partire da un timestamp 
 * generato con converti_in_timestamp.
 * 
 * @param timestamp Il timestamp da cui estrarre il giorno
 * 
 * @pre timestamp deve essere un intero non negativo, coerente con il formato usato in converti_in_timestamp
 * 
 * @post Viene restituito un intero compreso tra 0 e 6, corrispondente al giorno della settimana
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Il giorno della settimana (0-6)
 */
int estrai_giorno(int timestamp);

/**
 * @brief Estrae l'ora da un timestamp
 * 
 * La funzione restituisce un valore intero che rappresenta l'ora (da 0 a 23) estratta 
 * dal valore intero timestamp, interpretato come un momento temporale su scala oraria.
 * 
 * @param timestamp Il timestamp da cui estrarre l'ora
 * 
 * @pre timestamp è un numero intero (può assumere qualsiasi valore intero)
 * 
 * @post Viene restituito un intero compreso tra 0 e 23, calcolato come timestamp % 24
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int L'ora del giorno (0-23)
 */
int estrai_ora(int timestamp);

/**
 * @brief Ottiene la coda globale delle prenotazioni
 * 
 * La funzione restituisce il puntatore alla coda globale delle prenotazioni,
 * che viene utilizzata per gestire tutte le prenotazioni del sistema.
 * 
 * @pre Nessuna
 * 
 * @post Restituisce il puntatore alla coda globale delle prenotazioni
 * 
 * @note Side Effect: Nessuno
 * 
 * @return CodaPrenotazioni Puntatore alla coda globale delle prenotazioni
 */
CodaPrenotazioni ottieni_coda_prenotazioni();

/**
 * @brief Inizializza una nuova coda di prenotazioni
 * 
 * La funzione crea e inizializza una nuova struttura CodaPrenotazioni,
 * allocando la memoria necessaria per l'array heap con una capacità iniziale.
 * 
 * @pre Nessuna
 * 
 * @post Se l'allocazione ha successo, viene restituito un puntatore a una nuova coda inizializzata
 * @post Se l'allocazione fallisce, viene restituito NULL
 * 
 * @note Side Effect: Alloca memoria per la struttura CodaPrenotazioni e per l'array heap
 * 
 * @return CodaPrenotazioni Puntatore alla nuova coda inizializzata, o NULL in caso di errore
 */
CodaPrenotazioni inizializza_coda(void);

/**
 * @brief Crea una nuova prenotazione
 * 
 * La funzione crea una nuova struttura Prenotazione con i parametri specificati,
 * assegnando un ID univoco e calcolando la priorità se non specificata.
 * 
 * @param id_utente ID dell'utente che effettua la prenotazione
 * @param id_veicolo ID del veicolo prenotato
 * @param giorno_inizio Giorno di inizio prenotazione (0-6)
 * @param ora_inizio Ora di inizio prenotazione (0-23)
 * @param giorno_fine Giorno di fine prenotazione (0-6)
 * @param ora_fine Ora di fine prenotazione (0-23)
 * @param priorita Priorità della prenotazione (se < 0, viene calcolata automaticamente)
 * @param posizione_riconsegna Posizione di riconsegna del veicolo
 * 
 * @pre id_utente e id_veicolo devono essere interi positivi
 * @pre giorno_inizio e giorno_fine devono essere compresi tra 0 e 6
 * @pre ora_inizio e ora_fine devono essere compresi tra 0 e 23
 * 
 * @post Se l'allocazione ha successo, viene restituito un puntatore a una nuova prenotazione inizializzata
 * @post Se l'allocazione fallisce, viene restituito NULL
 * 
 * @note Side Effect: Alloca memoria per la struttura Prenotazione
 * 
 * @return Prenotazione Puntatore alla nuova prenotazione creata, o NULL in caso di errore
 */
Prenotazione crea_prenotazione(int id_utente, int id_veicolo, 
                              int giorno_inizio, int ora_inizio,
                              int giorno_fine, int ora_fine, 
                              int priorita, int posizione_riconsegna);

/**
 * @brief Verifica la validità di una fascia oraria
 * 
 * La funzione verifica se l'intervallo temporale definito da giorno e ora di inizio 
 * e giorno e ora di fine è valido, cioè se rispetta i vincoli di intervalli corretti e coerenti.
 * 
 * @param giorno_inizio Giorno di inizio (0-6)
 * @param ora_inizio Ora di inizio (0-23)
 * @param giorno_fine Giorno di fine (0-6)
 * @param ora_fine Ora di fine (0-23)
 * 
 * @pre giorno_inizio e giorno_fine devono essere interi compresi tra 0 e 6 (inclusi)
 * @pre ora_inizio e ora_fine devono essere interi compresi tra 0 e 23 (inclusi)
 * 
 * @post Viene restituito 1 se l'intervallo temporale è valido, cioè se:
 *       - i giorni e le ore sono nei range corretti
 *       - il timestamp calcolato per inizio è strettamente minore di quello di fine
 *       Viene restituito 0 in caso contrario
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int 1 se l'intervallo è valido, 0 altrimenti
 */
int verifica_fascia_oraria(int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine);

/**
 * @brief Scambia due prenotazioni
 * 
 * La funzione scambia i valori di due strutture Prenotazione passate tramite puntatore.
 * 
 * @param a Puntatore alla prima prenotazione
 * @param b Puntatore alla seconda prenotazione
 * 
 * @pre I puntatori a e b devono essere validi e non NULL
 * 
 * @post I contenuti delle strutture puntate da a e b risultano scambiati
 * 
 * @note Side Effect: Modifica i dati delle strutture puntate da a e b
 */
void scambia_prenotazioni(struct Prenotazione* a,struct Prenotazione *b);

/**
 * @brief Ripristina la proprietà di heap minima risalendo
 * 
 * La funzione ripristina la proprietà di heap minima nella coda delle prenotazioni 
 * risalendo dall'indice indice verso la radice, scambiando le prenotazioni per mantenere 
 * l'ordine di priorità.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param indice Indice da cui iniziare il bubble up
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * @pre indice deve essere un intero compreso tra 0 e la dimensione attuale della coda meno uno
 * 
 * @post La proprietà di heap minima è ristabilita dalla posizione indice fino alla radice della coda
 * 
 * @note Side Effect: Modifica l'array heap della coda, scambiando elementi tramite la funzione scambia_prenotazioni
 */
void bubble_up(CodaPrenotazioni coda, int indice);

/**
 * @brief Ripristina la proprietà di heap minima scendendo
 * 
 * La funzione ripristina la proprietà di heap minima nella coda delle prenotazioni 
 * scendendo dall'indice indice verso i figli, scambiando le prenotazioni per mantenere 
 * l'ordine di priorità.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param indice Indice da cui iniziare il bubble down
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * @pre indice deve essere un intero compreso tra 0 e la dimensione attuale della coda meno uno
 * 
 * @post La proprietà di heap minima è ristabilita dalla posizione indice fino alle foglie della coda
 * 
 * @note Side Effect: Modifica l'array heap della coda, scambiando elementi tramite la funzione scambia_prenotazioni
 */
void bubble_down(CodaPrenotazioni coda, int indice);

/**
 * @brief Aggiunge una prenotazione alla coda
 * 
 * La funzione inserisce una nuova prenotazione nella coda delle prenotazioni, 
 * verificando la validità della fascia oraria, ridimensionando l'array se necessario 
 * e mantenendo la proprietà di heap minima.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param prenotazione Prenotazione da aggiungere
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * @pre prenotazione deve contenere una fascia oraria valida
 * 
 * @post La prenotazione viene aggiunta alla coda e la struttura heap è riorganizzata
 * @post Se l'array era pieno, viene riallocato con capacità raddoppiata
 * @post In caso di errore, la coda rimane invariata e viene restituito un codice di errore
 * 
 * @note Side Effect: Potenziale riallocazione dinamica dell'array heap della coda
 * @note Side Effect: Modifica dell'array heap con l'inserimento e la riorganizzazione della nuova prenotazione
 * 
 * @return int 0 se l'operazione è riuscita, -1 in caso di errore generico, -2 se la fascia oraria non è valida
 */
int aggiungi_prenotazione(CodaPrenotazioni coda, Prenotazione prenotazione);

/**
 * @brief Cerca una prenotazione nella coda per ID
 * 
 * La funzione cerca una prenotazione specifica nella coda delle prenotazioni
 * utilizzando il suo ID. La ricerca viene effettuata linearmente su tutti gli
 * elementi della coda.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param id_prenotazione ID della prenotazione da cercare
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * @pre id_prenotazione deve essere un intero positivo
 * 
 * @post Se la prenotazione viene trovata, viene restituito un puntatore alla prenotazione
 * @post Se la prenotazione non viene trovata o la coda è NULL, viene restituito NULL
 * 
 * @note Side Effect: Nessuno
 * 
 * @return Prenotazione Puntatore alla prenotazione trovata, o NULL se non trovata
 */
Prenotazione cerca_prenotazione(CodaPrenotazioni coda, int id_prenotazione);

/**
 * @brief Modifica lo stato di una prenotazione
 * 
 * La funzione modifica lo stato di una prenotazione specifica nella coda.
 * Se la prenotazione viene completata (stato = 2), aggiorna anche la posizione
 * del veicolo associato alla posizione di riconsegna specificata nella prenotazione.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param id_prenotazione ID della prenotazione da modificare
 * @param nuovo_stato Nuovo stato da assegnare alla prenotazione (0: In attesa, 1: Confermata, 2: Completata, 3: Cancellata)
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * @pre id_prenotazione deve essere un intero positivo
 * @pre nuovo_stato deve essere un intero compreso tra 0 e 3
 * 
 * @post Se la prenotazione viene trovata, il suo stato viene aggiornato
 * @post Se la prenotazione viene completata, la posizione del veicolo viene aggiornata
 * @post Se la prenotazione non viene trovata, la funzione restituisce -1
 * 
 * @note Side Effect: Modifica lo stato della prenotazione e, se completata, la posizione del veicolo associato
 * 
 * @return int 0 se l'operazione è riuscita, -1 se la prenotazione non è stata trovata
 */
int modifica_stato_prenotazione(CodaPrenotazioni coda, int id_prenotazione, int nuovo_stato);

/**
 * @brief Stampa le informazioni di una prenotazione
 * 
 * La funzione stampa su stdout tutte le informazioni relative a una prenotazione,
 * inclusi ID, utente, veicolo, orari di inizio e fine, stato e priorità.
 * 
 * @param prenotazione Puntatore alla prenotazione da stampare
 * 
 * @pre prenotazione deve essere un puntatore valido a una struttura Prenotazione
 * 
 * @post Le informazioni della prenotazione vengono stampate su stdout
 * 
 * @note Side Effect: Scrive su stdout
 */
void stampa_prenotazione(Prenotazione prenotazione);

/**
 * @brief Salva tutte le prenotazioni su file
 * 
 * La funzione salva tutte le prenotazioni presenti nella coda globale su un file.
 * Il file viene creato o sovrascritto se già esistente. Ogni prenotazione viene
 * salvata con tutti i suoi attributi in un formato leggibile.
 * 
 * @param coda Puntatore alla coda delle prenotazioni da salvare
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * 
 * @post Tutte le prenotazioni vengono salvate su file
 * @post Se il file esiste già, viene sovrascritto
 * 
 * @note Side Effect: Crea o sovrascrive un file sul filesystem
 */
void salva_prenotazioni_su_file(CodaPrenotazioni coda);

/**
 * @brief Carica le prenotazioni da un file di testo nella coda
 * 
 * La funzione legge tutte le prenotazioni dal file "data/prenotazioni.txt" e le inserisce
 * nella struttura CodaPrenotazioni fornita.
 * 
 * @param coda Puntatore alla coda delle prenotazioni dove inserire i dati
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata
 * @pre Il file "data/prenotazioni.txt" deve esistere e deve essere accessibile in lettura
 * @pre Il file deve contenere prenotazioni formattate correttamente, una per riga, nel seguente ordine:
 *      id_prenotazione id_utente id_veicolo giorno_ora_inizio giorno_ora_fine stato priorita posizione_riconsegna
 * 
 * @post Le prenotazioni lette correttamente vengono aggiunte alla coda
 * @post Il valore della variabile globale id_counter viene aggiornato se vengono trovati id_prenotazione maggiori di quello attuale
 * 
 * @note Side Effect: Lettura da file "data/prenotazioni.txt"
 * @note Side Effect: Modifica del contenuto della struttura coda
 * @note Side Effect: Possibile modifica della variabile globale id_counter
 * 
 * @return int 0 se il caricamento è avvenuto con successo, -1 in caso di errore
 */
int carica_prenotazioni_da_file(CodaPrenotazioni coda);

/**
 * @brief Carica le prenotazioni nella coda globale
 * 
 * La funzione carica le prenotazioni da file nella coda globale di prenotazioni,
 * assicurandosi che la coda sia inizializzata correttamente e svuotata prima del caricamento.
 * 
 * @pre Nessuna precondizione esplicita richiesta da parte del chiamante
 * 
 * @post Se la coda globale coda_globale non esiste, viene creata
 * @post Se la coda esiste già, viene svuotata tramite pulisci_coda
 * @post Le prenotazioni salvate precedentemente su file vengono caricate nella coda
 * 
 * @note Side Effect: Possibile stampa su standard output
 * @note Side Effect: Modifica della variabile globale coda_globale, che può essere allocata o svuotata
 * @note Side Effect: Lettura da file di prenotazioni
 */
void carica_prenotazioni();

/**
 * @brief Resetta la coda di prenotazioni
 * 
 * La funzione resetta la coda di prenotazioni indicata, eliminando logicamente tutte le prenotazioni
 * in essa contenute senza deallocare la memoria.
 * 
 * @param coda Puntatore alla coda da resettare
 * 
 * @pre Il puntatore coda deve puntare a una struttura CodaPrenotazioni inizializzata correttamente,
 *      oppure può essere NULL
 * 
 * @post La coda indicata avrà dimensione pari a 0
 * @post Le prenotazioni precedentemente contenute non sono più considerate valide dalla coda
 * 
 * @note Side Effect: Modifica dello stato interno della struttura coda, in particolare del campo dimensione
 */
void pulisci_coda(CodaPrenotazioni coda);

/**
 * @brief Libera la memoria della coda di prenotazioni
 * 
 * La funzione libera tutta la memoria allocata dinamicamente associata alla coda di prenotazioni
 * passata come parametro, deallocando sia l'array interno heap sia la struttura CodaPrenotazioni.
 * 
 * @param coda Puntatore alla coda da distruggere
 * 
 * @pre Il puntatore coda può essere NULL oppure deve puntare a una struttura CodaPrenotazioni
 *      precedentemente allocata tramite malloc o simile
 * 
 * @post Tutta la memoria associata alla coda viene liberata
 * 
 * @note Side Effect: Deallocazione della memoria associata alla struttura CodaPrenotazioni e al suo campo heap
 */
void distruggi_coda(CodaPrenotazioni coda);

/**
 * @brief Aggiorna le priorità delle prenotazioni attive
 * 
 * La funzione aggiorna le priorità di tutte le prenotazioni attive (cioè non cancellate né completate)
 * nella coda, in base alla data di sistema corrente. Dopo l'aggiornamento, riorganizza l'heap per
 * mantenere la proprietà di struttura a priorità.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata correttamente
 * 
 * @post Tutte le prenotazioni non completate o cancellate avranno la loro priorità aggiornata
 *       coerentemente alla data di sistema
 * @post L'heap rispetterà nuovamente la struttura di max-heap (o min-heap, a seconda della definizione nel progetto)
 * 
 * @note Side Effect: Modifica il contenuto della struttura coda, aggiornando i campi priorita delle prenotazioni
 *             e riorganizzando la struttura heap
 */
void aggiorna_priorita_prenotazioni(CodaPrenotazioni coda);

/**
 * @brief Rimuove le prenotazioni scadute dalla coda
 * 
 * La funzione aggiorna lo stato delle prenotazioni nella coda che risultano scadute rispetto alla data di sistema:
 * tutte le prenotazioni il cui timestamp di fine è precedente a quello corrente e che non sono ancora completate 
 * o cancellate vengono marcate come COMPLETATA.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * 
 * @pre coda deve essere un puntatore valido a una struttura CodaPrenotazioni inizializzata. Se coda è NULL, 
 *      la funzione non ha alcun effetto.
 * 
 * @post Ogni prenotazione scaduta nella coda, cioè con giorno_ora_fine < timestamp_corrente e stato diverso 
 *       da COMPLETATA o CANCELLATA, verrà modificata ponendo stato = COMPLETATA.
 * 
 * @note Side Effect: Modifica il campo stato di alcune prenotazioni presenti nella struttura heap di coda.
 */
void rimuovi_prenotazioni_scadute(CodaPrenotazioni coda);

/**
 * @brief Verifica la validità di un intervallo di prenotazione
 * 
 * La funzione verifica se l'intervallo temporale specificato da giorno_ora_inizio a giorno_ora_fine 
 * è valido rispetto alla data di sistema attuale.
 * 
 * @param giorno_ora_inizio Timestamp di inizio prenotazione
 * @param giorno_ora_fine Timestamp di fine prenotazione
 * 
 * @pre giorno_ora_inizio e giorno_ora_fine sono timestamp interi validi, ottenuti tramite converti_in_timestamp
 * 
 * @post Il valore di ritorno indica lo stato di validità:
 *       -1: data di inizio nel passato
 *       -2: data di fine precedente o uguale alla data di inizio
 *       0: data valida
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Codice di validità dell'intervallo (-1, -2, o 0)
 */
int valida_data_prenotazione(int giorno_ora_inizio, int giorno_ora_fine);

/**
 * @brief Verifica sovrapposizioni di prenotazioni per un veicolo
 * 
 * La funzione verifica se l'intervallo temporale indicato si sovrappone a una prenotazione già presente 
 * nella coda per lo stesso veicolo, ignorando quelle cancellate o completate.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param id_veicolo ID del veicolo da verificare
 * @param giorno_ora_inizio Timestamp di inizio prenotazione
 * @param giorno_ora_fine Timestamp di fine prenotazione
 * 
 * @pre coda è una struttura valida di tipo CodaPrenotazioni o NULL
 * @pre id_veicolo è un identificatore intero valido
 * @pre giorno_ora_inizio < giorno_ora_fine e sono entrambi timestamp validi
 * 
 * @post Viene restituito:
 *       -1 se la coda è nulla
 *       1 se esiste una sovrapposizione con una prenotazione attiva dello stesso veicolo
 *       0 altrimenti
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Codice indicante la presenza di sovrapposizioni (-1, 0, o 1)
 */
int verifica_sovrapposizioni(CodaPrenotazioni coda, int id_veicolo, int giorno_ora_inizio, int giorno_ora_fine);

/**
 * @brief Conta le prenotazioni completate di un utente
 * 
 * La funzione conta quante prenotazioni nella coda appartengono all'utente con identificatore id_utente 
 * e hanno stato COMPLETATA.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param id_utente ID dell'utente di cui contare le prenotazioni
 * 
 * @pre coda è una struttura valida di tipo CodaPrenotazioni oppure NULL
 * @pre id_utente è un intero identificativo valido di un utente
 * 
 * @post Se la coda è nulla, viene restituito 0
 * @post Altrimenti, viene restituito il numero di prenotazioni completate dall'utente specificato
 * 
 * @note Side Effect: Nessuno. La coda non viene modificata
 * 
 * @return int Numero di prenotazioni completate dall'utente
 */
int conta_prenotazioni_completate(CodaPrenotazioni coda, int id_utente);

/**
 * @brief Ottiene l'ID di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->id_prenotazione
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int ID della prenotazione o -1 se p è NULL
 */
int ottieni_id_prenotazione(Prenotazione p);

/**
 * @brief Ottiene l'ID dell'utente associato a una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->id_utente
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int ID dell'utente o -1 se p è NULL
 */
int ottieni_id_utente_prenotazione(Prenotazione p);

/**
 * @brief Ottiene l'ID del veicolo associato a una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->id_veicolo
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int ID del veicolo o -1 se p è NULL
 */
int ottieni_id_veicolo_prenotazione(Prenotazione p);

/**
 * @brief Ottiene il timestamp di inizio di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->giorno_ora_inizio
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Timestamp di inizio prenotazione o -1 se p è NULL
 */
int ottieni_giorno_ora_inizio(Prenotazione p);

/**
 * @brief Ottiene il timestamp di fine di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->giorno_ora_fine
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Timestamp di fine prenotazione o -1 se p è NULL
 */
int ottieni_giorno_ora_fine(Prenotazione p);

/**
 * @brief Ottiene lo stato di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->stato
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Stato della prenotazione o -1 se p è NULL
 */
int ottieni_stato_prenotazione(Prenotazione p);

/**
 * @brief Ottiene la priorità di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce p->priorita
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Priorità della prenotazione o -1 se p è NULL
 */
int ottieni_priorita(Prenotazione p);

/**
 * @brief Ottiene il giorno di inizio di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce estrai_giorno(p->giorno_ora_inizio)
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Giorno di inizio prenotazione o -1 se p è NULL
 */
int ottieni_giorno_inizio(Prenotazione p);

/**
 * @brief Ottiene l'ora di inizio di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce estrai_ora(p->giorno_ora_inizio)
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Ora di inizio prenotazione o -1 se p è NULL
 */
int ottieni_ora_inizio(Prenotazione p);

/**
 * @brief Ottiene il giorno di fine di una prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, restituisce estrai_giorno(p->giorno_ora_fine)
 * @post Se p è NULL, restituisce -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Giorno di fine prenotazione o -1 se p è NULL
 */
int ottieni_giorno_fine(Prenotazione p);

/**
 * @brief Restituisce l'ora di fine della prenotazione
 * 
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, viene restituito estrai_ora(p->giorno_ora_fine)
 * @post Se p è NULL, viene restituito -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int L'ora di fine (0-23) o -1 se p è NULL
 */
int ottieni_ora_fine(Prenotazione p);

int ottieni_posizione_riconsegna(Prenotazione p);

/**
 * @brief Restituisce il numero di prenotazioni nella coda
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * 
 * @pre coda è un puntatore valido a una struttura CodaPrenotazioni, oppure NULL
 * 
 * @post Se coda è valido, viene restituito coda->dimensione
 * @post Se coda è NULL, viene restituito -1
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Il numero di prenotazioni nella coda o -1 se coda è NULL
 */
int ottieni_dimensione_coda(CodaPrenotazioni coda);

/**
 * @brief Imposta l'ID della prenotazione
 * 
 * @param id_prenotazione Nuovo ID della prenotazione
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, p->id_prenotazione = id_prenotazione
 * @post Se p è NULL, non viene effettuata alcuna modifica
 * 
 * @note Side Effect: Modifica diretta del campo id_prenotazione della struttura p
 */
void imposta_id_prenotazione(int id_prenotazione, Prenotazione p);

/**
 * @brief Imposta lo stato della prenotazione
 * 
 * @param stato Nuovo stato della prenotazione
 * @param p Puntatore alla prenotazione
 * 
 * @pre p è un puntatore valido a una struttura Prenotazione, oppure NULL
 * 
 * @post Se p è valido, p->stato = stato
 * @post Se p è NULL, non viene effettuata alcuna modifica
 * 
 * @note Side Effect: Modifica diretta del campo stato nella struttura p
 */
void imposta_stato_prenotazione(int stato, Prenotazione p);

/**
 * @brief Conta le prenotazioni completate da un utente prima di una specifica prenotazione
 * 
 * La funzione conta il numero di prenotazioni completate (stato = 2) da un utente specifico
 * che hanno un ID inferiore a quello della prenotazione corrente. Questo è utile per
 * calcolare lo sconto fedeltà applicabile a una prenotazione.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param id_utente ID dell'utente di cui contare le prenotazioni
 * @param id_prenotazione_corrente ID della prenotazione di riferimento
 * 
 * @pre coda è un puntatore valido a una struttura CodaPrenotazioni
 * @pre id_utente è un identificatore valido
 * @pre id_prenotazione_corrente è un identificatore valido
 * 
 * @post Viene restituito il numero di prenotazioni completate dall'utente con ID minore di id_prenotazione_corrente
 * 
 * @note Side Effect: Nessuno
 * 
 * @return int Numero di prenotazioni completate dall'utente prima della prenotazione specificata
 */
int conta_prenotazioni_completate_prima_di(CodaPrenotazioni coda, int id_utente, int id_prenotazione_corrente);

/**
 * @brief Ottiene una prenotazione specifica dalla coda
 * 
 * La funzione restituisce il puntatore alla prenotazione presente nella posizione specificata
 * all'interno della coda delle prenotazioni.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param i Indice della prenotazione da ottenere
 * 
 * @pre coda è un puntatore valido a una struttura CodaPrenotazioni
 * @pre i è un indice valido (0 <= i < dimensione_coda)
 * 
 * @post Se i parametri sono validi, viene restituito il puntatore alla prenotazione richiesta
 * @post Se i parametri non sono validi, viene restituito NULL
 * 
 * @note Side Effect: Nessuno
 * 
 * @return Prenotazione Puntatore alla prenotazione richiesta o NULL se i parametri non sono validi
 */
Prenotazione ottieni_prenotazione_in_coda(CodaPrenotazioni coda, int i);

/**
 * @brief Rimuove tutte le prenotazioni di un utente dalla coda
 * 
 * La funzione rimuove tutte le prenotazioni associate a un determinato utente dalla coda,
 * mantenendo la proprietà dell'heap durante la rimozione.
 * 
 * @param coda Puntatore alla coda delle prenotazioni
 * @param id_utente ID dell'utente le cui prenotazioni devono essere rimosse
 * 
 * @pre coda è un puntatore valido a una struttura CodaPrenotazioni
 * @pre id_utente è un identificatore valido
 * 
 * @post Tutte le prenotazioni dell'utente specificato vengono rimosse dalla coda
 * @post La struttura dell'heap viene mantenuta valida dopo ogni rimozione
 * 
 * @note Side Effect: Modifica la struttura della coda rimuovendo le prenotazioni dell'utente
 */
void rimuovi_prenotazioni_utente(CodaPrenotazioni coda, int id_utente);

#endif // PRENOTAZIONI_H
