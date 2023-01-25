#include "trie.h"

int main(void) {
    struct trienode *trie_root = NULL;
    char code;
    char word[MAX_WORD_SIZE];

    memset(word, 0, 50);

    for (;;) {
        printf("Enter code: ");
        scanf(" %c", &code);
        while (getchar() != '\n');

        switch (code) {
            case 'i':
                printf("Initialising trie...\n");
                bool initCheck = initTrie(&trie_root);
                if (initCheck) {
                    printf("Successfully initialised trie!\n");
                }
                break;
            case 'a':
                printf("Please input the word you'd like to add to the trie (max 50 letters): ");
                fgets(word, MAX_WORD_SIZE+1, stdin);
                trim_newline(word);
                bool addCheck = insertWord(&trie_root, word);
                if (addCheck) {
                    printf("Successfully added %s to the trie\n", word);
                } else {
                    printf("uh oh, something went wrong. Failed to add %s to the trie\n", word);
                }
                break;
            case 'c':
                printf("Please input the word you'd like to check for in the trie: ");
                fgets(word, MAX_WORD_SIZE+1, stdin);
                trim_newline(word);
                bool wordExists = checkWordExists(&trie_root, word);
                if (wordExists) {
                    printf("Successfully located %s in the trie\n", word);
                } else {
                    printf("Could not locate %s in the trie\n", word);
                }
                break;
            case 'd':
                printf("Please input the word you'd like to delete from the trie: ");
                fgets(word, MAX_WORD_SIZE+1, stdin);
                trim_newline(word);
                bool deleteCheck = handleDeleteWord(&trie_root, word);
                if (deleteCheck) {
                    printf("Successfully deleted %s from the trie\n", word);
                } else {
                    printf("Failed to delete %s from the trie\n", word);
                }
                break;
            case 'p':
                printf("Please input the prefix you'd like to print related words from: ");
                fgets(word, MAX_WORD_SIZE+1, stdin);
                trim_newline(word);
                printWordsFromPrefix(&trie_root, word);
                break;
            case 'q':
                return 0;
                break;
            default:
                printf("Invalid option code\n");
                break;
        }
    }
}