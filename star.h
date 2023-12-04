#ifndef STAR_H
#define STAR_H
#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif
//Ask Dr. Tony if we are allowed to use inheritance since we didn't learn in class
//Ask Dr. Tony if we are allowed to use vectors since we didn't learn in class
//Ask Dr. Tony if we are allowed to have the .cpp and .h framework since we didn't learn in class

class Star : public Collectible{
    public:
        static const int width = 7;
        static const int height = 7;
        Star();

        /// @brief Draws the star using the collectible draw function and the .pic file of the rocket
        //  written by: Allen
        void draw();

        //inherited functions from collectible
        int getWidth();
        int getHeight();
};
#endif