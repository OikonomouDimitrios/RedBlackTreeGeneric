//
// Created by Oikonomou Dimitrios on 25/2/2023.
//


#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "RedBlackTreeFunctions.h"

typedef enum Colour {
    Red,
    Black
} Colour;

struct rbTree {
    Node root;
    Node sentinelNode; //to avoid edge cases with nulls

    int (*compare)(const void *, const void *);

    char *(*transformKeyToString)(const void *);

};

struct node {
    const void *key;
    Colour colour;
    Node left;
    Node right;
    Node parent;
};

RedBlackTree RBTree;

const char *colours[] = {"red", "black"};


void insertFixup(RedBlackTree *redBlackTree, Node z);

void leftRotate(RedBlackTree *redBlackTree, Node x);

void rightRotate(RedBlackTree *redBlackTree, Node y);

void transplant(RedBlackTree *redBlackTree, Node u, Node v);

bool isLeftChild(Node node);

bool isRightChild(Node node);

Node TreeMinimum(Node auxNode, Node sentinelNode);

void deleteFixup(RedBlackTree *redBlackTree, Node x);

Node initializeNewNode(Node sentinelNode, const void *key, Colour colour);

Node initializeNullNode();

Node findNode(Node auxNode, RedBlackTree rbTree, const void *key);

void freeNode(Node n);

void printTreeInternal(RedBlackTree redBlackTree, Node x);

void RBT_insertNode(RedBlackTree *redBlackTree, const void *valueFromUser) {
    Node nullNode = (*redBlackTree)->sentinelNode;
    if (findNode((*redBlackTree)->root, *redBlackTree, valueFromUser)) {
        printf("value already exists! No duplicates allowed.\n");
        return;
    }
    Node newNode = initializeNewNode((*redBlackTree)->sentinelNode, valueFromUser, Red);
    Node y = nullNode;
    Node x = (*redBlackTree)->root;
    while (x != nullNode) {
        y = x;
        if ((*redBlackTree)->compare((newNode->key), (x->key)) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    newNode->parent = y;
    if (y == nullNode) {
        (*redBlackTree)->root = newNode;
    } else if ((*redBlackTree)->compare((newNode->key), (y->key)) < 0) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }
    insertFixup(redBlackTree, newNode);
}

void insertFixup(RedBlackTree *redBlackTree, Node z) {
    Node uncle;
    Node nullNode = (*redBlackTree)->sentinelNode;
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
                    leftRotate(redBlackTree, z);
                }
                z->parent->colour = Black;
                if (z->parent->parent != nullNode) {
                    z->parent->parent->colour = Red;
                    rightRotate(redBlackTree, z->parent->parent);
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
                    rightRotate(redBlackTree, z);
                }
                z->parent->colour = Black;
                if (z->parent->parent != nullNode) {
                    z->parent->parent->colour = Red;
                    leftRotate(redBlackTree, z->parent->parent);
                }
            }
        }
    }
    (*redBlackTree)->root->colour = Black;
}

RedBlackTree
RBT_initializeTree(int (*compare)(const void *, const void *), char *(*transformKeyToString)(const void *)) {
    RBTree = (RedBlackTree) malloc(sizeof(struct rbTree));
    Node sentinel = initializeNullNode();
    RBTree->root = sentinel;
    RBTree->sentinelNode = sentinel;
    RBTree->compare = compare;
    RBTree->transformKeyToString = transformKeyToString;
    return RBTree;
}

void rightRotate(RedBlackTree *redBlackTree, Node y) {
    Node nullNode = (*redBlackTree)->sentinelNode;
    Node x = y->left;
    y->left = x->right;
    if (x->right != nullNode) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullNode) {
        (*redBlackTree)->root = x;
    } else if (isLeftChild(y)) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

void leftRotate(RedBlackTree *redBlackTree, Node x) {
//The code for LEFT-ROTATE assumes that x.right is not T.nil and that the
//root’s parent is T.nil.
    Node nullNode = (*redBlackTree)->sentinelNode;
    Node y = x->right;
    x->right = y->left;
    if (y->left != nullNode) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullNode) {
        (*redBlackTree)->root = y;
    } else if (isLeftChild(x)) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

}

void RBT_deleteNode(RedBlackTree *redBlackTree, const void *valueFromUser) {
    Node nullNode = (*redBlackTree)->sentinelNode;
    Node nodeForDeletion = findNode((*redBlackTree)->root, *redBlackTree, valueFromUser);
    if (!nodeForDeletion) {
        printf("No such key exists in RB Tree!\n");
        return;
    } else {
        Node y = nodeForDeletion;
        Colour y_original_Colour = y->colour;
        Node x;
        if (nodeForDeletion->left == nullNode) {
            x = nodeForDeletion->right;
            transplant(redBlackTree, nodeForDeletion, nodeForDeletion->right);
        } else if (nodeForDeletion->right == nullNode) {
            x = nodeForDeletion->left;
            transplant(redBlackTree, nodeForDeletion, nodeForDeletion->left);

        } else {
            y = TreeMinimum(nodeForDeletion->right, (*redBlackTree)->sentinelNode);
            y_original_Colour = y->colour;
            x = y->right;
            if (y->parent == nodeForDeletion) {
                x->parent = y;
            } else {
                transplant(redBlackTree, y, y->right);
                y->right = nodeForDeletion->right;
                y->right->parent = y;
            }
            transplant(redBlackTree, nodeForDeletion, y);
            y->left = nodeForDeletion->left;
            y->left->parent = y;
            y->colour = nodeForDeletion->colour;
        }
        freeNode(nodeForDeletion);
        if (y_original_Colour == Black) {
            deleteFixup(redBlackTree, x);
        }
    }
}

void deleteFixup(RedBlackTree *redBlackTree, Node x) {
    while (x != (*redBlackTree)->root && x->colour == Black) {
        if (x == x->parent->left) {
            Node w = x->parent->right;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                x->parent->colour = Red; // case 1
                leftRotate(redBlackTree, x->parent); // case 1
                w = x->parent->right; // case 1
            }
            if (w->left->colour == Black && w->right->colour == Black) {
                w->colour = Red; // case 2
                x = x->parent; // case 2
            } else {
                if (w->right->colour == Black) {
                    w->left->colour = Black; // case 3
                    w->colour = Red; // case 3
                    rightRotate(redBlackTree, w); // case 3
                    w = x->parent->right; // case 3
                }

                w->colour = x->parent->colour; // case 4
                x->parent->colour = Black; // case 4
                w->right->colour = Black; // case 4
                leftRotate(redBlackTree, x->parent); // case 4
                x = (*redBlackTree)->root; // case 4
            }
        } else { // same as then clause with "right" and "left" exchanged
            Node w = x->parent->left;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                x->parent->colour = Red; // case 1
                rightRotate(redBlackTree, x->parent); // case 1
                w = x->parent->left; // case 1
            }
            if (w->right->colour == Black && w->left->colour == Black) {
                w->colour = Red; // case 2
                x = x->parent; // case 2
            } else {
                if (w->left->colour == Black) {
                    w->right->colour = Black; // case 3
                    w->colour = Red; // case 3
                    leftRotate(redBlackTree, w); // case 3
                    w = x->parent->left; // case 3
                }

                w->colour = x->parent->colour; // case 4
                x->parent->colour = Black; // case 4
                w->left->colour = Black; // case 4
                rightRotate(redBlackTree, x->parent); // case 4
                x = (*redBlackTree)->root; // case 4
            }
        }
    }
    x->colour = Black;
}


Node TreeMinimum(Node auxNode, Node sentinelNode) {
    while (auxNode->left != sentinelNode) {
        return TreeMinimum(auxNode->left, sentinelNode);
    }
    return auxNode;
}

Node findNode(Node auxNode, RedBlackTree rbTree, const void *key) {
    if (!auxNode || auxNode == (rbTree)->sentinelNode) return NULL;
    int result = rbTree->compare(key, (auxNode->key));
    if (result == 0) return auxNode;
    if (result < 0) return findNode(auxNode->left, rbTree, key);
    else return findNode(auxNode->right, rbTree, key);
}

void RBT_printTree(RedBlackTree *redBlackTree) {
    assert((*redBlackTree) && (*redBlackTree)->root);
    printTreeInternal((*redBlackTree), (*redBlackTree)->root);
}

void printTreeInternal(RedBlackTree redBlackTree, Node x) {
    if (x != (redBlackTree)->sentinelNode) {
        if (x->left != (redBlackTree)->sentinelNode) {
            printTreeInternal(redBlackTree, x->left);
        }
        char isLeftOrRightChild[50];
        char keyValue[4];
        char *strParentKey = NULL;
        if (x->parent->key != NULL) {
            strParentKey = redBlackTree->transformKeyToString(x->parent->key);
            sprintf(keyValue, "%s", strParentKey);
            free(strParentKey);
//            sprintf(keyValue, "%s", ((char *) x->parent->key));
//            sprintf(keyValue, "%d", *((int *) x->parent->key));
        }
        if (isLeftChild(x)) {
            strcpy(isLeftOrRightChild, "left child of ");
            strcat(isLeftOrRightChild, keyValue);
        } else if (isRightChild(x)) {
            strcpy(isLeftOrRightChild, "right child of ");
            strcat(isLeftOrRightChild, keyValue);
        } else if (x->parent == (redBlackTree)->sentinelNode) {
            strcpy(isLeftOrRightChild, "root");
        }
        char *strKey = redBlackTree->transformKeyToString(x->key);
//        printf("\nkey : %d color : %s is %s ", *((int *) x->key), colours[x->colour], isLeftOrRightChild);
        printf("\nkey : %s color : %s is %s ", strKey, colours[x->colour], isLeftOrRightChild);
        free(strKey);
        if (x->right != (redBlackTree)->sentinelNode) {
            printTreeInternal(redBlackTree, x->right);
        }
    } else if (x == redBlackTree->sentinelNode) {
        printf("\n There are no nodes to print\n");
    }
}

void transplant(RedBlackTree *redBlackTree, Node u, Node v) {
    if (u->parent == (*redBlackTree)->sentinelNode) {
        (*redBlackTree)->root = v;
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


Node initializeNewNode(Node sentinelNode, const void *key, Colour colour) {
    Node newRecord = (Node) malloc(sizeof(struct node));
    assert(newRecord != NULL);
    (newRecord->key) = key;
    newRecord->colour = colour ? colour : Red;
    newRecord->left = sentinelNode;
    newRecord->right = sentinelNode;
    newRecord->parent = sentinelNode;
    return newRecord;
}

Node initializeNullNode() {
    Node newRecord = (Node) malloc(sizeof(struct node));
    assert(newRecord != NULL);
    newRecord->colour = Black;
    newRecord->left = newRecord;
    newRecord->right = newRecord;
    newRecord->parent = newRecord;
    return newRecord;
}

void RBT_postorder_walk(RedBlackTree *redBlackTree, Node n, void (*callback)(Node)) {
    if (n == NULL || n == (*redBlackTree)->sentinelNode) {
        return;
    }
    RBT_postorder_walk(redBlackTree, n->left, callback);
    RBT_postorder_walk(redBlackTree, n->right, callback);
    callback(n);
}

void RBT_free(RedBlackTree *redBlackTree) {
    // Free the nodes in the tree using a post-order traversal.
    RBT_postorder_walk(redBlackTree, (*redBlackTree)->root, freeNode);
    free((*redBlackTree)->sentinelNode);
    // Free the tree itself.
    free(redBlackTree);
}

// Helper function to free a node.
void freeNode(Node n) {
//    free(n->key);
//    free(n->value);
    free(n);
}