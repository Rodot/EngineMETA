#include "Engine.h"
#include <Gamebuino-Meta.h>

//static variables
float Engine::gravity = 0.1;
Object* Engine::objects[ENGINE_NUM_OBJECTS];
TileMap* Engine::map;

void Engine::init() {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    objects[i] = 0; //NULL POINTER
  }
  map = 0;
}

void Engine::update() {
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] != 0) {
      objects[i]->update();
    }
  }
}

void Engine::draw() {
  if (map != 0) {
    map->draw();
  }
  for (int i = 0; i < ENGINE_NUM_OBJECTS; i++) {
    if (objects[i] != 0) {
      objects[i]->draw();
    }
  }
  gb.display.println(gb.getCpuLoad());
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

