#ifndef GAME_H
#define GAME_H

#include "definations.h"

extern AppState appState;
extern bool instructionMenuVisible;
extern bool debugInfoVisible;
extern bool isShooting;

void initGame();
void startScreen();
void gameScreen();
void updateCursorCoords(int x, int y);

#endif //GAME_H

