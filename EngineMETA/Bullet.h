#ifndef _BULLET_H_
#define _BULLET_H_

#include <Arduino.h>
#include "Object.h"
#include "Toolbox.h"
#include "Engine.h"
#include "Particle.h"

class Bullet : public Object {
  public:
    Bullet(float X, float Y, float VX, float VY, int direction);
    virtual void die();
    virtual void update();
    virtual void updatePhysics();
    virtual void interact(Object* obj);

};


#endif //_BULLET_H_
