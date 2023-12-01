#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H
#include <vector>
#include "star.h"
#include "fuel.h"
#include "Collectible.h"
#include "rocket.h"

class Collectibles{
    private:
        std::vector<Collectible*> objects;
        int generate_rate; //Collectibles generated per second

    public:
        Collectibles();
        void update();
        void generate(int altitude);
        void draw();
        void remove(int i);
        void clean();
        bool checkCollectibleCollision(Rocket rocket);
};
#endif