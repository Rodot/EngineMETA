#ifndef _TOOLBOX_H_
#define  _TOOLBOX_H_

#include <Arduino.h>

float norm(float n);
bool collidePointRect(int16_t x1, int16_t y1 ,int16_t x2 ,int16_t y2, int16_t w, int16_t h);
bool collideRectRect(int16_t x1, int16_t y1, int16_t w1, int16_t h1 ,int16_t x2 ,int16_t y2, int16_t w2, int16_t h2);

#endif // _TOOLBOX_H_
