#include <iostream>
#include <GL/freeglut.h>
#include "definations.h"
#include "callbackfunctions.h"
#include "game.h"
#include <time.h>

using namespace std;

void init();

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL-DuckHunt");

    // Register all callback functions
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(setCursor);
    glutMotionFunc(setCursor);

    init();

    glutMainLoop();

    return 0;
}

void init() {

    time_t t;
    srand((unsigned int) time(&t));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 0);
    //initGame();
}
