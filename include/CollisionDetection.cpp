#include "CollisionDetection.h"

template<typename T, typename F>
bool collisionBelow(T &obj1, F &obj2) {
    if (obj1.position.y + obj1.drawBox.height > obj2.position.y && obj1.position.y < obj2.position.y + obj2.drawBox.height) {
        if (obj1.position.x + obj1.drawBox.width > obj2.position.x && obj1.position.x < obj2.position.x + obj2.drawBox.width) {
            return true;
        }
    }
    return false;
}

template<typename T, typename F>
bool collisionTop(T &obj1, F &obj2) {
    if (obj1.position.y < obj2.position.y + obj2.drawBox.height && obj1.position.y + obj1.drawBox.height > obj2.position.y) {
        if (obj1.position.x + obj1.drawBox.width > obj2.position.x && obj1.position.x < obj2.position.x + obj2.drawBox.width) {
            return true;
        }
    }
    return false;
}

template<typename T, typename F>
bool collisionRight(T &obj1, F &obj2) {
    if (obj1.position.y + obj1.drawBox.height > obj2.position.y && obj1.position.y < obj2.position.y + obj2.drawBox.height) {
        if (obj1.position.x + obj1.drawBox.width > obj2.position.x && obj1.position.x < obj2.position.x + obj2.drawBox.width) {
            return true;
        }
    }
    return false;
}

template<typename T, typename F>
bool collisionLeft(T &obj1, F &obj2) {
    if (obj1.position.y + obj1.drawBox.height > obj2.position.y && obj1.position.y < obj2.position.y + obj2.drawBox.height) {
        if (obj1.position.x < obj2.position.x + obj2.drawBox.width && obj1.position.x + obj1.drawBox.width > obj2.position.x) {
            return true;
        }
    }
    return false;
}

// for wall collisions I wanted to detect them earlier to react in time
bool wallCollisionTop(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y < object.position.y + object.drawBox.height + 2 &&
        sprite.position.y + sprite.drawBox.height > object.position.y) {
        if (sprite.position.x + sprite.drawBox.width > object.position.x &&
            sprite.position.x < object.position.x + object.drawBox.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionBelow(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.drawBox.height + 2 > object.position.y &&
        sprite.position.y < object.position.y + object.drawBox.height) {
        if (sprite.position.x + sprite.drawBox.width > object.position.x &&
            sprite.position.x < object.position.x + object.drawBox.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionRight(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.drawBox.height > object.position.y &&
        sprite.position.y < object.position.y + object.drawBox.height) {
        if (sprite.position.x + sprite.drawBox.width + 2 > object.position.x &&
            sprite.position.x < object.position.x + object.drawBox.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionLeft(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.drawBox.height > object.position.y &&
        sprite.position.y < object.position.y + object.drawBox.height) {
        if (sprite.position.x < object.position.x + object.drawBox.width + 2 &&
            sprite.position.x + sprite.drawBox.width > object.position.x) {
            return true;
        }
    }
    return false;
}

bool wallCollisionDetection(Sprite &sprite, std::list<Wall> &walls) {
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

bool objectCollisionDetection(Sprite &sprite, std::list<LevelObjects> &objects) {
    for (auto &object : objects) {
        if (collisionBelow(sprite, object) || collisionTop(sprite, object) || collisionLeft(sprite, object) ||
            collisionRight(sprite, object)) {
            return true;
        }
    }
    return false;
}

bool spriteCollisionDetection(Sprite &sprite1, Sprite &sprite2) {
    if (collisionBelow(sprite1, sprite2) || collisionTop(sprite1, sprite2) || collisionLeft(sprite1, sprite2) ||
        collisionRight(sprite1, sprite2)) {
        return true;
    }

    return false;
}