//
// Created by Oikonomou Dimitrios on 1/3/2023.
//

#ifndef REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
#define REDBLACKTREEGENERIC_INTEGERTYPEKEY_H

#include <malloc.h>
#include <assert.h>

typedef struct IntKey {
    int key;
} IntKey;

IntKey *new_integer_type();

int integer_type_compare(const IntKey *k1, const IntKey *k2);

char *integer_type_to_string(const int *key);

#endif //REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
