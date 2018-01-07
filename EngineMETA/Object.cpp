#include "Object.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"
#include "Toolbox.c"

Object::Object() {
  x = random(8, 72);
  y = random(8, 56);
  width = random(2, 2);
  height = random(2, 2);
  vx = random(0, 5) - 2;
  vy = random(0, 5) - 2;
  bounce = 0.8;
  friction = 0.8;
}

Object::Object(float X, float Y, float W, float H) {
  x = X;
  y = Y;
  width = W;
  height = H;
  vx = 0;
  vy = 0;
}

Object::Object(float X, float Y, float W, float H, float VX, float VY) {
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
  width = W;
  height = H;
}

void Object::update() {
  x += vx;
  if (collideTile() > 0) {
    float step = norm(vx)*0.5;
    do {
      x -= step;
    } while (collideTile() > 0);
    vx *= - bounce;
    vy *= friction;
  }

  y += vy;
  if (collideTile() > 0) {
    float step = norm(vy)*0.5;
    do {
      y -= step;
    } while (collideTile() > 0);
    vy *= - bounce;
    vx *= friction;
  }

  vy += Engine::gravity;
}



void Object::draw() {
  gb.display.setColor(WHITE);
  gb.display.drawRect(x - Engine::cameraX, y - Engine::cameraY, width, height);
}

int16_t Object::collideTile() {
  int16_t tile = -1;
  int16_t temp = Engine::map->getTile(x, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width - 1, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x, y + height - 1);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width - 1, y + height - 1);
  if (temp > tile) tile = temp;
  return tile;
}

int16_t Object::collide(Object* obj) {
  return collideRectRect(x, y, width, height, obj->x, obj->y, obj->width, obj->height);
}


