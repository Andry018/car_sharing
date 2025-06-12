#ifndef HASH_H
#define HASH_H

/**
 * @brief Genera un hash DJB2 per una stringa
 * 
 * La funzione implementa l'algoritmo di hash DJB2, un algoritmo di hash
 * non crittografico che produce un valore hash a 32 bit per una stringa.
 * 
 * @param str La stringa da cui generare l'hash
 * 
 * @pre str deve essere una stringa valida terminata con '\0'
 * 
 * @post Restituisce un valore hash unsigned int
 * 
 * @sideeffect Nessuno
 * 
 * @return unsigned int Il valore hash generato
 */
unsigned int hash_djb2(const char* str);

#endif // HASH_H