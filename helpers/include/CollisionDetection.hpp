#ifndef DOUBLE_TROUBLE_COLLISIONDETECTION_HPP
#define DOUBLE_TROUBLE_COLLISIONDETECTION_HPP

#include <list>
#include "LevelObject.hpp"
#include "Sprite.hpp"
#include "GeneralHelper.hpp"

void wallCollisionDetection(const Level& level, Player& player1, Player& player2, Zombie& zombie1, Zombie& zombie2);

bool objectCollisionDetection(Level& level, Player& player1, Player& player2, Zombie& zombie1, Zombie& zombie2);

#endif //DOUBLE_TROUBLE_COLLISIONDETECTION_HPP
