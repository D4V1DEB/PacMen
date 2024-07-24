#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Ghost {
    public:
        virtual void move(Sprite& player) = 0;
        Sprite sprite;
    protected:
        int speed;
};

class Chaser : public Ghost {
    public:
        Chaser(int ghostspeed);
        void move(Sprite& player) override;
};

class Patroller : public Ghost {
    public:
        Patroller(int ghostspeed, std::vector<Vector2f> patrolPoints);
        void move(Sprite& player) override;
    private:
        std::vector<Vector2f> patrolPoints;
        size_t currentPoint;
};

class RandomWalker : public Ghost {
    public:
        RandomWalker(int ghostspeed);
        void move(Sprite& player) override;
};
