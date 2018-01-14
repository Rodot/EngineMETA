#ifndef _PARTICLE_H_
#define _PARTICL_H_

#include "Object.h"

class Particle : public Object {
  public:
    Particle(float X, float Y, float VX, float VY, float W, float H, boolean collide);
    virtual void update();
    virtual void die();
};

#endif
