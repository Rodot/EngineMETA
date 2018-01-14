#ifndef _OBJECT_H_
#define  _OBJECT_H_

#include <Arduino.h>
#include <Gamebuino-Meta.h>


class Object {
  public:
    float x, y, vx, vy, ax, ay, width, height, bounce, friction, density;
    int life;
    bool collideMap, collideObjects, justCreated;
    Color color;

    Object();
    Object(float X, float Y, float W, float H, float VX, float VY);
    virtual void init();
    virtual void update();
    virtual void die();
    virtual void updatePhysics();
    virtual int collideMapX();
    virtual int collideMapY();
    virtual void interact(Object* obj);
    virtual void draw();
    int collidingTile();
    int colliding(Object* obj);
    float getCenterX();
    float getCenterY();
};

#endif // _OBJECT_H_
