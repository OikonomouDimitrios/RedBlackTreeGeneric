
//
// Created by Oikonomou Dimitrios on 5/3/2023.
//


#include <stdio.h>
#include "IntegerTypeKey.h"

IntKey *new_integer_type() {
    IntKey *New = malloc(sizeof(IntKey));
    return New;
}

int integer_type_compare(const IntKey *k1, const IntKey *k2) {
    assert(k1 != NULL && k2 != NULL);
    return k1->key > k2->key ? 1 : k1->key == k2->key ? 0 : -1;
}

void integer_type_to_string(const int *key, char *buffer, size_t buffer_size) {
    int value = *((int *) key);
    snprintf(buffer, buffer_size, "%d", value);
}