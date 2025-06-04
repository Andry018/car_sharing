#ifndef F_UTILI_H
#define F_UTILI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

// Costanti per i colori
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

/**
 * @brief Imposta il colore del testo stampato nel terminale
 * 
 * La funzione imposta il colore del testo per le successive operazioni di output,
 * compatibile sia con Windows che con sistemi Unix-like.
 * 
 * @pre color è un intero, compatibile con i codici colore standard di Windows
 *      (SetConsoleTextAttribute) o codici ANSI su Unix/Linux/Mac
 * 
 * @post Il colore del testo stampato successivamente cambia secondo il valore di color
 * 
 * @sideeffect Modifica temporaneamente l'aspetto dell'output sul terminale
 * @sideeffect Emette sequenze ANSI o chiama API di Windows
 * 
 * @param color Codice colore da impostare
 */
void set_color(int color);

/**
 * @brief Pulisce il buffer di input standard
 * 
 * La funzione pulisce il buffer di input standard (stdin), scartando tutti i caratteri
 * fino al prossimo newline incluso.
 * 
 * @pre Nessuna, ma ha senso solo se chiamata dopo una lettura da stdin che potrebbe
 *      lasciare caratteri residui (es. scanf)
 * 
 * @post Il buffer di input viene svuotato fino al primo newline ('\n'), evitando
 *       problemi nelle successive letture da input
 * 
 * @sideeffect Consuma dati da stdin
 */
void svuota_buffer(void);

/**
 * @brief Cancella il contenuto visibile del terminale
 * 
 * La funzione cancella il contenuto visibile del terminale, in modo cross-platform.
 * 
 * @pre Nessuna
 * 
 * @post Il contenuto dello schermo viene cancellato
 * @post Il cursore ritorna in cima
 * 
 * @sideeffect Esegue un comando di sistema (system("cls") o system("clear"))
 */
void pulisci_schermo(void);

/**
 * @brief Salva lo stato del sistema e libera la memoria
 * 
 * La funzione salva lo stato del sistema (lista veicoli e coda prenotazioni) su file,
 * e libera la memoria dinamica associata alla lista dei veicoli.
 * 
 * @pre Le funzioni salva_lista_veicoli(), get_coda_prenotazioni() e
 *      salva_prenotazioni_su_file() devono essere definite e funzionanti
 * @pre pulisci_lista_veicoli() deve liberare correttamente la memoria
 * 
 * @post I dati vengono persistiti su file
 * @post La memoria della lista veicoli è liberata
 * 
 * @sideeffect Scrive su file
 * @sideeffect Libera memoria dinamica
 */
void salvataggio(void);

/**
 * @brief Stampa una riga decorativa superiore
 * 
 * La funzione stampa una riga decorativa (bordo superiore), colorata in ciano.
 * 
 * @pre Nessuna
 * 
 * @post Una linea ===================================== viene stampata con colore ciano,
 *       poi il colore viene resettato
 * 
 * @sideeffect Output su console con colore
 */
void stampa_bordo_superiore(void);

/**
 * @brief Stampa una riga decorativa inferiore
 * 
 * La funzione stampa una riga decorativa (bordo inferiore), uguale alla superiore.
 * 
 * @pre Nessuna
 * 
 * @post Una linea ===================================== viene stampata in ciano
 * 
 * @sideeffect Output su console con colore
 */
void stampa_bordo_inferiore(void);

/**
 * @brief Stampa una riga separatrice decorativa
 * 
 * La funzione stampa una riga separatrice decorativa in ciano, più corta del bordo.
 * 
 * @pre Nessuna
 * 
 * @post Una linea ------------------------------------- viene stampata
 * 
 * @sideeffect Output su console con colore
 */
void stampa_separatore(void);

/**
 * @brief Stampa la data e l'ora corrente del sistema
 * 
 * La funzione stampa a video la data e l'ora corrente del sistema in formato leggibile,
 * utilizzando i colori per evidenziare le informazioni.
 * 
 * @pre La funzione get_data_sistema() deve essere definita e funzionante
 * @pre La console deve supportare l'output testuale e i codici colore
 * 
 * @post Viene stampata a video la data e l'ora corrente del sistema
 * @post Il formato di output è: "Data sistema: [giorno] [ora]:00"
 * 
 * @sideeffect Modifica l'output del terminale
 * @sideeffect Cambia temporaneamente il colore del testo
 */
void stampa_data_sistema(void);

#endif