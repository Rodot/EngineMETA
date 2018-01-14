#ifndef _TOOLBOX_H_
#define  _TOOLBOX_H_

#include <Arduino.h>

float norm(float n);
bool collidePointRect(int x1, int y1 ,int x2 ,int y2, int w, int h);
bool collideRectRect(int x1, int y1, int w1, int h1 ,int x2 ,int y2, int w2, int h2);

#endif // _TOOLBOX_H_
