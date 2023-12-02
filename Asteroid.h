#ifndef ASTEROID_H
#define ASTEROID_H
#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif

class Asteroid : public Collectible{
    private:
        const int width = 15;
        const int height = 15;
    public:
        Asteroid();
        void draw();
        int getWidth();
        int getHeight();
};
#endif