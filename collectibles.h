#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H
#include <vector>
#include "star.h"
#include "fuel.h"
#include "Collectible.h"
#include "rocket.h"
#include <memory>

class Collectibles{
    private:
        std::vector<std::unique_ptr<Collectible>> objects;
        int generate_rate; //Collectibles generated per second

    public:
        Collectibles();
        void update();
        void generate(float time, int altitude);
        void draw();
        void remove(int i);
        bool checkCollectibleCollision(Rocket rocket);
};
#endif