#include "anagrams.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error - Invalid or insufficient input provided");
        return -1;
    }

    if (!doAnagramSearch(argv[1])) {
        perror("Error - Failed to open words file");
        return -1;
    }

    return 0;
}
