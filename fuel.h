#ifndef FUEL_H
#define FUEL_H
#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif

class Fuel : public Collectible{
    private:
        const int width = 13;
        const int height = 13;
    public:
        Fuel();
        void draw();
        bool collision(int x, int y);
        int getWidth();
        int getHeight();
};
#endif