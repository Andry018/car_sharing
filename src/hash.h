#ifndef HASH_H
#define HASH_H

/**
 * @brief Calcola l'hash di una stringa usando l'algoritmo djb2
 * 
 * La funzione implementa l'algoritmo di hash djb2, un algoritmo di hash non crittografico
 * che produce un valore hash a 32 bit per una data stringa di input.
 * 
 * @pre str è un puntatore valido a una stringa terminata da \0
 * 
 * @post Viene restituito un valore hash a 32 bit per la stringa di input
 * 
 * @sideeffect Nessuno
 * 
 * @param str Stringa di input da cui calcolare l'hash
 * @return unsigned int Valore hash calcolato
 */
unsigned int hash_djb2(const char* str);

#endif // HASH_H