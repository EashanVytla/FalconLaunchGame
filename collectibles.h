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
        //Contructor
        Collectibles();
        /**This function checks if any collisions have occured or if the collectible has reached the end of the screen
         * the function takes a pointer to the rocket object as a parameter
         * The code was written by: Eashan
        **/
        void update(Rocket* rocket);

        /**This function generates a collectible at a random position based off game time and altitude
         * the function takes the game time and altitude as a paramter
         * The code was written by: Allen
        **/
        void generate(float time, int altitude);


        //Function inherited from collectible
        void draw();

        /**This function removes the object from the vector
         * the function takes an index as a parameter
         * The code was written by: Allen
        **/
        void remove(int i);
        /**This function removes all objects from the vector
         * the function takes no parameters and returns nothing
         * The code was written by: Eashan
        **/
        void clean();
};
#endif