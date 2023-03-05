//
// Created by DimitrisPhys_Desktop on 31/12/2022.
//

#ifndef REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
#define REDBLACKTREE_REDBLACKTREEFUNCTIONS_H

#include <stdbool.h>
#include <string.h>

typedef struct node *Node;

typedef struct rbTree *RedBlackTree;

void rbt_insert_node(RedBlackTree *redBlackTree, const void *value_from_user);

RedBlackTree
rbt_initialize_tree(int (*compare_func)(const void *, const void *), char *(*transform_key_to_string_func)(const void *));

void rbt_print_tree(RedBlackTree *redBlackTree);

void rbt_delete_node(RedBlackTree *redBlackTree, const void *value_from_user);

void rbt_free(RedBlackTree *redBlackTree);

#endif //REDBLACKTREE_REDBLACKTREEFUNCTIONS_H
