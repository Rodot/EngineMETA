#ifndef _TILEMAP_H_
#define  _TILEMAP_H_
#include <Arduino.h>

class TileMap {
  public:
    int *data;
    void draw();
    int tileWidth, tileHeight; //the size of the tiles in number of pixels
    int widthTiles, heightTiles; //the size of the map in number of tiles

    TileMap();
    int getTile(int x, int y);
};

#endif // _TILEMAP_H_
