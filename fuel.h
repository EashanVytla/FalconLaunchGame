#ifndef FUEL_H
#define FUEL_H
#ifndef COLLECTIBLE_H
#include "collectible.h"
#endif

class Fuel : public Collectible{
    public:
        static const int width = 13;
        static const int height = 13;
        Fuel();
        /**This function draws the fuel using the .pic and the draw function from collectible
         * the function returns nothing
         * The code was written by: Allen
        **/
        void draw();
        //inherited from collectible
        int getWidth();
        int getHeight();
};
#endif