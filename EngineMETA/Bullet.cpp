#include "Bullet.h"

Bullet::Bullet(float X, float Y, float VX, float VY, int direction) {
  Object::init();
  x = X;
  y = Y;
  width = 4;
  height = 1;
  vx = 7 * norm(direction);
  vy = VY + float(random(0, 10) - 5) / 10;
  bounce = 0.25;
  density = 0.5;
  life = 10;
  collideMap = true;
  collideObjects = false;
  if (direction < 0) {
    x -= width;
  }
  x -= vx; //go back one step so the first update is done in the right place
  x += 2 * VX; //offset by the shooter's speed to avoid killing him lol
  //not that far when underwater
  if (Engine::map->getTile(getCenterX(), getCenterY()) == 2) {
    x += vx / 2;
  }
}

void Bullet::die() {
  life = 0;
  Engine::addObject(new Particle(x + 1, y , -norm(vx) * 0.5, vy, 2, 1, true));
}

void Bullet::update() {
  Object::update();
  if (abs(vx) < 2) {
    life = 0;
  }
}

void Bullet::updatePhysics() {
  //water physics
  if ((Engine::map->getTile(getCenterX(), getCenterY()) == 2)) {
    vy *= 0.8;
    vx *= 0.8;
  } else {
    //normal physics
  }
}

void Bullet::interact(Object * obj) {
  if (!life) return;
  if (colliding(obj)) {
    obj->life -= 3;
    obj->vx += norm(vx);
    if (obj->life < 0) {
      obj->vx = norm(vx) * 3;
    }
    life = 0;
    return;
  }
}
