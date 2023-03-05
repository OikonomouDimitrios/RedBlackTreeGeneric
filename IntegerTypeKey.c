
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

char *integer_type_to_string(const int *key) {
    int value = *((int *) key);
    char *str = malloc(sizeof(char) * 12); // Maximum number of characters needed for a 32-bit integer
    sprintf(str, "%d", value);
    return str;
}