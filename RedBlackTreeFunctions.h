//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include <string.h>

typedef struct node *Node;

typedef struct rbTree *RedBlackTree;

/*
 * Contract for the rbt_insert_node function
 *
 * Preconditions:
 * - `redBlackTree` points to a valid RedBlackTree struct.
 * - `value_from_user` is a pointer to the value to be inserted into the tree.
 * - `error` is a pointer to a variable that can be used to indicate any errors that occur during the insertion process.
 *
 * Postconditions:
 * - If the value was successfully inserted into the tree, the function returns without modifying the RedBlackTree struct, and sets *error to 0.
 * - If an error occurs during the insertion process, the function sets *error to a non-zero value that indicates the type of error that occurred, and returns without modifying the RedBlackTree struct.
 */
void rbt_insert_node(RedBlackTree *redBlackTree, void *value_from_user, int *error);


RedBlackTree
rbt_initialize_tree(int (*compare_func)(const void *, const void *),
                    void (*transform_key_to_string_func)(const void *, char *buffer, size_t buffer_size));

void rbt_print_tree(RedBlackTree *redBlackTree);

void rbt_delete_node(RedBlackTree *redBlackTree, const void *value_from_user, int *error);

void rbt_free(RedBlackTree *redBlackTree);

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
