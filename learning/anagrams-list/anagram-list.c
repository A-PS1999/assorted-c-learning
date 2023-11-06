#include "anagram-list.h"

int main(void) {
    const char* fileName = "eng_370k_shuffle.txt";

    unsigned int tableSize;
    tableSize = getNumLines(fileName);

    struct HashTable *hashTable = NULL;
    hashTable = initHashTable(tableSize);

    generateAnagramTable(hashTable, fileName);
    printTable(&hashTable);

    freeHashTable(hashTable); 
    return 0;
}
