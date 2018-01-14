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
  if (gb.buttons.repeat(BUTTON_UP, 1)) {
    vy -= 1;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
    vy += 1;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    vx += 1;
    direction = 1;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    vx -= 1;
    direction = -1;
  }


  if (gb.buttons.repeat(BUTTON_A, 4)) {
    if (direction > 0) {
      Engine::addObject(new Bullet(x + width + 1, getCenterY(), vx, vy, direction));
    } else {
      Engine::addObject(new Bullet(x - 1, getCenterY(), vx, vy, direction));
    }
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    Engine::addObject(new Object(x, y - 6, 6, 6, direction * 3, vy - 1));
  }
  Engine::cameraTargetX = getCenterX() - gb.display.width() / 2 + direction * 15;
  Engine::cameraTargetY = getCenterY() - gb.display.height() / 2 ;

  updatePhysics();

  //limit speeds
  vx = constrain(vx, -3, 3);
  vy = constrain(vy, -3, 3);
  if (abs(vx) < 0.02) vx = 0;
  if (abs(vy) < 0.02) vy = 0;

  bounce = 0;
  friction = 0.6;
  x += vx;
  collideMapX();

  y += vy;
  collideMapY();
  bounce = 0.6;
  friction = 0;
}

void Player::draw() {
  gb.display.setColor(WHITE);
  Object::draw();
}

