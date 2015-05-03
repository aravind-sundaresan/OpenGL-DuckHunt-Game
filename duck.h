#ifndef DUCK_H
#define DUCK_H

#include <GL/gl.h>
#include "definations.h"

class Duck {

public:
    vec2f pos;
    GLfloat slope;
    bool flewAway;
    bool alive;
    bool onGround;

    Duck();
    void draw();
    void updatePos(float gameSpeed);
    bool isHit(int x, int y);
};

#endif // DUCK_H
