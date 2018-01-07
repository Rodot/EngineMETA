#ifndef _ENGINE_H_
#define	_ENGINE_H_

#include "Object.h"
#include "TileMap.h"

#define ENGINE_NUM_OBJECTS 20

class Engine {
  public:
    static float gravity, cameraX, cameraY;
    static Object *objects[ENGINE_NUM_OBJECTS];
    static TileMap *map;


    void init();
    void update();
    void draw();
    int addObject(Object* object);
    void setTileMap(TileMap* tileMap);

};

#endif // _ENGINE_H_
