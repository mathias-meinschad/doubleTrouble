#include "CollisionDetection.hpp"

template<typename T, typename F>
bool collisionBelow(const T &obj1, const F &obj2) {
    if (obj1.position.y + obj1.drawBox.height > obj2.position.y && obj1.position.y < obj2.position.y + obj2.drawBox.height) {
        if (obj1.position.x + obj1.drawBox.width > obj2.position.x && obj1.position.x < obj2.position.x + obj2.drawBox.width) {
            return true;
        }
    }
    return false;
}

template<typename T, typename F>
bool collisionTop(const T &obj1, const F &obj2) {
    if (obj1.position.y < obj2.position.y + obj2.drawBox.height && obj1.position.y + obj1.drawBox.height > obj2.position.y) {
        if (obj1.position.x + obj1.drawBox.width > obj2.position.x && obj1.position.x < obj2.position.x + obj2.drawBox.width) {
            return true;
        }
    }
    return false;
}

template<typename T, typename F>
bool collisionRight(const T &obj1, const F &obj2) {
    if (obj1.position.y + obj1.drawBox.height > obj2.position.y && obj1.position.y < obj2.position.y + obj2.drawBox.height) {
        if (obj1.position.x + obj1.drawBox.width > obj2.position.x && obj1.position.x < obj2.position.x + obj2.drawBox.width) {
            return true;
        }
    }
    return false;
}

template<typename T, typename F>
bool collisionLeft(const T &obj1, const F &obj2) {
    if (obj1.position.y + obj1.drawBox.height > obj2.position.y && obj1.position.y < obj2.position.y + obj2.drawBox.height) {
        if (obj1.position.x < obj2.position.x + obj2.drawBox.width && obj1.position.x + obj1.drawBox.width > obj2.position.x) {
            return true;
        }
    }
    return false;
}

// for wall collisions I wanted to detect them earlier to react in time
bool wallCollisionTop(const Sprite &sprite, const LevelObjects &object) {
    if (sprite.position.y < object.position.y + object.drawBox.height + 2 &&
        sprite.position.y + sprite.drawBox.height > object.position.y) {
        if (sprite.position.x + sprite.drawBox.width > object.position.x &&
            sprite.position.x < object.position.x + object.drawBox.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionBelow(const Sprite &sprite, const LevelObjects &object) {
    if (sprite.position.y + sprite.drawBox.height + 2 > object.position.y &&
        sprite.position.y < object.position.y + object.drawBox.height) {
        if (sprite.position.x + sprite.drawBox.width > object.position.x &&
            sprite.position.x < object.position.x + object.drawBox.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionRight(const Sprite &sprite,  const LevelObjects &object) {
    if (sprite.position.y + sprite.drawBox.height > object.position.y &&
        sprite.position.y < object.position.y + object.drawBox.height) {
        if (sprite.position.x + sprite.drawBox.width + 2 > object.position.x &&
            sprite.position.x < object.position.x + object.drawBox.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionLeft(const Sprite &sprite, const LevelObjects &object) {
    if (sprite.position.y + sprite.drawBox.height > object.position.y &&
        sprite.position.y < object.position.y + object.drawBox.height) {
        if (sprite.position.x < object.position.x + object.drawBox.width + 2 &&
            sprite.position.x + sprite.drawBox.width > object.position.x) {
            return true;
        }
    }
    return false;
}

bool wallCollision(Sprite &sprite, const std::list<LevelObjects> &walls) {
    bool collision = false;
    for (auto &wall : walls) {
        if (wallCollisionRight(sprite, wall)) {
            sprite.position.x -= 1;
            sprite.velocity_x = 0;
            collision = true;
        }

        if (wallCollisionLeft(sprite, wall)) {
            sprite.position.x += 1;
            sprite.velocity_x = 0;
            collision = true;
        }

        if (wallCollisionBelow(sprite, wall)) {
            if (sprite.position.y + 10 < wall.position.y) {
                sprite.position.y = wall.position.y - sprite.drawBox.height;
            }
            sprite.grounded = true;
            sprite.velocity_y = 0;
            collision = true;
        }

        if (wallCollisionTop(sprite, wall)) {
            sprite.position.y = wall.position.y + wall.drawBox.height + 2;
            sprite.velocity_y = 0;
            collision = true;
        }
    }

    return collision;
}

bool objectCollision( Sprite &sprite,  std::list<LevelObjects> &objects) {
    for (auto &object : objects) {
        if (collisionBelow(sprite, object) || collisionTop(sprite, object) || collisionLeft(sprite, object) ||
            collisionRight(sprite, object)) {
            return true;
        }
    }
    return false;
}

bool spriteCollision(Sprite &sprite1, Sprite &sprite2) {
    if (collisionBelow(sprite1, sprite2) || collisionTop(sprite1, sprite2) || collisionLeft(sprite1, sprite2) ||
        collisionRight(sprite1, sprite2)) {
        return true;
    }

    return false;
}

void wallCollisionDetection(const Level& level, Player& player1, Player& player2, Zombie& zombie1, Zombie& zombie2) {
    if (!wallCollision(player1, level.walls)) {
        player1.grounded = false;
    }

    if (!wallCollision(player2, level.walls)) {
        player2.grounded = false;
    }

    if (wallCollision(zombie1, level.walls)) {
        zombie1.direction = zombie1.direction == LEFT ? RIGHT : LEFT;
        zombie1.velocity_x = zombie1.direction == LEFT ? (-ZOMBIE_VELOCITY) : ZOMBIE_VELOCITY;
    }

    if (wallCollision(zombie2, level.walls)) {
        zombie2.direction = zombie2.direction == LEFT ? RIGHT : LEFT;
        zombie2.velocity_x = zombie2.direction == LEFT ? (-ZOMBIE_VELOCITY) : ZOMBIE_VELOCITY;
    }
}

bool objectCollisionDetection(Level& level, Player& player1, Player& player2, Zombie& zombie1, Zombie& zombie2) {
    bool levelDone = false;
    if (objectCollision(player1, level.staticEnemies)) {
        SDL_Delay(500);
        resetPositions(level, player1, player2, zombie1, zombie2);
        level.showLevelInfoTime = SDL_GetTicks();
    }

    if (objectCollision(player2, level.staticEnemies)) {
        SDL_Delay(500);
        resetPositions(level, player1, player2, zombie1, zombie2);
        level.showLevelInfoTime = SDL_GetTicks();
    }

    if (objectCollision(player1, level.finishElements)
        && objectCollision(player2, level.finishElements)) {
        levelDone = true;
    }

    if (spriteCollision(player1, zombie1)
        || spriteCollision(player1, zombie2)
        || spriteCollision(player2, zombie2)
        || spriteCollision(player2, zombie1)) {
        SDL_Delay(500);
        resetPositions(level, player1, player2, zombie1, zombie2);
        level.showLevelInfoTime = SDL_GetTicks();
    }

    return levelDone;
}