#ifndef UTENTI_H
#define UTENTI_H

#define TABLE_SIZE 100
#define MAX_PASSWORD_LENGTH 64

typedef struct Utente *Utente;

// Function declarations
int carica_ultimo_id_utente();
void inizializza_tabella_utenti();
void salva_utenti_file();
int carica_utenti_file();
int inserisci_utente(const char* username, const char* nome_completo);
Utente cerca_utente(const char* username);
Utente cerca_utente_per_id(int id);
void stampa_utenti();
int verifica_password(const char* password, Utente u);
void hash_password(const char* input, char* output);

// Getter functions
int get_id_utente(const char* username);
char* get_nome_utente(Utente u);
char* get_username_utente(Utente u);
char* get_password_utente(const char* username);
int get_isAdmin_utente(const char* username);

// Setter functions
void set_id_utente(int id, Utente u);
void set_nome_utente( const char* nome_completo, Utente u);
void set_username_utente(const char* new_username);
void set_password_utente(const char* password, Utente u);

#endif // UTENTI_H