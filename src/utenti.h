#ifndef UTENTI_H
#define UTENTI_H

#define TABLE_SIZE 100
#define MAX_PASSWORD_LENGTH 64

typedef struct Utente *Utente;

// Function declarations
/**
 * @brief Carica l'ultimo ID utente utilizzato dal file
 * 
 * La funzione apre il file data/utenti.txt, legge tutte le righe e restituisce il valore massimo
 * del campo id trovato nel file. Se il file non esiste o è vuoto, restituisce 0.
 * 
 * @pre Il file data/utenti.txt, se esiste, deve contenere righe in cui l'id è il primo campo
 *      e rappresenta un intero valido
 * 
 * @post Restituisce l'id massimo tra quelli trovati nel file
 * @post Se il file non esiste, viene restituito 0
 * 
 * @sideeffect Nessuno
 * 
 * @return int L'ultimo ID utilizzato o 0 se il file non esiste
 */
int carica_ultimo_id_utente();

/**
 * @brief Inizializza la tabella degli utenti
 * 
 * La funzione imposta tutti gli elementi della tabella utenti a NULL,
 * preparando la struttura per l'inserimento di nuovi utenti.
 * 
 * @pre La tabella utenti deve essere dichiarata come array di puntatori a Utente
 * 
 * @post Tutti gli elementi della tabella sono impostati a NULL
 * 
 * @sideeffect Modifica la tabella utenti globale
 */
void inizializza_tabella_utenti();

/**
 * @brief Salva gli utenti su file
 * 
 * La funzione salva tutti gli utenti presenti nella tabella nel file data/utenti.txt.
 * Ogni utente viene salvato con i suoi dati: id, nome utente, password, nome completo e stato admin.
 * 
 * @pre La tabella utenti deve essere inizializzata
 * @pre Il file data/utenti.txt deve essere scrivibile
 * 
 * @post I dati degli utenti vengono scritti nel file
 * 
 * @sideeffect Scrittura su file
 */
void salva_utenti_file();

/**
 * @brief Carica gli utenti da file
 * 
 * La funzione carica gli utenti dal file data/utenti.txt nella tabella.
 * Se il file non esiste, viene creato con un utente admin di default.
 * 
 * @pre Il file data/utenti.txt deve essere leggibile o scrivibile
 * 
 * @post Gli utenti vengono caricati nella tabella
 * @post Se il file non esiste, viene creato con un utente admin
 * 
 * @sideeffect Lettura da file e modifica della tabella utenti
 * 
 * @return int 1 se il caricamento è avvenuto con successo, 0 altrimenti
 */
int carica_utenti_file();

/**
 * @brief Inserisce un nuovo utente nella tabella
 * 
 * La funzione inserisce un nuovo utente nella tabella hash con i dati forniti.
 * 
 * @param nome_utente Il nome utente dell'utente
 * @param nome_completo Il nome completo dell'utente
 * @param password La password dell'utente (verrà hashata)
 * 
 * @pre nome_utente, nome_completo e password devono essere stringhe valide
 * @pre La tabella utenti deve essere inizializzata
 * 
 * @post Un nuovo utente viene inserito nella tabella
 * 
 * @sideeffect Modifica la tabella utenti
 * 
 * @return int 1 se l'inserimento è avvenuto con successo, 0 altrimenti
 */
int inserisci_utente(const char* nome_utente, const char* nome_completo, const char* password);

/**
 * @brief Cerca un utente per nome utente
 * 
 * La funzione cerca un utente nella tabella hash usando il nome utente come chiave.
 * 
 * @param nome_utente Il nome utente da cercare
 * 
 * @pre La tabella utenti deve essere inizializzata
 * 
 * @post Restituisce il puntatore all'utente se trovato, NULL altrimenti
 * 
 * @sideeffect Nessuno
 * 
 * @return Utente Il puntatore all'utente trovato o NULL
 */
Utente cerca_utente(const char* nome_utente);

/**
 * @brief Cerca un utente per ID
 * 
 * La funzione cerca un utente nella tabella usando l'ID come chiave.
 * 
 * @param id L'ID dell'utente da cercare
 * 
 * @pre La tabella utenti deve essere inizializzata
 * 
 * @post Restituisce il puntatore all'utente se trovato, NULL altrimenti
 * 
 * @sideeffect Nessuno
 * 
 * @return Utente Il puntatore all'utente trovato o NULL
 */
Utente cerca_utente_per_id(int id);

/**
 * @brief Stampa tutti gli utenti nella tabella
 * 
 * La funzione stampa le informazioni di tutti gli utenti presenti nella tabella.
 * 
 * @pre La tabella utenti deve essere inizializzata
 * 
 * @post Le informazioni degli utenti vengono stampate su stdout
 * 
 * @sideeffect Output su console
 */
void stampa_utenti();

/**
 * @brief Rimuove un utente dalla tabella
 * 
 * La funzione rimuove un utente dalla tabella e libera la memoria associata.
 * Rimuove anche tutte le prenotazioni associate all'utente.
 * 
 * @param id L'ID dell'utente da rimuovere
 * 
 * @pre La tabella utenti deve essere inizializzata
 * 
 * @post L'utente viene rimosso dalla tabella
 * @post Le prenotazioni dell'utente vengono rimosse
 * 
 * @sideeffect Modifica la tabella utenti e la coda prenotazioni
 * 
 * @return int 1 se la rimozione è avvenuta con successo, 0 altrimenti
 */
int rimuovi_utente(int id);

// Getter functions
/**
 * @brief Ottiene l'ID di un utente
 * 
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * 
 * @post Restituisce l'ID dell'utente o -1 se l'utente non è valido
 * 
 * @sideeffect Nessuno
 * 
 * @return int L'ID dell'utente o -1
 */
int ottieni_id_utente(Utente u);

/**
 * @brief Ottiene il nome completo di un utente
 * 
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * 
 * @post Restituisce il nome completo dell'utente o NULL se l'utente non è valido
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* Il nome completo dell'utente o NULL
 */
const char* ottieni_nome_completo_utente(Utente u);

/**
 * @brief Ottiene il nome utente di un utente
 * 
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * 
 * @post Restituisce il nome utente dell'utente o NULL se l'utente non è valido
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* Il nome utente dell'utente o NULL
 */
const char* ottieni_nome_utente(Utente u);

/**
 * @brief Ottiene la password di un utente
 * 
 * @param nome_utente Il nome utente dell'utente
 * 
 * @pre La tabella utenti deve essere inizializzata
 * 
 * @post Restituisce la password hashata dell'utente o NULL se l'utente non esiste
 * 
 * @sideeffect Nessuno
 * 
 * @return const char* La password hashata dell'utente o NULL
 */
const char* ottieni_password_utente(const char* nome_utente);

/**
 * @brief Ottiene lo stato admin di un utente
 * 
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * 
 * @post Restituisce 1 se l'utente è admin, 0 se non lo è, -1 se l'utente non è valido
 * 
 * @sideeffect Nessuno
 * 
 * @return int Lo stato admin dell'utente
 */
int ottieni_isAdmin_utente(Utente u);

// Setter functions
/**
 * @brief Imposta l'ID di un utente
 * 
 * @param id Il nuovo ID da assegnare
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * 
 * @post L'ID dell'utente viene aggiornato
 * 
 * @sideeffect Modifica l'ID dell'utente
 */
void imposta_id_utente(int id, Utente u);

/**
 * @brief Imposta il nome completo di un utente
 * 
 * @param nome_completo Il nuovo nome completo
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * @pre nome_completo deve essere una stringa valida
 * 
 * @post Il nome completo dell'utente viene aggiornato
 * 
 * @sideeffect Modifica il nome completo dell'utente
 */
void imposta_nome_utente(const char* nome_completo, Utente u);

/**
 * @brief Imposta il nome utente di un utente
 * 
 * @param nuovo_nome_utente Il nuovo nome utente
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * @pre nuovo_nome_utente deve essere una stringa valida e non deve esistere già
 * 
 * @post Il nome utente dell'utente viene aggiornato
 * 
 * @sideeffect Modifica il nome utente dell'utente
 */
void imposta_nome_utente_utente(const char* nuovo_nome_utente, Utente u);

/**
 * @brief Imposta la password di un utente
 * 
 * @param password La nuova password
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * @pre password deve essere una stringa valida
 * 
 * @post La password dell'utente viene aggiornata (hashata)
 * 
 * @sideeffect Modifica la password dell'utente
 */
void imposta_password_utente(const char* password, Utente u);

// Funzioni per validare
/**
 * @brief Valida un nome utente
 * 
 * Verifica che il nome utente rispetti i criteri di validità:
 * - Lunghezza tra 3 e 29 caratteri
 * - Solo caratteri alfanumerici e underscore
 * 
 * @param nome_utente Il nome utente da validare
 * 
 * @pre nome_utente deve essere una stringa valida
 * 
 * @post Restituisce 1 se il nome utente è valido, 0 altrimenti
 * 
 * @sideeffect Nessuno
 * 
 * @return int 1 se valido, 0 altrimenti
 */
int valida_nome_utente(const char* nome_utente);

/**
 * @brief Valida un nome completo
 * 
 * Verifica che il nome completo rispetti i criteri di validità:
 * - Lunghezza tra 3 e 49 caratteri
 * - Solo lettere, spazi e alcuni caratteri speciali
 * 
 * @param nome Il nome completo da validare
 * 
 * @pre nome deve essere una stringa valida
 * 
 * @post Restituisce 1 se il nome è valido, 0 altrimenti
 * 
 * @sideeffect Nessuno
 * 
 * @return int 1 se valido, 0 altrimenti
 */
int valida_nome_completo(const char* nome);

/**
 * @brief Verifica la password di un utente
 * 
 * Confronta la password fornita con quella memorizzata dell'utente.
 * 
 * @param password La password da verificare
 * @param u Il puntatore all'utente
 * 
 * @pre u deve essere un puntatore valido
 * @pre password deve essere una stringa valida
 * 
 * @post Restituisce 1 se la password è corretta, 0 altrimenti
 * 
 * @sideeffect Nessuno
 * 
 * @return int 1 se la password è corretta, 0 altrimenti
 */
int verifica_password(const char* password, Utente u);

/**
 * @brief Genera l'hash di una password
 * 
 * Genera un hash della password usando l'algoritmo DJB2.
 * 
 * @param input La password da hashare
 * @param output Il buffer dove salvare l'hash
 * 
 * @pre input deve essere una stringa valida
 * @pre output deve essere un buffer di dimensione MAX_PASSWORD_LENGTH
 * 
 * @post L'hash della password viene salvato in output
 * 
 * @sideeffect Modifica il buffer output
 */
void hash_password(const char* input, char* output);

#endif // UTENTI_H