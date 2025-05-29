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
int inserisci_utente(const char* username, const char* nome_completo, const char* password);
Utente cerca_utente(const char* username);
Utente cerca_utente_per_id(int id);
void stampa_utenti();

int rimuovi_utente(int id);

// Getter functions
int get_id_utente(Utente u);
const char* get_nome_utente(Utente u);
const char* get_username_utente(Utente u);
const char* get_password_utente(const char* username);
int get_isAdmin_utente(Utente u);

// Setter functions
void set_id_utente(int id, Utente u);
void set_nome_utente( const char* nome_completo, Utente u);
void set_username_utente(const char* new_username, Utente u);
void set_password_utente(const char* password, Utente u);

// Funzioni per validare
int valida_username(const char* username);
int valida_nome_completo(const char* nome);
int verifica_password(const char* password, Utente u);
void hash_password(const char* input, char* output);

#endif // UTENTI_H