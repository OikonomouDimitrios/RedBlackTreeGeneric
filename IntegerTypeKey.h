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

void integer_type_to_string(const int *key, char *buffer, size_t buffer_size);

#endif //REDBLACKTREEGENERIC_INTEGERTYPEKEY_H
