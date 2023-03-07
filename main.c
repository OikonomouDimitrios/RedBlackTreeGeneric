#include <stdio.h>
#include "RedBlackTreeFunctions.h"
#include "IntegerTypeKey.h"
#include "StringTypeKey.h"

IntKey *getValueFromUser();

StringKey *getStringValueFromUser();

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
    int error = 0;
    RedBlackTree RBTree = rbt_initialize_tree((int (*)(const void *, const void *)) integer_type_compare,
                                              (void (*)(const void *, char *buffer,
                                                        size_t buffer_size)) integer_type_to_string);
//    RedBlackTree RBTree_string = rbt_initialize_tree((int (*)(const void *, const void *)) string_type_compare,
//                                                     (void (*)(const void *, char *buffer,
//                                                               size_t buffer_size)) string_type_to_string);

    while (c != 'q') {
        printf("\ninsert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
            rbt_insert_node(&RBTree, (void *) getValueFromUser(), &error);
            if (error) {
                printf("Value already exists! No duplicates allowed.\n");
            } else {
                printf("Value successfully inserted into red black tree!\n");
            }
//            rbt_insert_node(&RBTree_string, (void *) getStringValueFromUser());
        } else if (c == 'p') {
            rbt_print_tree(&RBTree);
//            rbt_print_tree(&RBTree_string);
        } else if (c == 'd') {
            rbt_delete_node(&RBTree, (void *) getValueFromUser(), &error);
            if (error) {
                printf("Value does not exist in red black tree!\n");
            } else {
                printf("Value successfully deleted from red black tree!\n");
            }
//            rbt_delete_node(&RBTree_string, (void *) getStringValueFromUser());
        }
    }
    rbt_free(&RBTree);
//    rbt_free(&RBTree_string);

    return 0;
}

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
