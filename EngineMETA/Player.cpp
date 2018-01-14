#include "Player.h"
#include <Gamebuino-Meta.h>
#include "Toolbox.h"

void Player::update() {
  if (gb.buttons.repeat(BUTTON_UP, 1)) {
    vy -= 0.5;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
    vy += 0.5;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    vx += 0.5;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    vx -= 0.5;
  }
  if (gb.buttons.pressed(BUTTON_A)) {
    Engine::addObject(new Object(x, y - 6, 6, 6, norm(vx) * 3, vy));
  }
  Object::update();
}

void Player::draw() {
  gb.display.setColor(BLUE);
  Object::draw();
}

