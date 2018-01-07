#include "Object.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"
#include "Toolbox.c"

Object::Object() {
  x = random(8, 72);
  y = random(8, 56);
  width = 4;
  height = 4;
  vx = random(0, 3) - 1;
  vy = random(0, 3) - 1;
  bounce = 0.9;
  friction = 0;
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
    float step = norm(vx) * 0.5;
    do {
      x -= step;
    } while (collideTile() > 0);
    vx *= - bounce;
    vy *= friction;
  }

  y += vy;
  if (collideTile() > 0) {
    float step = norm(vy) * 0.5;
    do {
      y -= step;
    } while (collideTile() > 0);
    vy *= - bounce;
    vx *= friction;
  }

  vy += Engine::gravity;
  vx = constrain(vx, -2, 2);
  vy = constrain(vy, -2, 2);
  if (abs(vx) < 0.1) vx = 0;
  if (abs(vy) < 0.1) vy = 0;
}

void Object::interact(Object* obj) {
  if (collide(obj)) {
    int16_t dx;
    int16_t dy;
    if ((vx == 0) && (vy == 0)) {
      return;
    }
    if (vx == 0) { //vertical collision
      dx = 1;
      dy = 0;
    } else if (vy == 0) { //horizontal collision
      dx = 0;
      dy = 1;
    } else if ((vx > 0) && (vy > 0)) { //bottom right corner
      dx = (x + width) - obj->x;
      dy = (y + height) - obj->y;
    } else if ((vx > 0) && (vy <= 0)) { //top right corner
      dx = (x + width) - obj->x;
      dy = y - (obj->y + obj->height);
    } else if ((vx < 0) && (vy < 0)) { //top left corner
      dx = x - (obj->x + obj->width);
      dy = y - (obj->y + obj->height);
    } else { //bottom left corner
      dx = x - (obj->x + obj->width);
      dy = (y + width) - obj->y;
    }
    dx = abs(dx);
    dy = abs(dy);
    if (dx < dy) { //horizontal collision
      float step = norm(vx) * 0.5;
      do {
        x -= step;
      } while (collide(obj) > 0);

      float v1 = vx;
      float m1 = width * height;
      float v2 = obj->vx;
      float m2 = obj->width * obj->height;
      vx = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
      obj->vx = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);

    } else { //vertical collision
      float step = norm(vy) * 0.5;
      do {
        y -= step;
      } while (collide(obj) > 0);

      float v1 = vy;
      float m1 = width * height;
      float v2 = obj->vy;
      float m2 = obj->width * obj->height;
      vy = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
      obj->vy = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
    }
  }
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


