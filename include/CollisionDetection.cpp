#include "CollisionDetection.h"


bool collisionBelow(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height + 2 > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionTop(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y < object.position.y + object.height + 2 && sprite.position.y + sprite.height > object.position.y) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionRight(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x + sprite.width + 2 > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionLeft(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x < object.position.x + object.width + 2 && sprite.position.x + sprite.width > object.position.x) {
            return true;
        }
    }
    return false;
}

bool wallCollisionDetection(Sprite &sprite, std::list<Wall> &walls) {
    bool collision = false;
    for (auto &wall : walls) {
        if (collisionRight(sprite, wall)) {
            sprite.position.x -= 1;
            sprite.velocity_x = 0;
            collision = true;
        }

        if (collisionLeft(sprite, wall)) {
            sprite.position.x += 1;
            sprite.velocity_x = 0;
            collision = true;
        }

        if (collisionBelow(sprite, wall)) {
            if (sprite.position.y + 10 < wall.position.y) {
                sprite.position.y = wall.position.y - sprite.height;
            }
            sprite.grounded = true;
            sprite.velocity_y = 0;
            collision = true;
        }

        if (collisionTop(sprite, wall)) {
            sprite.position.y = wall.position.y + wall.height + 2;
            sprite.velocity_y = 0;
            collision = true;
        }
    }

    return collision;
}

bool otherCollisionDetection(Sprite &sprite, std::list<LevelObjects> &objects) {
    for (auto &object : objects) {
        if (collisionBelow(sprite, object) || collisionTop(sprite, object) || collisionLeft(sprite, object) || collisionRight(sprite, object)) {
            return true;
        }
    }
    return false;
}