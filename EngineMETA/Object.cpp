#include "Object.h"
#include <Gamebuino-Meta.h>
#include "Engine.h"
#include "Toolbox.c"

Object::Object() {
  x = random(8, 72);
  y = random(8, 56);
  width = random(2, 11);
  height = random(2, 11);;
  vx = random(0, 2) - 0.5f;
  vy = random(0, 2) - 0.5f;
  density = 1;
}

Object::Object(float X, float Y, float W, float H) {
  x = X;
  y = Y;
  width = W;
  height = H;
  vx = 0;
  vy = 0;
  density = 1;
}

Object::Object(float X, float Y, float W, float H, float VX, float VY, float D) {
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
  width = W;
  height = H;
  density = D;
}

void Object::update() {
  x += vx;
  if (collideTile() > 0) {
    do {
      x -= norm(vx);
    } while (collideTile() > 0);
    vx *= -1;
  }

  y += vy;
  if (collideTile() > 0) {
    do {
      y -= norm(vy);
    } while (collideTile() > 0);
    vy *= -1;
  }

  vy += Engine::gravity * density;
}

void Object::draw() {
  gb.display.setColor(WHITE);
  gb.display.drawRect(x, y, width, height);
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
  collideRectRect(x, y, width, height, obj->x, obj->y, obj->width, obj->height);
}


