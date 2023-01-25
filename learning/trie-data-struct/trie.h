#ifndef TRIE_H
#define TRIE_H

#define NUM_LETTERS_IN_ALPHABET 26
#define MAX_WORD_SIZE 51

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
bool handleDeleteWord(struct trienode **trie_root, char* word);
bool deleteLeafWord(struct trienode **trie_root, char *word, size_t word_len);
bool deleteNonLeafWord(struct trienode **trie_root, char *word, size_t word_len);
bool checkWordExists(struct trienode **trie_root, char *word);
int checkIfLeafNode(struct trienode **trie_root, char *word, size_t word_len);
int getBranchingIndex(struct trienode **trie_root, char *word, size_t word_len);
char* getLongestPrefix(struct trienode **trie_root, char *word, size_t word_len);
void nullExcessLetters(char *suffix, int suffixPos);
void handleChildPrinting(struct trienode* node, char *prefix, char *suffix, int suffixPos);
void printWordsFromPrefix(struct trienode **trie_root, char *prefix);
void trienodeRecursiveFree(struct trienode* to_free);
void trim_newline(char *str);

#endif