#ifndef _OBJECT_H_
#define  _OBJECT_H_

#include <Arduino.h>

class Object {
  public:
    float x, y, vx, vy, width, height, bounce, friction;
    int16_t life;

    Object();
    Object(float X, float Y, float W, float H, float VX, float VY);
    void init();
    virtual void update();
    void interact(Object* obj);
    virtual void draw();
    int16_t collideTile();
    int16_t collide(Object* obj);
    float getCenterX();
    float getCenterY();
};

#endif // _OBJECT_H_
