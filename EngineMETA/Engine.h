#ifndef _ENGINE_H_
#define	_ENGINE_H_

#include "Object.h"
#include "Player.h"
#include "TileMap.h"

#define ENGINE_NUM_OBJECTS 50

class Engine {
  public:
    static float gravity, cameraX, cameraY, cameraTargetX, cameraTargetY;
    static Object *objects[ENGINE_NUM_OBJECTS];
    static TileMap *map;


    void init();
    void clear();
    void update();
    void draw();
    static int addObject(Object* object);
    void setTileMap(TileMap* tileMap);

};

#endif // _ENGINE_H_
