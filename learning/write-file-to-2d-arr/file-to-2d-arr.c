#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filetoarr.h"

#define ARR_IDX(WIDTH, ROW, COL) (WIDTH * ROW) + COL

extern char *strtok_r(char *, const char *, char **);

int main() {

	Engine gameEngine;

    FILE* filePtr = fopen("input.txt", "r");

    if (!filePtr) return 1;

    char lineBuffer[1024];

    unsigned int lvlNum;
	unsigned int width;
	unsigned int height;
	int startX;
	int startY;

    while (!feof(filePtr)) {
		fgets(lineBuffer, 1024, filePtr);

		if (lineBuffer[0] == '#') break;

		char* strPointer;
		char* label = strtok_r(lineBuffer, ":", &strPointer);
		char* data = strtok_r(NULL, ": ", &strPointer);

		if (strstr(label, "lvl")) {
			lvlNum = (unsigned int)atoi(data);
		}
		else if (strstr(label, "w")) {
			width = (unsigned int)atoi(data);
		}
		else if (strstr(label, "h")) {
			height = (unsigned int)atoi(data);
		}
		else if (strstr(label, "x")) {
			startX = atoi(data);
		}
		else if (strstr(label, "y")) {
			startY = atoi(data);
		}
	}

	printf("%u\n", lvlNum);
	printf("%u\n", width);
	printf("%u\n", height);
	printf("%d\n", startX);
	printf("%d\n", startY);

	gameEngine.currMap.mapWidth = width;
	gameEngine.currMap.mapHeight = height;
	gameEngine.currMap.levelNum = lvlNum;
	gameEngine.currMap.mapArr = calloc(width * height, sizeof(gameEngine.currMap.mapArr[0]));

	int currRow = 0;

	while (!feof(filePtr)) {
		fgets(lineBuffer, 1024, filePtr);

		for (int currCol=0; currCol < width; currCol++) {
			gameEngine.currMap.mapArr[ARR_IDX(gameEngine.currMap.mapWidth, currRow, currCol)] = lineBuffer[currCol];
		}
		
		currRow++;
	}

	printf("\n");

	for (int y=0; y < height; y++) {
		for (int x=0; x < width; x++) {
			printf("%c", gameEngine.currMap.mapArr[ARR_IDX(width, y, x)]);
		}
		printf("\n");
	}

    fclose(filePtr);
	free(gameEngine.currMap.mapArr);

    return 0;
}