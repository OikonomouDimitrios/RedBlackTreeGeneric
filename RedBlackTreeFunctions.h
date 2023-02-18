//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include "Node.h"
#include <string.h>

Node findNode(Node rootNode, int key);

int getValueFromUser();

void insertFixup(Node *rootNode, Node z);

void leftRotate(Node *rootNode, Node x);

void rightRotate(Node *rootNode, Node y);

bool isLeftChild(Node node);

bool isRightChild(Node node);

Node TreeMinimum(Node auxNode);

void deleteFixup(Node *rootNode, Node x);

void initializeBasicNodes() {
    nullNode = initializeNullNode();
    root = nullNode;
}

void insertNode(Node *rootNode) {
    int valueFromUser = getValueFromUser();
    if (findNode(*rootNode, valueFromUser)) {
        printf("value already exists! No duplicates allowed.\n");
        return;
    }
    Node newNode = initializeNewNode(valueFromUser, Red);
    Node y = nullNode;
    Node x = *rootNode;
    while (x != nullNode) {
        y = x;
        if (newNode->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    newNode->parent = y;
    if (y == nullNode) {
        (*rootNode) = newNode;
    } else if (newNode->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    insertFixup(&root, newNode);
}

void insertFixup(Node *rootNode, Node z) {
    Node uncle;
    while (z->parent && z->parent != nullNode && z->parent->colour == Red) {
        if (!z->parent->parent || z->parent->parent == nullNode) {
            break;
        }
        if (z->parent == z->parent->parent->left) {
            uncle = z->parent->parent->right;
            if (uncle->colour == Red) {
                z->parent->colour = Black;
                uncle->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(rootNode, z);
                }
                z->parent->colour = Black;
                if (z->parent->parent != nullNode) {
                    z->parent->parent->colour = Red;
                    rightRotate(rootNode, z->parent->parent);
                }
            }
        } else {
            uncle = z->parent->parent->left;
            if (uncle->colour == Red) {
                z->parent->colour = Black;
                uncle->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(rootNode, z);
                }
                z->parent->colour = Black;
                if (z->parent->parent != nullNode) {
                    z->parent->parent->colour = Red;
                    leftRotate(rootNode, z->parent->parent);
                }
            }
        }
    }
    (*rootNode)->colour = Black;
}


void rightRotate(Node *rootNode, Node y) {
    Node x = y->left;
    y->left = x->right;
    if (x->right != nullNode) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullNode) {
        (*rootNode) = x;
    } else if (isLeftChild(y)) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void leftRotate(Node *rootNode, Node x) {
//The pseudocode for LEFT-ROTATE assumes that x.right is not T.nil and that the
//root’s parent is T.nil.
    Node y = x->right;
    x->right = y->left;
    if (y->left != nullNode) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullNode) {
        (*rootNode) = y;
    } else if (isLeftChild(x)) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

}

int getValueFromUser() {
    int x;
    printf("\ngive me a key:");
    scanf("%d", &x);
    return x;

}

void printTree(Node x) {
    if (x != nullNode) {
        if (x->left != nullNode) {
            printTree(x->left);
        }
        char isLeftOrRightChild[50];
        char keyValue[4];
        sprintf(keyValue, "%d", x->parent->key);
        if (isLeftChild(x)) {
            strcpy(isLeftOrRightChild, "left child of ");
            strcat(isLeftOrRightChild, keyValue);
        } else if (isRightChild(x)) {
            strcpy(isLeftOrRightChild, "right child of ");
            strcat(isLeftOrRightChild, keyValue);
        } else if (x->parent == nullNode) {
            strcpy(isLeftOrRightChild, "root");
        }
        printf("\nkey : %d color : %s is %s ", x->key, colours[x->colour], isLeftOrRightChild);
        if (x->right != nullNode) {
            printTree(x->right);
        }
    } else if (x == nullNode) {
        printf("\n There are no nodes to print\n");
    }
}


void transplant(Node *rootNode, Node u, Node v) {
    if (u->parent == nullNode) {
        (*rootNode) = v;
    } else if (isLeftChild(u)) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void deleteNode(Node *rootNode) {
    Node z = findNode(*rootNode, getValueFromUser());
    if (!z) {
        printf("No such key exists in RB Tree!\n");
        return;
    } else {
        Node y = z;
        Colour y_original_Colour = y->colour;
        Node x;
        if (z->left == nullNode) {
            x = z->right;
            transplant(rootNode, z, z->right);
        } else if (z->right == nullNode) {
            x = z->left;
            transplant(rootNode, z, z->left);

        } else {
            y = TreeMinimum(z->right);
            y_original_Colour = y->colour;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(rootNode, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(rootNode, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->colour = z->colour;
        }
        //delete node here
        if (y_original_Colour == Black) {
            deleteFixup(rootNode, x);
        }
    }

    printf("not implemented!");
    //TODO IMPLEMENT
}

void deleteFixup(Node *rootNode, Node x) {
    while (x != *rootNode && x->colour == Black) {
        if (x == x->parent->left) {
            Node w = x->parent->right;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                x->parent->colour = Red; // case 1
                leftRotate(rootNode, x->parent); // case 1
                w = x->parent->right; // case 1
            }
            if (w->left->colour == Black && w->right->colour == Black) {
                w->colour = Red; // case 2
                x = x->parent; // case 2
            } else {
                if (w->right->colour == Black) {
                    w->left->colour = Black; // case 3
                    w->colour = Red; // case 3
                    rightRotate(rootNode, w); // case 3
                    w = x->parent->right; // case 3
                }

                w->colour = x->parent->colour; // case 4
                x->parent->colour = Black; // case 4
                w->right->colour = Black; // case 4
                leftRotate(rootNode, x->parent); // case 4
                x = *rootNode; // case 4
            }
        } else { // same as then clause with "right" and "left" exchanged
            Node w = x->parent->left;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                x->parent->colour = Red; // case 1
                rightRotate(rootNode, x->parent); // case 1
                w = x->parent->left; // case 1
            }
            if (w->right->colour == Black && w->left->colour == Black) {
                w->colour = Red; // case 2
                x = x->parent; // case 2
            } else {
                if (w->left->colour == Black) {
                    w->right->colour = Black; // case 3
                    w->colour = Red; // case 3
                    leftRotate(rootNode, w); // case 3
                    w = x->parent->left; // case 3
                }

                w->colour = x->parent->colour; // case 4
                x->parent->colour = Black; // case 4
                w->left->colour = Black; // case 4
                rightRotate(rootNode, x->parent); // case 4
                x = *rootNode; // case 4
            }
        }
    }
    x->colour = Black;
}


Node TreeMinimum(Node auxNode) {
    while (auxNode->left != nullNode) {
        return TreeMinimum(auxNode->left);
    }
    return auxNode;
}

Node findNode(Node rootNode, int key) {
    if (!rootNode || rootNode == nullNode) return NULL;
    if (key == rootNode->key) return rootNode;
    if (key < rootNode->key) return findNode(rootNode->left, key);
    else return findNode(rootNode->right, key);
}

bool isLeftChild(Node node) {
    return node == node->parent->left;
}

bool isRightChild(Node node) {
    return node == node->parent->right;
}

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
