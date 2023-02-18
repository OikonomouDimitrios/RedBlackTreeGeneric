#include <stdio.h>
#include "RedBlackTreeFunctions.h"

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
    initializeBasicNodes();
    while (c != 'q') {
        printf("\n insert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            insertNode(&root);
        } else if (c == 'p') {
            printTree(root);
        } else if (c == 'd') {
            deleteNode(&root);
        }
    }
    return 0;
}
