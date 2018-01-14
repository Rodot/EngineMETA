#ifndef _PLAYER_H_
#define  _PLAYER_H_

#include "Object.h"
#include "Engine.h"

class Player : public Object{
  virtual void update();
  virtual void draw();
  
};

#endif // _PLAYER_H_
