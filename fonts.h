#ifndef FONTS_H
#define FONTS_H

#include <iostream>
#include "definations.h"

extern const vec3f *FONT_SIZE_NORMAL;
extern const vec3f *FONT_SIZE_BIG;
extern const vec3f *FONT_SIZE_SMALL;

void drawBitmapText(std::string text, int x, int y, int z);

void drawStrokeText(std::string text, int x, int y, int z, const vec3f *fontSize);

#endif //FONTS_H

