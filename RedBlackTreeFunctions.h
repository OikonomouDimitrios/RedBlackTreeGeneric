//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include <string.h>

typedef struct node *Node;

typedef struct rbTree *RedBlackTree;
extern RedBlackTree RBTree;

void RB_insertNode(RedBlackTree *redBlackTree);

void RB_initializeTree();

void RB_printTree(RedBlackTree *redBlackTree);

void RB_deleteNode(RedBlackTree *redBlackTree);

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
