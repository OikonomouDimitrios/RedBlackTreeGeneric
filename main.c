#include <stdio.h>
#include "RedBlackTreeFunctions.h"
#include "IntegerTypeKey.h"
#include "StringTypeKey.h"

IntKey *getValueFromUser();

StringKey *getStringValueFromUser();

void print_menu();


IntKey *getValueFromUser() {
    IntKey *integerType = new_integer_type();
    printf("\nEnter an integer: ");
    scanf("%d", &(integerType)->key);
    return integerType;
}

StringKey *getStringValueFromUser() {
    char buffer[100]; // or whatever size you want to allocate for the string
    printf("Enter a string: ");
    scanf("%s", buffer);
    StringKey *str = new_string_type();
    assert(str != NULL);
    strcpy(str->key, buffer);
    return str;
}

void print_menu() {
    printf("\n====================\n");
    printf("=      MENU        =\n");
    printf("====================\n");
    printf("1. Insert integer node to integers' Red-Black tree\n");
    printf("2. Insert string node to  string' Red-Black tree\n");
    printf("3. Print integers tree\n");
    printf("4. Print strings tree\n");
    printf("5. Delete integer node\n");
    printf("6. Delete string node\n");
    printf("7. Exit\n");
    printf("====================\n\n");
}

int main() {
    printf("\nThis program simulates two Red Black Trees, one for integers, one for strings\n");
    int error, is_empty = 0;
    RedBlackTree RBTree = rbt_initialize_tree((int (*)(const void *, const void *)) integer_type_compare,
                                              (void (*)(const void *, char *buffer,
                                                        size_t buffer_size)) integer_type_to_string);
    RedBlackTree RBTree_string = rbt_initialize_tree((int (*)(const void *, const void *)) string_type_compare,
                                                     (void (*)(const void *, char *buffer,
                                                               size_t buffer_size)) string_type_to_string);
    int choice = 0;

    while (choice != 7) {
        print_menu();
        printf("Enter your choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer
            while (getchar() != '\n') {}
            printf("Invalid input! Please enter an integer.\n");
            continue;
        }
        switch (choice) {
            case 1: {
                error = 0;
                rbt_insert_node(&RBTree, getValueFromUser(), &error);
                if (error) {
                    printf("Value already exists! No duplicates allowed.\n");
                } else {
                    printf("Value successfully inserted into red black tree!\n");
                }
                break;
            }
            case 2: {
                error = 0;
                rbt_insert_node(&RBTree_string, getStringValueFromUser(), &error);
                if (error) {
                    printf("Value already exists! No duplicates allowed.\n");
                } else {
                    printf("Value successfully inserted into red black tree!\n");
                }
                break;
            }
            case 3: {
                is_empty = 0;
                rbt_print_tree(&RBTree, &is_empty);
                if (is_empty) {
                    printf("Integer tree is empty.\n");
                }
                break;
            }
            case 4: {
                is_empty = 0;
                rbt_print_tree(&RBTree_string, &is_empty);
                if (is_empty) {
                    printf("String tree is empty.\n");
                }
                break;
            }
            case 5: {
                error = 0;
                rbt_delete_node(&RBTree, getValueFromUser(), &error);
                if (error) {
                    printf("Value does not exist in red black tree!\n");
                } else {
                    printf("Value successfully deleted from red black tree!\n");
                }
                break;
            }
            case 6: {
                error = 0;
                rbt_delete_node(&RBTree_string, getStringValueFromUser(), &error);
                if (error) {
                    printf("String  not found in the tree.\n");
                } else {
                    printf("String successfully deleted from red black tree!\n");
                }
                break;
            }
            case 7:
                printf("Exiting...");
                rbt_free(&RBTree);
                rbt_free(&RBTree_string);
                break;
            default: {
                printf("Invalid choice! Please choose an option from 1-7.\n");
                break;
            }
        }
    }
}