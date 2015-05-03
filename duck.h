#ifndef DUCK_H
#define DUCK_H

#include <GL/gl.h>
#include "definations.h"

class Duck {

public:
    vec2f pos;
    GLfloat slope;
    GLfloat initYPos;

    bool alive;

    Duck();
    void draw();
    void updatePos();
    bool isHit(int x, int y);
};

#endif // DUCK_H
