#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int main(void) {
    struct treenode *root = NULL;
    char code;
    int val;

    for (;;) {
        printf("Enter code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')
            ;
        switch (code) {
            case 'i':
                printf("Enter the value to insert into the tree: ");
                scanf(" %d", &val);
                insert_node(&root, val);
                break;
            case 'd':
                printf("Enter the node value you'd like to delete: ");
                scanf(" %d", &val);
                delete_node(&root, val);
                break;
            case 'p':
                print_tree_inorder(root);
                break;
            case 's':
                printf("Enter the value to look for in the tree: ");
                scanf(" %d", &val);
                struct treenode *res = search_node(root, val);
                if (res != NULL) {
                    printf("Node with value %d found\n", res->val);
                } else printf("Node with value %d not found\n", val);
                break;
            case 'k':
                printf("Destroying tree...\n");
                tree_destroy(root);
                root = NULL;
                break;
            case 'q':
                return 0;
                break;
            default:
                printf("Invalid code\n");
        }
    }
}