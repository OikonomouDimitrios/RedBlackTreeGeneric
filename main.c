#include <stdio.h>
#include "RedBlackTreeFunctions.h"
#include "IntegerTypeKey.h"
#include "StringTypeKey.h"

IntKey *getValueFromUser();

StringKey *getStringValueFromUser();

int main() {
    printf("\nThis program simulates a Red Black Tree\n");
    char c = '*';
//    RedBlackTree RBTree = rbt_initialize_tree((int (*)(const void *, const void *)) integer_type_compare,
//                                              (char *(*)(const void *)) integer_type_to_string);
    RedBlackTree RBTree_string = rbt_initialize_tree((int (*)(const void *, const void *)) string_type_compare,
                                                     (char *(*)(const void *)) string_type_to_string);

    while (c != 'q') {
        printf("\ninsert(i), print(parent), delete(d), quit(q)\n");
        scanf("\n %c", &c);
        if (c == 'i') {
//            rbt_insert_node(&RBTree, (void *) getValueFromUser());
            rbt_insert_node(&RBTree_string, (void *) getStringValueFromUser());
        } else if (c == 'p') {
            rbt_print_tree(&RBTree_string);
        } else if (c == 'd') {
//            rbt_delete_node(&RBTree, (void *) getValueFromUser());
            rbt_delete_node(&RBTree_string, (void *) getStringValueFromUser());
        }
    }
//    rbt_free(&RBTree);
    rbt_free(&RBTree_string);

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
