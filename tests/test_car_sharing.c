#include <stdio.h>
#include <assert.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "tariffe.h"
#include "utenti.h"
#include <string.h>
#include "fasce_orarie.h"
#define M 64


// Prototipi delle funzioni di test
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
int run_test_case(const char* tc_id, const char* test_type){
    char input_fname[M], output_fname[M], oracle_fname[M];
  
    // Costruisce i nomi dei file per il test case
    snprintf(input_fname, M,  "tests/%s/%s_input.txt", tc_id, tc_id);
    snprintf(output_fname, M, "tests/%s/%s_output.txt", tc_id, tc_id);
    snprintf(oracle_fname, M, "tests/%s/%s_oracle.txt", tc_id, tc_id);

    int pass = 0;
    // Esegue il test appropriato in base al tipo
    if (strcmp(test_type, "creazione_prenotazione") == 0) {
       test_creazione_prenotazione(input_fname, output_fname, oracle_fname);
       pass = compara_file(output_fname, oracle_fname) == 0;
    } else if (strcmp(test_type, "costo_noleggio") == 0) {
        test_costo_noleggio(input_fname, output_fname, oracle_fname);  
        pass = compara_file(output_fname, oracle_fname) == 0;  
    } else if (strcmp(test_type, "visualizza_disponibilita") == 0) {    
        test_visualizza_disponibilita(input_fname, output_fname, oracle_fname);
        pass = compara_file(output_fname, oracle_fname) == 0;
    } else if (strcmp(test_type, "storico_prenotazioni") == 0) {
        test_storico_prenotazioni(input_fname, output_fname, oracle_fname);
        pass = compara_file(output_fname, oracle_fname) == 0;
    } 
    return pass;
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
    FILE* suite = fopen(suite_file, "r");
    FILE* result = fopen(result_file, "w");

    if (suite == NULL || result == NULL) {
        printf("Errore apertura test suite o risultati\n");
        return;
    }

    char tc_id[M], test_type[M];
    // Legge e esegue ogni test case dalla suite
    while (fscanf(suite, "%s %s", tc_id, test_type) == 2) {
        int pass = run_test_case(tc_id, test_type);
        printf("%s [%s]: %s\n", tc_id, test_type, pass ? "PASS" : "FAIL");
        fprintf(result, "%s - %s - %s\n", tc_id, test_type, pass ? "PASS" : "FAIL");
    }

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
    FILE *f1 = fopen(file1, "rb");
    FILE *f2 = fopen(file2, "rb");
    if (!f1 || !f2) return 1;
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
    if (c1 != c2) result = 1;
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
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    // Parsing dei parametri di input
    int id_utente = atoi(input[0]);
    int id_veicolo = atoi(input[1]);
    int giorno_inizio = atoi(input[2]);
    int ora_inizio = atoi(input[3]);
    int giorno_fine = atoi(input[4]);
    int ora_fine = atoi(input[5]);
    int priorita = atoi(input[6]);
    int posizione_riconsegna = atoi(input[7]);

    // Creazione della prenotazione
    Prenotazione p = crea_prenotazione(id_utente, id_veicolo, giorno_inizio, 
                                     ora_inizio, giorno_fine, ora_fine, priorita, 
                                     posizione_riconsegna);
    
    // Scrittura dei risultati nel file di output
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }
    
    fprintf(f_output, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", 
            get_id_prenotazione(p), 
            get_id_utente_prenotazione(p), 
            get_id_veicolo_prenotazione(p), 
            get_giorno_ora_inizio(p), 
            get_giorno_ora_fine(p), 
            get_stato_prenotazione(p), 
            get_priorita(p), 
            get_posizione_riconsegna(p));
    
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
    list veicoli = get_lista_veicoli();
    
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
                CodaPrenotazioni coda_prenotazioni = get_coda_prenotazioni();
                if (coda_prenotazioni == NULL) {
                    printf("Errore nell'ottenere la coda delle prenotazioni\n");
                    return;
                }
                CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, coda_prenotazioni);
                
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

    // Ottieni la coda delle prenotazioni
    CodaPrenotazioni coda_prenotazioni = get_coda_prenotazioni();
    
    // Scrittura dei risultati
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    // Stampa delle prenotazioni dell'utente nel periodo specificato
    int dimensione = get_dimensione_coda(coda_prenotazioni);
    for (int i = 0; i < dimensione; i++) {
        Prenotazione p = get_prenotazione_in_coda(coda_prenotazioni, i);
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
        free(coda_prenotazioni);
    }
}

/**
 * Funzione principale che gestisce l'esecuzione dei test
 * Se non vengono forniti argomenti, esegue tutti i test
 * Altrimenti esegue solo i test specificati come argomenti
 */
int main(int argc, char *argv[]) {
    int total_tests = 0;
    int passed_tests = 0;

    if (argc == 1){
        // Nessun argomento: esegue tutti i test
        esegui_test_suite("tests/test_suite.txt", "tests/test_results.txt");
    } else {
        // Argomenti specifici: esegue solo i test indicati
        for (int arg = 1; arg < argc; arg++) {
            char* test_type = argv[arg];
            printf("sto per aprire il file test_suite.txt\n");
            FILE* suite = fopen("tests/test_suite.txt", "r");
            if (!suite) {
                printf("Errore apertura test_suite.txt\n");
                continue;
            }
            printf("Aperto test_suite.txt con successo\n");
            char tc_id[M], type[M];
            rewind(suite);
            char line[128];
            while (fgets(line, sizeof(line), suite)) {
                printf("RIGA: [%s]", line);
            }
            rewind(suite);
            while (fscanf(suite, "%s %s", tc_id, type) == 2) {
                printf("Letto: %s %s\n", tc_id, type);
                if (strcmp(type, test_type) == 0) {
                    total_tests++;
                    int pass = run_test_case(tc_id, type);
                    if (pass) passed_tests++;
                    printf("%s [%s]: %s\n", tc_id, type, pass ? "PASS" : "FAIL");
                }
            }
            fclose(suite);
        }
    }

    printf("\nRiepilogo test:\n");
    printf("Test eseguiti: %d\n", total_tests);
    printf("Test passati: %d\n", passed_tests);
    printf("Test falliti: %d\n", total_tests - passed_tests);
    
    return 0;
}