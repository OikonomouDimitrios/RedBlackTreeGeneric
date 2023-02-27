#include <stdio.h>
#include "RedBlackTreeFunctions.h"

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
    RedBlackTree RBTree = RBT_initializeTree();
    while (c != 'q') {
        printf("\ninsert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            RBT_insertNode(&RBTree);
        } else if (c == 'p') {
            RBT_printTree(&RBTree);
        } else if (c == 'd') {
            RBT_deleteNode(&RBTree);
        }
    }
    RBT_free(&RBTree);
    return 0;
}
