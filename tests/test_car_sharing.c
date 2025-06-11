#include <stdio.h>
#include <assert.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "tariffe.h"
#include "utenti.h"
#include "test_utils.h"
#include <string.h>
#include "fasce_orarie.h"
#include <stdbool.h>
#define M 64
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Definizione della struttura CodaPrenotazioni per i test
struct CodaPrenotazioni {
    Prenotazione prenotazione;
    struct CodaPrenotazioni* next;
};

// Variabili globali per i test
static list veicoli_test = NULL;
static CodaPrenotazioni coda_test = NULL;

// Contatore ID dedicato ai test
static int test_id_counter = 1;

// Funzione per inizializzare la coda di test
static void inizializza_coda_test() {
    if (coda_test != NULL) {
        pulisci_coda_test();
    }
    coda_test = NULL;  // Inizializza la coda come vuota
    // Reset del contatore ID dei test
    test_id_counter = 1;
}

// Funzione per inizializzare gli utenti di test
static void inizializza_utenti_test() {
    // Inizializza la tabella degli utenti
    inizializza_tabella_utenti();
    
    int id_utente = 1;
    // Crea alcuni utenti di test
    inserisci_utente("user1", "Utente Test 1", "password1");
    set_id_utente(id_utente,cerca_utente("user1"));
    id_utente++;
    inserisci_utente("user2", "Utente Test 2", "password2");
    set_id_utente(id_utente,cerca_utente("user2"));
    id_utente++;
    inserisci_utente("user3", "Utente Test 3", "password3");
    set_id_utente(id_utente,cerca_utente("user3"));
}

// Funzione per inizializzare la lista dei veicoli di test
static void inizializza_veicoli_test() {
    if (veicoli_test != NULL) {
        pulisci_lista_veicoli_test();
    }
    
    // Crea alcuni veicoli di test
    Veicolo v1 = crea_veicolo();
    if (v1) {
        set_id_veicolo(v1, 1);
        set_tipo_veicolo(v1, 0);
        set_modello_veicolo(v1, "Fiat 500");
        set_targa_veicolo(v1, "AB123CD");
        set_posizione_veicolo(v1, 0);
        set_disponibilita_veicolo(v1, 1);
        veicoli_test = aggiungi_veicolo_test(veicoli_test, v1);
    }
    
    Veicolo v2 = crea_veicolo();
    if (v2) {
        set_id_veicolo(v2, 2);
        set_tipo_veicolo(v2, 1);
        set_modello_veicolo(v2, "Jeep Renegade");
        set_targa_veicolo(v2, "EF456GH");
        set_posizione_veicolo(v2, 1);
        set_disponibilita_veicolo(v2, 1);
        veicoli_test = aggiungi_veicolo_test(veicoli_test, v2);
    }
}

// Funzione per ottenere la lista dei veicoli di test
list get_lista_veicoli_test(void) {
    return veicoli_test;
}

// Funzione per ottenere la coda di test
CodaPrenotazioni get_coda_test(void) {
    return coda_test;
}

// Prototipi delle funzioni di test
void test_creazione_veicoli(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_creazione_prenotazione(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_costo_noleggio(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_visualizza_disponibilita(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_storico_prenotazioni(const char* input_fname, const char* output_fname, const char* oracle_fname);
int compara_file(const char* file1, const char* file2);

/**
 * Esegue un singolo caso di test basato sul tipo di test specificato
 * @param tc_id: ID del test case
 * @param test_type: Tipo di test da eseguire
 * @return: 1 se il test passa, 0 se fallisce
 */
int run_test_case(const char* tc_id, const char* test_type) {
    char input_fname[100];
    char output_fname[100];
    char oracle_fname[100];
    
    // Costruisci i nomi dei file
    snprintf(input_fname, sizeof(input_fname), "tests/%s/%s_input.txt", tc_id, tc_id);
    snprintf(output_fname, sizeof(output_fname), "tests/%s/%s_output.txt", tc_id, tc_id);
    snprintf(oracle_fname, sizeof(oracle_fname), "tests/%s/%s_oracle.txt", tc_id, tc_id);
    
    // Esegui il test appropriato
    if (strcmp(test_type, "creazione_veicoli") == 0) {
        test_creazione_veicoli(input_fname, output_fname, oracle_fname);
    } else if (strcmp(test_type, "creazione_prenotazione") == 0) {
        test_creazione_prenotazione(input_fname, output_fname, oracle_fname);
    } else if (strcmp(test_type, "costo_noleggio") == 0) {
        test_costo_noleggio(input_fname, output_fname, oracle_fname);
    } else if (strcmp(test_type, "visualizza_disponibilita") == 0) {
        test_visualizza_disponibilita(input_fname, output_fname, oracle_fname);
    } else if (strcmp(test_type, "storico_prenotazioni") == 0) {
        test_storico_prenotazioni(input_fname, output_fname, oracle_fname);
    }
    
    // Confronta l'output con l'oracolo
    int result = compara_file(output_fname, oracle_fname);
    
    // Registra il risultato
    FILE* f = fopen("tests/risultati.txt", "a");
    if (f) {
        if (result == 0) {
            fprintf(f, "%s PASS\n", tc_id);
            printf(ANSI_COLOR_GREEN "%s PASS\n" ANSI_COLOR_RESET, tc_id);
        } else {
            fprintf(f, "%s FAIL\n", tc_id);
            printf(ANSI_COLOR_RED "%s FAIL\n" ANSI_COLOR_RESET, tc_id);
        }
        fclose(f);
    }
    
    return result;
}

/**
 * Legge le linee di input da un file di test
 * @param filename: Nome del file di input
 * @param lines: Array dove salvare le linee lette
 * @param max_lines: Numero massimo di linee da leggere
 * @return: Numero di linee effettivamente lette
 */
int leggi_input_test(const char* filename, char lines[][M], int max_lines) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    int count = 0;
    while (count < max_lines && fgets(lines[count], M, f)) {
        // Rimuovi newline finale
        lines[count][strcspn(lines[count], "\r\n")] = 0;
        count++;
    }
    fclose(f);
    return count;
}

/**
 * Esegue una suite completa di test
 * @param suite_file: File contenente la lista dei test da eseguire
 * @param result_file: File dove salvare i risultati
 */
void esegui_test_suite(const char* suite_file, const char* result_file) {
    printf("Apertura file test suite: %s\n", suite_file);
    FILE* suite = fopen(suite_file, "r");
    if (!suite) {
        printf("Errore apertura file test suite\n");
        return;
    }

    printf("Apertura file risultati: %s\n", result_file);
    FILE* result = fopen(result_file, "w");
    if (!result) {
        printf("Errore apertura file risultati\n");
        fclose(suite);
        return;
    }

    char tc_id[M], test_type[M];
    int total_tests = 0;
    int passed_tests = 0;

    // Legge e esegue ogni test case dalla suite
    while (fscanf(suite, "%s %s", tc_id, test_type) == 2) {
        total_tests++;
        int pass = run_test_case(tc_id, test_type);
        if (!pass) {
            passed_tests++;
        }
        printf("%s [%s]: %s\n", tc_id, test_type, pass ? "FAIL" : "PASS");
        fprintf(result, "%s - %s - %s\n", tc_id, test_type, pass ? "FAIL" : "PASS");
        fflush(result);  // Forza la scrittura su file
    }

    printf("Fine lettura test cases\n");
    // Stampa il riepilogo dei test
    printf("\nRiepilogo test:\n");
    printf("Totali: %d\n", total_tests);
    printf("Passati: %d\n", passed_tests);
    printf("Falliti: %d\n", total_tests - passed_tests);
    printf("Percentuale successo: %.2f%%\n", (float)passed_tests/total_tests * 100);

    // Salva il riepilogo nel file dei risultati
    fprintf(result, "\nRiepilogo test:\n");
    fprintf(result, "Totali: %d\n", total_tests);
    fprintf(result, "Passati: %d\n", passed_tests);
    fprintf(result, "Falliti: %d\n", total_tests - passed_tests);
    fprintf(result, "Percentuale successo: %.2f%%\n", (float)passed_tests/total_tests * 100);

    fclose(suite);
    fclose(result);
}

/**
 * Confronta due file byte per byte
 * @param file1: Primo file da confrontare
 * @param file2: Secondo file da confrontare
 * @return: 0 se i file sono identici, 1 se sono diversi
 */
int compara_file(const char* file1, const char* file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    
    if (!f1 || !f2) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return 1;
    }

    int result = 0;
    int c1, c2;
    
    do {
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        
        if (c1 != c2) {
            result = 1;
            break;
        }
    } while (c1 != EOF && c2 != EOF);

    // Verifica che entrambi i file siano finiti
    if (c1 != c2) {
        result = 1;
    }

    fclose(f1);
    fclose(f2);
    return result;
}

/**
 * Test per la creazione di una nuova prenotazione
 * Verifica che una prenotazione venga creata correttamente con i parametri specificati
 * Input atteso:
 * - id_utente
 * - id_veicolo
 * - giorno_inizio
 * - ora_inizio
 * - giorno_fine
 * - ora_fine
 * - priorita
 * - posizione_riconsegna
 */
void test_creazione_prenotazione(const char* input_fname, const char* output_fname, const char* oracle_fname) {
    printf("DEBUG: Inizio test_creazione_prenotazione\n");
    
    // Inizializza le strutture di test
    printf("DEBUG: Inizializzazione veicoli test\n");
    inizializza_veicoli_test();
    printf("DEBUG: Inizializzazione utenti test\n");
    inizializza_utenti_test();
    printf("DEBUG: Inizializzazione coda test\n");
    inizializza_coda_test();
    
    // Pulisci la coda delle prenotazioni di test
    printf("DEBUG: Pulizia coda test\n");
    if (get_coda_test() != NULL) {
        pulisci_coda_test();
    }
    
    printf("DEBUG: Lettura input test\n");
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    // Parsing dei parametri di input
    int id_utente = atoi(input[0]);      // id_utente (int)
    int id_veicolo = atoi(input[1]);     // id_veicolo(int)
    int giorno_inizio = atoi(input[2]);  // giorno_inizio (int, 0-6)
    int ora_inizio = atoi(input[3]);     // ora_inizio (int, 0-23)
    int giorno_fine = atoi(input[4]);    // giorno_fine (int, 0-6)
    int ora_fine = atoi(input[5]);       // ora_fine (int, 0-23)
    int priorita = atoi(input[6]);       // priorita (int, 0-2)
    int posizione_riconsegna = atoi(input[7]); // 0

    printf("DEBUG: Verifica utente %d\n", id_utente);
    // Verifica che l'utente esista
    Utente u = cerca_utente_per_id(id_utente);
    if (u == NULL) {
        printf(ANSI_COLOR_RED "DEBUG: Utente non trovato\n" ANSI_COLOR_RESET);
        FILE *f_output = fopen(output_fname, "w");
        if (f_output) fclose(f_output);
        return;
    }

    printf("DEBUG: Verifica veicolo %d\n", id_veicolo);
    // Verifica che il veicolo esista
    list veicoli = get_lista_veicoli_test();
    bool veicolo_trovato = false;
    while (veicoli != NULL) {
        Veicolo v = get_veicolo_senza_rimuovere(veicoli);
        if (v && get_id_veicolo(v) == id_veicolo) {
            veicolo_trovato = true;
            break;
        }
        veicoli = get_next_node(veicoli);
    }
    if (!veicolo_trovato) {
        printf(ANSI_COLOR_RED "DEBUG: Veicolo non trovato\n" ANSI_COLOR_RESET);
        FILE *f_output = fopen(output_fname, "w");
        if (f_output) fclose(f_output);
        return;
    }

    printf("DEBUG: Creazione prenotazione\n");
    // Creazione della prenotazione
    Prenotazione p = crea_prenotazione(id_utente, id_veicolo, giorno_inizio, 
                                       ora_inizio, giorno_fine, ora_fine, priorita, 
                                       posizione_riconsegna);
    
    if (p == NULL) {
        printf(ANSI_COLOR_RED "DEBUG: Creazione prenotazione fallita\n" ANSI_COLOR_RESET);
        FILE *f_output = fopen(output_fname, "w");
        if (f_output) fclose(f_output);
        return;
    }

    printf("DEBUG: Aggiunta prenotazione alla coda\n");
    // Aggiungi la prenotazione alla coda di test
    CodaPrenotazioni coda = get_coda_test();
    if (coda == NULL) {
        printf(ANSI_COLOR_RED "DEBUG: Coda test NULL\n" ANSI_COLOR_RESET);
        free(p);
        FILE *f_output = fopen(output_fname, "w");
        if (f_output) fclose(f_output);
        return;
    }

    if (aggiungi_prenotazione(coda, p) != 0) {
        printf(ANSI_COLOR_RED "DEBUG: Aggiunta prenotazione fallita\n" ANSI_COLOR_RESET);
        free(p);
        FILE *f_output = fopen(output_fname, "w");
        if (f_output) fclose(f_output);
        return;
    }
    
    printf("DEBUG: Scrittura risultati\n");
    // Scrittura dei risultati nel file di output
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf(ANSI_COLOR_RED "DEBUG: Errore apertura file output\n" ANSI_COLOR_RESET);
        free(p);
        return;
    }
    
    // Usa spazi invece di newline per separare i valori
    fprintf(f_output, "%d %d %d %d %d %d %d %d", 
            get_id_prenotazione(p), 
            get_id_utente_prenotazione(p), 
            get_id_veicolo_prenotazione(p), 
            get_giorno_ora_inizio(p), 
            get_giorno_ora_fine(p), 
            get_stato_prenotazione(p), 
            get_priorita(p), 
            get_posizione_riconsegna(p));
    
    fclose(f_output);
    free(p);
    printf(ANSI_COLOR_GREEN "DEBUG: Test completato con successo\n" ANSI_COLOR_RESET);
}

/**
 * Test per il calcolo del costo di noleggio
 * Verifica che il costo venga calcolato correttamente in base ai parametri
 * Input atteso:
 * - id_prenotazione
 * - id_veicolo
 * - giorno_inizio
 * - ora_inizio
 * - giorno_fine
 * - ora_fine
 */
void test_costo_noleggio(const char* input_fname, const char* output_fname, const char* oracle_fname){
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    // Parsing dei parametri di input
    int id_veicolo = atoi(input[1]);
    int giorno_inizio = atoi(input[2]);
    int ora_inizio = atoi(input[3]);
    int giorno_fine = atoi(input[4]);
    int ora_fine = atoi(input[5]);

    // Calcolo del costo
    int timestamp_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    int timestamp_fine = converti_in_timestamp(giorno_fine, ora_fine);
    double costo = calcola_tariffa_prenotazione(id_veicolo, timestamp_inizio, timestamp_fine);
   
    // Scrittura del risultato
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }
    
    fprintf(f_output, "%.2f\n", costo);
    
    fclose(f_output);

    // Verifica del risultato
    int cmp = compara_file(output_fname, oracle_fname);
    
    // Registrazione del risultato
    FILE* f = fopen("tests/risultati.txt", "a");
    if (f) {
        if (cmp == 0) {
            fprintf(f, "%s PASS\n", input_fname);
        } else {
            fprintf(f, "%s FAIL\n", input_fname);
        }
        fclose(f);
    }
}

/**
 * Test per la visualizzazione della disponibilità dei veicoli
 * Verifica che vengano correttamente identificati i veicoli disponibili
 * Input atteso:
 * - giorno
 * - ora
 */
void test_visualizza_disponibilita(const char* input_fname, const char* output_fname, const char* oracle_fname){
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    // Parsing dei parametri di input
    int giorno = atoi(input[0]);
    int ora = atoi(input[1]);

    // Ottieni la lista dei veicoli
    list veicoli = get_lista_veicoli_test();
    
    // Scrittura dei risultati
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    // Stampa dei veicoli disponibili
    list temp = veicoli;
    while (temp != NULL) {
        Veicolo v = get_veicolo_senza_rimuovere(temp);
        if (v) {
            // Inizializza il calendario per il veicolo
            CalendarioVeicolo calendario = inizializza_calendario(get_id_veicolo(v));
            if (calendario) {
                // Aggiorna il calendario con le prenotazioni esistenti
                CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, coda_test);
                
                // Verifica la disponibilità del veicolo nel momento specifico
                if (nuovo_calendario && verifica_disponibilita(nuovo_calendario, giorno, ora, giorno, ora + 1)) {
                    fprintf(f_output, "%d %s %s\n", 
                            get_id_veicolo(v), 
                            get_nome_tipo_veicolo(get_tipo_veicolo(v)), 
                            get_nome_posizione_veicolo(get_posizione_veicolo(v)));
                }
                
                // Libera la memoria del calendario
                free(nuovo_calendario);
                free(calendario);
            }
        } else {
            printf("Errore nell'ottenere il veicolo\n");
            return;
        }
        temp = get_next_node(temp);
    }

    fclose(f_output);

    // Verifica del risultato
    int cmp = compara_file(output_fname, oracle_fname);
    
    // Registrazione del risultato
    FILE* f = fopen("tests/risultati.txt", "a");
    if (f) {
        if (cmp == 0) {
            fprintf(f, "%s PASS\n", input_fname);
        } else {
            fprintf(f, "%s FAIL\n", input_fname);
        }
        fclose(f);
    }
    free(veicoli);
}

/**
 * Test per la visualizzazione dello storico prenotazioni
 * Verifica che vengano correttamente recuperate le prenotazioni di un utente
 * Input atteso:
 * - id_utente
 * - giorno_inizio
 * - ora_inizio
 * - giorno_fine
 * - ora_fine
 */
void test_storico_prenotazioni(const char* input_fname, const char* output_fname, const char* oracle_fname){
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    // Parsing dei parametri di input
    int id_utente = atoi(input[0]);
    int giorno_inizio = atoi(input[1]);
    int ora_inizio = atoi(input[2]);
    int giorno_fine = atoi(input[3]);
    int ora_fine = atoi(input[4]);
    
    // Scrittura dei risultati
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    // Stampa delle prenotazioni dell'utente nel periodo specificato
    int dimensione = get_dimensione_coda(coda_test);
    for (int i = 0; i < dimensione; i++) {
        Prenotazione p = get_prenotazione_in_coda(coda_test, i);
        if (p == NULL) {
            printf("Errore nell'ottenere la prenotazione in coda\n");
            return;
        }
        if (p && get_id_utente_prenotazione(p) == id_utente) {
            int giorno_p = estrai_giorno(get_giorno_ora_inizio(p));
            int ora_p = estrai_ora(get_giorno_ora_inizio(p));
            
            // Verifica se la prenotazione è nel periodo richiesto
            if ((giorno_p > giorno_inizio || (giorno_p == giorno_inizio && ora_p >= ora_inizio)) &&
                (giorno_p < giorno_fine || (giorno_p == giorno_fine && ora_p <= ora_fine))) {
                fprintf(f_output, "%d %d %d %d %d %d %d %d\n", 
                        get_id_prenotazione(p),
                        get_id_utente_prenotazione(p),
                        get_id_veicolo_prenotazione(p),
                        get_giorno_ora_inizio(p),
                        get_giorno_ora_fine(p),
                        get_stato_prenotazione(p),
                        get_priorita(p),
                        get_posizione_riconsegna(p));
            }
        }
    }

    fclose(f_output);

    // Verifica del risultato
    int cmp = compara_file(output_fname, oracle_fname);
    
    // Registrazione del risultato
    FILE* f = fopen("tests/risultati.txt", "a");
    if (f) {
        if (cmp == 0) {
            fprintf(f, "%s PASS\n", input_fname);
        } else {
            fprintf(f, "%s FAIL\n", input_fname);
        }
        fclose(f);
    }
}

void pulisci_lista_veicoli_test(void) {
    list current = veicoli_test;
    while (current != NULL) {
        list next = current->next;
        free(current->v);
        free(current);
        current = next;
    }
    veicoli_test = NULL;
}

void test_creazione_veicoli(const char* input_fname, const char* output_fname, const char* oracle_fname) {
    (void)oracle_fname; // Evita il warning del parametro non utilizzato
    
    // Pulisci la lista dei veicoli di test
    if (veicoli_test != NULL) {
        pulisci_lista_veicoli_test();
    }
    
    // Leggi il file di input
    FILE* f_input = fopen(input_fname, "r");
    if (!f_input) {
        return;
    }
    
    // Leggi ogni riga e crea un veicolo
    int id, tipo, posizione, disponibilita;
    char modello[50], targa[10];
    while (fscanf(f_input, "%d %d %s %s %d %d", &id, &tipo, modello, targa, &posizione, &disponibilita) == 6) {
        // Crea un nuovo veicolo
        Veicolo v = crea_veicolo();
        if (v) {
            // Inizializza i campi del veicolo
            set_id_veicolo(v, id);
            set_tipo_veicolo(v, tipo);
            set_modello_veicolo(v, modello);
            set_targa_veicolo(v, targa);
            set_posizione_veicolo(v, posizione);
            set_disponibilita_veicolo(v, disponibilita);
            
            // Aggiungi alla lista
            veicoli_test = aggiungi_veicolo_test(veicoli_test, v);
        }
    }
    fclose(f_input);
    
    // Scrivi i veicoli nel file di output
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        return;
    }
    
    // Stampa i veicoli
    list temp = veicoli_test;
    while (temp != NULL) {
        Veicolo v = get_veicolo_senza_rimuovere(temp);
        if (v) {
            fprintf(f_output, "%d %d %s %s %d %d\n",
                    get_id_veicolo(v),
                    get_tipo_veicolo(v),
                    get_modello_veicolo(v),
                    get_targa_veicolo(v),
                    get_posizione_veicolo(v),
                    get_disponibilita_veicolo(v));
        }
        temp = get_next_node(temp);
    }
    fclose(f_output);
}

void pulisci_coda_test(void) {
    while (!coda_vuota_test()) {
        Prenotazione p = estrai_test();
        if (p) {
            free(p);
        }
    }
    coda_test = NULL;
}

bool coda_vuota_test(void) {
    return get_coda_test() == NULL;
}

Prenotazione estrai_test(void) {
    CodaPrenotazioni coda = get_coda_test();
    if (coda == NULL) {
        return NULL;
    }
    
    Prenotazione p = coda->prenotazione;
    CodaPrenotazioni temp = coda;
    coda_test = coda->next;
    free(temp);
    return p;
}

/**
 * Funzione principale che gestisce l'esecuzione dei test
 * Se non vengono forniti argomenti, esegue tutti i test
 * Altrimenti esegue solo i test specificati come argomenti
 */
int main(int argc, char *argv[]) {
    // Inizializza la coda di test
    inizializza_coda_test();
    
    if (argc == 1) {
        // Nessun argomento: esegue tutti i test
        esegui_test_suite("tests/test_suite.txt", "tests/test_results.txt");
    } else {
        // Argomenti specifici: esegue solo i test indicati
        FILE* suite = fopen("tests/test_suite.txt", "r");
        if (!suite) {
            printf("Errore apertura test_suite.txt\n");
            return 1;
        }

        char tc_id[M], type[M];
        int total_tests = 0;
        int passed_tests = 0;

        while (fscanf(suite, "%s %s", tc_id, type) == 2) {
            for (int arg = 1; arg < argc; arg++) {
                if (strcmp(type, argv[arg]) == 0) {
                    total_tests++;
                    int pass = run_test_case(tc_id, type);
                    if (pass) passed_tests++;
                    printf("%s [%s]: %s\n", tc_id, type, pass ? "PASS" : "FAIL");
                    break;
                }
            }
        }
        fclose(suite);

        printf("\nRiepilogo test:\n");
        printf("Test eseguiti: %d\n", total_tests);
        printf("Test passati: %d\n", passed_tests);
        printf("Test falliti: %d\n", total_tests - passed_tests);
    }
    
    // Pulizia della coda di test
    if (coda_test != NULL) {
        pulisci_coda(coda_test);
        coda_test = NULL;
    }
    
    return 0;
}