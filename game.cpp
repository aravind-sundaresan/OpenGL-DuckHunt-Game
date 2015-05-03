#include <stdlib.h>
#include "definations.h"
#include "game.h"
#include "fonts.h"
#include <sstream>

using namespace std;

AppState appState = START_SCREEN;
bool instructionMenuVisible = true;
bool debugInfoVisible = false;
int cursorX, cursorY;
bool isShooting = false;

int duckCount = INITIAL_DUCK_CNT;
float duckInitYPos[MAX_DUCK_CNT];
vec2f duckPos[MAX_DUCK_CNT];
float duckSlope[MAX_DUCK_CNT];

void showInstructions();
void showDebugInfo();
void drawBackground();
void drawCursor();

void initGame() {
    for (int i = 0; i < MAX_DUCK_CNT; i++) {
        // Generate random slope
        duckSlope[i] =  ((float) rand() / (RAND_MAX));

        // Random initial y pos
        duckInitYPos[i] = (rand() % 300) + 100;
        duckPos[i].x = 0;
        duckPos[i].y = duckInitYPos[i];
    }
}

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
    drawCursor();
//    drawDucks();

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

void drawCursor() {
    if (isShooting) {
        glBegin(GL_QUADS);
            glColor3f(0.7, 0, 0);
            glVertex2f (cursorX - 4.5, cursorY - 4);
            glVertex2f (cursorX - 4.5, cursorY + 4);
            glVertex2f (cursorX + 4, cursorY + 4);
            glVertex2f (cursorX + 4, cursorY - 4);
            glVertex2f (cursorX - 4, cursorY - 4);
		glEnd();
    }
    glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
    	glVertex2f (cursorX - 5, cursorY - 5);
        glVertex2f (cursorX - 5, cursorY + 5);
        glVertex2f (cursorX + 5, cursorY + 5);
        glVertex2f (cursorX + 5, cursorY - 5);
		glVertex2f (cursorX - 5, cursorY - 5);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex2f (cursorX - 10, cursorY);
        glVertex2f (cursorX + 10, cursorY);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1, 1, 1);
        glVertex2f (cursorX, cursorY - 10);
        glVertex2f (cursorX, cursorY + 10);
	glEnd();
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
