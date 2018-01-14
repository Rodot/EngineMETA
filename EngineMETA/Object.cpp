#include "Object.h"

#include "Engine.h"
#include "Toolbox.h"

Object::Object() {
  init();
}

Object::Object(float X, float Y, float W, float H, float VX, float VY) {
  init();
  x = X;
  y = Y;
  vx = VX;
  vy = VY;
  width = W;
  height = H;
}

void Object::init() {
  x = random(8, 72);
  y = random(8, 56);
  vx = 0;
  vy = 0;
  ax = 0;
  ay = 0;
  width = 6;
  height = 6;
  bounce = 0.8;
  friction = 0.9;
  density = 1.2;
  life = 10;
  collideMap = true;
  collideObjects = true;
  justCreated = true;
  color = GRAY;
}

void Object::die() {
  Engine::addObject(new Particle(x, y , vx, -3, width, height, false));
}

void Object::update() {
  updatePhysics();

  //limit speeds
  vx = constrain(vx, -7, 7);
  vy = constrain(vy, -7, 7);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  vx += ax;
  x += vx;
  collideMapX();

  vy += ay;
  y += vy;
  collideMapY();


}

void Object::updatePhysics() {
  //water physics
  if (collideMap && (Engine::map->getTile(getCenterX(), getCenterY()) == 2)) {
    vy += (Engine::gravity * (density - 1));
    vy *= 0.6;
    vx *= 0.6;
  } else {
    //normal physics
    vy += (Engine::gravity * density);
  }
}

int Object::collideMapX() {
  if (collideMap) {
    if (vx > 0) {
      if ((Engine::map->getTile(x + width, y) == 1) || (Engine::map->getTile(x + width, y + height) == 1)) {
        int tileX = (((int)(x + width) / (int)Engine::map->tileWidth) * (int)Engine::map->tileWidth);
        x = tileX - width - 0.01;
        vx *= - bounce;
        vy *= friction;
        return 1;
      }
    }
    else {
      if ((Engine::map->getTile(x, y) == 1) || (Engine::map->getTile(x, y + height) == 1)) {
        int tileX = (((int)x / (int)Engine::map->tileWidth) * (int)Engine::map->tileWidth);
        x = tileX + Engine::map->tileWidth + 0.01;
        vx *= - bounce;
        vy *= friction;
        return 1;
      }
    }
  }
  return 0;
}

int Object::collideMapY() {
  if (collideMap) {
    if (vy > 0) {
      if ((Engine::map->getTile(x, y + height) == 1) || (Engine::map->getTile(x + width, y + height) == 1)) {
        int tileY = (((int)(y + height) / (int)Engine::map->tileHeight) * (int)Engine::map->tileHeight);
        y = tileY - height - 0.01;
        vy *= - bounce;
        vx *= friction;
        return 1;
      }
    } else {
      if ((Engine::map->getTile(x, y) == 1) || (Engine::map->getTile(x + width, y) == 1)) {
        int tileY = (((int)y / (int)Engine::map->tileHeight) * (int)Engine::map->tileHeight);
        y = tileY + Engine::map->tileHeight + 0.01;
        vy *= - bounce;
        vx *= friction;
        return 1;
      }
    }
  }
  return 0;
}

void Object::interact(Object * obj) {
  if (collideObjects && obj->collideObjects) {
    if (colliding(obj)) {
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
        float m1 = width * height * density;
        float v2 = obj->vx;
        float m2 = obj->width * obj->height * obj->density;
        vx = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
        obj->vx = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
        vx *= obj->bounce * bounce;
        obj->vx *= obj->bounce * bounce;
        //friction
        float fvy = (vy - obj->vy) * (friction + obj->friction) / 2;
        vy -= fvy;
        obj->vy += fvy;

      } else { //vertical collision
        y -= (py + 0.01);

        float v1 = vy;
        float m1 = width * height * density;
        float v2 = obj->vx;
        float m2 = obj->width * obj->height * obj->density;
        vy = v1 * (m1 - m2) / (m1 + m2) + v2 * 2 * m2 / (m1 + m2);
        obj->vy = v1 * 2 * m1 / (m1 + m2) + v2 * (m2 - m1) / (m1 + m2);
        vy *= obj->bounce * bounce;
        obj->vy *= obj->bounce * bounce;
        //friction
        float fvx = (vx - obj->vx) * (friction + obj->friction) / 2;
        vx -= fvx;
        obj->vx += fvx;
      }
    }
  }
}

void Object::draw() {
  gb.display.setColor(color);
  gb.display.drawRect((int)(x + 0.05) - (int)Engine::cameraX, (int)(y + 0.05) - (int)Engine::cameraY, width, height);
}

int Object::collidingTile() {
  int tile = -1;
  int temp = Engine::map->getTile(x, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width, y);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x, y + height);
  if (temp > tile) tile = temp;
  temp = Engine::map->getTile(x + width, y + height);
  if (temp > tile) tile = temp;
  return tile;
}

int Object::colliding(Object * obj) {
  return collideRectRect(x, y, width, height, obj->x, obj->y, obj->width, obj->height);
}

float Object::getCenterX() {
  return (x + width / 2);
}

float Object::getCenterY() {
  return (y + height / 2);
}


