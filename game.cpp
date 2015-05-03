#include <stdlib.h>
#include "definations.h"
#include "game.h"
#include "fonts.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include "duck.h"
#include <GL/freeglut.h>

using namespace std;

AppState appState = START_SCREEN;
GameState gameState = ROUND_INIT;
bool instructionMenuVisible = true;
bool debugInfoVisible = false;
int cursorX, cursorY;
bool isShooting = false;
bool notifyMsg = false;
int score;
string msg;


vector<int> duckIndices;

Duck ducks[MAX_DUCK_CNT];

void showInstructions();
void showDebugInfo();
void drawBackground();
void drawCursor();
void drawDucks();
void chooseRandomDucks(int n);

void initGame() {
    score = 0;
    notifyMsg = false;
    glutTimerFunc(2000, notifyGame, 0);
    chooseRandomDucks(INITIAL_DUCK_CNT);
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
    drawDucks();

    stringstream ss;
    ss << "Ducks killed: " << score;
    string scoreStr = ss.str();
    drawStrokeText(scoreStr.c_str(), WIDTH/3, 3*HEIGHT/4, 0, FONT_SIZE_NORMAL);

    if (notifyMsg) {
        drawStrokeText(msg.c_str(), WIDTH/3, HEIGHT/2.5, 0, FONT_SIZE_NORMAL);
    }

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

void updateGameState() {
    switch (gameState) {
        case GAME_RESTART:
            notifyMsg = true;
            msg = "Restarting...";
            gameState = ROUND_INIT;
            initGame();
            break;

        case ROUND_INIT:
            break;

        case ROUND_ACTIVE:
            for (int i = 0; i < duckIndices.size(); i++) {
                ducks[duckIndices[i]].updatePos();
            }
            break;

        case ROUND_DONE:
            msg = "GAME OVER";
            notifyMsg = true;
            instructionMenuVisible = true;
            break;

        default:
            break;
    }
}

void fire() {
    int tempX = cursorX;
    int tempY = cursorY;
    //cout << "Cursor x, y: " << tempX << ", " << tempY << endl;
    for (int i = 0; i < duckIndices.size(); i++) {
        int a = duckIndices[i];
        //cout << "Duck["<< i+1 << "] x, y: " << ducks[a].pos.x << ", " << ducks[a].pos.y << endl;
        if (ducks[a].isHit(tempX, tempY)) {
            //cout << "Duck[" << i+1 << "] is hit!" << endl;
            ducks[a].alive = false;
            score++;
        }
    }
}

void drawDucks() {
    if (gameState == ROUND_ACTIVE)
        for (int i = 0; i < duckIndices.size(); i++) {
            ducks[duckIndices[i]].draw();;
        }
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
        "  r - Restart Game\n"
        "  d - Toggle Debugging Information", 10, HEIGHT-50, 0);
}

void showDebugInfo() {

    string debugText;

    stringstream ss;
    ss << "Debugging Info: " << endl;
    ss << "  Cursor X: " << cursorX << endl;
    ss << "  Cursor Y: " << cursorY << endl;
    ss << "  Duck Count: " << duckIndices.size() << endl;

    debugText = ss.str();

    drawBitmapText(debugText.c_str(), 10, HEIGHT - 500, 0);
}

void updateCursorCoords(int x, int y) {
    cursorX = x;
    cursorY = CURSOR_YMAX-y;
}

void chooseRandomDucks(int n) {
    duckIndices.clear();
    while (duckIndices.size() < n) {
        int x = rand() % MAX_DUCK_CNT;
        if (duckIndices.size() != 0 && find(duckIndices.begin(), duckIndices.end(), x) == duckIndices.end())
            continue;
        duckIndices.push_back(x);
    }
}

void notifyGame(int val) {
    switch (val) {
        case 0:                                 // Show "READY"
            notifyMsg = true;
            msg = "Ready";
            glutTimerFunc(1000, notifyGame, 1);
            break;

        case 1:
            msg = "3";
            glutTimerFunc(1000, notifyGame, 2);
            break;

        case 2:
            msg = "2";
            glutTimerFunc(1000, notifyGame, 3);
            break;

        case 3:
            msg = "1";
            glutTimerFunc(1000, notifyGame, 4);
            break;

        case 4:
            msg = "GO";
            glutTimerFunc(1000, notifyGame, 5);
            break;

        case 5:
            notifyMsg = false;
            gameState = ROUND_ACTIVE;

        default:
            break;
    }
}
