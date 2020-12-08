#ifndef DOUBLE_TROUBLE_COLLISIONDETECTION_H
#define DOUBLE_TROUBLE_COLLISIONDETECTION_H

#include <list>
#include "LevelObject.hpp"
#include "Sprite.hpp"

bool wallCollisionDetection(Sprite &sprite, std::list<Wall> &walls);

bool enemyCollisionDetection(Sprite &sprite, std::list<StaticEnemy> &enemies);

#endif //DOUBLE_TROUBLE_COLLISIONDETECTION_H
