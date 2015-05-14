#include "duck.h"
#include <iostream>

using namespace std;

Duck::Duck() {

}

void Duck::draw() {
    // Only draw the duck if it's still on the screen
    if (!flewAway) {
        //glPushAttrib(GL_CURRENT_BIT);
        glPushMatrix();
//        if (!alive)
//            glRotatef(90, 0, 0, 1);
        glBegin(GL_QUADS);
            //if (alive)
                //glColor3f(0.5, 0.35, 0.05);
            //else
                //glColor3f(0.5, 0, 0.05);
            glTexCoord2d(0, 0);
            glVertex2f (pos.x - DUCK_XSIZE/2, pos.y - DUCK_YSIZE/2);
            glTexCoord2d(0, 1);
            glVertex2f (pos.x - DUCK_XSIZE/2, pos.y + DUCK_YSIZE/2);
            glTexCoord2d(1, 1);
            glVertex2f (pos.x + DUCK_XSIZE/2, pos.y + DUCK_YSIZE/2);
            glTexCoord2d(1, 0);
            glVertex2f (pos.x + DUCK_XSIZE/2, pos.y - DUCK_YSIZE/2);
        glEnd();
        glPopMatrix();
        //glPopAttrib();
    }
}

void Duck::updatePos(float gameSpeed) {
    if (alive) {
        if (pos.y >= HEIGHT-DUCK_YSIZE)
            slope = -slope;
        else if (pos.y <= GROUND_LEVEL+DUCK_YSIZE)
            slope = -slope;
        pos.x += gameSpeed;
        pos.y = pos.y + slope * gameSpeed;
        if (pos.x > WIDTH)
            flewAway = true;
    } else {
        pos.y -= gameSpeed;
        if (pos.y <= GROUND_LEVEL) {
            pos.y = GROUND_LEVEL;
            onGround = true;
        }
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
