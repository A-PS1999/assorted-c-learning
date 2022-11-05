#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

struct hashtable* init_hashtable(int size) {
    struct hashtable* new_table;
    if ((new_table = malloc(sizeof(struct hashtable))) == NULL) {
        perror("Error: failed to allocate memory for hash table\n");
        exit(EXIT_FAILURE);
    }
    new_table->table_size = size;
    new_table->num_entries = 0;
    if ((new_table->entries = malloc(size*sizeof(struct list_node))) == NULL) {
        perror("Error: failed to allocate memory for hash table array\n");
        exit(EXIT_FAILURE);
    }
    
    return new_table;
}

uint64_t hash(char *name) {
    uint64_t hash = HASH_OFFSET_BASIS;

    for (char *ch = name; *ch; ch++) {
        hash ^= (uint64_t)(unsigned char)(*ch);
        hash *= HASH_PRIME;
    }

    return hash;
}

void free_hashtable(struct hashtable *table) {
    if (table == NULL) {
        printf("Error: there is no table to free!\n");
        return;
    }

    for (int i = 0; i < table->table_size; i++) {
        if (table->entries[i] != NULL) {
            free_list(table->entries[i]);
            table->entries[i] = NULL;
        }
    }

    free(table->entries);
    free(table);
}

void insert_entry(struct hashtable **table) {
    if (table == NULL) {
        printf("Error: Table must be initialised before it can be used!\n");
        return;
    }

    char name[HASHTABLE_NAME_MAX];
    char birthdate[HASHTABLE_BIRTHDATE_MAX];
    char address[HASHTABLE_ADDRESS_MAX];
    char gender = 'X';
    struct hashtable *curr = *table;

    printf("Enter name (max 40 characters): ");
    fgets(name, HASHTABLE_NAME_MAX, stdin);
    uint64_t created_key = hash(name) % curr->table_size;

    printf("Enter gender (M/F): ");
    scanf("%c", &gender);
    while ((getchar()) != '\n');

    printf("Enter birthdate (max 20 characters): ");
    fgets(birthdate, HASHTABLE_BIRTHDATE_MAX, stdin);

    printf("Enter address (max 40 characters): ");
    fgets(address, HASHTABLE_ADDRESS_MAX, stdin);

    struct table_item* created_entry = create_item(name, gender, birthdate, address);
    struct list_node* to_insert = create_node(created_key, created_entry);

    if (!curr->entries[created_key]) {
        curr->entries[created_key] = to_insert;
    } else {
        while (curr->entries[created_key]->next != NULL) {
            curr->entries[created_key] = curr->entries[created_key]->next;
        }
        curr->entries[created_key]->next = to_insert;
    }
    curr->num_entries = curr->num_entries+1;
}

struct list_node* search_hashtable(struct hashtable *table, char *name) {
    if (table == NULL) {
        printf("Error: Table must be initialised before it can be searched!\n");
        return NULL;
    }
    uint64_t search_key = hash(name) % table->table_size;

    if (!table->entries[search_key]) {
        printf("No key for %s exists in the hashtable\n", name);
        return NULL;
    }

    while (table->entries[search_key]->next != NULL) {
        if ((strcmp(table->entries[search_key]->data->name, name)) == 0) {
            struct list_node* found = table->entries[search_key];
            return found;
        }

        table->entries[search_key] = table->entries[search_key]->next;
    }

    printf("No key for %s exists in the hashtable\n", name);
    return NULL;
}

void delete_entry(struct hashtable **table, char *name) {
    if (table == NULL) {
        printf("Error: table must be initialised before items can be deleted!\n");
        return;
    }

    struct hashtable *ref = *table;
    uint64_t search_key = hash(name) % ref->table_size;
    struct list_node *prev, *curr, *to_delete;

    if (!ref->entries[search_key]) {
        printf("No key for %s exists in the hashtable\n", name);
        return;
    }

    to_delete = search_hashtable(ref, name);
    if (to_delete == NULL) {
        printf("Can't delete: did not find %s\n", name);
        return;
    }

    for (curr = ref->entries[search_key], prev = NULL; curr != NULL && (strcpy(name, curr->data->name) != 0); prev=curr, curr = curr->next);

    if (prev == NULL) {
        ref->entries[search_key] = curr->next;
    } else {
        prev->next = curr->next;
    }

    free_item(curr->data);
    free(curr);
    ref->num_entries = ref->num_entries-1;
}

struct list_node* create_node(uint64_t key, struct table_item* entry) {
    struct list_node* new_node;
    if ((new_node = malloc(sizeof(struct list_node))) == NULL) {
        perror("Error: failed to allocate memory for new linked list node\n");
        exit(EXIT_FAILURE);
    }
    new_node->hash_key = key;
    new_node->next = NULL;
    new_node->data = entry;

    return new_node;
}

void free_list(struct list_node* node) {
    struct list_node* temp;

    while (node != NULL) {
        temp = node;
        node = node->next;
        free_item(temp->data);
        free(temp);
    }
}

struct table_item* create_item(char *name, char gender, char *birthdate, char *address) {
    struct table_item* new_entry;
    if ((new_entry = malloc(sizeof(struct table_item))) == NULL) {
        perror("Error: failed to allocate memory for new table item\n");
        exit(EXIT_FAILURE);
    }

    if ((new_entry->name = malloc(sizeof(char)*HASHTABLE_NAME_MAX)) == NULL) {
        perror("Error: failed to allocate memory for entry name\n");
        exit(EXIT_FAILURE);
    }

    if ((new_entry->birthdate = malloc(sizeof(char)*HASHTABLE_BIRTHDATE_MAX)) == NULL) {
        perror("Error: failed to allocate memory for entry birthdate\n");
        exit(EXIT_FAILURE);
    }

    if ((new_entry->address = malloc(sizeof(char)*HASHTABLE_ADDRESS_MAX)) == NULL) {
        perror("Error: failed to allocate memory for entry address\n");
        exit(EXIT_FAILURE);
    }

    new_entry->name = name;
    new_entry->birthdate = birthdate;
    new_entry->address = address;
    new_entry->gender = gender;

    return new_entry;
}

void print_item(struct table_item* item) {
    printf("Name: %s\n", item->name);
    printf("Birth date: %s\n", item->birthdate);
    printf("Gender: %c\n", item->gender);
    printf("Address: %s\n", item->address);
    printf("--------------------\n");
}

void free_item(struct table_item* item) {
    free(item->address);
    free(item->birthdate);
    free(item->name);
    free(item);
}