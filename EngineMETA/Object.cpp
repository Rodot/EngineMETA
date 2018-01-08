#include "Object.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"
#include "Toolbox.c"

Object::Object() {
  x = random(8, 72);
  y = random(8, 56);
  width = 6;
  height = 6;
  vx = random(0, 3) - 1;
  vy = random(0, 3) - 1;
  bounce = 0.8;
  friction = 0.98;
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
  vy += Engine::gravity;
  vy *= friction;
  vx *= friction;
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -3, 3);
  if (abs(vx) < 0.1) vx = 0;
  if (abs(vy) < 0.1) vy = 0;
  //x += vx;
  //y += vy;
  x += vx;

  if (vx > 0) {
    if ((Engine::map->getTile(x + width, y) > 0) || (Engine::map->getTile(x + width, y + height) > 0)) {
      uint16_t tileX = (((uint16_t)(x + width) / (uint16_t)Engine::map->tileWidth) * (uint16_t)Engine::map->tileWidth);
      x = tileX - width - 0.01;
      vx *= - bounce;
    }
  }
  else {
    if ((Engine::map->getTile(x, y) > 0) || (Engine::map->getTile(x, y + height) > 0)) {
      uint16_t tileX = (((uint16_t)x / (uint16_t)Engine::map->tileWidth) * (uint16_t)Engine::map->tileWidth);
      x = tileX + Engine::map->tileWidth + 0.01;
      vx *= - bounce;
    }
  }

  y += vy;
  if (vy > 0) {
    if ((Engine::map->getTile(x, y + height) > 0) || (Engine::map->getTile(x + width, y + height) > 0)) {
      uint16_t tileY = (((uint16_t)(y + height) / (uint16_t)Engine::map->tileHeight) * (uint16_t)Engine::map->tileHeight);
      y = tileY - height - 0.01;
      vy *= - bounce;
    }
  } else {
    if ((Engine::map->getTile(x, y) > 0) || (Engine::map->getTile(x + width, y) > 0)) {
      uint16_t tileY = (((uint16_t)y / (uint16_t)Engine::map->tileHeight) * (uint16_t)Engine::map->tileHeight);
      y = tileY + Engine::map->tileHeight + 0.01;
      vy *= - bounce;
    }
  }
}

void Object::interact(Object * obj) {
  if (collide(obj)) {
    if ((vx == 0) && (vy == 0)) {
      return;
    }
    //distance between centers
    float dx, dy;
    //penetration depth
    float px, py;

    dx = obj->getCenterX() - getCenterX();
    dy = obj->getCenterY() - getCenterY();

    if ((dx >= 0) && (dy >= 0)) { //bottom right corner
      px = (x + width) - obj->x;
      py = (y + height) - obj->y;
    } else if ((dx >= 0) && (dy <= 0)) { //top right corner
      px = (x + width) - obj->x;
      py = y - (obj->y + obj->height);
    } else if ((dx <= 0) && (dy <= 0)) { //top left corner
      px = x - (obj->x + obj->width);
      py = y - (obj->y + obj->height);
    } else { //bottom left corner
      px = x - (obj->x + obj->width);
      py = (y + height) - obj->y;
    }
    if (abs(px) < abs(py)) { //horizontal collision
      x -= (px + 0.01);

      float v1 = vx;
      float m1 = width * height;
      float v2 = obj->vx;
      float m2 = obj->width * obj->height;
      vx = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
      obj->vx = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
      vx *= obj->bounce * bounce;
      obj->vx *= obj->bounce * bounce;

    } else { //vertical collision
      y -= (py + 0.01);

      float v1 = vy;
      float m1 = width * height;
      float v2 = obj->vy;
      float m2 = obj->width * obj->height;
      vy = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
      obj->vy = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
      vy *= obj->bounce * bounce;
      obj->vy *= obj->bounce * bounce;
    }
  }
}

void Object::draw() {
  gb.display.drawRect((int16_t)(x + 0.05) - (int16_t)Engine::cameraX, (int16_t)(y + 0.05) - (int16_t)Engine::cameraY, width, height);
}

int16_t Object::collideTile() {
  int16_t tile = -1;
  int16_t temp = Engine::map->getTile(x, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x, y + height);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width, y + height);
  if (temp > tile) tile = temp;
  return tile;
}

int16_t Object::collide(Object * obj) {
  return collideRectRect(x, y, width, height, obj->x, obj->y, obj->width, obj->height);
}

float Object::getCenterX() {
  return (x + width / 2);
}

float Object::getCenterY() {
  return (y + height / 2);
}


