#include "CollisionDetection.h"


bool wallCollisionBelow(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height + 2 > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionBelow(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionBelow(Sprite &sprite, Sprite &sprite2) {
    if (sprite.position.y + sprite.height > sprite2.position.y && sprite.position.y < sprite2.position.y + sprite2.height) {
        if (sprite.position.x + sprite.width > sprite2.position.x && sprite.position.x < sprite2.position.x + sprite2.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionTop(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y < object.position.y + object.height + 2 && sprite.position.y + sprite.height > object.position.y) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionTop(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y < object.position.y + object.height && sprite.position.y + sprite.height > object.position.y) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionTop(Sprite &sprite, Sprite &sprite2) {
    if (sprite.position.y < sprite2.position.y + sprite2.height && sprite.position.y + sprite.height > sprite2.position.y) {
        if (sprite.position.x + sprite.width > sprite2.position.x && sprite.position.x < sprite2.position.x + sprite2.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionRight(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x + sprite.width + 2 > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionRight(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x + sprite.width > object.position.x && sprite.position.x < object.position.x + object.width) {
            return true;
        }
    }
    return false;
}

bool collisionRight(Sprite &sprite, Sprite &sprite2) {
    if (sprite.position.y + sprite.height > sprite2.position.y && sprite.position.y < sprite2.position.y + sprite2.height) {
        if (sprite.position.x + sprite.width > sprite2.position.x && sprite.position.x < sprite2.position.x + sprite2.width) {
            return true;
        }
    }
    return false;
}

bool wallCollisionLeft(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x < object.position.x + object.width + 2 && sprite.position.x + sprite.width > object.position.x) {
            return true;
        }
    }
    return false;
}

bool collisionLeft(Sprite &sprite, LevelObjects &object) {
    if (sprite.position.y + sprite.height > object.position.y && sprite.position.y < object.position.y + object.height) {
        if (sprite.position.x < object.position.x + object.width && sprite.position.x + sprite.width > object.position.x) {
            return true;
        }
    }
    return false;
}

bool collisionLeft(Sprite &sprite, Sprite &sprite2) {
    if (sprite.position.y + sprite.height > sprite2.position.y && sprite.position.y < sprite2.position.y + sprite2.height) {
        if (sprite.position.x < sprite2.position.x + sprite2.width && sprite.position.x + sprite.width > sprite2.position.x) {
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
                sprite.position.y = wall.position.y - sprite.height;
            }
            sprite.grounded = true;
            sprite.velocity_y = 0;
            collision = true;
        }

        if (wallCollisionTop(sprite, wall)) {
            sprite.position.y = wall.position.y + wall.height + 2;
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

bool spriteCollisionDetection(Sprite &sprite, Sprite& sprite2) {
    if (collisionBelow(sprite, sprite2) || collisionTop(sprite, sprite2) || collisionLeft(sprite, sprite2) ||
        collisionRight(sprite, sprite2)) {
        return true;
    }
    return false;
}