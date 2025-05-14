#include "hash.h"

unsigned int hash_djb2(const char* str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}