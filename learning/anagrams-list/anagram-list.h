#ifndef ANAGRAM_LIST_H
#define ANAGRAM_LIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define HASH_OFFSET_BASIS 14695981039346656037UL
#define HASH_PRIME 1099511628211UL
#define MAX_WORD_LEN 100
#define ALPHABET_LEN 26

typedef unsigned long long HashType;

struct TableItem {
    char word[MAX_WORD_LEN];
};

struct ListNode {
    struct TableItem *data;
    struct ListNode *next;
    HashType hashKey;
};

struct HashTable {
    int tableSize;
    int numEntries;
    struct ListNode **entries;
};

// Hashtable functions
struct HashTable* initHashTable(int tableSize);
HashType getHash(char* word);
void insertEntry(struct HashTable *table, struct ListNode* node);
void freeHashTable(struct HashTable *table);

// Linked list functions
struct ListNode* createNode(HashType hashKey, struct TableItem *entry);
void freeList(struct ListNode *node);
unsigned int getListLen(struct ListNode *node);

// Table item functions
struct TableItem* createItem(char* word);

// Misc functions
unsigned int getNumLines(const char* fileName);
void generateAnagramTable(struct HashTable *table, const char* fileName);
void printTable(struct HashTable **table);
void stripNewLine(char* word);

#endif
