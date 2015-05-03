#ifndef DEFINATIONS_H
#define DEFINATIONS_H

#include <stdlib.h>
#include <GL/gl.h>

// Window constants
#define WIDTH           1366
#define HEIGHT          712
#define XMIN            0
#define XMAX            WIDTH
#define YMIN            0
#define YMAX            HEIGHT
#define CURSOR_XMAX     1365
#define CURSOR_YMAX     712
#define GROUND_LEVEL    200

#define INITIAL_DUCK_CNT    1
#define MAX_DUCK_CNT        20

#define DUCK_XSIZE      30
#define DUCK_YSIZE      20

typedef enum {
    START_SCREEN,
    GAME_SCREEN
} AppState;

typedef enum {
    GAME_RESTART,
    ROUND_INIT,
    ROUND_ACTIVE,
    ROUND_DONE
} GameState;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vec3f;

typedef struct {
    GLfloat x;
    GLfloat y;
} vec2f;

#endif //DEFINATIONS_H
