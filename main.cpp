#include <iostream>
#include <GL/freeglut.h>
#include "definations.h"
#include "callbackfunctions.h"
#include "game.h"
#include <time.h>
#include <SOIL/SOIL.h>

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
    GLuint texture = SOIL_load_OGL_texture
                    (
                        "images/duck-hunt-home.jpg",
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
                    );

    // check for an error during the load process
    if(texture == 0)
        cout << "SOIL loading error: " << SOIL_last_result() << endl;
    //initGame();
}
