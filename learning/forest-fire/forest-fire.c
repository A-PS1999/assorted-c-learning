#include "forest-fire.h"

int main(int argc, char** argv) {
    if (!isValidInput(argc, argv)) {
        perror("Error - Invalid inputs provided");
        return -1;
    }

    Forest forestSim;

    if (!readForestFile(&forestSim, argv[1])) {
        perror("Error - Failed to initialise simulation");
        return -1;
    }

    srand(time(NULL));

    for (int i=0; i < TOTAL_GENS; i++) {
        printSim(&forestSim);
        updateSim(&forestSim);
    }

    return 0;
}
