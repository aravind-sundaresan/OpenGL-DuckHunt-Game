#include <stdlib.h>
#include "definations.h"
#include "game.h"
#include "fonts.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include "duck.h"
#include <GL/freeglut.h>
#include <unistd.h>
#include <SOIL/SOIL.h>

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
float gameSpeed;
int duckCount;
int gameLevel;
GLuint duckTexture;

vector<int> duckIndices;

Duck ducks[MAX_DUCK_CNT];

void initRound();
void showInstructions();
void showDebugInfo();
void drawBackground();
void drawCursor();
void drawDucks();
void chooseRandomDucks(int n);
void initializeAllDucks();

void initGame() {

    duckTexture = SOIL_load_OGL_texture
                    (
                        "images/duck.jpg",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                    );
    //glActiveTexture(duckTexture);
    // check for an error during the load process
    if(duckTexture == 0)
        cout << "SOIL loading error: " << SOIL_last_result() << endl;

    duckCount = INITIAL_DUCK_CNT;
    gameLevel = 1;
    gameSpeed = 1.0f;
    score = 0;
    initializeAllDucks();
    initRound();
}

void initRound() {
    for (int i = 0; i < MAX_DUCK_CNT; i++) {
        ducks[i].alive = true;
        ducks[i].flewAway = false;
    }
    gameState = ROUND_INIT;
    notifyMsg = false;
    glutTimerFunc(100, notifyGame, 0);
    chooseRandomDucks(duckCount);
}

void initializeAllDucks() {
    for (int i = 0; i < MAX_DUCK_CNT; i++) {
        ducks[i].slope = ((float) rand() / (RAND_MAX));
        ducks[i].pos.y = (rand() % 500) + 250;
        ducks[i].pos.x = 0;
        ducks[i].alive = true;
        ducks[i].flewAway = false;
        ducks[i].onGround = false;
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

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2d(0, 0);
        glTexCoord2d(1, 0);
        glVertex2d(WIDTH, 0);
        glTexCoord2d(1, 1);
        glVertex2d(WIDTH, HEIGHT);
        glTexCoord2d(0, 1);
        glVertex2d(0, HEIGHT);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void gameScreen() {

    drawBackground();
    drawCursor();
    drawDucks();

    stringstream ss;
    ss << "Ducks killed: " << score;
    string scoreStr = ss.str();
    drawStrokeText(scoreStr.c_str(), WIDTH/3, 0.9*HEIGHT, 0, FONT_SIZE_SMALL);

    ss.str("");
    ss << "Level: " << gameLevel;
    string levelStr = ss.str();
    drawStrokeText(levelStr.c_str(), 0.8 * WIDTH, 0.9*HEIGHT, 0, FONT_SIZE_SMALL);

    if (notifyMsg) {
        int offset = (msg.size() >= 1) ? 20 * msg.size() : 0;
        drawStrokeText(msg.c_str(), WIDTH/2 - offset, 0.5 * HEIGHT, 0, FONT_SIZE_SMALL);
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
    //cout << "GameState: " << gameState << endl;
    bool allDucksOnGround;
    switch (gameState) {
        case GAME_RESTART:
            notifyMsg = true;
            msg = "Restarting...";
            initGame();
            break;

        case ROUND_INIT:
            break;

        case ROUND_ACTIVE:
            //cout << "Round active " << endl;
            // Update position of all the ducks
            for (int i = 0; i < duckIndices.size(); i++) {
                ducks[duckIndices[i]].updatePos(gameSpeed);
            }

            // Check if any duck has flown away
            for (int i = 0; i < duckIndices.size(); i++) {
                int a = duckIndices[i];
                if (ducks[a].flewAway) {
                    gameState = GAME_OVER;
                    return;
                }
            }

            // Check if all ducks are on the ground
            allDucksOnGround = true;
            for (int i = 0; i < duckIndices.size(); i++) {
                int a = duckIndices[i];
                if (!ducks[a].onGround) {
                    allDucksOnGround = false;
                    break;
                }
            }

            if (allDucksOnGround) {
                gameState = ROUND_OVER;
                return;
            }

            break;

        case ROUND_OVER:
            notifyMsg = true;
            msg = "Starting New Round...";
            duckCount++;
            gameSpeed += 1.5f;
            gameLevel++;
            gameState = ROUND_INIT;
            glutTimerFunc(2000, notifyGame, 6);
            break;

        case GAME_OVER:
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
    for (int i = 0; i < duckIndices.size(); i++) {
        int a = duckIndices[i];
        if (ducks[a].isHit(tempX, tempY)) {
            ducks[a].alive = false;
            score++;
        }
    }
}

void drawDucks() {
    glEnable(GL_TEXTURE_2D);
    if (gameState == ROUND_ACTIVE | gameState == ROUND_OVER)
        for (int i = 0; i < duckIndices.size(); i++) {
            ducks[duckIndices[i]].draw();;
        }
    glDisable(GL_TEXTURE_2D);
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
    ss << "  GameState: " << gameState << endl;
    ss << "  Cursor X: " << cursorX << endl;
    ss << "  Cursor Y: " << cursorY << endl;
    ss << "  Duck Count: " << duckIndices.size() << endl;
    for (vector<int>::iterator it = duckIndices.begin(); it != duckIndices.end(); ++it) {
        ss << "    Duck[" << *it << "]:: pos- x: " << ducks[*it].pos.x << ", y: " << ducks[*it].pos.y;
        ss << ", alive: " << (ducks[*it].alive) ? "yes" : "no";
        ss << ", flewAway: " << (ducks[*it].flewAway) ? "yes" : "no";
        ss << endl;
    }

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
        if (duckIndices.size() != 0 && find(duckIndices.begin(), duckIndices.end(), x) != duckIndices.end())
            continue;
        duckIndices.push_back(x);
    }
}

void notifyGame(int val) {
    switch (val) {
        case 0:                        // Show "READY"
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
            break;

        case 6:
            notifyMsg = false;
            initRound();
            break;

        default:
            break;
    }
}
