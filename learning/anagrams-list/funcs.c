#include "anagram-list.h"

struct HashTable* initHashTable(int tableSize) {
    struct HashTable *newTable;

    if ((newTable = malloc(sizeof(struct HashTable))) == NULL)  {
        perror("Error: Failed to allocate memory for HashTable struct.");
        exit(EXIT_FAILURE);
    }

    if ((newTable->entries = calloc(tableSize, sizeof(struct ListNode*))) == NULL) {
        perror("Error: Failed to allocate sufficient memory for table entries");
        exit(EXIT_FAILURE);
    }

    newTable->tableSize = tableSize;
    newTable->numEntries = 0;

    return newTable;
}

HashType getHash(char* word) {
    int primes[32] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,
        61,67,71,73,79,83,89,97,101,103,107,109,113,127,131
    };

    HashType res = 1;

    char* curr = word;

    while (isalpha((unsigned char)*curr)) {
        res *= primes[*curr - 'a'];
        curr++;
    } 

    return res;
}

unsigned int getNumLines(const char* fileName) {
    unsigned int res = 0;

    FILE* file;
    file = fopen(fileName, "r");

    if (!file) {
        perror("Error: Failed to open words file");
        exit(EXIT_FAILURE);
    }

    char fileBuffer[MAX_WORD_LEN];

    while (true) {
        size_t wordLen = fread(fileBuffer, 1, MAX_WORD_LEN, file);

        if (ferror(file)) {
            perror("Error: Experienced a file error");
            exit(EXIT_FAILURE);
        }

        for (size_t i=0; i < wordLen; i++) {
            if (fileBuffer[i] == '\n') {
                res++;
            }
        }

        if (feof(file)) {
            break;
        }
    }

    return res;
}

void generateAnagramTable(struct HashTable *table, const char* fileName) {

    FILE* file;

    file = fopen(fileName, "r");

    if (!file) {
        perror("Error: Failed to open words file");
        exit(EXIT_FAILURE);
    }

    char fileBuffer[MAX_WORD_LEN];

    HashType hash;

    while (fgets(fileBuffer, MAX_WORD_LEN, file)) {
        stripNewLine(fileBuffer);
        struct TableItem *newEntry = createItem(fileBuffer);
        hash = getHash(fileBuffer) % table->tableSize;
        struct ListNode *newNode = createNode(hash, newEntry);

        insertEntry(table, newNode);
    }
}

void insertEntry(struct HashTable *table, struct ListNode* node) {
    uint64_t inputHash = node->hashKey;
    struct HashTable *curr = table;

    if (!curr->entries[inputHash]) {
        curr->entries[inputHash] = node;
    } else {
        while (curr->entries[inputHash]->next != NULL) {
            curr->entries[inputHash] = curr->entries[inputHash]->next;
        }
        curr->entries[inputHash]->next = node;
    }
    curr->numEntries = curr->numEntries + 1;
}

struct TableItem* createItem(char* word) {
    struct TableItem* newItem;

    if ((newItem = malloc(sizeof(struct TableItem))) == NULL) {
        perror("Error: Failed to allocate memory for new data item");
        exit(EXIT_FAILURE);
    }

    size_t wordLen = strlen(word);
    strncpy(newItem->word, word, wordLen);

    return newItem;
}

struct ListNode* createNode(HashType hashKey, struct TableItem *entry) {
    struct ListNode* newNode;

    if ((newNode = malloc(sizeof(struct ListNode))) == NULL) {
        perror("Error: Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }

    newNode->hashKey = hashKey;
    newNode->next = NULL;
    newNode->data = entry;

    return newNode;
}

void printTable(struct HashTable **table) {
    struct HashTable *curr = *table;
    struct ListNode *currNode;

    for (int i=0; i < curr->tableSize; i++) {
        if (curr->entries[i]) {
            int len = getListLen(curr->entries[i]);
            printf("%d ", len);
            currNode = curr->entries[i];
            while (currNode != NULL) {
                printf("%s ", currNode->data->word);
                currNode = currNode->next;
            }
            printf("\n");
        }
    }
}

void stripNewLine(char* word) {
    char* curr = word;

    while (*curr) {
        if (*curr == '\n') {
            *curr = '\0';
        }
        curr++;
    }
}

unsigned int getListLen(struct ListNode *node) {
    unsigned int res = 0;

    struct ListNode *curr = node;

    while (curr != NULL) {
        res++;
        curr = curr->next;
    }

    return res;
}

void freeList(struct ListNode *node) {
    struct ListNode* temp;

    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp->data);
        free(temp);
    }
}

void freeHashTable(struct HashTable *table) {

    for (int i=0; i < table->tableSize; i++) {
        if (table->entries[i] != NULL) {
            freeList(table->entries[i]);
        }
    }

    free(table->entries);
    free(table);
}
