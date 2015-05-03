#include "duck.h"
#include <iostream>

using namespace std;

Duck::Duck() {
    slope = ((float) rand() / (RAND_MAX));
    pos.y = (rand() % 300) + 100;
    pos.x = 0;
    initYPos = pos.y;
    alive = true;
}

void Duck::draw() {
    glPushAttrib(GL_CURRENT_BIT);
    glBegin(GL_QUADS);
        if (alive)
            glColor3f(0.5, 0.35, 0.05);
        else
            glColor3f(0.5, 0, 0.05);
        glVertex2f (pos.x - DUCK_XSIZE/2, pos.y - DUCK_YSIZE/2);
        glVertex2f (pos.x - DUCK_XSIZE/2, pos.y + DUCK_YSIZE/2);
        glVertex2f (pos.x + DUCK_XSIZE/2, pos.y + DUCK_YSIZE/2);
        glVertex2f (pos.x + DUCK_XSIZE/2, pos.y - DUCK_YSIZE/2);
    glEnd();
    glPopAttrib();
}

void Duck::updatePos() {
    if (alive) {
        pos.x++;
        pos.y = pos.y + slope;
    } else {
        pos.y--;
        if (pos.y <= GROUND_LEVEL)
            pos.y = GROUND_LEVEL;
    }
}

bool Duck::isHit(int x, int y) {
    if (!alive)
        return false;
    if (x < pos.x + DUCK_XSIZE/2 && x > pos.x - DUCK_XSIZE/2
        && y < pos.y + DUCK_YSIZE/2 && y > pos.y - DUCK_YSIZE/2)
            return true;
    else
        return false;
}
