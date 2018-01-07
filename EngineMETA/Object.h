#ifndef _OBJECT_H_
#define  _OBJECT_H_

#include <Arduino.h>

class Object {
  public:
    float x, y, vx, vy, width, height, density;

    Object();
    Object(float X, float Y, float W, float H);
    Object(float X, float Y, float W, float H, float VX, float VY, float D);
    void init();
    void update();
    void draw();
    int16_t collideTile();
    int16_t collide(Object* obj);

};

#endif // _OBJECT_H_
