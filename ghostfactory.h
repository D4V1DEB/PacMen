#pragma once
#include "ghost.h"
#include <vector>

class GhostFactory {
    public:
        static Ghost* createGhost(const std::string& type, int ghostspeed);
};