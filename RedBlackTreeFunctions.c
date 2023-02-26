//
// Created by Oikonomou Dimitrios on 25/2/2023.
//


#include <stdio.h>
#include <malloc.h>
#include "RedBlackTreeFunctions.h"

typedef enum Colour {
    Red,
    Black
} Colour;

struct rbTree {
    Node root;
};

struct node {
    int key;
    Colour colour;
    Node left;
    Node right;
    Node parent;
};

Node rootNode, nullNode;
RedBlackTree RBTree;

const char *colours[] = {"red", "black"};


void insertFixup(Node z);

void leftRotate(Node x);

void rightRotate(Node y);

void transplant(Node u, Node v);

bool isLeftChild(Node node);

bool isRightChild(Node node);

Node TreeMinimum(Node auxNode);

void deleteFixup(Node x);

Node initializeNewNode(int key, Colour colour);

Node initializeNullNode();

Node findNode(Node auxNode, int key);

int getValueFromUser();

void printTreeInternal(Node x);

void RB_insertNode() {
    int valueFromUser = getValueFromUser();
    if (findNode((RBTree)->root, valueFromUser)) {
        printf("value already exists! No duplicates allowed.\n");
        return;
    }
    Node newNode = initializeNewNode(valueFromUser, Red);
    Node y = nullNode;
    Node x = (RBTree)->root;
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
        (RBTree)->root = newNode;
    } else if (newNode->key < y->key) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    insertFixup(newNode);
}

void insertFixup(Node z) {
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
                    leftRotate(z);
                }
                z->parent->colour = Black;
                if (z->parent->parent != nullNode) {
                    z->parent->parent->colour = Red;
                    rightRotate(z->parent->parent);
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
                    rightRotate(z);
                }
                z->parent->colour = Black;
                if (z->parent->parent != nullNode) {
                    z->parent->parent->colour = Red;
                    leftRotate(z->parent->parent);
                }
            }
        }
    }
    (RBTree)->root->colour = Black;
}

void RB_initializeTree() {
    RBTree = (RedBlackTree) malloc(sizeof(struct rbTree));
    nullNode = initializeNullNode();
    rootNode = nullNode;
    RBTree->root = rootNode;
}

void rightRotate(Node y) {
    Node x = y->left;
    y->left = x->right;
    if (x->right != nullNode) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullNode) {
        (RBTree)->root = x;
    } else if (isLeftChild(y)) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void leftRotate(Node x) {
//The pseudocode for LEFT-ROTATE assumes that x.right is not T.nil and that the
//root’s parent is T.nil.
    Node y = x->right;
    x->right = y->left;
    if (y->left != nullNode) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullNode) {
        (RBTree)->root = y;
    } else if (isLeftChild(x)) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

}

void RB_deleteNode() {
    Node z = findNode((RBTree)->root, getValueFromUser());
    if (!z) {
        printf("No such key exists in RB Tree!\n");
        return;
    } else {
        Node y = z;
        Colour y_original_Colour = y->colour;
        Node x;
        if (z->left == nullNode) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullNode) {
            x = z->left;
            transplant(z, z->left);

        } else {
            y = TreeMinimum(z->right);
            y_original_Colour = y->colour;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->colour = z->colour;
        }
        //delete node here
        if (y_original_Colour == Black) {
            deleteFixup(x);
        }
    }
}

void deleteFixup(Node x) {
    while (x != (RBTree)->root && x->colour == Black) {
        if (x == x->parent->left) {
            Node w = x->parent->right;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                x->parent->colour = Red; // case 1
                leftRotate(x->parent); // case 1
                w = x->parent->right; // case 1
            }
            if (w->left->colour == Black && w->right->colour == Black) {
                w->colour = Red; // case 2
                x = x->parent; // case 2
            } else {
                if (w->right->colour == Black) {
                    w->left->colour = Black; // case 3
                    w->colour = Red; // case 3
                    rightRotate(w); // case 3
                    w = x->parent->right; // case 3
                }

                w->colour = x->parent->colour; // case 4
                x->parent->colour = Black; // case 4
                w->right->colour = Black; // case 4
                leftRotate(x->parent); // case 4
                x = (RBTree)->root; // case 4
            }
        } else { // same as then clause with "right" and "left" exchanged
            Node w = x->parent->left;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                x->parent->colour = Red; // case 1
                rightRotate(x->parent); // case 1
                w = x->parent->left; // case 1
            }
            if (w->right->colour == Black && w->left->colour == Black) {
                w->colour = Red; // case 2
                x = x->parent; // case 2
            } else {
                if (w->left->colour == Black) {
                    w->right->colour = Black; // case 3
                    w->colour = Red; // case 3
                    leftRotate(w); // case 3
                    w = x->parent->left; // case 3
                }

                w->colour = x->parent->colour; // case 4
                x->parent->colour = Black; // case 4
                w->left->colour = Black; // case 4
                rightRotate(x->parent); // case 4
                x = (RBTree)->root; // case 4
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

Node findNode(Node auxNode, int key) {
    if (!auxNode || auxNode == nullNode) return NULL;
    if (key == auxNode->key) return auxNode;
    if (key < auxNode->key) return findNode(auxNode->left, key);
    else return findNode(auxNode->right, key);
}

void RB_printTree() {
    printTreeInternal((RBTree)->root);
}

void printTreeInternal(Node x) {
    if (x != nullNode) {
        if (x->left != nullNode) {
            printTreeInternal(x->left);
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
            printTreeInternal(x->right);
        }
    } else if (x == nullNode) {
        printf("\n There are no nodes to print\n");
    }
}

void transplant(Node u, Node v) {
    if (u->parent == nullNode) {
        (RBTree)->root = v;
    } else if (isLeftChild(u)) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


bool isLeftChild(Node node) {
    return node == node->parent->left;
}

bool isRightChild(Node node) {
    return node == node->parent->right;
}


int getValueFromUser() {
    int x;
    printf("\ngive me a key:");
    scanf("%d", &x);
    return x;

}

Node initializeNewNode(int key, Colour colour) {
    Node newRecord = (Node) malloc(sizeof(struct node));
    newRecord->key = key;
    newRecord->colour = colour ? colour : Red;
    newRecord->left = nullNode;
    newRecord->right = nullNode;
    newRecord->parent = nullNode;
    return newRecord;
}

Node initializeNullNode() {
    Node newRecord = initializeNewNode(0, Black);
    newRecord->left = newRecord;
    newRecord->right = newRecord;
    newRecord->parent = newRecord;
    return newRecord;
}
