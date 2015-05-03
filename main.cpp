#include <iostream>
#include <GL/freeglut.h>
#include "definations.h"
#include "callbackfunctions.h"

using namespace std;

void init();

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL-DuckHunt");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(specialKeys);

    init();

    glutMainLoop();

    return 0;
}

void init() {
    glClearColor(0, 0, 0, 0);
}
