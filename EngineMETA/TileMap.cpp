#include "TileMap.h"

#include <Gamebuino-Meta.h>
#include "Engine.h"

uint8_t myMap2[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

uint8_t myMap[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

TileMap::TileMap() {
  data = myMap;
  widthTiles = 12;
  heightTiles = 10;
  tileWidth = 8;
  tileHeight = 8;
}

void TileMap::draw() {
  gb.display.setColor(BROWN);
  for (int i = 0; i < widthTiles; i++) {
    for (int j = 0; j < heightTiles; j++) {
      if (data[i + (j * widthTiles)] > 0) {
        gb.display.drawRect(i * tileWidth - Engine::cameraX, j * tileHeight - Engine::cameraY, tileWidth, tileHeight);
      }
    }
  }
}

int16_t TileMap::getTile(int16_t x, int16_t y) {
  int16_t i = x / tileWidth;
  int16_t j = y / tileHeight;
  if((i < 0) || (i > widthTiles) || (j < 0) || (j > heightTiles)){
    return -1;
  }
  return data[i + (j * widthTiles)];
}

