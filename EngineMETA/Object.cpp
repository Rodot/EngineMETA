#include "Object.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"
#include "Toolbox.c"

Object::Object() {
  x = random(8, 72);
  y = random(8, 56);
  width = 8;
  height = 8;
  vx = random(0, 3) - 1;
  vy = random(0, 3) - 1;
  bounce = 0.9;
  friction = 0.95;
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
  vx = constrain(vx, -2, 2);
  vy = constrain(vy, -2, 2);
  if (abs(vx) < 0.1) vx = 0;
  if (abs(vy) < 0.1) vy = 0;
  x += vx;
  y += vy;
  /*x += vx;
    if (collideTile() > 0) {
    float step = norm(vx) * 0.5;
    do {
      x -= step;
    } while (collideTile() > 0);
    vx *= - bounce;
    }

    y += vy;
    if (collideTile() > 0) {
    float step = norm(vy) * 0.5;
    do {
      y -= step;
    } while (collideTile() > 0);
    vy *= - bounce;
    }*/

  //distance between centers
  float dx, dy;
  //penetration depth
  float px, py;
  uint16_t tileCenterX, tileCenterY;
  bool collision = false;
  int16_t tileWidth = Engine::map->tileWidth;
  int16_t tileHeight = Engine::map->tileHeight;

  for (float tx = x; tx <= (x + width); tx += tileWidth) {
    tx = min(x + width, tx);
    for (float ty = y; ty <= (y + height); ty += tileHeight) {
      ty = min(y + height, ty);
      if (Engine::map->getTile(tx, ty)) {
        collision = true;
        //distance between the tile center and the object center
        float tileX = (((uint16_t)tx / tileWidth) * tileWidth);
        float tileY = (((uint16_t)ty / tileHeight) * tileHeight);
        dx =  tileX + (tileWidth / 2) - x;
        dy =  tileY + (tileHeight / 2) - y;
        if ((dx >= 0) && (dy >= 0)) { //bottom right corner
          px = (x + width) - tileX;
          py = (y + height) - tileY;
        } else if ((dx >= 0) && (dy <= 0)) { //top right corner
          px = (x + width) - tileX;
          py = y - (tileY + tileHeight);
        } else if ((dx <= 0) && (dy <= 0)) { //top left corner
          px = x - (tileX + tileWidth);
          py = y - (tileY + tileHeight);
        } else { //bottom left corner
          px = x - (tileX + tileWidth);
          py = (y + width) - tileY;
        }
        if (abs(px) < abs(py)) { //horizontal collision
          x -= px;
          vx *= -bounce;
        } else { //vertical collision
          y -= py;
          vy *= -bounce;
        }
      }
    }
  }

}

void Object::interact(Object* obj) {
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
      py = (y + width) - obj->y;
    }
    if (abs(px) < abs(py)) { //horizontal collision
      x -= px;

      float v1 = vx;
      float m1 = width * height;
      float v2 = obj->vx;
      float m2 = obj->width * obj->height;
      vx = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
      obj->vx = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
      vx *= obj->bounce * bounce;
      obj->vx *= obj->bounce * bounce;

    } else { //vertical collision
      y -= py;

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

float Object::getCenterX() {
  return (x + width / 2);
}

float Object::getCenterY() {
  return (y + height / 2);
}


