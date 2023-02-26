#include <stdio.h>
#include "RedBlackTreeFunctions.h"

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
    RB_initializeTree();
    while (c != 'q') {
        printf("\ninsert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            RB_insertNode(&RBTree);
        } else if (c == 'p') {
            RB_printTree(&RBTree);
        } else if (c == 'd') {
            RB_deleteNode(&RBTree);
        }
    }
    return 0;
}
