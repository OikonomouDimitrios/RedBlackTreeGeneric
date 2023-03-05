//
// Created by Oikonomou Dimitrios on 25/2/2023.
//


#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "RedBlackTreeFunctions.h"

#define BUFFER_SIZE 100

typedef enum Colour {
    Red,
    Black
} Colour;

struct rbTree {
    Node root;
    Node sentinel_node; //to avoid edge cases with nulls

    int (*compare_func)(const void *, const void *);

    void (*transform_key_to_string_func)(const void *, char *buffer, size_t buffer_size);

};

struct node {
    void *key;
    Colour colour;
    Node left;
    Node right;
    Node parent;
};

RedBlackTree RBTree;

const char *colours[] = {"red", "black"};


void rbt_insert_node_fixup(RedBlackTree *redBlackTree, Node aux_node);

void rbt_left_rotate(RedBlackTree *redBlackTree, Node aux_node);

void rbt_right_rotate(RedBlackTree *redBlackTree, Node aux_node);

void rbt_transplant(RedBlackTree *redBlackTree, Node aux_node, Node v);

bool rbt_is_left_child(Node node);

bool rbt_is_right_child(Node node);

Node rbt_tree_minimum(Node aux_node, Node sentinelNode);

void rbt_delete_fixup(RedBlackTree *redBlackTree, Node aux_node);

Node rbt_initialize_new_node(Node sentinel_node, void *key, Colour colour);

Node rbt_initialize_sentinel();

Node rbt_find_node(Node auxNode, RedBlackTree rbTree, const void *key);

void rbt_free_node(Node aux_node);

void rbt_print_tree_internal(RedBlackTree redBlackTree, Node aux_node);

void rbt_insert_node(RedBlackTree *redBlackTree, void *value_from_user) {
    Node nullNode = (*redBlackTree)->sentinel_node;
    if (rbt_find_node((*redBlackTree)->root, *redBlackTree, value_from_user)) {
        printf("value already exists! No duplicates allowed.\n");
        return;
    }
    Node new_node = rbt_initialize_new_node((*redBlackTree)->sentinel_node, value_from_user, Red);
    Node y = nullNode;
    Node x = (*redBlackTree)->root;
    while (x != nullNode) {
        y = x;
        if ((*redBlackTree)->compare_func((new_node->key), (x->key)) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    new_node->parent = y;
    if (y == nullNode) {
        (*redBlackTree)->root = new_node;
    } else if ((*redBlackTree)->compare_func((new_node->key), (y->key)) < 0) {
        y->left = new_node;
    } else {
        y->right = new_node;
    }
    rbt_insert_node_fixup(redBlackTree, new_node);
}

void rbt_insert_node_fixup(RedBlackTree *redBlackTree, Node aux_node) {
    Node uncle;
    Node nullNode = (*redBlackTree)->sentinel_node;
    while (aux_node->parent && aux_node->parent != nullNode && aux_node->parent->colour == Red) {
        if (!aux_node->parent->parent || aux_node->parent->parent == nullNode) {
            break;
        }
        if (aux_node->parent == aux_node->parent->parent->left) {
            uncle = aux_node->parent->parent->right;
            if (uncle->colour == Red) {
                aux_node->parent->colour = Black;
                uncle->colour = Black;
                aux_node->parent->parent->colour = Red;
                aux_node = aux_node->parent->parent;
            } else {
                if (aux_node == aux_node->parent->right) {
                    aux_node = aux_node->parent;
                    rbt_left_rotate(redBlackTree, aux_node);
                }
                aux_node->parent->colour = Black;
                if (aux_node->parent->parent != nullNode) {
                    aux_node->parent->parent->colour = Red;
                    rbt_right_rotate(redBlackTree, aux_node->parent->parent);
                }
            }
        } else {
            uncle = aux_node->parent->parent->left;
            if (uncle->colour == Red) {
                aux_node->parent->colour = Black;
                uncle->colour = Black;
                aux_node->parent->parent->colour = Red;
                aux_node = aux_node->parent->parent;
            } else {
                if (aux_node == aux_node->parent->left) {
                    aux_node = aux_node->parent;
                    rbt_right_rotate(redBlackTree, aux_node);
                }
                aux_node->parent->colour = Black;
                if (aux_node->parent->parent != nullNode) {
                    aux_node->parent->parent->colour = Red;
                    rbt_left_rotate(redBlackTree, aux_node->parent->parent);
                }
            }
        }
    }
    (*redBlackTree)->root->colour = Black;
}

RedBlackTree
rbt_initialize_tree(int (*compare_func)(const void *, const void *),
                    void(*transform_key_to_string_func)(const void *, char *buffer, size_t buffer_size)) {
    RBTree = (RedBlackTree) malloc(sizeof(struct rbTree));
    Node sentinel = rbt_initialize_sentinel();
    RBTree->root = sentinel;
    RBTree->sentinel_node = sentinel;
    RBTree->compare_func = compare_func;
    RBTree->transform_key_to_string_func = transform_key_to_string_func;
    return RBTree;
}

void rbt_right_rotate(RedBlackTree *redBlackTree, Node aux_node) {
    Node nullNode = (*redBlackTree)->sentinel_node;
    Node x = aux_node->left;
    aux_node->left = x->right;
    if (x->right != nullNode) {
        x->right->parent = aux_node;
    }
    x->parent = aux_node->parent;
    if (aux_node->parent == nullNode) {
        (*redBlackTree)->root = x;
    } else if (rbt_is_left_child(aux_node)) {
        aux_node->parent->left = x;
    } else {
        aux_node->parent->right = x;
    }
    x->right = aux_node;
    aux_node->parent = x;
}

void rbt_left_rotate(RedBlackTree *redBlackTree, Node aux_node) {
    Node nullNode = (*redBlackTree)->sentinel_node;
    Node y = aux_node->right;
    aux_node->right = y->left;
    if (y->left != nullNode) {
        y->left->parent = aux_node;
    }
    y->parent = aux_node->parent;
    if (aux_node->parent == nullNode) {
        (*redBlackTree)->root = y;
    } else if (rbt_is_left_child(aux_node)) {
        aux_node->parent->left = y;
    } else {
        aux_node->parent->right = y;
    }
    y->left = aux_node;
    aux_node->parent = y;

}

void rbt_delete_node(RedBlackTree *redBlackTree, const void *value_from_user) {
    Node nullNode = (*redBlackTree)->sentinel_node;
    Node node_to_be_deleted = rbt_find_node((*redBlackTree)->root, *redBlackTree, value_from_user);
    if (!node_to_be_deleted) {
        printf("No such key exists in RB Tree!\n");
        return;
    } else {
        Node y = node_to_be_deleted;
        Colour y_original_Colour = y->colour;
        Node x;
        if (node_to_be_deleted->left == nullNode) {
            x = node_to_be_deleted->right;
            rbt_transplant(redBlackTree, node_to_be_deleted, node_to_be_deleted->right);
        } else if (node_to_be_deleted->right == nullNode) {
            x = node_to_be_deleted->left;
            rbt_transplant(redBlackTree, node_to_be_deleted, node_to_be_deleted->left);

        } else {
            y = rbt_tree_minimum(node_to_be_deleted->right, (*redBlackTree)->sentinel_node);
            y_original_Colour = y->colour;
            x = y->right;
            if (y->parent == node_to_be_deleted) {
                x->parent = y;
            } else {
                rbt_transplant(redBlackTree, y, y->right);
                y->right = node_to_be_deleted->right;
                y->right->parent = y;
            }
            rbt_transplant(redBlackTree, node_to_be_deleted, y);
            y->left = node_to_be_deleted->left;
            y->left->parent = y;
            y->colour = node_to_be_deleted->colour;
        }
        rbt_free_node(node_to_be_deleted);
        if (y_original_Colour == Black) {
            rbt_delete_fixup(redBlackTree, x);
        }
    }
}

void rbt_delete_fixup(RedBlackTree *redBlackTree, Node aux_node) {
    while (aux_node != (*redBlackTree)->root && aux_node->colour == Black) {
        if (aux_node == aux_node->parent->left) {
            Node w = aux_node->parent->right;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                aux_node->parent->colour = Red; // case 1
                rbt_left_rotate(redBlackTree, aux_node->parent); // case 1
                w = aux_node->parent->right; // case 1
            }
            if (w->left->colour == Black && w->right->colour == Black) {
                w->colour = Red; // case 2
                aux_node = aux_node->parent; // case 2
            } else {
                if (w->right->colour == Black) {
                    w->left->colour = Black; // case 3
                    w->colour = Red; // case 3
                    rbt_right_rotate(redBlackTree, w); // case 3
                    w = aux_node->parent->right; // case 3
                }

                w->colour = aux_node->parent->colour; // case 4
                aux_node->parent->colour = Black; // case 4
                w->right->colour = Black; // case 4
                rbt_left_rotate(redBlackTree, aux_node->parent); // case 4
                aux_node = (*redBlackTree)->root; // case 4
            }
        } else { // same as then clause with "right" and "left" exchanged
            Node w = aux_node->parent->left;
            if (w->colour == Red) {
                w->colour = Black; // case 1
                aux_node->parent->colour = Red; // case 1
                rbt_right_rotate(redBlackTree, aux_node->parent); // case 1
                w = aux_node->parent->left; // case 1
            }
            if (w->right->colour == Black && w->left->colour == Black) {
                w->colour = Red; // case 2
                aux_node = aux_node->parent; // case 2
            } else {
                if (w->left->colour == Black) {
                    w->right->colour = Black; // case 3
                    w->colour = Red; // case 3
                    rbt_left_rotate(redBlackTree, w); // case 3
                    w = aux_node->parent->left; // case 3
                }

                w->colour = aux_node->parent->colour; // case 4
                aux_node->parent->colour = Black; // case 4
                w->left->colour = Black; // case 4
                rbt_right_rotate(redBlackTree, aux_node->parent); // case 4
                aux_node = (*redBlackTree)->root; // case 4
            }
        }
    }
    aux_node->colour = Black;
}


Node rbt_tree_minimum(Node aux_node, Node sentinelNode) {
    while (aux_node->left != sentinelNode) {
        return rbt_tree_minimum(aux_node->left, sentinelNode);
    }
    return aux_node;
}

Node rbt_find_node(Node auxNode, RedBlackTree rbTree, const void *key) {
    if (!auxNode || auxNode == (rbTree)->sentinel_node) return NULL;
    int result = rbTree->compare_func(key, (auxNode->key));
    if (result == 0) return auxNode;
    if (result < 0) return rbt_find_node(auxNode->left, rbTree, key);
    else return rbt_find_node(auxNode->right, rbTree, key);
}

void rbt_print_tree(RedBlackTree *redBlackTree) {
    assert((*redBlackTree) && (*redBlackTree)->root);
    rbt_print_tree_internal((*redBlackTree), (*redBlackTree)->root);
}

void rbt_print_tree_internal(RedBlackTree redBlackTree, Node aux_node) {
    if (aux_node != (redBlackTree)->sentinel_node) {
        if (aux_node->left != (redBlackTree)->sentinel_node) {
            rbt_print_tree_internal(redBlackTree, aux_node->left);
        }
        char is_left_or_right_child[50];
        char keyValue[150];
        char buffer[BUFFER_SIZE];
        if (aux_node != NULL && aux_node->parent != (redBlackTree)->sentinel_node && aux_node->parent &&
            aux_node->parent->key != NULL) {
            redBlackTree->transform_key_to_string_func(aux_node->parent->key, buffer, BUFFER_SIZE);
            sprintf(keyValue, "%s", buffer);
        }
        if (rbt_is_left_child(aux_node)) {
            strcpy(is_left_or_right_child, "left child of ");
            strcat(is_left_or_right_child, keyValue);
        } else if (rbt_is_right_child(aux_node)) {
            strcpy(is_left_or_right_child, "right child of ");
            strcat(is_left_or_right_child, keyValue);
        } else if (aux_node->parent == (redBlackTree)->sentinel_node) {
            strcpy(is_left_or_right_child, "root");
        }
        redBlackTree->transform_key_to_string_func(aux_node->key, buffer, BUFFER_SIZE);
        printf("\nkey : %s color : %s is %s ", buffer, colours[aux_node->colour], is_left_or_right_child);
        if (aux_node->right != (redBlackTree)->sentinel_node) {
            rbt_print_tree_internal(redBlackTree, aux_node->right);
        }
    } else if (aux_node == redBlackTree->sentinel_node) {
        printf("\n There are no nodes to print\n");
    }
}

void rbt_transplant(RedBlackTree *redBlackTree, Node aux_node, Node v) {
    if (aux_node->parent == (*redBlackTree)->sentinel_node) {
        (*redBlackTree)->root = v;
    } else if (rbt_is_left_child(aux_node)) {
        aux_node->parent->left = v;
    } else {
        aux_node->parent->right = v;
    }
    v->parent = aux_node->parent;
}


bool rbt_is_left_child(Node node) {
    return node == node->parent->left;
}

bool rbt_is_right_child(Node node) {
    return node == node->parent->right;
}


Node rbt_initialize_new_node(Node sentinel_node, void *key, Colour colour) {
    Node newRecord = (Node) malloc(sizeof(struct node));
    assert(newRecord != NULL);
    (newRecord->key) = key;
    newRecord->colour = colour ? colour : Red;
    newRecord->left = sentinel_node;
    newRecord->right = sentinel_node;
    newRecord->parent = sentinel_node;
    return newRecord;
}

Node rbt_initialize_sentinel() {
    Node newRecord = (Node) malloc(sizeof(struct node));
    assert(newRecord != NULL);
    newRecord->colour = Black;
    newRecord->left = newRecord;
    newRecord->right = newRecord;
    newRecord->parent = newRecord;
    return newRecord;
}

void rbt_postorder_walk(RedBlackTree *redBlackTree, Node n, void (*callback)(Node)) {
    if (n == NULL || n == (*redBlackTree)->sentinel_node) {
        return;
    }
    rbt_postorder_walk(redBlackTree, n->left, callback);
    rbt_postorder_walk(redBlackTree, n->right, callback);
    callback(n);
}

void rbt_free(RedBlackTree *redBlackTree) {
    // Free the nodes in the tree using a post-order traversal.
    rbt_postorder_walk(redBlackTree, (*redBlackTree)->root, rbt_free_node);
    free((*redBlackTree)->sentinel_node);
    // Free the tree itself.
    free(*redBlackTree);
}

// Helper function to free a node.
void rbt_free_node(Node aux_node) {
    free(aux_node->key);
    free(aux_node);
}