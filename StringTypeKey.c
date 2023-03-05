//
// Created by Oikonomou Dimitrios on 5/3/2023.
//

#include <malloc.h>
#include <stdio.h>
#include "StringTypeKey.h"

StringKey *new_string_type() {
    StringKey *New = malloc(sizeof(StringKey));
    return New;
}

int string_type_compare(const StringKey *k1, const StringKey *k2) {
    return strcmp(k1->key, k2->key);
}

void string_type_to_string(const char *inputStr, char *buffer, size_t buffer_size) {
    snprintf(buffer, buffer_size, "%s", inputStr);
}