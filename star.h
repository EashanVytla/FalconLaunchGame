#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif
//Ask Dr. Tony if we are allowed to use inheritance since we didn't learn in class
//Ask Dr. Tony if we are allowed to use vectors since we didn't learn in class
//Ask Dr. Tony if we are allowed to have the .cpp and .h framework since we didn't learn in class

class Star : public Collectible{
    public:
        const int width = 7;
        const int height = 7;
        Star();
        void draw();
        bool collision(int x, int y);
        bool isAtBottom();
};
