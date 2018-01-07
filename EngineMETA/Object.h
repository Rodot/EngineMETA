#ifndef _OBJECT_H_
#define  _OBJECT_H_

#include <Arduino.h>

class Object {
  public:
    float x, y, vx, vy, width, height, bounce, friction;

    Object();
    Object(float X, float Y, float W, float H);
    Object(float X, float Y, float W, float H, float VX, float VY);
    void init();
    void update();
    void interact(Object* obj);
    void draw();
    int16_t collideTile();
    int16_t collide(Object* obj);
};

#endif // _OBJECT_H_
