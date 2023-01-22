#ifndef TRIE_H
#define TRIE_H

#define NUM_LETTERS_IN_ALPHABET 26

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct trienode {
    struct trienode *children[NUM_LETTERS_IN_ALPHABET];
    bool is_word;
};

bool initTrie(struct trienode **trie_root);
struct trienode* createNewTrienode(void);
bool insertWord(struct trienode **trie_root, char *word);
bool deleteWord(struct trienode **trie_root, char *word);
bool checkWordExists(struct trienode **trie_root, char *word);
int getBranchingIndex(struct trienode **trie_root, char *word);
char* getLongestPrefix(struct trienode **trie_root, char *word);
void printWordsFromPrefix(struct trienode **trie_root, char *prefix);
void trienodeRecursiveFree(struct trienode* to_free);
void trim_newline(char *str);

#endif