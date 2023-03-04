//
// Created by Oikonomou Dimitrios on 1/3/2023.
//

#ifndef REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
#define REDBLACKTREEGENERIC_INTEGERTYPEKEY_H

#include <malloc.h>
#include <assert.h>

typedef struct IntKey {
    int x;
} IntegerTypeKey;

IntegerTypeKey *newIntegerTypeKey() {
    IntegerTypeKey *New = malloc(sizeof(IntegerTypeKey));
    /* printf("%p\n", New); */
    return New;
}

int intKeyCompare(const int *k1, const int *k2) {
    assert(k1 != NULL && k2 != NULL);
    return *k1 > *k2 ? 1 : *k1 == *k2 ? 0 : -1;
}

char *intKeyToString(const int *key) {
    int value = *((int *) key);
    char *str = malloc(sizeof(char) * 12); // Maximum number of characters needed for a 32-bit integer
    sprintf(str, "%d", value);
    return str;
}

#endif //REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
