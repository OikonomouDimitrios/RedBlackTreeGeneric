//
// Created by Oikonomou Dimitrios on 3/3/2023.
//

#ifndef REDBLACKTREEGENERIC_STRINGTYPEKEY_H
#define REDBLACKTREEGENERIC_STRINGTYPEKEY_H

#include <malloc.h>
#include <string.h>

typedef struct StringKey {
    char key[150];
} StringKey;

StringKey *new_string_type();

int string_type_compare(const StringKey *k1, const StringKey *k2);

void string_type_to_string(const char *inputStr, char *buffer, size_t buffer_size);

#endif //REDBLACKTREEGENERIC_STRINGTYPEKEY_H
