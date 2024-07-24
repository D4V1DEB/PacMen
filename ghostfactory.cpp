#include "ghostfactory.h"
#include <stdexcept>

Ghost* GhostFactory::createGhost(const std::string& type, int ghostspeed)
{
    if (type == "Chaser") {
        return new Chaser(ghostspeed);
    } else if (type == "Patroller") {
        std::vector<Vector2f> patrolPoints = { Vector2f(100, 100), Vector2f(200, 100), Vector2f(200, 200), Vector2f(100, 200) };
        return new Patroller(ghostspeed, patrolPoints);
    } else if (type == "RandomWalker") {
        return new RandomWalker(ghostspeed);
    } else {
        throw std::invalid_argument("Unknown ghost type");
    }
}