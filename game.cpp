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
    drawStrokeText("DUCK HUNT", WIDTH/2, HEIGHT/2, 0, FONT_SIZE_BIG);

    glLineWidth(1);
    drawStrokeText("PRESS ENTER TO START", WIDTH/2, HEIGHT/2+100, 0, FONT_SIZE_NORMAL);
    drawStrokeText("Press Esc to Quit", WIDTH/2, HEIGHT/2+200, 0, FONT_SIZE_SMALL);
    drawStrokeText("By:\n\tARAVIND SUNDARESAN - 1PE12CS022\n\tG ARUN KUMAR - 1PE12CS048",
        WIDTH/2, HEIGHT/2, 0, FONT_SIZE_SMALL);

}

void gameScreen() {

    drawBackground();

    if (debugInfoVisible)
        showDebugInfo();

    if (instructionMenuVisible)
        showInstructions();
}

void drawBackground() {

    float groundSize = 0.3;
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);
    glBegin(GL_QUADS);
        // Ground
        glColor3f(0, 0.5, 0);
        glVertex3f(0, 0, -0.5);
        glVertex3f(WIDTH, 0, -0.5);
        glVertex3f(WIDTH, HEIGHT * groundSize, -0.5);
        glVertex3f(0, HEIGHT * groundSize, -0.5);
        // Sky
        glColor3f(0.43 , 0.77, 0.86);
        glVertex3f(WIDTH, HEIGHT * groundSize, -0.5);
        glVertex3f(0, HEIGHT * groundSize, -0.5);
        glVertex3f(0, HEIGHT, -0.5);
        glVertex3f(WIDTH, HEIGHT, -0.5);

    glEnd();
    glPopAttrib();
    glPopMatrix();
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

    drawBitmapText(debugText.c_str(), 10, HEIGHT - 450, 0);
}

void updateCursorCoords(int x, int y) {
    cursorX = x;
    cursorY = CURSOR_YMAX-y;
}
