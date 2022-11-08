#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>
#include <string.h>

#define HASH_OFFSET_BASIS 14695981039346656037UL
#define HASH_PRIME 1099511628211UL
#define HASHTABLE_NAME_MAX 41
#define HASHTABLE_BIRTHDATE_MAX 21
#define HASHTABLE_ADDRESS_MAX 41

struct table_item {
    char *name;
    char gender;
    char *birthdate;
    char *address;
};

struct list_node {
    struct table_item *data;
    struct list_node *next;
    uint64_t hash_key;
};

struct hashtable {
    int table_size;
    int num_entries;
    struct list_node **entries;
};

// hashtable functions
struct hashtable* init_hashtable(int size);
uint64_t hash(char *name);
void free_hashtable(struct hashtable *table);
void insert_entry(struct hashtable **table);
struct list_node* search_hashtable(struct hashtable *table, char *name);
void delete_entry(struct hashtable **table, char *name);

// linked list functions
struct list_node* create_node(uint64_t key, struct table_item* entry);
void free_list(struct list_node* node);

// table item functions
struct table_item* create_item(char *name, char gender, char *birthdate, char *address);
void print_item(struct table_item* item);
void free_item(struct table_item* item);

// utility function
void trim_newline(char *str);

#endif