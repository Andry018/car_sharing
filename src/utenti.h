#ifndef UTENTI_H
#define UTENTI_H

#define TABLE_SIZE 100
#define MAX_PASSWORD_LENGTH 64

typedef struct Utente *Utente;

/**
 * @brief Restituisce l'ID utente più alto presente nel file utenti.txt
 * 
 * La funzione restituisce l'ID utente più alto presente nel file utenti.txt,
 * ignorando l'amministratore.
 * 
 * @pre Il file utenti.txt deve esistere e essere leggibile
 * @post Restituisce l'ID più alto trovato nel file
 * @post Restituisce 0 se il file non esiste o non è leggibile
 * @sideeffect Nessuno
 * @return int ID più alto trovato, 0 se il file non esiste o non è leggibile
 */
int carica_ultimo_id_utente();

/**
 * @brief Inizializza la tabella hash degli utenti e garantisce la presenza dell'utente amministratore
 * 
 * Inizializza la tabella hash degli utenti e garantisce la presenza dell'utente
 * amministratore (Admin) con ID 0.
 * 
 * @pre La tabella hash deve essere accessibile
 * @post La tabella hash è inizializzata
 * @post L'utente Admin è presente nella tabella con:
 *      - id = 0
 *      - username = "Admin"
 *      - nome_completo = "Administrator"
 *      - isAdmin = 1
 * @sideeffect Modifica la tabella hash degli utenti
 * @sideeffect Crea il file utenti.txt se non esiste
 */
void inizializza_tabella_utenti();

/**
 * @brief Salva su file tutte le informazioni degli utenti presenti nella tabella
 * 
 * La funzione salva su file "data/utenti.txt" tutte le informazioni degli utenti
 * presenti nella tabella tabellaUtenti.
 * 
 * @pre La tabella hash deve essere inizializzata
 * @pre La directory data/ deve esistere e essere scrivibile
 * @post Il file utenti.txt contiene tutte le informazioni degli utenti
 * @post Ogni riga del file contiene: id username nome_completo isAdmin
 * @sideeffect Crea o sovrascrive il file utenti.txt
 */
void salva_utenti_file();

/**
 * @brief Legge il contenuto del file e inserisce gli utenti nella tabella hash
 * 
 * La funzione legge il contenuto del file data/utenti.txt e inserisce gli utenti
 * nella tabella hash in memoria.
 * 
 * @pre Il file utenti.txt deve esistere e essere leggibile
 * @pre La tabella hash deve essere inizializzata
 * @post Gli utenti sono inseriti nella tabella hash
 * @post Restituisce 1 se tutti gli utenti vengono inseriti con successo
 * @post Restituisce 0 se ci sono errori durante l'inserimento
 * @sideeffect Modifica la tabella hash degli utenti
 * @return int 1 se tutti gli utenti vengono inseriti con successo, 0 altrimenti
 */
int carica_utenti_file();

/**
 * @brief Inserisce un nuovo utente nella tabella hash
 * 
 * La funzione inserisce un nuovo utente nella tabella hash globale tabellaUtenti.
 * L'ID dell'utente è assegnato automaticamente, incrementale, e unico, a meno che
 * l'utente non sia l'admin (che ha sempre ID 0).
 * 
 * @pre username è una stringa valida (non NULL)
 * @pre nome_completo è una stringa valida (non NULL)
 * @pre password è una stringa valida (non NULL)
 * @pre La tabella hash deve essere inizializzata
 * @post Se l'inserimento ha successo, restituisce 1
 * @post Se l'inserimento fallisce, restituisce 0
 * @sideeffect Modifica la tabella hash degli utenti
 * @param username Nome utente del nuovo utente
 * @param nome_completo Nome completo del nuovo utente
 * @param password Password del nuovo utente
 * @return int 1 se l'inserimento ha successo, 0 altrimenti
 */
int inserisci_utente(const char* username, const char* nome_completo, const char* password);

/**
 * @brief Cerca un utente nella tabella hash in base al campo username
 * 
 * La funzione cerca un utente nella tabella hash tabellaUtenti in base al campo username.
 * Utilizza probing lineare per risolvere eventuali collisioni.
 * 
 * @pre username è una stringa valida (non NULL)
 * @pre La tabella hash deve essere inizializzata
 * @post Se l'utente è trovato, restituisce un puntatore alla struttura Utente
 * @post Se l'utente non è trovato, restituisce NULL
 * @sideeffect Nessuno
 * @param username Nome utente da cercare
 * @return Utente Puntatore alla struttura Utente se trovata, NULL altrimenti
 */
Utente cerca_utente(const char* username);

/**
 * @brief Cerca un utente nella tabella in base all'ID
 * 
 * La funzione cerca e restituisce un puntatore all'utente corrispondente all'id
 * fornito nella tabella degli utenti, se presente.
 * 
 * @pre id è un intero valido
 * @pre La tabella hash deve essere inizializzata
 * @post Se l'utente è trovato, restituisce un puntatore alla struttura Utente
 * @post Se l'utente non è trovato, restituisce NULL
 * @sideeffect Nessuno
 * @param id ID dell'utente da cercare
 * @return Utente Puntatore alla struttura Utente se trovata, NULL altrimenti
 */
Utente cerca_utente_per_id(int id);

/**
 * @brief Stampa la lista di tutti gli utenti presenti nella tabella
 * 
 * La funzione stampa a video la lista di tutti gli utenti presenti nella tabella hash
 * tabellaUtenti, mostrando ID, username, nome completo e se sono admin o meno.
 * 
 * @pre La tabella hash deve essere inizializzata
 * @post Le informazioni degli utenti sono stampate su stdout
 * @sideeffect Stampa su stdout
 */
void stampa_utenti();

/**
 * @brief Rimuove un utente dalla tabella hash
 * 
 * La funzione rimuove l'utente con l'ID specificato dalla tabella hash degli utenti.
 * 
 * @pre id è un intero valido
 * @pre La tabella hash deve essere inizializzata
 * @post Se l'utente è rimosso con successo, restituisce 1
 * @post Se l'utente non è trovato, restituisce 0
 * @sideeffect Modifica la tabella hash degli utenti
 * @param id ID dell'utente da rimuovere
 * @return int 1 se l'utente è stato rimosso con successo, 0 altrimenti
 */
int rimuovi_utente(int id);

/**
 * @brief Calcola l'hash della stringa input usando la funzione hash_djb2
 * 
 * Calcola l'hash della stringa input usando la funzione hash_djb2 e scrive il risultato
 * (in forma numerica) nella stringa output.
 * 
 * @pre input è un puntatore valido a una stringa terminata da \0
 * @pre output è un buffer sufficientemente grande per contenere l'hash
 * @post output contiene la rappresentazione in stringa dell'hash calcolato
 * @sideeffect Modifica il buffer output
 * @param input Stringa di input da cui calcolare l'hash
 * @param output Buffer dove scrivere l'hash calcolato
 */
void hash_password(const char* input, char* output);

/**
 * @brief Restituisce l'ID dell'utente associato allo username
 * 
 * @pre username è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente esiste, restituisce il suo ID
 * @post Se l'utente non esiste, restituisce -1
 * @sideeffect Nessuno
 * @param username Nome utente dell'utente da cercare
 * @return int ID dell'utente se trovato, -1 altrimenti
 */
int get_id_utente(const char* username);

/**
 * @brief Restituisce il nome completo dell'utente associato allo username
 * 
 * @pre username è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente esiste, restituisce il suo nome completo
 * @post Se l'utente non esiste, restituisce NULL
 * @sideeffect Nessuno
 * @param username Nome utente dell'utente da cercare
 * @return const char* Nome completo dell'utente se trovato, NULL altrimenti
 */
const char* get_nome_utente(const char* username);

/**
 * @brief Restituisce lo username dell'utente associato allo username passato
 * 
 * @pre username è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente esiste, restituisce il suo username
 * @post Se l'utente non esiste, restituisce NULL
 * @sideeffect Nessuno
 * @param username Nome utente dell'utente da cercare
 * @return const char* Username dell'utente se trovato, NULL altrimenti
 */
const char* get_username_utente(const char* username);

/**
 * @brief Restituisce il primo carattere della password dell'utente
 * 
 * @pre username è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente esiste, restituisce il primo carattere della sua password
 * @post Se l'utente non esiste, restituisce NULL
 * @sideeffect Chiama cerca_utente(username)
 * @param username Nome utente dell'utente da cercare
 * @return const char* Primo carattere della password se l'utente esiste, NULL altrimenti
 */
const char* get_password_utente(const char* username);

/**
 * @brief Restituisce il valore isAdmin dell'utente
 * 
 * @pre u è un puntatore valido a una struttura Utente
 * @post Se l'utente è valido, restituisce il suo valore isAdmin
 * @post Se l'utente non è valido, restituisce -1
 * @sideeffect Nessuno
 * @param u Puntatore alla struttura Utente
 * @return int 1 se l'utente è admin, 0 se non lo è, -1 se l'utente non è valido
 */
int get_isAdmin_utente(Utente u);

/**
 * @brief Imposta l'ID dell'utente
 * 
 * @pre u è un puntatore valido a una struttura Utente
 * @post Se l'utente è valido, utente->id = id
 * @post Se l'utente non è valido, stampa un messaggio di errore
 * @sideeffect Eventuale output su stdout in caso di utente non valido
 * @param id Nuovo ID da assegnare
 * @param u Puntatore alla struttura Utente
 */
void set_id_utente(int id, Utente u);

/**
 * @brief Imposta il nome completo dell'utente
 * 
 * @pre u è un puntatore valido a una struttura Utente
 * @pre nome_completo è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente è valido, utente->nome_completo viene aggiornato con nome_completo
 * @post Se l'utente non è valido, stampa un messaggio di errore
 * @sideeffect Modifica diretta del campo nome_completo nella struttura utente
 * @param nome_completo Nuovo nome completo da assegnare
 * @param u Puntatore alla struttura Utente
 */
void set_nome_utente(const char* nome_completo, Utente u);

/**
 * @brief Imposta il campo username dell'utente
 * 
 * Imposta il campo username dell'utente con new_username, se questo non è già
 * usato da un altro utente.
 * 
 * @pre u è un puntatore valido a una struttura Utente
 * @pre new_username è un puntatore valido a una stringa terminata da \0
 * @post Se new_username non è già in uso, il campo username dell'utente è aggiornato
 * @post Se new_username è già in uso, stampa un messaggio di errore
 * @sideeffect Stampa messaggi su stdout
 * @sideeffect Modifica diretta del campo username nella struttura utente
 * @param new_username Nuovo username da assegnare
 * @param u Puntatore alla struttura Utente
 */
void set_username_utente(const char* new_username, Utente u);

/**
 * @brief Aggiorna la password dell'utente
 * 
 * Aggiorna la password dell'utente con l'hash della password fornita.
 * 
 * @pre u è un puntatore valido a una struttura Utente
 * @pre username è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente è valido, utente->password viene aggiornato con l'hash della password
 * @post Se l'utente non è valido, stampa un messaggio di errore
 * @sideeffect Modifica diretta del campo password nella struttura utente
 * @param username Username dell'utente
 * @param u Puntatore alla struttura Utente
 */
void set_password_utente(const char* username, Utente u);

/**
 * @brief Verifica la validità di un username
 * 
 * La funzione verifica se la stringa username rispetta i criteri di validità definiti
 * per i nomi utente del sistema. In particolare, controlla:
 * - che la lunghezza sia compresa tra 3 e 29 caratteri inclusi
 * - che tutti i caratteri siano lettere (A-Z, a-z), cifre (0-9) o il carattere underscore _
 * 
 * @pre username deve essere una stringa terminata da carattere nullo ('\0')
 * @pre La stringa username non deve essere NULL
 * @post Non modifica il contenuto di username o altre variabili esterne
 * @post Restituisce 1 se username rispetta le regole di validità
 * @post Restituisce 0 in caso contrario
 * @sideeffect Nessuno
 * @param username Username da validare
 * @return int 1 se l'username è valido, 0 altrimenti
 */
int valida_username(const char* username);

/**
 * @brief Verifica la validità di un nome completo
 * 
 * La funzione controlla se la stringa nome rispetta i criteri di validità per un nome
 * completo nel sistema. In particolare:
 * - la lunghezza deve essere compresa tra 3 e 49 caratteri inclusi
 * - ogni carattere deve essere una lettera (A-Z, a-z), uno spazio ' ', un apostrofo '
 *   o un trattino -
 * 
 * @pre nome deve essere una stringa terminata da carattere nullo ('\0')
 * @pre nome non deve essere NULL
 * @post Non modifica la stringa nome né altre variabili esterne
 * @post Restituisce 1 se il nome è valido
 * @post Restituisce 0 se non è valido
 * @sideeffect Nessuno
 * @param nome Nome completo da validare
 * @return int 1 se il nome è valido, 0 altrimenti
 */
int valida_nome_completo(const char* nome);

/**
 * @brief Verifica se la password fornita corrisponde a quella memorizzata
 * 
 * Verifica se la password fornita corrisponde alla password memorizzata per l'utente.
 * 
 * @pre u è un puntatore valido a una struttura Utente
 * @pre password è un puntatore valido a una stringa terminata da \0
 * @post Se l'utente è valido e la password corrisponde, restituisce 1
 * @post Se l'utente non è valido o la password non corrisponde, restituisce 0
 * @sideeffect Chiama hash_password per ottenere l'hash della password in input
 * @param password Password da verificare
 * @param u Puntatore alla struttura Utente
 * @return int 1 se la password corrisponde, 0 altrimenti
 */
int verifica_password(const char* password, Utente u);

#endif // UTENTI_H