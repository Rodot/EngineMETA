#include <Gamebuino-Meta.h>
#include "Engine.h"
Engine engine = Engine();

void setup() {
  gb.begin();
  engine.init();
}

void loop() {

  while (!gb.update());
  gb.display.clear();
  if (gb.buttons.pressed(BUTTON_MENU)) {
    engine.clear();
    engine.init();
  }
  if (Engine::objects[0]) {
    Engine::cameraTargetX = Engine::objects[0]->getCenterX() - gb.display.width() / 2;
    Engine::cameraTargetY = Engine::objects[0]->getCenterY() - gb.display.height() / 2;
  }
  engine.update();
  engine.draw();
}

