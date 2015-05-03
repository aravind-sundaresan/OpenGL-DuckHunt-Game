#ifndef GAME_H
#define GAME_H

#include "definations.h"

extern AppState appState;
extern bool instructionMenuVisible;
extern bool debugInfoVisible;

void startScreen();
void simulationScreen();
void updateCursorCoords(int x, int y);

#endif //GAME_H

