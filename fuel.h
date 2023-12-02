#ifndef FUEL_H
#define FUEL_H
#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif

class Fuel : public Collectible{
    public:
        const int width = 13;
        const int height = 13;
        Fuel();
        void draw();
        int getWidth();
        int getHeight();
};
#endif