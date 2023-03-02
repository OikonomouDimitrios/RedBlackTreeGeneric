#include <stdio.h>
#include "RedBlackTreeFunctions.h"
#include "IntegerTypeKey.h"

int getValueFromUser();

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
    RedBlackTree RBTree = RBT_initializeTree(keyCompare);
    while (c != 'q') {
        printf("\ninsert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            RBT_insertNode(&RBTree, getValueFromUser());
        } else if (c == 'p') {
            RBT_printTree(&RBTree);
        } else if (c == 'd') {
            RBT_deleteNode(&RBTree, getValueFromUser());
        }
    }
    RBT_free(&RBTree);
    return 0;
}

int getValueFromUser() {
    int x;
    printf("\ngive me a key:");
    scanf("%d", &x);
    return x;
}