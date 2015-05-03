#include <GL/freeglut.h>
#include "fonts.h"

const vec3f _FONT_SIZE_NORMAL = {0.5f, 0.5f, 1.0f};
const vec3f _FONT_SIZE_BIG = {1.0f, 1.0f, 1.0f};
const vec3f _FONT_SIZE_SMALL = {0.25f, 0.25f, 1.0f};

const vec3f *FONT_SIZE_NORMAL = &_FONT_SIZE_NORMAL;
const vec3f *FONT_SIZE_BIG = &_FONT_SIZE_BIG;
const vec3f *FONT_SIZE_SMALL = &_FONT_SIZE_SMALL;

void drawBitmapText(std::string text, int x, int y, int z) {

    glRasterPos3f(x, y, z);
//    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (unsigned char const *) text.c_str());
    glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char const *) text.c_str());
}

void drawStrokeText(std::string text, int x, int y, int z, const vec3f *fontSize) {

    glPushMatrix();

    glTranslatef(x, y, z);
    glScalef(fontSize->x, fontSize->y, fontSize->z);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char const *) text.c_str());

    glPopMatrix();
}
