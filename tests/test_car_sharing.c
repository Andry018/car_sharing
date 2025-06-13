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

// Function declarations
int compara_file(const char* file1, const char* file2);
list ottieni_lista_veicoli_test(void);
CodaPrenotazioni ottieni_coda_test(void);
list aggiungi_veicolo_senza_menu(list, Veicolo);

// Variabili globali per i test
static CodaPrenotazioni coda_test = NULL;

// Definizione della struttura nodo per la lista veicoli
struct nodo {
    Veicolo veicolo;
    struct nodo* successivo;
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
    list veicoli = ottieni_lista_veicoli();
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
        // Rimuovi nuova linea finale
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
                                    ora_inizio, giorno_fine, ora_fine, priorita,  
                                    posizione_riconsegna);
   
    // Output in formato spazio-separato usando i valori convertiti
    fprintf(f_output, "%d %d %d %d %d %d %d %d\n", 
            ottieni_id_prenotazione(p),
            ottieni_id_utente_prenotazione(p),
            ottieni_id_veicolo_prenotazione(p),
            ottieni_giorno_ora_inizio(p),
            ottieni_giorno_ora_fine(p),
            ottieni_stato_prenotazione(p),
            ottieni_priorita(p),  // Usa la priorità calcolata automaticamente
            ottieni_posizione_riconsegna(p));

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
    int id_utente = atoi(input[0]);
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

    // Controllo errore ora_fine < ora_inizio nello stesso giorno
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

    // Ottieni il tipo di veicolo
    list veicoli = ottieni_lista_veicoli();
    list temp = veicoli;
    int tipo_veicolo = -1;
    while (temp != NULL) {
        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);
        if (v && ottieni_id_veicolo(v) == id_veicolo) {
            tipo_veicolo = ottieni_tipo_veicolo(v);
            break;
        }
        temp = ottieni_successivo_nodo(temp);
    }

    // Calcola il costo del noleggio
    int timestamp_inizio = converti_in_timestamp(giorno_inizio, ora_inizio);
    int timestamp_fine = converti_in_timestamp(giorno_fine, ora_fine);
    double costo = calcola_tariffa_prenotazione(coda_test, tipo_veicolo, timestamp_inizio, timestamp_fine, id_utente);
    
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
    // Inizializza la data di sistema
    inizializza_data_sistema();
    
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    int giorno_inizio = atoi(input[0]);
    int ora_inizio = atoi(input[1]);
    int giorno_fine = atoi(input[2]);
    int ora_fine = atoi(input[3]);

    

    // Avanza la data di sistema fino al periodo richiesto
    int ore_da_avanzare = (giorno_inizio * 24 + ora_inizio) - (ottieni_giorno_corrente() * 24 + ottieni_ora_corrente());
    if (ore_da_avanzare > 0) {
        avanza_tempo(ore_da_avanzare);
    }

    // Ottieni la lista veicoli simulata
    list veicoli = ottieni_lista_veicoli();

    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }
    

    // Per ogni veicolo, verifica la disponibilità nell'intervallo richiesto
    list temp = veicoli;
    while (temp != NULL) {
        Veicolo v = ottieni_veicolo_senza_rimuovere(temp);

        CalendarioVeicolo calendario = inizializza_calendario(ottieni_id_veicolo(v));
        CodaPrenotazioni coda = ottieni_coda_prenotazioni();
        CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, coda);
        free(nuovo_calendario);
        if (v && ottieni_disponibilita_veicolo(v)) {
            CalendarioVeicolo calendario = inizializza_calendario(ottieni_id_veicolo(v));
            CalendarioVeicolo nuovo_calendario = aggiorna_calendario(calendario, ottieni_coda_test());
            if (nuovo_calendario && verifica_disponibilita(nuovo_calendario, giorno_inizio, ora_inizio, giorno_fine, ora_fine)) {
                fprintf(f_output, "%d %s %s\n",
                        ottieni_id_veicolo(v),
                        ottieni_modello_veicolo(v),
                        ottieni_nome_posizione_veicolo(ottieni_posizione_veicolo(v)));
            }
            free(nuovo_calendario);
        }
        temp = ottieni_successivo_nodo(temp);
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
    char input[10][M];
    leggi_input_test(input_fname, input, 10);

    int id_utente = atoi(input[0]);

    FILE* f_output = fopen(output_fname, "w");
    if (!f_output) {
        printf("Errore apertura file di output: %s\n", output_fname);
        return;
    }

    CodaPrenotazioni coda = ottieni_coda_test();
    if (!verifica_utente_esistente(id_utente, f_output, output_fname, oracle_fname)) {
        fclose(f_output);
        return;
    }
    if (id_utente == 0){
        for (int i = 0; i < ottieni_dimensione_coda(coda); i++) {
            Prenotazione p = ottieni_prenotazione_in_coda(coda, i);
            if (!p) continue;
            fprintf(f_output, "%d %d %d %d %d %d %d %d\n",
                    ottieni_id_prenotazione(p),
                    ottieni_id_utente_prenotazione(p),
                    ottieni_id_veicolo_prenotazione(p),
                    ottieni_giorno_ora_inizio(p),
                    ottieni_giorno_ora_fine(p),
                    ottieni_stato_prenotazione(p),
                    ottieni_priorita(p),
                    ottieni_posizione_riconsegna(p));
        }
    }else{
    for (int i = 0; i < ottieni_dimensione_coda(coda); i++) {
        Prenotazione p = ottieni_prenotazione_in_coda(coda, i);
        if (!p) continue;
        if (ottieni_id_utente_prenotazione(p) == id_utente) {
            fprintf(f_output, "%d %d %d %d %d %d %d %d\n",
                    ottieni_id_prenotazione(p),
                    ottieni_id_utente_prenotazione(p),
                    ottieni_id_veicolo_prenotazione(p),
                    ottieni_giorno_ora_inizio(p),
                    ottieni_giorno_ora_fine(p),
                    ottieni_stato_prenotazione(p),
                    ottieni_priorita(p),
                    ottieni_posizione_riconsegna(p));
        }
    }
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

int main(int argc, char *argv[]) {
    (void)argc;  // Suppress unused parameter warning
    (void)argv;  // Suppress unused parameter warning
    // Inizializzazione delle strutture dati vuote per i test
    coda_test = inizializza_coda();
    if (!coda_test) {
        printf("Errore nell'inizializzazione della coda test\n");
        return 1;
    }

    // Inizializziamo la lista veicoli vuota per i test
    imposta_lista_veicoli(NULL);  // Usa la lista globale
    
    // Aggiungiamo alcuni veicoli di test
    Veicolo v1 = crea_veicolo(); 
    if (!v1) {
        printf("Errore nella creazione del veicolo di test 1\n");
        return 1;
    }
    imposta_id_veicolo(v1, 1);
    imposta_tipo_veicolo(v1, 0);
    imposta_modello_veicolo(v1, "Fiat500");
    imposta_targa_veicolo(v1, "AA000BB");
    imposta_posizione_veicolo(v1, 0);
    imposta_disponibilita_veicolo(v1, 1);      // Changed from 0 to 1
    
    Veicolo v2 = crea_veicolo();
    if (!v2) {
        printf("Errore nella creazione del veicolo di test 2\n");
        return 1;
    }
    imposta_id_veicolo(v2, 2);
    imposta_tipo_veicolo(v2, 3);
    imposta_modello_veicolo(v2, "HondaCBR");
    imposta_targa_veicolo(v2, "CC111DD");
    imposta_posizione_veicolo(v2, 1);
    imposta_disponibilita_veicolo(v2, 1);      // Changed from 0 to 1

    Veicolo v3 = crea_veicolo();
    if (!v3) {
        printf("Errore nella creazione del veicolo di test 3\n");
        return 1;
    }
    imposta_id_veicolo(v3, 3);
    imposta_tipo_veicolo(v3, 1);
    imposta_modello_veicolo(v3, "JeepWrangler");
    imposta_targa_veicolo(v3, "EE222FF");
    imposta_posizione_veicolo(v3, 2);
    imposta_disponibilita_veicolo(v3, 1);      // Changed from 0 to 1

    Veicolo v4 = crea_veicolo();
    if (!v4) {
        printf("Errore nella creazione del veicolo di test 4\n");
        return 1;
    }
    imposta_id_veicolo(v4, 4);
    imposta_tipo_veicolo(v4, 2);
    imposta_modello_veicolo(v4, "TeslaModelS");
    imposta_targa_veicolo(v4, "GG333HH");
    imposta_posizione_veicolo(v4, 3);
    imposta_disponibilita_veicolo(v4, 1);      // Changed from 0 to 1
    
    list veicoli = ottieni_lista_veicoli();
    veicoli = aggiungi_veicolo_senza_menu(veicoli, v1);
    veicoli = aggiungi_veicolo_senza_menu(veicoli, v2);
    veicoli = aggiungi_veicolo_senza_menu(veicoli, v3);
    veicoli = aggiungi_veicolo_senza_menu(veicoli, v4);
    imposta_lista_veicoli(veicoli);

    // Inizializziamo la hash table utenti vuota per i test
    Utente tabella_utenti[TABLE_SIZE];
    inizializza_tabella_utenti(tabella_utenti);

    // Aggiungiamo alcuni utenti di test 
    inserisci_utente("amministratore", "Amministratore", "Test0");
    inserisci_utente("Test1", "UtenteTest1", "Test1");
    inserisci_utente("Test2", "UtenteTest2", "Test2");
   

    // Aggiungiamo alcune prenotazioni di test
    Prenotazione p1 = crea_prenotazione(1, 1, 1, 10, 1, 12, 0, 1);  // utente 1, veicolo 1, giorno 1, 10-12
    imposta_stato_prenotazione(1,p1);
    Prenotazione p2 = crea_prenotazione(1, 2, 2, 14, 2, 16, 0, 0); // utente 1, veicolo 2, giorno 2, 14-16
    imposta_stato_prenotazione(1,p2);
    Prenotazione p3 = crea_prenotazione(2, 3, 3, 9, 3, 11, 0, 2); // utente 2, veicolo 3, giorno 3, 9-11
    
    Prenotazione p4 = crea_prenotazione(2, 4, 4, 13, 4, 15, 0, 3); // utente 2, veicolo 4, giorno 4, 13-15  
    Prenotazione p5 = crea_prenotazione(2, 2, 2, 16, 2, 17, 0, 0); // utente 2, veicolo 2, giorno 2, 16-17
    Prenotazione p6 = crea_prenotazione(2, 2, 2, 17, 2, 18, 0, 0); // utente 2, veicolo 2, giorno 2, 17-18
    Prenotazione p7 = crea_prenotazione(2, 2, 2, 18, 2, 19, 0, 0); // utente 2, veicolo 2, giorno 2, 18-19
    Prenotazione p8 = crea_prenotazione(2, 2, 2, 19, 2, 20, 0, 0); // utente 2, veicolo 2, giorno 2, 19-20
    Prenotazione p9 = crea_prenotazione(2, 2, 2, 20, 2, 21, 0, 0); // utente 2, veicolo 2, giorno 2, 20-21
    Prenotazione p10 = crea_prenotazione(2, 2, 2, 21, 2, 22, 0, 0); // utente 2, veicolo 2, giorno 2, 21-22
    Prenotazione p11 = crea_prenotazione(2, 2, 2, 22, 2, 23, 0, 0); // utente 2, veicolo 2, giorno 2, 22-23
    Prenotazione p12 = crea_prenotazione(2, 2, 2, 23, 3, 0, 0, 0); // utente 2, veicolo 2, giorno 2, 23-0

    Prenotazione p13 = crea_prenotazione(2, 2, 3, 0, 3, 1, 0, 0); // utente 2, veicolo 2, giorno 3, 0-1
    Prenotazione p14 = crea_prenotazione(2, 2, 3, 1, 3, 2, 0, 0); // utente 2, veicolo 2, giorno 3, 1-2

     imposta_stato_prenotazione(2, p5);  // Imposta lo stato della prenotazione p5 a "Completata"
    imposta_stato_prenotazione(2, p6);  // Imposta lo stato della prenotazione p6 a "Completata"
    imposta_stato_prenotazione(2, p7);  // Imposta lo stato della prenotazione p7 a "Completata"
    imposta_stato_prenotazione(2, p8);  // Imposta lo stato della prenotazione p8 a "Completata"
    imposta_stato_prenotazione(2, p9);  // Imposta lo stato della prenotazione p9 a "Completata"
    imposta_stato_prenotazione(2, p10); // Imposta lo stato della prenotazione p10 a "Completata"
    imposta_stato_prenotazione(2, p11); // Imposta lo stato della prenotazione p11 a "Completata"
    imposta_stato_prenotazione(2, p12); // Imposta lo stato della prenotazione p12 a "Completata"
    imposta_stato_prenotazione(2, p13); // Imposta lo stato della prenotazione p13 a "Completata"
    imposta_stato_prenotazione(2, p14); // Imposta lo stato della prenotazione p14 a "Completata"

    aggiungi_prenotazione(coda_test, p1);    
    aggiungi_prenotazione(coda_test, p2);
    aggiungi_prenotazione(coda_test, p3);
    aggiungi_prenotazione(coda_test, p4);
    aggiungi_prenotazione(coda_test, p5);
    aggiungi_prenotazione(coda_test, p6);
    aggiungi_prenotazione(coda_test, p7);
    aggiungi_prenotazione(coda_test, p8);
    aggiungi_prenotazione(coda_test, p9);
    aggiungi_prenotazione(coda_test, p10);
    aggiungi_prenotazione(coda_test, p11);
    aggiungi_prenotazione(coda_test, p12);
    aggiungi_prenotazione(coda_test, p13);
    aggiungi_prenotazione(coda_test, p14);
    aggiungi_prenotazione(coda_test, p15);
    aggiungi_prenotazione(coda_test, p16); 
    aggiungi_prenotazione(coda_test, p17);
    aggiungi_prenotazione(coda_test, p18);
    aggiungi_prenotazione(coda_test, p19);
    aggiungi_prenotazione(coda_test, p20);
    aggiungi_prenotazione(coda_test, p21);
    aggiungi_prenotazione(coda_test, p22);


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
    list nuovo = (list)malloc(sizeof(struct nodo));
    if (nuovo == NULL) {
        return veicoli;
    }
    
    // Imposta il veicolo nel nodo
    nuovo->veicolo = v;
    nuovo->successivo = veicoli;
    
    return nuovo;
}

CodaPrenotazioni ottieni_coda_test(void) {
    return coda_test;
}
