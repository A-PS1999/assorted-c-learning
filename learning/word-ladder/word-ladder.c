#include "stack.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error: Inputs are either insufficient or result in an unsolvable word ladder");
        exit(EXIT_FAILURE);
    }

    WordNode *root = NULL;
    root = initWordNode(argv[1]);

    buildWordLadder(&root, argv[2]);
    //printWordLadder(&root);

    return 0;
}
