#include "definations.h"
#include "game.h"
#include "fonts.h"
#include <sstream>

using namespace std;

AppState appState = START_SCREEN;
bool instructionMenuVisible = true;
bool debugInfoVisible = false;
int cursorX, cursorY;

void showInstructions();
void showDebugInfo();
void drawBackground();

void startScreen() {

    glLineWidth(3);
    drawStrokeText("DUCK HUNT", WIDTH/5, 3*HEIGHT/4, 0, FONT_SIZE_BIG);

    glLineWidth(1);
    drawStrokeText("PRESS ENTER TO START", WIDTH/5.5, HEIGHT/2.5, 0, FONT_SIZE_NORMAL);
    drawStrokeText("Press Esc to Quit", WIDTH/1.8, HEIGHT/3.4, 0, FONT_SIZE_SMALL);
    drawStrokeText("By:\n\tARAVIND SUNDARESAN - 1PE12CS022\n\tG ARUN KUMAR - 1PE12CS048",
     WIDTH/2, HEIGHT/7, 0, FONT_SIZE_SMALL);

}

void gameScreen() {

    drawBackground();

    if (debugInfoVisible)
        showDebugInfo();

    if (instructionMenuVisible)
        showInstructions();
}

void drawBackground() {

}

void showInstructions() {
    drawBitmapText("Instructions:\n"
        "  q - Quit simulation\n"
        "  i - Toggle Instructions\n"
        "  d - Toggle Debugging Information", 10, HEIGHT-50, 0);
}

void showDebugInfo() {

    string debugText;

    stringstream ss;
    ss << "Debugging Info: " << endl;
    ss << "  Cursor X: " << cursorX << endl;
    ss << "  Cursor Y: " << cursorY << endl;

    debugText = ss.str();

    drawBitmapText(debugText.c_str(), 10, HEIGHT - 500, 0);
}

void updateCursorCoords(int x, int y) {
    cursorX = x;
    cursorY = CURSOR_YMAX-y;
}
