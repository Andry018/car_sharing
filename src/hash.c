#include "hash.h"

/**
 * @brief Implementazione dell'algoritmo di hash djb2
 * 
 * L'algoritmo djb2 è un algoritmo di hash non crittografico che produce un valore
 * hash a 32 bit per una data stringa di input. È noto per la sua semplicità e
 * buona distribuzione dei valori hash.
 * 
 * L'algoritmo:
 * 1. Inizia con un valore hash di 5381
 * 2. Per ogni carattere nella stringa:
 *    - Moltiplica il valore hash corrente per 33 (shift left di 5 + somma)
 *    - Aggiunge il valore ASCII del carattere corrente
 * 
 * @param str Stringa di input da cui calcolare l'hash
 * @return unsigned int Valore hash calcolato
 */
unsigned int hash_djb2(const char* str) {
    unsigned int hash = 5381;  // Valore iniziale (magic number)
    int c;

    // Itera su ogni carattere della stringa
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c

    return hash;
}