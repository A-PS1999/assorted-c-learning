#include "trie.h"

bool initTrie(struct trienode **trie_root) {
    struct trienode *root;

    if ((root = calloc(1, sizeof(struct trienode))) == NULL) {
        printf("Error: failed to allocate memory for initial trie node\n");
        exit(EXIT_FAILURE);
    }
    root->is_word = false;

    *trie_root = root;

    return true;
}

struct trienode* createNewTrienode(void) {
    struct trienode *new_node;

    if ((new_node = calloc(1, sizeof(struct trienode))) == NULL) {
        printf("Error: failed to allocate memory for initial trie node\n");
        exit(EXIT_FAILURE);
    }
    new_node->is_word = false;

    return new_node;
}

bool insertWord(struct trienode **trie_root, char *word) {
    struct trienode *curr_node = *trie_root;

    if (*trie_root == NULL) {
        printf("Error: Please ensure trie is initialised before attempting to insert a word\n");
        return false;
    }

    size_t word_len = strlen(word);

    if (word_len == 0) {
        printf("Error: Please input a valid word\n");
        return false;
    }

    for (int i=0; i < word_len; i++) {
        int key = tolower(word[i]) - 'a';

        if (curr_node->children[key] == NULL) {
            curr_node->children[key] = createNewTrienode();
        }
        curr_node = curr_node->children[key];
    }

    curr_node->is_word = true;

    return true;
}

int getBranchingIndex(struct trienode **trie_root, char *word) {
    struct trienode *curr_node = *trie_root;

    if (*trie_root == NULL) {
        printf("Error: Please ensure trie is initialised.\n");
        return 0;
    }

    size_t word_len = strlen(word);

    if (word_len == 0) {
        printf("Error: Please input a valid word\n");
        return 0;
    }

    int largestBranchingIndex = 0;
    for (int i=0; i < word_len; i++) {
        int currKey = tolower(word[i]) - 'a';

        if (curr_node->children[currKey]) {

            for (int j=0; j < NUM_LETTERS_IN_ALPHABET; j++) {
                if (j != currKey && curr_node->children[j]) {
                    largestBranchingIndex = i+1;
                    break;
                }
            }
            curr_node = curr_node->children[currKey];
        }
    }

    return largestBranchingIndex;
}

char* getLongestPrefix(struct trienode **trie_root, char *word) {
    if (*trie_root == NULL) {
        printf("Error: Please ensure trie is initialised.\n");
        return 0;
    }

    size_t word_len = strlen(word);

    if (word_len == 0) {
        printf("Error: Please input a valid word\n");
        return 0;
    }

    // Allocation of memory for longest prefix string, which we will return from function
    // after possibly shortening it if we detect a branching point
    char* longestPrefix = calloc(word_len+1, sizeof(char));
    strcpy(longestPrefix, word);

    int branching_index = getBranchingIndex(trie_root, longestPrefix);
    if (branching_index >= 0) {
        longestPrefix[branching_index] = '\0';
        // Shortens allocated memory for string to branch point +1
        longestPrefix = (char *)realloc(longestPrefix, (branching_index+1)*sizeof(char));
    }

    return longestPrefix;
}

bool deleteWord(struct trienode **trie_root, char *word) {
    struct trienode *curr_node = *trie_root;

    if (*trie_root == NULL) {
        printf("Error: Please ensure trie is initialised before attempting to delete a word\n");
        return false;
    }

    size_t word_len = strlen(word);

    if (word_len == 0) {
        printf("Error: Please input a valid word\n");
        return false;
    }

    char* longestPrefixFound = getLongestPrefix(trie_root, word);

    int i;
    for (i=0; longestPrefixFound[i] != '\0'; i++) {
        int key = tolower(longestPrefixFound[i]) - 'a';
        if (curr_node->children[key]) {
            curr_node = curr_node->children[key];
        } else {
            free(longestPrefixFound);
            return false;
        }
    }

    for (; i < word_len; i++) {
        int key = tolower(word[i]) - 'a';
        if (curr_node->children[key]) {
            struct trienode* to_free = curr_node->children[key];
            curr_node->children[key] = NULL;
            trienodeRecursiveFree(to_free);
        }
    }

    free(longestPrefixFound);

    return true;
}

bool checkWordExists(struct trienode **trie_root, char *word) {
    struct trienode *curr_node = *trie_root;

    if (*trie_root == NULL) {
        printf("Error: Please ensure trie is initialised before attempting to search a word\n");
        return false;
    }

    size_t word_len = strlen(word);

    if (word_len == 0) {
        printf("Error: Please input a valid word\n");
        return false;
    }

    for (int i=0; i < word_len; i++) {
        int key = tolower(word[i]) - 'a';

        if (curr_node->children[key] == NULL) {
            return false;
        }
        curr_node = curr_node->children[key];
    }

    if (curr_node->is_word) {
        return true;
    } else {
        return false;
    }
}

void printWordsFromPrefix(struct trienode **trie_root, char *prefix) {
    struct trienode *curr_node = *trie_root;

    if (*trie_root == NULL) {
        printf("Error: Please ensure trie is initialised before attempting to search a word\n");
        return;
    }

    for (int i=0; prefix[i] != '\0'; i++) {
        int key = tolower(prefix[i]) - 'a';
        if (curr_node->children[key]) {
            curr_node = curr_node->children[key];
        } else {
            printf("Failed to find words beginning with %s", prefix);
            return;
        }
    }

    // TODO
}

void trienodeRecursiveFree(struct trienode* to_free) {
    for (int i=0; i < NUM_LETTERS_IN_ALPHABET; i++) {
        if (to_free->children[i]) {
            trienodeRecursiveFree(to_free->children[i]);
        } else continue;
    }
    free(to_free);
}

void trim_newline(char *str) {
    size_t len = strlen(str);

    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}