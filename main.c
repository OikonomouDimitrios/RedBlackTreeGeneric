#include <stdio.h>
#include "RedBlackTreeFunctions.h"
#include "IntegerTypeKey.h"
#include "StringTypeKey.h"

int *getValueFromUser();

char *getStringValueFromUser();

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
    RedBlackTree RBTree = RBT_initializeTree((int (*)(const void *, const void *)) intKeyCompare,
                                              (char *(*)(const void *)) intKeyToString);
//    RedBlackTree RBTree = RBT_initializeTree((int (*)(const void *, const void *)) keyCompare,
//                                             (char *(*)(const void *)) returnString);

    while (c != 'q') {
        printf("\ninsert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            RBT_insertNode(&RBTree, (void *) getValueFromUser());
        } else if (c == 'p') {
            RBT_printTree(&RBTree);
        } else if (c == 'd') {
            RBT_deleteNode(&RBTree, (void *) getValueFromUser());
        }
    }
    RBT_free(&RBTree);
    return 0;
}

int *getValueFromUser() {
    int *x = (int *) malloc(sizeof(int));
    printf("\nEnter an integer: ");
    scanf("%d", x);
    return x;
}

char *getStringValueFromUser() {
    char buffer[100]; // or whatever size you want to allocate for the string
    printf("Enter a string: ");
    scanf("%s", buffer);

    // Allocate a new string with the correct length
    char *str = (char *) malloc(strlen(buffer) + 1);
    if (str == NULL) {
        printf("Error: Failed to allocate memory for string.\n");
        exit(1);
    }

    // Copy the string into the new memory
    strcpy(str, buffer);

    return str;
}
