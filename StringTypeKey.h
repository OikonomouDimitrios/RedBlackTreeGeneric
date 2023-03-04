//
// Created by Oikonomou Dimitrios on 3/3/2023.
//

#ifndef REDBLACKTREEGENERIC_STRINGTYPEKEY_H
#define REDBLACKTREEGENERIC_STRINGTYPEKEY_H

#include <malloc.h>
#include <string.h>

typedef struct StringKey {
    char x[40];
} StringTypeKey;

StringTypeKey *newStringTypeKey() {
    StringTypeKey *New = malloc(sizeof(StringTypeKey));
    /* printf("%p\n", New); */
    return New;
}

int keyCompare(const char k1[], const char k2[]) {
    return strcmp(k1, k2);
}

char *returnString(const char *inputStr) {
    char *resultStr = malloc(strlen(inputStr) + 1);
    strcpy(resultStr, inputStr);
    return resultStr;
}

#endif //REDBLACKTREEGENERIC_STRINGTYPEKEY_H
