#ifndef _PLAYER_H_
#define  _PLAYER_H_

#include "Object.h"
#include "Engine.h"
#include "Bullet.h"

class Player : public Object {
  public:
    Player();
    virtual void init();
    virtual void die();
    virtual void update();
    virtual void interact(Object* obj);
    virtual void draw();
    int direction;

    bool jumped = false;

};

#endif // _PLAYER_H_
