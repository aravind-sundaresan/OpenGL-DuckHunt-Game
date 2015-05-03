#ifndef DEFINATIONS_H
#define DEFINATIONS_H

#include <GL/gl.h>

// Window constants
#define WIDTH           1366
#define HEIGHT          768
#define XMIN            0
#define XMAX            WIDTH
#define YMIN            0
#define YMAX            HEIGHT
#define CURSOR_XMAX     1365
#define CURSOR_YMAX     712

typedef enum {
    START_SCREEN,
    GAME_SCREEN
} AppState;

typedef struct {

    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3f;

#endif //DEFINATIONS_H
