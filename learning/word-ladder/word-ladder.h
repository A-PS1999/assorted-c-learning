#ifndef WORD_LADDER_H
#define WORD_LADDER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 5
#define BASE_CHILD_NUM 4

typedef struct WordNode WordNode;
struct WordNode {
    char word[MAX_WORD_LEN];
    int numChildren;
    int currChildLimit;
    WordNode **children;
};

bool isValidInput(int argc, char** argv);
WordNode* initWordNode(char* word);
void buildWordLadder(WordNode** root, char* target);
bool wordInTree(char* word, WordNode** root);
void recurseWordNodes(WordNode* currNode, char* target, FILE* file, WordNode** root);
bool oneEditDistance(char* parentWord, char* word);
void insertChildNode(WordNode* parent, char* newWord);
void printWordLadder(WordNode** root);
void stripNewLine(char* word);

#endif
