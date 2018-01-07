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
  engine.update();
  engine.draw();
}

