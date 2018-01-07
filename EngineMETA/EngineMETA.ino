#include <Gamebuino-Meta.h>
#include "Engine.h"
Engine engine = Engine();

void setup() {
  gb.begin();
  engine.init();

  while (engine.addObject(new Object()));

  engine.setTileMap(new TileMap());
}

void loop() {

  while (!gb.update());
  gb.display.clear();
  if (gb.buttons.repeat(BUTTON_UP, 1)) {
    Engine::objects[0]->vy -= 0.5;
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 1)) {
    Engine::objects[0]->vy += 0.5;
  }
  if (gb.buttons.repeat(BUTTON_RIGHT, 1)) {
    Engine::objects[0]->vx += 0.5;
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 1)) {
    Engine::objects[0]->vx -= 0.5;
  }
  if (gb.buttons.pressed(BUTTON_A)) {
    Engine::gravity *= -1;
  }
  if (gb.buttons.pressed(BUTTON_B)) {
    for (uint16_t i = 0; i < ENGINE_NUM_OBJECTS; i++) {
      Engine::objects[i]->x = random(8, 72);
      Engine::objects[i]->y = random(8, 56);
      Engine::objects[i]->width = random(4,8);
      Engine::objects[i]->height = random(4,8);
      Engine::objects[i]->vx = random(0, 3) - 1;
      Engine::objects[i]->vy = random(0, 3) - 1;
    }
  }
  engine.update();
  engine.draw();
}

