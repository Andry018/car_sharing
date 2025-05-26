#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "prenotazioni.h"
#include "data_sistema.h"
#include "f_utili.h"

// Stati possibili di una prenotazione


// Struttura per rappresentare una prenotazione
struct Prenotazione {
    int id_prenotazione;
    int id_utente;
    int id_veicolo;
    int giorno_ora_inizio;  // Formato: giorno*24*60 + ora*60 
    int giorno_ora_fine;    // Formato: giorno*24*60 + ora*60 
    int stato;              //0: In attesa, 1: Confermata, 2: Completata, 3: Cancellata
    int priorita;          // Campo per la priorità (più basso = più prioritario)
} ;

// Struttura della coda con priorità
 struct CodaPrenotazioni {
    struct Prenotazione *heap;    // Array dinamico per l'heap
    int capacita;          // Capacità massima dell'array
    int dimensione;        // Numero di elementi attuali
};  

// Funzioni di utilità per l'heap
#define GENITORE(i) ((i - 1) / 2)
#define FIGLIO_SINISTRO(i) (2 * i + 1)
#define FIGLIO_DESTRO(i) (2 * i + 2)

// Variabile globale per la coda delle prenotazioni
static struct CodaPrenotazioni *coda_globale = NULL;

// Contatore globale per gli ID delle prenotazioni
static int id_counter = 0;

// Funzione per ottenere la coda globale
CodaPrenotazioni get_coda_prenotazioni() {
    return coda_globale;
}

// Funzione per inizializzare una nuova coda
 CodaPrenotazioni inizializza_coda() {
     CodaPrenotazioni coda =(CodaPrenotazioni) malloc(sizeof(CodaPrenotazioni));
    if (coda == NULL) {
        return NULL;
    }
    
    coda->capacita = 10;  // Capacità iniziale
    coda->dimensione = 0;
    coda->heap = ( Prenotazione)malloc(sizeof(Prenotazione) * coda->capacita);
    
    if (coda->heap == NULL) {
        free(coda);
        return NULL;
    }
    
    return coda;
}

// Funzione per scambiare due prenotazioni
void scambia_prenotazioni( struct Prenotazione* a,struct Prenotazione* b) {
    struct Prenotazione temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione per fare bubble up nell'heap
void bubble_up( CodaPrenotazioni coda, int index) {
    while (index > 0 && coda->heap[GENITORE(index)].priorita > coda->heap[index].priorita) {
        scambia_prenotazioni(&coda->heap[GENITORE(index)], &coda->heap[index]);
        index = GENITORE(index);
    }
}

// Funzione per fare bubble down nell'heap
void bubble_down( CodaPrenotazioni coda, int index) {
    int min_index = index;
    int left = FIGLIO_SINISTRO(index);
    int right = FIGLIO_DESTRO(index);
    
    if (left < coda->dimensione && coda->heap[left].priorita < coda->heap[min_index].priorita) {
        min_index = left;
    }
    
    if (right < coda->dimensione && coda->heap[right].priorita < coda->heap[min_index].priorita) {
        min_index = right;
    }
    
    if (min_index != index) {
        scambia_prenotazioni(&coda->heap[index], &coda->heap[min_index]);
        bubble_down(coda, min_index);
    }
}

// Funzione per convertire giorno e ora in un singolo valore
int converti_in_timestamp(int giorno, int ora) {
    return giorno * 24 + ora;
}

// Funzione per estrarre giorno da timestamp
int estrai_giorno(int timestamp) {
    return timestamp / 24;
}

// Funzione per estrarre ora da timestamp
int estrai_ora(int timestamp) {
    return timestamp % 24;
}

// Funzione per verificare se una fascia oraria è valida
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

// Funzione per creare una nuova prenotazione
 Prenotazione crea_prenotazione(int id_utente, int id_veicolo, 
                                     int giorno_inizio, int ora_inizio,
                                     int giorno_fine, int ora_fine, 
                                     int priorita) {
     Prenotazione nuova = ( Prenotazione)malloc(sizeof( Prenotazione));
    if (nuova == NULL) {
        return NULL;
    }
    
    nuova->id_prenotazione = ++id_counter;
    nuova->id_utente = id_utente;
    nuova->id_veicolo = id_veicolo;
    nuova->giorno_ora_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    nuova->giorno_ora_fine = converti_in_timestamp(giorno_fine, ora_fine);
    nuova->stato = 0;  // In attesa
    
    if (priorita < 0) {
        // Se non è specificata una priorità, la calcoliamo in base al tempo
        nuova->priorita = calcola_priorita_temporale(nuova->giorno_ora_inizio);
    } else {
        nuova->priorita = priorita;
    }
    
    return nuova;
}

// Funzione per aggiungere una prenotazione alla coda
int aggiungi_prenotazione( CodaPrenotazioni coda,  Prenotazione prenotazione) {
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
    
    // Se necessario, ridimensiona l'array
    if (coda->dimensione >= coda->capacita) {
        int nuova_capacita = coda->capacita * 2;
         Prenotazione nuovo_heap = ( Prenotazione)realloc(coda->heap, 
                                                        sizeof( Prenotazione) * nuova_capacita);
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

// Funzione per rimuovere la prenotazione con priorità più alta
 Prenotazione rimuovi_prenotazione( CodaPrenotazioni coda) {
     Prenotazione prenotazione_vuota = {0};
    
    if (coda == NULL || coda->dimensione == 0) {
        return prenotazione_vuota;
    }
    
     Prenotazione prenotazione = &coda->heap[0];
    coda->heap[0] = coda->heap[coda->dimensione - 1];
    coda->dimensione--;
    
    if (coda->dimensione > 0) {
        bubble_down(coda, 0);
    }
    
    return prenotazione;
}

// Funzione per cercare una prenotazione per ID
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

// Funzione per cercare prenotazioni per giorno e ora
 Prenotazione cerca_prenotazione_per_orario( CodaPrenotazioni coda, int giorno, int ora) {
    if (coda == NULL) {
        return NULL;
    }
    
    int timestamp = converti_in_timestamp(giorno, ora);
    
    for (int i = 0; i < coda->dimensione; i++) {
        if (coda->heap[i].giorno_ora_inizio <= timestamp &&
            coda->heap[i].giorno_ora_fine > timestamp) {
            return &coda->heap[i];
        }
    }
    
    return NULL;
}

// Funzione per modificare lo stato di una prenotazione
int modifica_stato_prenotazione( CodaPrenotazioni coda, int id_prenotazione, int nuovo_stato) {
     Prenotazione prenotazione = cerca_prenotazione(coda, id_prenotazione);
    if (prenotazione == NULL) {
        return -1;
    }
    
    prenotazione->stato = nuovo_stato;
    return 0;
}

// Funzione per stampare una prenotazione
void stampa_prenotazione(Prenotazione p) {
    const char* stati[] = {"In attesa", "Confermata", "Completata", "Cancellata"};
    
    printf("  ID Prenotazione: %d\n", get_id_prenotazione(p));
    printf("  ID Utente: %d\n",get_id_utente_prenotazione(p));
    printf("  ID Veicolo: %d\n",get_id_veicolo_prenotazione(p));
    printf("  Inizio: %s ore %02d:00\n", 
           get_nome_giorno(get_giorno_inizio(p)), 
           get_ora_inizio(p));
    printf("  Fine: %s ore %02d:00\n", 
           get_nome_giorno(get_giorno_fine(p)), 
          get_ora_fine(p));
    
    printf("  Stato: ");
    switch(get_stato_prenotazione(p)) {
        case 0:
            set_color(14);  // Giallo per prenotazioni in attesa
            break;
        case 1:
            set_color(10);  // Verde per prenotazioni confermate
            break;
        case 2:
            set_color(11);  // Ciano per prenotazioni completate
            break;
        case 3:
            set_color(12);  // Rosso per prenotazioni cancellate
            break;
    }
    printf("%s\n", stati[get_stato_prenotazione(p)]);
    set_color(7);  // Bianco
}

// Funzione per salvare la coda in un file
void salva_prenotazioni_su_file( CodaPrenotazioni coda) {
    FILE* file = fopen("data/prenotazioni.txt", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file per la scrittura!\n");
        return;
    }
    
    for (int i = 0; i < coda->dimensione; i++) {
        fprintf(file, "%d %d %d %d %d %d %d\n",
                coda->heap[i].id_prenotazione,
                coda->heap[i].id_utente,
                coda->heap[i].id_veicolo,
                coda->heap[i].giorno_ora_inizio,
                coda->heap[i].giorno_ora_fine,
                coda->heap[i].stato,
                coda->heap[i].priorita);
    }
    
    fclose(file);
}

// Funzione per caricare le prenotazioni da un file
int carica_prenotazioni_da_file( CodaPrenotazioni coda) {
    if (coda == NULL) {
        printf("Errore: coda non inizializzata!\n");
        return -1;
    }

    FILE* file = fopen("data/prenotazioni.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file per la lettura!\n");
        return -1;
    }
    
    int stato_temp;
    while (!feof(file)) {
         struct Prenotazione prenotazione;
        if (fscanf(file, "%d %d %d %d %d %d %d\n",
               &prenotazione.id_prenotazione,
               &prenotazione.id_utente,
               &prenotazione.id_veicolo,
               &prenotazione.giorno_ora_inizio,
               &prenotazione.giorno_ora_fine,
               &stato_temp,
               &prenotazione.priorita) == 7) {
            
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
    if (carica_prenotazioni_da_file(coda_globale) == 0) {
        printf("Prenotazioni caricate con successo.\n");
    }
}

// Funzione per pulire la coda
void pulisci_coda( CodaPrenotazioni coda) {
    if (coda == NULL) {
        return;
    }
    
    coda->dimensione = 0;
}

// Funzione per liberare la memoria della coda
void distruggi_coda( CodaPrenotazioni coda) {
    if (coda == NULL) {
        return;
    }
    
    free(coda->heap);
    free(coda);
}

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

void rimuovi_prenotazioni_scadute( CodaPrenotazioni coda) {
    if (coda == NULL) return;
    
    
    int timestamp_corrente = converti_in_timestamp(get_giorno_corrente(), get_ora_corrente());
    
    for (int i = 0; i < coda->dimensione; i++) {
        if (coda->heap[i].giorno_ora_fine < timestamp_corrente && 
            coda->heap[i].stato != 2 && 
            coda->heap[i].stato != 3) {
            coda->heap[i].stato = 2;
        }
    }
}

void stampa_data_sistema() {
    DataSistema data = get_data_sistema();
    const char* giorni[] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi", "Sabato", "Domenica"};
    
    printf("  %s, ore %02d:00\n", 
           giorni[get_giorno_sistema(data)], 
           get_ora_sistema(data));
}

int valida_data_prenotazione(int giorno_ora_inizio, int giorno_ora_fine) {
   
    int timestamp_corrente = converti_in_timestamp(get_giorno_corrente(), get_ora_corrente());
    
    // Controlla se la data di inizio è nel passato
    if (giorno_ora_inizio < timestamp_corrente) {
        return -1;  // Data nel passato
    }
    
    // Controlla se la data di fine è prima della data di inizio
    if (giorno_ora_fine <= giorno_ora_inizio) {
        return -2;  // Date non valide
    }
    
    return 0;  // Date valide
}

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

// Funzione per contare le prenotazioni completate di un utente
int conta_prenotazioni_completate( CodaPrenotazioni coda, int id_utente) {
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

// Getter functions for Prenotazione struct fields
int get_id_prenotazione( Prenotazione p) {
    if (p == NULL) return -1;
    return p->id_prenotazione;
}

int get_id_utente_prenotazione( Prenotazione p) {
    if (p == NULL) return -1;
    return p->id_utente;
}

int get_id_veicolo_prenotazione( Prenotazione p) {
    if (p == NULL) return -1;
    return p->id_veicolo;
}

int get_giorno_ora_inizio( Prenotazione p) {
    if (p == NULL) return -1;
    return p->giorno_ora_inizio;
}

int get_giorno_ora_fine( Prenotazione p) {
    if (p == NULL) return -1;
    return p->giorno_ora_fine;
}

int get_stato_prenotazione( Prenotazione p) {
    if (p == NULL) return -1;
    return p->stato;
}

int get_priorita( Prenotazione p) {
    if (p == NULL) return -1;
    return p->priorita;
}

// Helper functions to get specific time components
int get_giorno_inizio( Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_giorno(p->giorno_ora_inizio);
}

int get_ora_inizio( Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_ora(p->giorno_ora_inizio);
}

int get_giorno_fine( Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_giorno(p->giorno_ora_fine);
}

int get_ora_fine( Prenotazione p) {
    if (p == NULL) return -1;
    return estrai_ora(p->giorno_ora_fine);
}

 Prenotazione get_heap_coda( CodaPrenotazioni coda) {
    if (coda == NULL) return NULL;
    return coda->heap;
}

int get_capacita_coda( CodaPrenotazioni coda) {
    if (coda == NULL) return -1;
    return coda->capacita;
}

int get_dimensione_coda( CodaPrenotazioni coda) {
    if (coda == NULL) return -1;
    return coda->dimensione;
}

void set_id_prenotazione(int id_prenotazione,  Prenotazione p) {
    if (p == NULL) return;
    p->id_prenotazione = id_prenotazione;
}

void set_id_utente_prenotazione(int id_utente,  Prenotazione p) {
    if (p == NULL) return;
    p->id_utente = id_utente;
}

void set_id_veicolo_prenotazione(int id_veicolo,  Prenotazione p) {
    if (p == NULL) return;
    p->id_veicolo = id_veicolo;
}

void set_giorno_ora_inizio(int giorno_ora_inizio,  Prenotazione p) {
    if (p == NULL) return;
    p->giorno_ora_inizio = giorno_ora_inizio;
}

void set_giorno_ora_fine(int giorno_ora_fine,  Prenotazione p) {
    if (p == NULL) return;
    p->giorno_ora_fine = giorno_ora_fine;
}

void set_stato_prenotazione(int stato,  Prenotazione p) {
    if (p == NULL) return;
    p->stato = stato;
}

void set_priorita(int priorita,  Prenotazione p) {
    if (p == NULL) return;
    p->priorita = priorita;
}
