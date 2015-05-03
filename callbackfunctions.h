#ifndef CALLBACKFUNCS_H
#define CALLBACKFUNCS_H

void display();

void idle();

void reshape(int w, int h);

void normalKeys(unsigned char key, int x, int y);

void specialKeys(int key, int x, int y);

void mouseClick(int button, int state, int x, int y);

void setCursor(int x, int y);

void timerFunc(int n);

#endif //CALLBACKFUNCS_H
