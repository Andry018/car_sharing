#include <stdio.h>
#include <assert.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "tariffe.h"
#include "utenti.h"
#include "fasce_orarie.h"
#include <string.h>
#include <direct.h>
#define M 64

void test_creazione_prenotazione(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_costo_noleggio(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_visualizza_disponibilita(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_storico_prenotazioni(const char* input_fname, const char* output_fname, const char* oracle_fname);
int compara_file(const char* file1, const char* file2);


int run_test_case(const char* tc_id, const char* test_type){
    char input_fname[M], output_fname[M], oracle_fname[M];
  
    snprintf(input_fname, M,  "C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/%s/%s_input.txt", tc_id, tc_id);
    snprintf(output_fname, M, "C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/%s/%s_output.txt", tc_id, tc_id);
    snprintf(oracle_fname, M, "C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/%s/%s_oracle.txt", tc_id, tc_id);

    int pass = 0;
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

void esegui_test_suite(const char* suite_file, const char* result_file) {
    FILE* suite = fopen(suite_file, "r");
    FILE* result = fopen(result_file, "w");

    if (suite == NULL || result == NULL) {
        printf("Errore apertura test suite o risultati\n");
        return;
        
    }

    char tc_id[M], test_type[M];
    while (fscanf(suite, "%s %s", tc_id, test_type) == 2) {
        int pass = run_test_case(tc_id, test_type);
        printf("%s [%s]: %s\n", tc_id, test_type, pass ? "PASS" : "FAIL");
        fprintf(result, "%s - %s - %s\n", tc_id, test_type, pass ? "PASS" : "FAIL");
    }

    fclose(suite);
    fclose(result);
}

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

void test_creazione_prenotazione(const char* input_fname, const char* output_fname, const char* oracle_fname) {
    
    // Carica l'input dal file
char input[10][M];
    int n = leggi_input_test(input_fname, input, 10);

    
    int id_utente = atoi(input[0]);
    int id_veicolo = atoi(input[1]);
    int giorno_inizio = atoi(input[2]);
    int ora_inizio = atoi(input[3]);
    int giorno_fine = atoi(input[4]);
    int ora_fine = atoi(input[5]);
    int priorita = atoi(input[6]);
    int posizione_riconsegna = atoi(input[7]);

    Prenotazione p=crea_prenotazione(id_utente, id_veicolo, giorno_inizio, 
                                    ora_inizio, giorno_fine, ora_fine, priorita, 
                                    posizione_riconsegna);
    
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output){
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
        
       
    } fprintf(f_output, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", get_id_prenotazione(p), 
                get_id_utente_prenotazione(p), get_id_veicolo_prenotazione(p), 
                get_giorno_ora_inizio(p), get_giorno_ora_fine(p), 
                get_stato_prenotazione(p), get_priorita(p), 
                get_posizione_riconsegna(p));
    

    int cmp = compara_file(output_fname, oracle_fname);
    fclose(f_output);

    FILE* f = fopen("C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/risultati.txt", "a");
    if (f) {
        if (cmp == 0) {
            fprintf(f, "%s PASS\n", input_fname);
        } else {
            fprintf(f, "%s FAIL\n", input_fname);
        }
        fclose(f);
    }
}


void test_costo_noleggio(const char* input_fname, const char* output_fname, const char* oracle_fname){
    // Carica l'input dal file
    char input[10][M];
    int n = leggi_input_test(input_fname, input, 10);

    int id_prenotazione = atoi(input[0]);
    int id_veicolo = atoi(input[1]);
    int giorno_inizio = atoi(input[2]);
    int ora_inizio = atoi(input[3]);
    int giorno_fine = atoi(input[4]);
    int ora_fine = atoi(input[5]);

    // Calcola il costo del noleggio
    int timestamp_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    int timestamp_fine = converti_in_timestamp(giorno_fine, ora_fine);
    double costo = calcola_tariffa_prenotazione(id_veicolo, timestamp_inizio, timestamp_fine);
   
    // Stampa il risultato nel file di output
    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }
    
    fprintf(f_output, "%.2f\n", costo);
    
    fclose(f_output);

    int cmp = compara_file(output_fname, oracle_fname);
    
    FILE* f = fopen("C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/risultati.txt", "a");
    if (f) {
        if (cmp == 0) {
            fprintf(f, "%s PASS\n", input_fname);
        } else {
            fprintf(f, "%s FAIL\n", input_fname);
        }
        fclose(f);
    }

}

void test_visualizza_disponibilita(const char* input_fname, const char* output_fname, const char* oracle_fname){
    // Carica l'input dal file
    char input[10][M];
    int n = leggi_input_test(input_fname, input, 10);

    int giorno_inizio = atoi(input[0]);
    int ora_inizio = atoi(input[1]);
    int giorno_fine = atoi(input[2]);
    int ora_fine = atoi(input[3]);

    // Ottieni la lista veicoli simulata
    list veicoli = get_lista_veicoli_test();

    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    // Per ogni veicolo, verifica la disponibilità nell'intervallo richiesto
    list temp = veicoli;
    while (temp != NULL) {
        Veicolo v = get_veicolo_senza_rimuovere(temp);
        if (v && get_disponibilita_veicolo(v)) {
            CalendarioVeicolo calendario = inizializza_calendario(get_id_veicolo(v));
            CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, get_coda_test());
            if (nuovo_calendario && verifica_disponibilita(nuovo_calendario, giorno_inizio, ora_inizio, giorno_fine, ora_fine)) {
                fprintf(f_output, "%d %s %s\n",
                        get_id_veicolo(v),
                        get_nome_tipo_veicolo(get_tipo_veicolo(v)),
                        get_nome_posizione_veicolo(get_posizione_veicolo(v)));
            }
            free(nuovo_calendario);
        }
        temp = get_next_node(temp);
    }

    fclose(f_output);

    int cmp = compara_file(output_fname, oracle_fname);

    FILE* f = fopen("C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/risultati.txt", "a");
    if (f) {
        if (cmp == 0) {
            fprintf(f, "%s PASS\n", input_fname);
        } else {
            fprintf(f, "%s FAIL\n", input_fname);
        }
        fclose(f);
    }
}

void test_storico_prenotazioni(const char* input_fname, const char* output_fname, const char* oracle_fname){

}

int main(int argc, char *argv[]) {
    if (argc == 1){
    // Nessun argomento: esgue tutti i test
   esegui_test_suite("C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/test_suite.txt", "C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/test_results.txt");
    }else{
        // Argomenti specifici: esegue solo i test indicati
       for (int arg = 1; arg < argc; arg++) {
    char* test_type = argv[arg];
    //printf("entro nella directory dei test\n");
   // chdir("C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests");
    //printf("sono entrato nella directory dei test\n");
    printf("sto per aprire il file test_suite.txt\n");
    FILE* suite = fopen("C:/Users/gvarr/OneDrive/Desktop/Projects/C/car_sharing/tests/test_suite.txt", "r");
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
            int pass = run_test_case(tc_id, type);
            printf("%s [%s]: %s\n", tc_id, type, pass ? "PASS" : "FAIL");
        }
    }
    fclose(suite);
}
    }


    printf("Tutti i test sono stati eseguiti con successo!\n");
    return 0;
}