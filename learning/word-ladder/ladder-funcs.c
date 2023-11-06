#include "stack.h"

bool isValidInput(int argc, char** argv) {
    if (argc != 3) {
        return false;
    }

    const char fileName[] = "dictionary.txt";

    FILE* file;

    file = fopen(fileName, "r");
    if (!file) {
        perror("Error: Failed to open dictionary file");
        exit(EXIT_FAILURE);
    }

    char fileBuffer[MAX_WORD_LEN];

    bool startWordFound = false;
    bool endWordFound = false;

    while (fgets(fileBuffer, MAX_WORD_LEN, file)) {
        stripNewLine(fileBuffer);
        if (strcmp(fileBuffer, argv[1])==0) {
            startWordFound = true;
        } else if (strcmp(fileBuffer, argv[2])==0) {
            endWordFound = true;
        }
    }

    fclose(file);
    return startWordFound && endWordFound;
}

WordNode* initWordNode(char* word) {
    struct WordNode* newNode;

    if ((newNode = malloc(sizeof(WordNode))) == NULL) {
        perror("Error: Failed to allocate memory for a new node");
        exit(EXIT_FAILURE);
    }

    newNode->children = NULL;
    newNode->numChildren = 0;
    newNode->currChildLimit = BASE_CHILD_NUM;
    strcpy(newNode->word, word);

    return newNode;
}

void buildWordLadder(WordNode** root, char* target) {

    WordNode *tree = *root;
    const char fileName[] = "dictionary.txt";

    FILE* file;
    file = fopen(fileName, "r");
    if (!file) {
        perror("Error: Failed to open dictionary file");
        exit(EXIT_FAILURE);
    }

    recurseWordNodes(tree, target, file, root);
    fclose(file);
}

bool wordInTree(char* word, WordNode** root) {
    WordNode* curr = *root;

    Stack stack;
    stack = create();

    push(stack, *curr);

    while (!is_empty(stack)) {
        WordNode currNode = pop(stack);
        if (strcmp(word, currNode.word)==0) {
            destroy(stack);
            return true;
        }

        if (currNode.numChildren > 0 && currNode.children != NULL) {
            for (int i=0; i < currNode.numChildren; i++) {
                push(stack, *currNode.children[i]);
            }
        }
    }

    destroy(stack);
    return false;
}

void recurseWordNodes(WordNode* currNode, char* target, FILE* file, WordNode** root) {
    if (currNode == NULL) return;
    if (wordInTree(target, root)) return;

    fseek(file, 0, SEEK_SET);

    char fileBuffer[MAX_WORD_LEN];
    bool targetAdded = false;

    while (fgets(fileBuffer, MAX_WORD_LEN, file) && targetAdded == false) {
        stripNewLine(fileBuffer);
        if (wordInTree(fileBuffer, root)) continue;
        if (oneEditDistance(currNode->word, fileBuffer)) {
            if (strcmp(target, fileBuffer)==0) {
                targetAdded = true;
            }
            insertChildNode(currNode, fileBuffer);
        }
    }

    if (targetAdded == true) {
        recurseWordNodes(NULL, target, file, root);
    } else {
        for (int idx=0; idx < currNode->numChildren; idx++) {
            recurseWordNodes(currNode->children[idx], target, file, root);
        }
    }
}

bool oneEditDistance(char* parentWord, char* word) {
    int editDist = 0;

    int strIdx = 0;
    while (strIdx < MAX_WORD_LEN-1) {
        if (parentWord[strIdx] != word[strIdx]) {
            editDist++;
        }
        strIdx++;
    }

    return editDist == 1;
}

void insertChildNode(WordNode* parent, char* newWord) {
    if (parent->numChildren == parent->currChildLimit) {
        WordNode **newChildren = NULL;
        int newCapacity = parent->currChildLimit*2;
        newChildren = realloc(parent->children, newCapacity*sizeof(WordNode*));
        if (!newChildren) {
            perror("Error: Failed to allocate extra memory for new children");
            exit(EXIT_FAILURE);
        }
        parent->children = newChildren;
        parent->currChildLimit = newCapacity;
    }
    if (parent->children == NULL && parent->numChildren == 0) {
        if ((parent->children = calloc(BASE_CHILD_NUM, sizeof(WordNode*))) == NULL) {
            perror("Error: Failed to allocate initial children space");
            exit(EXIT_FAILURE);
        }
    }

    WordNode* newChild = initWordNode(newWord);
    int idx = 0;
    while (idx < parent->numChildren) {
        idx++;
    }
    parent->children[idx] = newChild;
    parent->numChildren += 1;
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