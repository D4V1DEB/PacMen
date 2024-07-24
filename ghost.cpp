#include "ghost.h"
#include <cstdlib>

Chaser::Chaser(int ghostspeed) {
    speed = ghostspeed;
}

void Chaser::move(Sprite& player) {
    // ---
    Vector2f playerPos = player.getPosition();
    Vector2f ghostPos = sprite.getPosition();
    Vector2f direction = playerPos - ghostPos;
    if (abs(direction.x) > abs(direction.y)) {
        direction.y = 0;
    } else {
        direction.x = 0;
    }
    sprite.move(speed * direction.x / abs(direction.x), speed * direction.y / abs(direction.y));
}

Patroller::Patroller(int ghostspeed, std::vector<Vector2f> points) : patrolPoints(points), currentPoint(0) {
    speed = ghostspeed;
}

void Patroller::move(Sprite& player) {
    // ------
    Vector2f target = patrolPoints[currentPoint];
    Vector2f ghostPos = sprite.getPosition();
    Vector2f direction = target - ghostPos;
    if (abs(direction.x) > abs(direction.y)) {
        direction.y = 0;
    } else {
        direction.x = 0;
    }
    sprite.move(speed * direction.x / abs(direction.x), speed * direction.y / abs(direction.y));
    if (abs(direction.x) <= speed && abs(direction.y) <= speed) {
        currentPoint = (currentPoint + 1) % patrolPoints.size();
    }
}

RandomWalker::RandomWalker(int ghostspeed) {
    speed = ghostspeed;
}

void RandomWalker::move(Sprite& player) {
    // --------------
    int direction = rand() % 4;
    switch (direction) {
    case 0: sprite.move(speed, 0); break; // Move right
    case 1: sprite.move(-speed, 0); break; // Move left
    case 2: sprite.move(0, speed); break; // Move down
    case 3: sprite.move(0, -speed); break; // Move up
    }
}
