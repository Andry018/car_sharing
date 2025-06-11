#include <stdio.h>
#include <assert.h>
#include "veicolo.h"
#include "prenotazioni.h"
#include "tariffe.h"
#include "utenti.h"
#include "fasce_orarie.h"
#include <string.h>
#include <direct.h>
#include "data_sistema.h"
#include "f_utili.h"
#define M 64

// Variabili globali per i test
static list veicoli_test = NULL;
static CodaPrenotazioni coda_test = NULL;

// Definizione della struttura node per la lista veicoli
struct node {
    Veicolo veicolo;
    struct node* next;
};

// Funzioni di utilità per i test
bool verifica_utente_esistente(int id_utente, FILE* f_output, const char* output_fname, const char* oracle_fname) {
    Utente utente = cerca_utente_per_id(id_utente);
    if (utente == NULL) {
        fprintf(f_output, "ERRORE_UTENTE_NON_TROVATO\n");
        fclose(f_output);
        int cmp = compara_file(output_fname, oracle_fname);
        FILE* f = fopen("tests/risultati.txt", "a");
        if (f) {
            if (cmp == 0) {
                fprintf(f, "%s PASS\n", output_fname);
            } else {
                fprintf(f, "%s FAIL\n", output_fname);
            }
            fclose(f);
        }
        return false;
    }
    return true;
}

bool verifica_veicolo_esistente(int id_veicolo, FILE* f_output, const char* output_fname, const char* oracle_fname) {
    list veicoli = get_lista_veicoli_test();
    Veicolo veicolo = cerca_veicolo(veicoli, id_veicolo);
    if (veicolo == NULL) {
        fprintf(f_output, "ERRORE_VEICOLO_NON_TROVATO\n");
        fclose(f_output);
        int cmp = compara_file(output_fname, oracle_fname);
        FILE* f = fopen("tests/risultati.txt", "a");
        if (f) {
            if (cmp == 0) {
                fprintf(f, "%s PASS\n", output_fname);
            } else {
                fprintf(f, "%s FAIL\n", output_fname);
            }
            fclose(f);
        }
        return false;
    }
    return true;
}

void test_creazione_prenotazione(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_costo_noleggio(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_visualizza_disponibilita(const char* input_fname, const char* output_fname, const char* oracle_fname);
void test_storico_prenotazioni(const char* input_fname, const char* output_fname, const char* oracle_fname);
int compara_file(const char* file1, const char* file2);

list aggiungi_veicolo_senza_menu(list, Veicolo);
list get_lista_veicoli_test(void);
CodaPrenotazioni get_coda_test(void);

int run_test_case(const char* tc_id, const char* test_type){
    char input_fname[M], output_fname[M], oracle_fname[M];
  
    snprintf(input_fname, M,  "tests/%s/%s_input.txt", tc_id, tc_id);
    snprintf(output_fname, M, "tests/%s/%s_output.txt", tc_id, tc_id);
    snprintf(oracle_fname, M, "tests/%s/%s_oracle.txt", tc_id, tc_id);

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
    
    // Inizializza la data di sistema
    inizializza_data_sistema();
    
    // Carica l'input dal file
    char input[10][M];
    int n = leggi_input_test(input_fname, input, 10);
    if (n == 0) {
        printf("Errore lettura input: %s\n", input_fname);
        return;
    }

    int id_utente = atoi(input[0]);
    int id_veicolo = atoi(input[1]);
    int giorno_inizio = atoi(input[2]);
    int ora_inizio = atoi(input[3]);
    int giorno_fine = atoi(input[4]);
    int ora_fine = atoi(input[5]);
    int priorita = atoi(input[6]);
    int posizione_riconsegna = atoi(input[7]);

    FILE* f_output = fopen(output_fname, "w");
    if (!f_output){
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    // Verifica se l'utente esiste
    if (!verifica_utente_esistente(id_utente, f_output, output_fname, oracle_fname)) {
        return;
    }

    // Verifica se il veicolo esiste
    if (!verifica_veicolo_esistente(id_veicolo, f_output, output_fname, oracle_fname)) {
        return;
    }

    // Verifica la validità della fascia oraria
    if (!verifica_fascia_oraria(giorno_inizio, ora_inizio, giorno_fine, ora_fine)) {
        fprintf(f_output, "ERRORE_FASCIA_ORARIA\n");
        fclose(f_output);
        int cmp = compara_file(output_fname, oracle_fname);
        FILE* f = fopen("tests/risultati.txt", "a");
        if (f) {
            if (cmp == 0) {
                fprintf(f, "%s PASS\n", input_fname);
            } else {
                fprintf(f, "%s FAIL\n", input_fname);
            }
            fclose(f);
        }
        return;
    }

    // Verifica la validità della data rispetto alla data di sistema
    int timestamp_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    int timestamp_fine = converti_in_timestamp(giorno_fine, ora_fine);
    int validazione = valida_data_prenotazione(timestamp_inizio, timestamp_fine);
    if (validazione != 0) {
        // Converti i codici di errore negativi in positivi per l'output
        int codice_errore = -validazione;  // -(-1) = 1, -(-2) = 2
        fprintf(f_output, "ERRORE_DATA_%d\n", codice_errore);
        fclose(f_output);
        int cmp = compara_file(output_fname, oracle_fname);
        FILE* f = fopen("tests/risultati.txt", "a");
        if (f) {
            if (cmp == 0) {
                fprintf(f, "%s PASS\n", input_fname);
            } else {
                fprintf(f, "%s FAIL\n", input_fname);
            }
            fclose(f);
        }
        return;
    }

    // Creiamo e testiamo la prenotazione con priorità automatica (-1)
    Prenotazione p = crea_prenotazione(id_utente, id_veicolo, giorno_inizio, 
                                    ora_inizio, giorno_fine, ora_fine, -1,  // Usa priorità automatica
                                    posizione_riconsegna);
   
    // Output in formato spazio-separato usando i valori convertiti
    fprintf(f_output, "%d %d %d %d %d %d %d %d\n", 
            get_id_prenotazione(p),
            get_id_utente_prenotazione(p),
            get_id_veicolo_prenotazione(p),
            timestamp_inizio,
            timestamp_fine,
            get_stato_prenotazione(p),
            get_priorita(p),  // Usa la priorità calcolata automaticamente
            get_posizione_riconsegna(p));

    fclose(f_output);
    int cmp = compara_file(output_fname, oracle_fname);
    
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

void test_costo_noleggio(const char* input_fname, const char* output_fname, const char* oracle_fname){
    char input[10][M];
    leggi_input_test(input_fname, input, 10);
    int id_prenotazione = atoi(input[0]);
    int id_veicolo = atoi(input[1]);
    int giorno_inizio = atoi(input[2]);
    int ora_inizio = atoi(input[3]);
    int giorno_fine = atoi(input[4]);
    int ora_fine = atoi(input[5]);

    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    // Verifica se il veicolo esiste
    if (!verifica_veicolo_esistente(id_veicolo, f_output, output_fname, oracle_fname)) {
        return;
    }

    // Ottieni il tipo di veicolo
    list veicoli = get_lista_veicoli_test();
    list temp = veicoli;
    int tipo_veicolo = -1;
    while (temp != NULL) {
        Veicolo v = get_veicolo_senza_rimuovere(temp);
        if (v && get_id_veicolo(v) == id_veicolo) {
            tipo_veicolo = get_tipo_veicolo(v);
            break;
        }
        temp = get_next_node(temp);
    }

    // Calcola il costo del noleggio
    int timestamp_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    int timestamp_fine = converti_in_timestamp(giorno_fine, ora_fine);
    double costo = calcola_tariffa_prenotazione(tipo_veicolo, timestamp_inizio, timestamp_fine);
    
    fprintf(f_output, "%.2f\n", costo);
    
    fclose(f_output);

    int cmp = compara_file(output_fname, oracle_fname);
    
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

void test_storico_prenotazioni(const char* input_fname, const char* output_fname, const char* oracle_fname){

}

int main(int argc, char *argv[]) {
    // Inizializzazione delle strutture dati vuote per i test
    coda_test = inizializza_coda();
    if (!coda_test) {
        printf("Errore nell'inizializzazione della coda test\n");
        return 1;
    }

    // Inizializziamo la lista veicoli vuota per i test
    veicoli_test = NULL;  // Inizializziamo direttamente a NULL invece di usare get_lista_veicoli()
    
    // Aggiungiamo alcuni veicoli di test
    Veicolo v1 = crea_veicolo(); 
    if (!v1) {
        printf("Errore nella creazione del veicolo di test 1\n");
        return 1;
    }
    set_id_veicolo(v1, 1);
    set_tipo_veicolo(v1, 0);
    set_modello_veicolo(v1, "JeepRenegade");
    set_targa_veicolo(v1, "AA000BB");
    set_posizione_veicolo(v1, 0);
    set_disponibilita_veicolo(v1, 0);      
    
    Veicolo v2 = crea_veicolo();
    if (!v2) {
        printf("Errore nella creazione del veicolo di test 2\n");
        return 1;
    }
    set_id_veicolo(v2, 2);
    set_tipo_veicolo(v2, 3);
    set_modello_veicolo(v2, "HondaCBR");
    set_targa_veicolo(v2, "CC111DD");
    set_posizione_veicolo(v2, 1);
    set_disponibilita_veicolo(v2, 0);
    
    veicoli_test = aggiungi_veicolo_senza_menu(veicoli_test, v1);
    veicoli_test = aggiungi_veicolo_senza_menu(veicoli_test, v2);

    // Inizializziamo la hash table utenti vuota per i test
    Utente tabella_utenti[TABLE_SIZE];
    inizializza_tabella_utenti(tabella_utenti);

    // Aggiungiamo alcuni utenti di test
    inserisci_utente("Test1", "UtenteTest1", "Test1");
    inserisci_utente("Test2", "UtenteTest2", "Test2");

    // Aggiungiamo alcune prenotazioni di test
    Prenotazione p1 = crea_prenotazione(1, 1, 1, 10, 1, 12, 0, 1);  // utente 1, veicolo 1, giorno 1, 10-12
    Prenotazione p2 = crea_prenotazione(2, 2, 2, 14, 2, 16, 0, 0);  // utente 2, veicolo 2, giorno 2, 14-16
    aggiungi_prenotazione(coda_test, p1);
    aggiungi_prenotazione(coda_test, p2);

    // Eseguiamo i test
    if (argc == 1) {
        esegui_test_suite("tests/test_suite.txt", "tests/test_results.txt");
    } else {
        // ... resto del codice per i test specifici ...
    }

    // Pulizia delle strutture dati di test
    distruggi_coda(coda_test);
    // distruggi_lista_veicoli(veicoli_test);
    // distruggi_hash_table(utenti_test);

    printf("Tutti i test sono stati eseguiti con successo!\n");
    return 0;
}

list aggiungi_veicolo_senza_menu(list veicoli, Veicolo v) {
    if (v == NULL) {
        return veicoli;
    }
    
    // Crea un nuovo nodo
    list nuovo = (list)malloc(sizeof(struct node));
    if (nuovo == NULL) {
        return veicoli;
    }
    
    // Imposta il veicolo nel nodo
    nuovo->veicolo = v;
    nuovo->next = veicoli;
    
    return nuovo;
}

list get_lista_veicoli_test(void) {
    return veicoli_test;
}

CodaPrenotazioni get_coda_test(void) {
    return coda_test;
}
