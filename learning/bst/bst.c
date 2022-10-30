#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct treenode* create_node(int data) {
    struct treenode *new_node = malloc(sizeof(struct treenode));
    if (new_node == NULL) {
        printf("Error: failed to allocate data for new tree node\n");
        exit(EXIT_FAILURE);
    }

    new_node->val = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

struct treenode* get_minmax(struct treenode *tree, char dir) {
    if (dir == 'l') {
        while (tree->left != NULL) {
            tree = tree->left;
        }

        return tree;
    } else if (dir == 'r') {
        while (tree->right != NULL) {
            tree = tree->right;
        }

        return tree;
    } else {
        printf("Error: dir must be l (left) or r (right)\n");
        return NULL;
    }
}

void insert_node(struct treenode **root, int data) {
    // fires only when tree root node is uninitialised (NULL)
    if (!(*root)) {
        struct treenode *new_node = create_node(data);
        *root = new_node;
        return;
    }

    struct treenode *curr = *root;
    struct treenode *trailing_node = NULL;

    while (curr != NULL) {
        trailing_node = curr;
        if (data < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (data < trailing_node->val) {
        trailing_node->left = create_node(data);
    } else {
        trailing_node->right = create_node(data);
    }
}

void delete_node(struct treenode **root, int to_delete) {
    if (!(*root)) {
        printf("The tree contains no nodes!\n");
        return;
    }

    struct treenode *curr = *root;
    struct treenode *parent_node = NULL;

    while (curr != NULL && curr->val != to_delete) {
        parent_node = curr;
        if (to_delete < curr->val) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (curr) {
        if (curr->left == NULL && curr->right == NULL) {

            // need to NULL parent node to get rid of problematic dangling pointer
            if (curr->val < parent_node->val) {
                parent_node->left = NULL;
            } else {
                parent_node->right = NULL;
            }

            free(curr);
            curr = NULL;
        } else if (curr->left || curr->right) {
            struct treenode* child = curr->left ? curr->left : curr->right;

            // same as above, need to NULL left or right of current node in this case, to remove dangling pointers
            if (child->val < curr->val) {
                curr->left = NULL;
            } else {
                curr->right = NULL;
            }

            curr->val = child->val;
            free(child);
            child = NULL;
        } else {
            struct treenode* successor = get_minmax(curr->right, 'l');

            curr->val = successor->val;
            // repeat process so that we can delete successor and make sure that dangling pointer is NULLed
            delete_node(root, successor->val);
        }
    } else {
        printf("Node to delete not found\n");
        return;
    }
}

struct treenode* search_node(struct treenode *tree, int to_find) {
    while (tree != NULL && tree->val != to_find) {
        if (to_find < tree->val) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }

    return tree;
}

void print_tree_inorder(struct treenode *node) {
    if (node == NULL) return;

    print_tree_inorder(node->left);
    printf("%d\n", node->val);
    print_tree_inorder(node->right);
}

void tree_destroy(struct treenode *tree) {
    if (tree == NULL) return;

    tree_destroy(tree->left);
    tree_destroy(tree->right);

    free(tree);
    tree = NULL;
}