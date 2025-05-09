#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stati possibili di una prenotazione
typedef enum {
    IN_ATTESA,
    CONFERMATA,
    COMPLETATA,
    CANCELLATA
} StatoPrenotazione;

// Struttura per rappresentare una prenotazione
typedef struct {
    int id_prenotazione;
    int id_utente;
    int id_veicolo;
    int giorno_settimana;  // 0-6 (Lun-Dom)
    int ora_inizio;        // 0-23
    int ora_fine;          // 0-23
    StatoPrenotazione stato;
    int priorita;          // Campo per la priorità (più basso = più prioritario)
} Prenotazione;

// Struttura della coda con priorità
typedef struct {
    Prenotazione* heap;    // Array dinamico per l'heap
    int capacita;          // Capacità massima dell'array
    int dimensione;        // Numero di elementi attuali
} CodaPrenotazioni;

// Funzioni di utilità per l'heap
#define GENITORE(i) ((i - 1) / 2)
#define FIGLIO_SINISTRO(i) (2 * i + 1)
#define FIGLIO_DESTRO(i) (2 * i + 2)

// Funzione per inizializzare una nuova coda
CodaPrenotazioni* inizializza_coda() {
    CodaPrenotazioni* coda = (CodaPrenotazioni*)malloc(sizeof(CodaPrenotazioni));
    if (coda == NULL) {
        return NULL;
    }
    
    coda->capacita = 10;  // Capacità iniziale
    coda->dimensione = 0;
    coda->heap = (Prenotazione*)malloc(sizeof(Prenotazione) * coda->capacita);
    
    if (coda->heap == NULL) {
        free(coda);
        return NULL;
    }
    
    return coda;
}

// Funzione per scambiare due prenotazioni
void scambia_prenotazioni(Prenotazione* a, Prenotazione* b) {
    Prenotazione temp = *a;
    *a = *b;
    *b = temp;
}

// Funzione per fare bubble up nell'heap
void bubble_up(CodaPrenotazioni* coda, int index) {
    while (index > 0 && coda->heap[GENITORE(index)].priorita > coda->heap[index].priorita) {
        scambia_prenotazioni(&coda->heap[GENITORE(index)], &coda->heap[index]);
        index = GENITORE(index);
    }
}

// Funzione per fare bubble down nell'heap
void bubble_down(CodaPrenotazioni* coda, int index) {
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

// Funzione per verificare se una fascia oraria è valida
int verifica_fascia_oraria(int giorno, int ora_inizio, int ora_fine) {
    if (giorno < 0 || giorno > 6) return 0;
    if (ora_inizio < 0 || ora_inizio > 23) return 0;
    if (ora_fine < 0 || ora_fine > 23) return 0;
    if (ora_inizio >= ora_fine) return 0;
    return 1;
}

// Funzione per creare una nuova prenotazione
Prenotazione crea_prenotazione(int id_utente, int id_veicolo, int giorno, int ora_inizio, int ora_fine, int priorita) {
    static int id_counter = 1;
    
    Prenotazione nuova;
    nuova.id_prenotazione = id_counter++;
    nuova.id_utente = id_utente;
    nuova.id_veicolo = id_veicolo;
    nuova.giorno_settimana = giorno;
    nuova.ora_inizio = ora_inizio;
    nuova.ora_fine = ora_fine;
    nuova.stato = IN_ATTESA;
    nuova.priorita = priorita;
    
    return nuova;
}

// Funzione per aggiungere una prenotazione alla coda
int aggiungi_prenotazione(CodaPrenotazioni* coda, Prenotazione prenotazione) {
    if (coda == NULL) {
        return -1;
    }
    
    // Verifica la validità della fascia oraria
    if (!verifica_fascia_oraria(prenotazione.giorno_settimana, 
                              prenotazione.ora_inizio, 
                              prenotazione.ora_fine)) {
        return -2;
    }
    
    // Se necessario, ridimensiona l'array
    if (coda->dimensione >= coda->capacita) {
        int nuova_capacita = coda->capacita * 2;
        Prenotazione* nuovo_heap = (Prenotazione*)realloc(coda->heap, 
                                                        sizeof(Prenotazione) * nuova_capacita);
        if (nuovo_heap == NULL) {
            return -1;
        }
        coda->heap = nuovo_heap;
        coda->capacita = nuova_capacita;
    }
    
    // Inserisci la nuova prenotazione alla fine dell'heap
    coda->heap[coda->dimensione] = prenotazione;
    bubble_up(coda, coda->dimensione);
    coda->dimensione++;
    
    return 0;
}

// Funzione per rimuovere la prenotazione con priorità più alta
Prenotazione rimuovi_prenotazione(CodaPrenotazioni* coda) {
    Prenotazione prenotazione_vuota = {0};
    
    if (coda == NULL || coda->dimensione == 0) {
        return prenotazione_vuota;
    }
    
    Prenotazione prenotazione = coda->heap[0];
    coda->heap[0] = coda->heap[coda->dimensione - 1];
    coda->dimensione--;
    
    if (coda->dimensione > 0) {
        bubble_down(coda, 0);
    }
    
    return prenotazione;
}

// Funzione per cercare una prenotazione per ID
Prenotazione* cerca_prenotazione(CodaPrenotazioni* coda, int id_prenotazione) {
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
Prenotazione* cerca_prenotazione_per_orario(CodaPrenotazioni* coda, int giorno, int ora) {
    if (coda == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < coda->dimensione; i++) {
        if (coda->heap[i].giorno_settimana == giorno &&
            coda->heap[i].ora_inizio <= ora &&
            coda->heap[i].ora_fine > ora) {
            return &coda->heap[i];
        }
    }
    
    return NULL;
}

// Funzione per modificare lo stato di una prenotazione
int modifica_stato_prenotazione(CodaPrenotazioni* coda, int id_prenotazione, StatoPrenotazione nuovo_stato) {
    Prenotazione* prenotazione = cerca_prenotazione(coda, id_prenotazione);
    if (prenotazione == NULL) {
        return -1;
    }
    
    prenotazione->stato = nuovo_stato;
    return 0;
}
// Funzione per stampare una prenotazione
void stampa_prenotazione(Prenotazione prenotazione) {
    printf("ID Prenotazione: %d\n", prenotazione.id_prenotazione);
    printf("ID Utente: %d\n", prenotazione.id_utente);
    printf("ID Veicolo: %d\n", prenotazione.id_veicolo);
    printf("Giorno della settimana: %d\n", prenotazione.giorno_settimana);
    printf("Ora inizio: %d\n", prenotazione.ora_inizio);
    printf("Ora fine: %d\n", prenotazione.ora_fine);
    if (prenotazione.stato == IN_ATTESA) {
        printf("Stato: In attesa\n");
    } else if (prenotazione.stato == CONFERMATA) {
        printf("Stato: Confermata\n");
    } else if (prenotazione.stato == COMPLETATA) {
        printf("Stato: Completata\n");
    } else if (prenotazione.stato == CANCELLATA) {
        printf("Stato: Cancellata\n");
    }
    printf("Priorità: %d\n", prenotazione.priorita);
}

//Funzione per salvare la coda in un file
void salvaPrenotazioniSuFile(CodaPrenotazioni* coda){
    FILE* file = fopen("prenotazioni.txt", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file per la scrittura!\n");
        return;
    }
    
    for (int i = 0; i < coda->dimensione; i++) {
        fprintf(file, "%d %d %d %d %d %d %d %d\n",
                coda->heap[i].id_prenotazione,
                coda->heap[i].id_utente,
                coda->heap[i].id_veicolo,
                coda->heap[i].giorno_settimana,
                coda->heap[i].ora_inizio,
                coda->heap[i].ora_fine,
                coda->heap[i].stato,
                coda->heap[i].priorita);
    }
    
    fclose(file);
}

// Funzione per caricare le prenotazioni da un file
void caricaPrenotazioniDaFile(CodaPrenotazioni* coda) {
    if (coda == NULL) {
        printf("Errore: coda non inizializzata!\n");
        return;
    }

    FILE* file = fopen("prenotazioni.txt", "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file per la lettura!\n");
        return;
    }
    
    int stato_temp;
    while (!feof(file)) {
        Prenotazione prenotazione;
        if (fscanf(file, "%d %d %d %d %d %d %d %d\n",
               &prenotazione.id_prenotazione,
               &prenotazione.id_utente,
               &prenotazione.id_veicolo,
               &prenotazione.giorno_settimana,
               &prenotazione.ora_inizio,
               &prenotazione.ora_fine,
               &stato_temp,
               &prenotazione.priorita) == 8) {
            
            prenotazione.stato = (StatoPrenotazione)stato_temp;
            if (aggiungi_prenotazione(coda, prenotazione) != 0) {
                printf("Errore nell'aggiunta della prenotazione %d!\n", prenotazione.id_prenotazione);
            }
        } else {
            printf("Errore nella lettura di una prenotazione dal file!\n");
            break;
        }
    }
    
    fclose(file);
}

// Funzione per pulire la coda
void pulisci_coda(CodaPrenotazioni* coda) {
    if (coda == NULL) {
        return;
    }
    
    coda->dimensione = 0;
}

// Funzione per liberare la memoria della coda
void distruggi_coda(CodaPrenotazioni* coda) {
    if (coda == NULL) {
        return;
    }
    
    free(coda->heap);
    free(coda);
}
