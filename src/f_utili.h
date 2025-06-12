#ifndef F_UTILI_H
#define F_UTILI_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* Costanti per i colori della console */
#define COLORE_BIANCO  7   // Colore di default
#define COLORE_VERDE   10  // Verde
#define COLORE_CIANO   11  // Ciano
#define COLORE_ROSSO   12  // Rosso
#define COLORE_MAGENTA 13  // Magenta
#define COLORE_GIALLO  14  // Giallo

/**
 * @brief Imposta il colore del testo nella console
 * 
 * Funzione cross-platform per impostare il colore del testo nella console.
 * Su Windows utilizza le API di Windows, su altri sistemi utilizza i codici ANSI.
 * 
 * @param colore Il codice colore da impostare:
 *              - COLORE_BIANCO  (7)  - Bianco (default)
 *              - COLORE_VERDE   (10) - Verde
 *              - COLORE_CIANO   (11) - Ciano
 *              - COLORE_ROSSO   (12) - Rosso
 *              - COLORE_MAGENTA (13) - Magenta
 *              - COLORE_GIALLO  (14) - Giallo
 * 
 * @pre Nessuna
 * 
 * @post Il colore del testo viene modificato
 * 
 * @sideeffect Modifica l'aspetto del testo nella console
 */
void imposta_colore(int colore);

/**
 * @brief Svuota il buffer di input
 * 
 * Rimuove tutti i caratteri rimanenti nel buffer di input
 * fino al prossimo carattere newline.
 * 
 * @pre Nessuna
 * 
 * @post Il buffer di input viene svuotato
 * 
 * @sideeffect Consuma i caratteri dal buffer di input
 */
void svuota_buffer(void);

/**
 * @brief Pulisce lo schermo della console
 * 
 * Funzione cross-platform per pulire lo schermo della console.
 * Su Windows utilizza il comando "cls", su altri sistemi "clear".
 * 
 * @pre Nessuna
 * 
 * @post Lo schermo della console viene pulito
 * 
 * @sideeffect Modifica l'output della console
 */
void pulisci_schermo(void);

/**
 * @brief Salva i dati e libera la memoria
 * 
 * Esegue il salvataggio di tutti i dati (veicoli, prenotazioni, utenti)
 * e libera la memoria allocata.
 * 
 * @pre I moduli veicoli, prenotazioni e utenti devono essere inizializzati
 * 
 * @post I dati vengono salvati su file
 * @post La memoria viene liberata
 * 
 * @sideeffect Modifica i file di salvataggio
 * @sideeffect Libera la memoria allocata
 */
void salvataggio(void);

/**
 * @brief Stampa un separatore orizzontale
 * 
 * Stampa una linea di separazione colorata di ciano.
 * 
 * @pre Nessuna
 * 
 * @post Viene stampato un separatore orizzontale
 * 
 * @sideeffect Modifica l'output della console
 */
void stampa_separatore(void);

/**
 * @brief Stampa il bordo superiore
 * 
 * Stampa una linea di bordo superiore colorata di ciano.
 * 
 * @pre Nessuna
 * 
 * @post Viene stampato il bordo superiore
 * 
 * @sideeffect Modifica l'output della console
 */
void stampa_bordo_superiore(void);

/**
 * @brief Stampa il bordo inferiore
 * 
 * Stampa una linea di bordo inferiore colorata di ciano.
 * 
 * @pre Nessuna
 * 
 * @post Viene stampato il bordo inferiore
 * 
 * @sideeffect Modifica l'output della console
 */
void stampa_bordo_inferiore(void);

/**
 * @brief Stampa la data e l'ora di sistema
 * 
 * Stampa la data corrente (giorno della settimana) e l'ora
 * del sistema in formato leggibile.
 * 
 * @pre La data di sistema deve essere inizializzata
 * 
 * @post Viene stampata la data e l'ora corrente
 * 
 * @sideeffect Modifica l'output della console
 */
void stampa_data_sistema(void);

#endif /* F_UTILI_H */