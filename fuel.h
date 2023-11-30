#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif

class Fuel : public Collectible{
    public:
        const int width = 13;
        const int height = 13;
        Fuel();
        void draw();
        bool collision(int x, int y);
        bool isAtBottom();
};