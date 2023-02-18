//
// Created by DimitrisPhys_Desktop on 30/12/2022.
//

#ifndef REDBLACKTREE_NODE_H
#define REDBLACKTREE_NODE_H

#include <malloc.h>
#include "Constants.h"

typedef struct node *Node;
struct node {
    int key;
    Colour colour;
    Node left;
    Node right;
    Node parent;
};
Node root, nullNode;

Node initializeNewNode(int key, Colour colour) {
    Node newRecord = (Node) malloc(sizeof(struct node));
    newRecord->key = key;
    newRecord->colour = colour ? colour : Red;
    newRecord->left = nullNode;
    newRecord->right = nullNode;
    newRecord->parent = nullNode;
}

Node initializeNullNode() {
    Node newRecord = initializeNewNode(0, Black);
    newRecord->left = newRecord;
    newRecord->right = newRecord;
    newRecord->parent = newRecord;
}

#endif //REDBLACKTREE_NODE_H
