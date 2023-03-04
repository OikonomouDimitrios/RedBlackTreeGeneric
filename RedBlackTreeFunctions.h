//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include <string.h>

typedef struct node *Node;

typedef struct rbTree *RedBlackTree;

void RBT_insertNode(RedBlackTree *redBlackTree, const void *valueFromUser);

RedBlackTree
RBT_initializeTree(int (*compare)(const void *, const void *), char *(*transformKeyToString)(const void *));

void RBT_printTree(RedBlackTree *redBlackTree);

void RBT_deleteNode(RedBlackTree *redBlackTree, const void *valueFromUser);

void RBT_free(RedBlackTree *redBlackTree);

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
