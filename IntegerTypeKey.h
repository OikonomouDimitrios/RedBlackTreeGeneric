//
// Created by Oikonomou Dimitrios on 1/3/2023.
//

#ifndef REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
#define REDBLACKTREEGENERIC_INTEGERTYPEKEY_H

#include <malloc.h>

typedef struct IntKey {
    int x;
} IntegerTypeKey;

IntegerTypeKey *newIntegerTypeKey() {
    IntegerTypeKey *New = malloc(sizeof(IntegerTypeKey));
    /* printf("%p\n", New); */
    return New;
}

int keyCompare(int k1, int k2) {
    return k1 > k2 ? 1 : k1 == k2 ? 0 : -1;
}

#endif //REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
