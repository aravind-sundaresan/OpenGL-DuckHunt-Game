#include "definations.h"
#include "game.h"
#include "fonts.h"

AppState appState = START_SCREEN;
bool instructionMenuVisible = true;

void showInstructions();

void startScreen() {

    glLineWidth(3);
    drawStrokeText("DUCK HUNT", WIDTH/2, HEIGHT/2, 0, FONT_SIZE_BIG);

    glLineWidth(1);
    drawStrokeText("PRESS ENTER TO START", WIDTH/2, HEIGHT/2+100, 0, FONT_SIZE_NORMAL);
    drawStrokeText("Press Esc to Quit", WIDTH/2, HEIGHT/2+200, 0, FONT_SIZE_SMALL);
    drawStrokeText("By:\n\tARAVIND SUNDARESAN - 1PE12CS022\n\tG ARUN KUMAR - 1PE12CS048",
        WIDTH/2, HEIGHT/2, 0, FONT_SIZE_SMALL);

}

void simulationScreen() {
    if (instructionMenuVisible)
        showInstructions();
}

void showInstructions() {
    drawBitmapText("Instructions:\n"
                           "  q - Quit simulation\n"
                           "  i - Toggle Instructions", WIDTH/2, HEIGHT/2, 0);
}
