#ifndef DOUBLE_TROUBLE_COLLISIONDETECTION_H
#define DOUBLE_TROUBLE_COLLISIONDETECTION_H

#include <list>
#include "LevelObject.hpp"
#include "Sprite.hpp"

bool wallCollisionDetection(Sprite &sprite, std::list<Wall> &walls);

bool otherCollisionDetection(Sprite &sprite, std::list<LevelObjects> &objects);

#endif //DOUBLE_TROUBLE_COLLISIONDETECTION_H
