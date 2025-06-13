#include "hash.h"

/**
 * @brief Genera un hash DJB2 per una stringa.
 * @param str La stringa da cui generare l'hash.
 * @return Il valore hash generato.
 */
unsigned int hash_djb2(const char* str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}
