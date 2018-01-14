#include "Engine.h"
#include <Gamebuino-Meta.h>

//static variables
float Engine::gravity = 0.3;
float Engine::cameraX = 8;
float Engine::cameraY = 8;
float Engine::cameraTargetX = 8;
float Engine::cameraTargetY = 8;
Object* Engine::objects[ENGINE_NUM_OBJECTS];
TileMap* Engine::map;

void Engine::init() {
  addObject(new Player());
  //while (addObject(new Object()));
  map = new TileMap();
}

void Engine::clear() {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    delete objects[i];
    objects[i] = NULL;
  }
}

void Engine::update() {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) continue;
    objects[i]->update();

    //interact with other objects
    for (int j = 0; j < ENGINE_NUM_OBJECTS; j++) {
      if (objects[j] == 0) continue;
      if (i == j) {
        continue;
      }
      if ((objects[i] != 0) && (objects[j] != 0)) {
        objects[i]->interact(objects[j]);
      }
    }
    //delete objects going out of the map
    if (  (objects[i]->x < 0)
          || (objects[i]->y < 0)
          || (objects[i]->x > (map->widthTiles * map->tileWidth))
          || (objects[i]->y > (map->heightTiles * map->tileHeight))) {
      delete objects[i];
      objects[i] = NULL;
    }
  }
}

void Engine::draw() {
  cameraX = (cameraX * 7 + cameraTargetX) / 8;
  cameraY = (cameraY * 7 + cameraTargetY) / 8;
  if (map != 0) {
    map->draw();
  }
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) continue;
    gb.display.setColor(WHITE);
    objects[i]->draw();
  }
  gb.display.print(gb.getCpuLoad());
  gb.display.print("% ");
  gb.display.print(gb.getFreeRam());
  gb.display.print(" ");
  int16_t num = 0;
  for (int16_t i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] != 0) num++;
  }
  gb.display.print(num);
  gb.display.print("/");
  gb.display.println(ENGINE_NUM_OBJECTS);
}

int Engine::addObject(Object* object) {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] == 0) {
      objects[i] = object;
      return 1; //object created
    }
  }
  return 0; //no more space
}

void Engine::setTileMap(TileMap* tileMap) {
  map = tileMap;
}

