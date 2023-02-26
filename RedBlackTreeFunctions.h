//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include <string.h>

typedef struct node *Node;
typedef struct rbTree *RedBlackTree;

void RB_insertNode();

void RB_initializeTree();

void RB_printTree();

void RB_deleteNode();

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
