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
    /**This function draws the asteroid on the screen
     * the function takes no parameters and returns nothing
    **/
        void draw();

        /**This returns the width of the asteroid
        **/
        int getWidth();
        /**This returns the height of the asteroid
        **/
        int getHeight();
};
#endif