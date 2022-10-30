#ifndef BST_H
#define BST_H

struct treenode {
    int val;
    struct treenode *left;
    struct treenode *right;
};

struct treenode* create_node(int val);
void insert_node(struct treenode **tree, int data);
struct treenode* search_node(struct treenode *tree, int to_find);
void delete_node(struct treenode **root, int to_delete);
struct treenode* get_minmax(struct treenode *tree, char dir);
void print_tree_inorder(struct treenode *tree);
void tree_destroy(struct treenode *tree);

#endif