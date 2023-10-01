typedef struct GameMap {
	unsigned int levelNum;
	unsigned int mapWidth;
	unsigned int mapHeight;
	int xPos;
    int yPos;
	char* mapArr;
} CurrMap;

typedef struct Engine {
	CurrMap currMap;
} Engine;

extern Engine gameEngine;