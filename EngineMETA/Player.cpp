#include "Player.h"
#include <Gamebuino-Meta.h>
#include "Toolbox.h"

Player::Player() {
  init();
}

void Player::init() {
  Object::init();
  direction = 1;
  color = WHITE;
}

void Player::die() {
  Engine::addObject(new Player());
}

void Player::update() {
  if (gb.buttons.repeat(BUTTON_A, 4)) {
    if (direction > 0) {
      Engine::addObject(new Bullet(x + width + 1, getCenterY(), vx, vy, direction));
    } else {
      Engine::addObject(new Bullet(x - 1, getCenterY(), vx, vy, direction));
    }
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    Engine::addObject(new Object(x, y - 8, 6, 6, direction , vy - 3));
  }

  ax = 0;
  ay = 0;

  //underwater
  if ((Engine::map->getTile(getCenterX(), getCenterY()) == 2)) {
    jumped = false;
    if (gb.buttons.repeat(BUTTON_UP, 1)) {
      vy -= 0.5;
    }
    if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
      vy += 0.5;
    }
  }
  if (gb.buttons.pressed(BUTTON_UP) && (!jumped)) {
    vy = -3;
    jumped = true;
  }
  if ((gb.buttons.timeHeld(BUTTON_UP) > 0) && (gb.buttons.timeHeld(BUTTON_UP) < 6) && (vy < 0)) {
    vy -= 0.5;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    vx += 1;
    direction = 1;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    vx -= 1;
    direction = -1;
  }

  updatePhysics();

  //limit speeds
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -5, 5);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  bounce = 0;
  if (vy >= 0) friction = 0.8;
  if (vy < 0) friction = 1;
  vx += ax;
  x += vx;
  int collided = collideMapX();
  //wall jump
  if ((vy > 0) && collided) {
    if (gb.buttons.pressed(BUTTON_UP)) {
      vy = -3;
      vx = - direction * 5;
      jumped = true;
    }
  }

  friction = 0.6;
  vy += ay;
  y += vy;
  bool falling = (vy > 0) ? true : false;
  collided = collideMapY();
  if (falling && collided) {
    jumped = false;
  }

  bounce = 0.6;

  Engine::cameraTargetX = getCenterX() - gb.display.width() / 2 + direction * 15;
  Engine::cameraTargetY = getCenterY() - gb.display.height() / 2 ;
}

//plain copy and paste expect for friction, erk
void Player::interact(Object * obj) {
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
        if(y > 0){
          jumped = false;
        }

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
        //obj->vx += fvx;
      }
    }
  }
}

void Player::draw() {
  gb.display.setColor(WHITE);
  Object::draw();
}

