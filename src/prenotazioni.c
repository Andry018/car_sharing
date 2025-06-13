#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "prenotazioni.h"
#include "data_sistema.h"
#include "f_utili.h"
#include "veicolo.h"
#include "utenti.h"

#define INITIAL_CAPACITY 10


// Stati possibili di una prenotazione


/**
 * @struct Prenotazione
 * @brief Rappresenta una prenotazione di un veicolo da parte di un utente.
 *
 * @var Prenotazione::id_prenotazione
 *   Identificativo univoco della prenotazione.
 * @var Prenotazione::id_utente
 *   Identificativo dell'utente che ha effettuato la prenotazione.
 * @var Prenotazione::id_veicolo
 *   Identificativo del veicolo prenotato.
 * @var Prenotazione::giorno_ora_inizio
 *   Timestamp di inizio prenotazione (giorno*24 + ora).
 * @var Prenotazione::giorno_ora_fine
 *   Timestamp di fine prenotazione (giorno*24 + ora).
 * @var Prenotazione::stato
 *   Stato della prenotazione (0: In attesa, 1: Confermata, 2: Completata, 3: Cancellata).
 * @var Prenotazione::priorita
 *   Priorità della prenotazione (più basso = più prioritario).
 * @var Prenotazione::posizione_riconsegna
 *   Posizione di riconsegna del veicolo.
 */
struct Prenotazione {
    int id_prenotazione;
    int id_utente;
    int id_veicolo;
    int giorno_ora_inizio;
    int giorno_ora_fine;
    int stato;
    int priorita;
    int posizione_riconsegna;
};

/**
 * @struct CodaPrenotazioni
 * @brief Rappresenta una coda di prenotazioni gestita tramite heap.
 *
 * @var CodaPrenotazioni::heap
 *   Array dinamico di prenotazioni.
 * @var CodaPrenotazioni::capacita
 *   Capacità massima dell'array.
 * @var CodaPrenotazioni::dimensione
 *   Numero di elementi attuali nella coda.
 */
struct CodaPrenotazioni {
    struct Prenotazione *heap;
    int capacita;
    int dimensione;
};  

// Funzioni di utilità per l'heap
#define GENITORE(i) ((i - 1) / 2)
#define FIGLIO_SINISTRO(i) (2 * i + 1)
#define FIGLIO_DESTRO(i) (2 * i + 2)

// Variabile globale per la coda delle prenotazioni
static struct CodaPrenotazioni *coda_globale = NULL;

// Contatore globale per gli ID delle prenotazioni
static int id_counter = 0;

/**
 * @brief Ottiene la coda globale delle prenotazioni.
 * @return Puntatore alla coda globale delle prenotazioni.
 */
CodaPrenotazioni ottieni_coda_prenotazioni() {
    return coda_globale;
}

/**
 * @brief Inizializza una nuova coda di prenotazioni.
 * @return Puntatore alla nuova coda inizializzata, o NULL in caso di errore.
 * @note Side Effect: Alloca memoria per la struttura CodaPrenotazioni e per l'array heap.
 */
CodaPrenotazioni inizializza_coda(void) {
    CodaPrenotazioni coda = (CodaPrenotazioni)malloc(sizeof(struct CodaPrenotazioni));
    if (coda == NULL) {
        return NULL;
    }
    
    // Initialize heap with initial capacity
    coda->heap = (Prenotazione)malloc(sizeof(struct Prenotazione) * INITIAL_CAPACITY);
    if (coda->heap == NULL) {
        free(coda);
        return NULL;
    }
    
    coda->capacita = INITIAL_CAPACITY;
    coda->dimensione = 0;
    return coda;
}

/**
 * @brief Scambia due prenotazioni.
 * @param a Puntatore alla prima prenotazione.
 * @param b Puntatore alla seconda prenotazione.
 * @note Side Effect: Modifica i dati delle strutture puntate da a e b.
 */
void scambia_prenotazioni( struct Prenotazione* a,struct Prenotazione* b) {
    struct Prenotazione temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Ripristina la proprietà di heap minima risalendo.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param indice Indice da cui iniziare il bubble up.
 * @note Side Effect: Modifica l'array heap della coda.
 */
void bubble_up( CodaPrenotazioni coda, int indice) {
    while (indice > 0 && coda->heap[GENITORE(indice)].priorita > coda->heap[indice].priorita) {
        scambia_prenotazioni(&coda->heap[GENITORE(indice)], &coda->heap[indice]);
        indice = GENITORE(indice);
    }
}

/**
 * @brief Ripristina la proprietà di heap minima scendendo.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param indice Indice da cui iniziare il bubble down.
 * @note Side Effect: Modifica l'array heap della coda.
 */
void bubble_down( CodaPrenotazioni coda, int indice) {
    int min_indice = indice;
    int left = FIGLIO_SINISTRO(indice);
    int right = FIGLIO_DESTRO(indice);
    
    if (left < coda->dimensione && coda->heap[left].priorita < coda->heap[min_indice].priorita) {
        min_indice = left;
    }
    
    if (right < coda->dimensione && coda->heap[right].priorita < coda->heap[min_indice].priorita) {
        min_indice = right;
    }
    
    if (min_indice != indice) {
        scambia_prenotazioni(&coda->heap[indice], &coda->heap[min_indice]);
        bubble_down(coda, min_indice);
    }
}

/**
 * @brief Converte giorno e ora in un timestamp univoco.
 * @param giorno Giorno della settimana (0-6).
 * @param ora Ora del giorno (0-23).
 * @return Il timestamp calcolato.
 */
int converti_in_timestamp(int giorno, int ora) {
    return giorno * 24 + ora;
}

/**
 * @brief Estrae il giorno da un timestamp.
 * @param timestamp Il timestamp da cui estrarre il giorno.
 * @return Il giorno della settimana (0-6).
 */
int estrai_giorno(int timestamp) {
    return timestamp / 24;
}

/**
 * @brief Estrae l'ora da un timestamp.
 * @param timestamp Il timestamp da cui estrarre l'ora.
 * @return L'ora del giorno (0-23).
 */
int estrai_ora(int timestamp) {
    return timestamp % 24;
}

/**
 * @brief Verifica la validità di una fascia oraria.
 * @param giorno_inizio Giorno di inizio (0-6).
 * @param ora_inizio Ora di inizio (0-23).
 * @param giorno_fine Giorno di fine (0-6).
 * @param ora_fine Ora di fine (0-23).
 * @return 1 se l'intervallo è valido, 0 altrimenti.
 */
int verifica_fascia_oraria(int giorno_inizio, int ora_inizio, int giorno_fine, int ora_fine) {
    int timestamp_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    int timestamp_fine = converti_in_timestamp(giorno_fine, ora_fine);
    
    if (giorno_inizio < 0 || giorno_inizio > 6) return 0;
    if (giorno_fine < 0 || giorno_fine > 6) return 0;
    if (ora_inizio < 0 || ora_inizio > 23) return 0;
    if (ora_fine < 0 || ora_fine > 23) return 0;
    if (timestamp_inizio >= timestamp_fine) return 0;
    return 1;
}

/**
 * @brief Crea una nuova prenotazione.
 * @param id_utente ID dell'utente.
 * @param id_veicolo ID del veicolo.
 * @param giorno_inizio Giorno di inizio (0-6).
 * @param ora_inizio Ora di inizio (0-23).
 * @param giorno_fine Giorno di fine (0-6).
 * @param ora_fine Ora di fine (0-23).
 * @param priorita Priorità della prenotazione (se < 0, viene calcolata automaticamente).
 * @param posizione_riconsegna Posizione di riconsegna del veicolo.
 * @return Puntatore alla nuova prenotazione, o NULL in caso di errore.
 * @note Side Effect: Alloca memoria per la struttura Prenotazione.
 */
Prenotazione crea_prenotazione(int id_utente, int id_veicolo, 
                                     int giorno_inizio, int ora_inizio,
                                     int giorno_fine, int ora_fine, 
                                     int priorita, int posizione_riconsegna) {
   

    Prenotazione nuova = (Prenotazione)malloc(sizeof(struct Prenotazione));
    if (nuova == NULL) {
        return NULL;
    }
    
    nuova->id_prenotazione = ++id_counter;
    nuova->id_utente = id_utente;
    nuova->id_veicolo = id_veicolo;
    nuova->giorno_ora_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    nuova->giorno_ora_fine = converti_in_timestamp(giorno_fine, ora_fine);
    nuova->stato = 0;  // In attesa
    nuova->posizione_riconsegna = posizione_riconsegna;
    
    if (priorita < 0) {
        // Se non è specificata una priorità, la calcoliamo in base al tempo
        nuova->priorita = calcola_priorita_temporale(nuova->giorno_ora_inizio);
    } else {
        nuova->priorita = priorita;
    }
    
    return nuova;
}

/**
 * @brief Aggiunge una prenotazione alla coda.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param prenotazione Prenotazione da aggiungere.
 * @return 0 se riuscito, -1 errore generico, -2 fascia oraria non valida, -3 utente non trovato, -4 veicolo non trovato.
 * @note Side Effect: Modifica la struttura della coda.
 */
int aggiungi_prenotazione(CodaPrenotazioni coda, Prenotazione prenotazione) {
    if (coda == NULL || prenotazione == NULL) {
        return -1;
    }

    // Verifica se la fascia oraria è valida
    if (!verifica_fascia_oraria(estrai_giorno(prenotazione->giorno_ora_inizio), 
                                estrai_ora(prenotazione->giorno_ora_inizio),
                                estrai_giorno(prenotazione->giorno_ora_fine), 
                                estrai_ora(prenotazione->giorno_ora_fine))) {
        return -2;  // Fascia oraria non valida
    }   

    // Verifica se l'utente esiste
    Utente utente = cerca_utente_per_id(prenotazione->id_utente);
    if (utente == NULL) {
        return -3;  // Utente non trovato
    }

    // Verifica se il veicolo esiste
    list veicoli = ottieni_lista_veicoli();
    Veicolo veicolo = cerca_veicolo(veicoli, prenotazione->id_veicolo);
    if (veicolo == NULL) {
        return -4;  // Veicolo non trovato
    }
    
    // Se necessario, ridimensiona l'array
    if (coda->dimensione >= coda->capacita) {
        int nuova_capacita = coda->capacita * 2;
        Prenotazione nuovo_heap = (Prenotazione)realloc(coda->heap, 
                                                        sizeof(struct Prenotazione) * nuova_capacita);
        if (nuovo_heap == NULL) {
            return -1;
        }
        coda->heap = nuovo_heap;
        coda->capacita = nuova_capacita;
    }
    
    // Inserisci la nuova prenotazione alla fine dell'heap
    coda->heap[coda->dimensione] = *prenotazione;
    bubble_up(coda, coda->dimensione);
    coda->dimensione++;
    
    return 0;
}

/**
 * @brief Cerca una prenotazione nella coda per ID.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param id_prenotazione ID della prenotazione da cercare.
 * @return Puntatore alla prenotazione trovata, o NULL se non trovata.
 */
 Prenotazione cerca_prenotazione( CodaPrenotazioni coda, int id_prenotazione) {
    if (coda == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < coda->dimensione; i++) {
        if (coda->heap[i].id_prenotazione == id_prenotazione) {
            return &coda->heap[i];
        }
    }
    
    return NULL;
}

/**
 * @brief Modifica lo stato di una prenotazione.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param id_prenotazione ID della prenotazione da modificare.
 * @param nuovo_stato Nuovo stato da assegnare (0: In attesa, 1: Confermata, 2: Completata, 3: Cancellata).
 * @return 0 se riuscito, -1 se la prenotazione non è stata trovata.
 * @note Side Effect: Modifica lo stato della prenotazione e, se completata, la posizione del veicolo associato.
 */
int modifica_stato_prenotazione( CodaPrenotazioni coda, int id_prenotazione, int nuovo_stato) {
     Prenotazione prenotazione = cerca_prenotazione(coda, id_prenotazione);
    if (prenotazione == NULL) {
        return -1;
    }
    
    prenotazione->stato = nuovo_stato;
    // Se la prenotazione è stata completata, aggiorna la posizione del veicolo
    if (nuovo_stato == 2) { // 2 = Completata
        // Recupera il veicolo associato
        list veicoli = ottieni_lista_veicoli();
        while (veicoli != NULL) {
            Veicolo v = ottieni_veicolo_senza_rimuovere(veicoli);
            if (v && ottieni_id_veicolo(v) == prenotazione->id_veicolo) {
                imposta_posizione_veicolo(v, prenotazione->posizione_riconsegna);
                break;
            }
            veicoli = ottieni_successivo_nodo(veicoli);
        }
    return 0;
}
return 0;
}

/**
 * @brief Stampa le informazioni di una prenotazione.
 * @param p Puntatore alla prenotazione da stampare.
 * @note Side Effect: Scrive su stdout.
 */
void stampa_prenotazione(Prenotazione p) {
    const char* stati[] = {"In attesa", "Confermata", "Completata", "Cancellata"};
    
    printf("  ID Prenotazione: %d\n", ottieni_id_prenotazione(p));
    printf("  ID Utente: %d\n",ottieni_id_utente_prenotazione(p));
    printf("  ID Veicolo: %d\n",ottieni_id_veicolo_prenotazione(p));
    printf("  Inizio: %s ore %02d:00\n", 
           ottieni_nome_giorno(ottieni_giorno_inizio(p)), 
           ottieni_ora_inizio(p));
    printf("  Fine: %s ore %02d:00\n", 
           ottieni_nome_giorno(ottieni_giorno_fine(p)), 
          ottieni_ora_fine(p));
    
    printf("  Stato: ");
    switch(ottieni_stato_prenotazione(p)) {
        case 0:
            imposta_colore(14);  // Giallo per prenotazioni in attesa
            break;
        case 1:
            imposta_colore(10);  // Verde per prenotazioni confermate
            break;
        case 2:
            imposta_colore(11);  // Ciano per prenotazioni completate
            break;
        case 3:
            imposta_colore(12);  // Rosso per prenotazioni cancellate
            break;
    }
    printf("%s\n", stati[ottieni_stato_prenotazione(p)]);
    printf("Posizione riconsegna: %s\n", ottieni_nome_posizione_veicolo(p->posizione_riconsegna));
    
    imposta_colore(7);  // Bianco
}

/**
 * @brief Salva tutte le prenotazioni su file.
 * @param coda Puntatore alla coda delle prenotazioni da salvare.
 * @note Side Effect: Sovrascrive il file data/prenotazioni.txt.
 */
void salva_prenotazioni_su_file( CodaPrenotazioni coda) {
    FILE* file = fopen("data/prenotazioni.txt", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file per la scrittura!\n");
        return;
    }
    
    for (int i = 0; i < coda->dimensione; i++) {
        fprintf(file, "%d %d %d %d %d %d %d %d\n",
                coda->heap[i].id_prenotazione,
                coda->heap[i].id_utente,
                coda->heap[i].id_veicolo,
                coda->heap[i].giorno_ora_inizio,
                coda->heap[i].giorno_ora_fine,
                coda->heap[i].stato,
                coda->heap[i].priorita,
                coda->heap[i].posizione_riconsegna);
    }
    
    fclose(file);
}

/**
 * @brief Carica le prenotazioni da un file di testo nella coda.
 * @param coda Puntatore alla coda delle prenotazioni dove inserire i dati.
 * @return 0 se il caricamento è avvenuto con successo, -1 in caso di errore.
 * @note Side Effect: Modifica la struttura della coda.
 */
int carica_prenotazioni_da_file(CodaPrenotazioni coda) {
    if (coda == NULL) {
        printf("Errore: coda non inizializzata!\n");
        return -1;
    }

    FILE* file = fopen("data/prenotazioni.txt", "r");
    if (file == NULL) {
        printf("errore nell'apertura del file per la lettura!\n");
        return -1;
    }
    
    int stato_temp;
    while (!feof(file)) {
         struct Prenotazione prenotazione;
        if (fscanf(file, "%d %d %d %d %d %d %d %d\n",
               &prenotazione.id_prenotazione,
               &prenotazione.id_utente,
               &prenotazione.id_veicolo,
               &prenotazione.giorno_ora_inizio,
               &prenotazione.giorno_ora_fine,
               &stato_temp,
               &prenotazione.priorita,
               &prenotazione.posizione_riconsegna) == 8) {
            
            // Aggiorna il contatore globale se necessario
            if (prenotazione.id_prenotazione > id_counter) {
                id_counter = prenotazione.id_prenotazione;
            }
            
            prenotazione.stato = stato_temp;
            if (aggiungi_prenotazione(coda, &prenotazione) != 0) {
                printf("Errore nell'aggiunta della prenotazione %d!\n", prenotazione.id_prenotazione);
            }
        } else {
            printf("Errore nella lettura di una prenotazione dal file!\n");
            break;
        }
    }
    
    fclose(file);
    return 0;
}

/**
 * @brief Carica le prenotazioni nella coda globale.
 * @note Side Effect: Modifica la variabile globale coda_globale.
 */
void carica_prenotazioni() {
    // Se la coda esiste già, puliscila
    if (coda_globale != NULL) {
        pulisci_coda(coda_globale);
    } else {
        // Altrimenti creala
        coda_globale = inizializza_coda();
        if (coda_globale == NULL) {
            printf("Errore nell'inizializzazione della coda!\n");
            return;
        }
    }
    
    // Carica le prenotazioni dal file
    int result = carica_prenotazioni_da_file(coda_globale);
    if (result == 0) {
        printf("Prenotazioni caricate con successo.\n");
    } else if (result == -1) {
        printf("Nessuna prenotazione trovata nel file.\n");
    }
}

/**
 * @brief Resetta la coda di prenotazioni.
 * @param coda Puntatore alla coda da resettare.
 * @note Side Effect: Modifica lo stato interno della struttura coda.
 */
void pulisci_coda( CodaPrenotazioni coda) {
    if (coda == NULL) {
        return;
    }
    
    coda->dimensione = 0;
}

/**
 * @brief Libera la memoria della coda di prenotazioni.
 * @param coda Puntatore alla coda da distruggere.
 * @note Side Effect: Deallocazione della memoria associata alla struttura CodaPrenotazioni e al suo campo heap.
 */
void distruggi_coda( CodaPrenotazioni coda) {
    if (coda == NULL) {
        return;
    }
    
    free(coda->heap);
    free(coda);
}

/**
 * @brief Aggiorna le priorità delle prenotazioni attive.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @note Side Effect: Modifica il campo priorita delle prenotazioni e riorganizza l'heap.
 */
void aggiorna_priorita_prenotazioni( CodaPrenotazioni coda) {
    if (coda == NULL) return;
    
    // Aggiorna la priorità di tutte le prenotazioni in base alla data di sistema
    for (int i = 0; i < coda->dimensione; i++) {
        if (coda->heap[i].stato != 0 && coda->heap[i].stato != 2) {
            coda->heap[i].priorita = calcola_priorita_temporale(coda->heap[i].giorno_ora_inizio);
        }
    }
    
    // Riorganizza l'heap dopo l'aggiornamento delle priorità
    for (int i = coda->dimensione / 2 - 1; i >= 0; i--) {
        bubble_down(coda, i);
    }
}

/**
 * @brief Rimuove le prenotazioni scadute dalla coda.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @note Side Effect: Modifica il campo stato delle prenotazioni scadute.
 */
void rimuovi_prenotazioni_scadute(CodaPrenotazioni coda) {
    if (coda == NULL) return;
    
    
    int timestamp_corrente = converti_in_timestamp(ottieni_giorno_corrente(), ottieni_ora_corrente());
    
    for (int i = 0; i < coda->dimensione; i++) {
        Prenotazione p = &coda->heap[i];

        if (p->giorno_ora_fine < timestamp_corrente && p->stato != 2 && p->stato != 3) {
            p->stato = 2;

            list veicoli = ottieni_lista_veicoli();
            Veicolo v = cerca_veicolo(veicoli, p->id_veicolo);
            if (v != NULL) {
                // Aggiorna la posizione del veicolo alla posizione di riconsegna
                imposta_posizione_veicolo(v, p->posizione_riconsegna);
            }
        }
    }
}

/**
 * @brief Verifica la validità di un intervallo di prenotazione rispetto alla data di sistema.
 * @param giorno_ora_inizio Timestamp di inizio prenotazione.
 * @param giorno_ora_fine Timestamp di fine prenotazione.
 * @return -1 se la data di inizio è nel passato, -2 se la data di fine è precedente o uguale alla data di inizio, 0 se valida.
 */
int valida_data_prenotazione(int giorno_ora_inizio, int giorno_ora_fine) {
    int timestamp_corrente = converti_in_timestamp(ottieni_giorno_corrente(), ottieni_ora_corrente());
    
    // Controlla se la data di inizio è nel passato rispetto alla data sistema
    if (giorno_ora_inizio < timestamp_corrente) {
        return -1;  // Data nel passato
    }
    
    // Controlla se la data di fine è prima della data di inizio
    if (giorno_ora_fine <= giorno_ora_inizio) {
        return -2;  // Date non valide
    }
     // Controlla se la data di inizio è nello stesso giorno della data di sistema
    int giorno_inizio = estrai_giorno(giorno_ora_inizio);
    int ora_inizio = estrai_ora(giorno_ora_inizio);
    int giorno_corrente = ottieni_giorno_corrente();
    int ora_corrente = ottieni_ora_corrente();
    
    if (giorno_inizio == giorno_corrente && ora_inizio < ora_corrente) {
        return -1;  // Data nel passato (stesso giorno ma ora precedente)
    }
    
    return 0;  // Date valide
}

/**
 * @brief Verifica sovrapposizioni di prenotazioni per un veicolo.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param id_veicolo ID del veicolo da verificare.
 * @param giorno_ora_inizio Timestamp di inizio prenotazione.
 * @param giorno_ora_fine Timestamp di fine prenotazione.
 * @return -1 se la coda è nulla, 1 se esiste una sovrapposizione, 0 altrimenti.
 */
int verifica_sovrapposizioni( CodaPrenotazioni coda, int id_veicolo, int giorno_ora_inizio, int giorno_ora_fine) {
    if (coda == NULL) return -1;
    
    for (int i = 0; i < coda->dimensione; i++) {
         struct Prenotazione p = coda->heap[i];
        
        // Ignora le prenotazioni cancellate o completate
        if (p.stato == 3 || p.stato == 2) continue;
        
        // Ignora le prenotazioni di altri veicoli
        if (p.id_veicolo != id_veicolo) continue;
        
        // Verifica sovrapposizione
        if ((giorno_ora_inizio >= p.giorno_ora_inizio && giorno_ora_inizio < p.giorno_ora_fine) ||
            (giorno_ora_fine > p.giorno_ora_inizio && giorno_ora_fine <= p.giorno_ora_fine) ||
            (giorno_ora_inizio <= p.giorno_ora_inizio && giorno_ora_fine >= p.giorno_ora_fine)) {
            return 1;  // Sovrapposizione trovata
        }
    }
    
    return 0;  // Nessuna sovrapposizione
}

/**
 * @brief Conta le prenotazioni completate di un utente.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param id_utente ID dell'utente.
 * @return Numero di prenotazioni completate dall'utente.
 */
int conta_prenotazioni_completate(CodaPrenotazioni coda, int id_utente) {
    if (coda == NULL) {
        return 0;
    }
    
    int conteggio = 0;
    for (int i = 0; i < coda->dimensione; i++) {
        if (coda->heap[i].id_utente == id_utente && coda->heap[i].stato == 2) {
            conteggio++;
        }
    }
    return conteggio;
}

/**
 * @brief Restituisce l'ID della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return ID della prenotazione, oppure -1 se p è NULL.
 */
int ottieni_id_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;
    return p->id_prenotazione;
}

/**
 * @brief Restituisce l'ID dell'utente associato alla prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return ID dell'utente, oppure -1 se p è NULL.
 */
int ottieni_id_utente_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;
    return p->id_utente;
}

/**
 * @brief Restituisce l'ID del veicolo associato alla prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return ID del veicolo, oppure -1 se p è NULL.
 */
int ottieni_id_veicolo_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;
    return p->id_veicolo;
}

/**
 * @brief Restituisce il timestamp di inizio della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Timestamp di inizio, oppure -1 se p è NULL.
 */
int ottieni_giorno_ora_inizio(Prenotazione p) {
    if (p == NULL) return -1;
    return p->giorno_ora_inizio;
}

/**
 * @brief Restituisce il timestamp di fine della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Timestamp di fine, oppure -1 se p è NULL.
 */
int ottieni_giorno_ora_fine(Prenotazione p) {
    if (p == NULL) return -1;
    return p->giorno_ora_fine;
}

/**
 * @brief Restituisce lo stato della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Stato della prenotazione, oppure -1 se p è NULL.
 */
int ottieni_stato_prenotazione(Prenotazione p) {
    if (p == NULL) return -1;
    return p->stato;
}

/**
 * @brief Restituisce la priorità della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Priorità, oppure -1 se p è NULL.
 */
int ottieni_priorita(Prenotazione p) {
    if (p == NULL) return -1;
    return p->priorita;
}

/**
 * @brief Restituisce il giorno di inizio della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Giorno di inizio (0-6), oppure -1 se p è NULL.
 */
int ottieni_giorno_inizio(Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_giorno(p->giorno_ora_inizio);
}

/**
 * @brief Restituisce l'ora di inizio della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Ora di inizio (0-23), oppure -1 se p è NULL.
 */
int ottieni_ora_inizio(Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_ora(p->giorno_ora_inizio);
}

/**
 * @brief Restituisce il giorno di fine della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Giorno di fine (0-6), oppure -1 se p è NULL.
 */
int ottieni_giorno_fine(Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_giorno(p->giorno_ora_fine);
}

/**
 * @brief Restituisce l'ora di fine della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Ora di fine (0-23), oppure -1 se p è NULL.
 */
int ottieni_ora_fine(Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_ora(p->giorno_ora_fine);
}

/**
 * @brief Restituisce la posizione di riconsegna della prenotazione.
 * @param p Puntatore alla prenotazione.
 * @return Posizione di riconsegna, oppure -1 se p è NULL.
 */
int ottieni_posizione_riconsegna(Prenotazione p) {
    if (p == NULL) return -1;
    return p->posizione_riconsegna;
}

/**
 * @brief Restituisce la dimensione attuale della coda.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @return Dimensione attuale, oppure -1 se coda è NULL.
 */
int ottieni_dimensione_coda(CodaPrenotazioni coda) {
    if (coda == NULL) return -1;
    return coda->dimensione;
}

/**
 * @brief Imposta l'ID della prenotazione.
 * @param id_prenotazione Nuovo ID.
 * @param p Puntatore alla prenotazione.
 */
void imposta_id_prenotazione(int id_prenotazione, Prenotazione p) {
    if (p == NULL) return;
    p->id_prenotazione = id_prenotazione;
}

/**
 * @brief Imposta lo stato della prenotazione.
 * @param stato Nuovo stato.
 * @param p Puntatore alla prenotazione.
 */
void imposta_stato_prenotazione(int stato, Prenotazione p) {
    if (p == NULL) return;
    p->stato = stato;
}


/**
 * @brief Restituisce il puntatore alla prenotazione in posizione i nella coda.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param i Indice della prenotazione.
 * @return Puntatore alla prenotazione, oppure NULL se indice non valido o coda NULL.
 */
Prenotazione ottieni_prenotazione_in_coda(CodaPrenotazioni coda, int i) {
    if (coda == NULL || i < 0 || i >= coda->dimensione) {
        return NULL;
    }
    return &coda->heap[i];
}

/**
 * @brief Conta le prenotazioni completate di un utente prima di una certa prenotazione.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param id_utente ID dell'utente.
 * @param id_prenotazione_corrente ID della prenotazione di riferimento.
 * @return Numero di prenotazioni completate prima di quella specificata.
 */
int conta_prenotazioni_completate_prima_di(CodaPrenotazioni coda, int id_utente, int id_prenotazione_corrente) {
    if (coda == NULL) return 0;
    int conteggio = 0;
    for (int i = 0; i < coda->dimensione; i++) {
        Prenotazione p = &coda->heap[i];
        if (p->id_utente == id_utente && p->stato == 2 && p->id_prenotazione < id_prenotazione_corrente) {
            conteggio++;
        }
    }
    return conteggio;
}

/**
 * @brief Rimuove tutte le prenotazioni di un utente dalla coda.
 * @param coda Puntatore alla coda delle prenotazioni.
 * @param id_utente ID dell'utente le cui prenotazioni devono essere rimosse.
 * @note Side Effect: Modifica la struttura della coda.
 */
void rimuovi_prenotazioni_utente(CodaPrenotazioni coda, int id_utente) {
    if (coda == NULL) return;
    for (int i = 0; i < coda->dimensione; ) {
        if (coda->heap[i].id_utente == id_utente) {
            // Rimuovi la prenotazione (sposta l'ultima qui e riduci la dimensione)
            coda->heap[i] = coda->heap[coda->dimensione - 1];
            coda->dimensione--;
            // Mantieni la proprietà dell'heap
            bubble_down(coda, i);
        } else {
            i++;
        }
    }
}
