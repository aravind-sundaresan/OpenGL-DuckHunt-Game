#include <GL/freeglut.h>
#include "callbackfunctions.h"
#include "game.h"
#include <iostream>

using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (appState == START_SCREEN) {
        startScreen();
    } else if (appState == GAME_SCREEN) {
        gameScreen();
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGHT, 0, 2);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    updateGameState();
    glutPostRedisplay();
}

void normalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 27:    // ESC key
            if (appState == START_SCREEN)
                exit(EXIT_SUCCESS);
        case 13:    // Enter key
            if (appState == START_SCREEN) {
                glutSetCursor(GLUT_CURSOR_NONE);
                appState = GAME_SCREEN;
                initGame();
            }
            break;
        case 'q':
            if (appState == GAME_SCREEN) {
                glutSetCursor(GLUT_CURSOR_INHERIT);
                appState = START_SCREEN;
            }
            break;
        case 'i':
            instructionMenuVisible = !instructionMenuVisible;
            break;
        case 'd':
            debugInfoVisible = !debugInfoVisible;
            break;
        case 'r':
            if (appState == GAME_SCREEN)
                gameState = GAME_RESTART;
            break;
        default:
            break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        default:
            break;
    }
}


void mouseClick(int button, int state, int x, int y) {
    if (appState == GAME_SCREEN) {
        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                isShooting = true;
                fire();
            }
            else
                isShooting = false;
        }
    }
}

void setCursor(int x, int y) {
    updateCursorCoords(x, y);
}
