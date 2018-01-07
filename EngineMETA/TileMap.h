#ifndef _TILEMAP_H_
#define  _TILEMAP_H_
#include <Arduino.h>

class TileMap {
  public:
    uint8_t *data;
    void draw();
    uint8_t tileWidth, tileHeight; //the size of the tiles in number of pixels
    uint8_t widthTiles, heightTiles; //the size of the map in number of tiles

    TileMap();
    int16_t getTile(int16_t x, int16_t y);
};

#endif // _TILEMAP_H_
