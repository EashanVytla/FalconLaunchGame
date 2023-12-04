#ifndef ROCKET_H
#define ROCKET_H
#include "window.h"
class Rocket{
    private:
        int x, y;
        double fuelLevel;
        int altitude;
    public:
        static const int width = 13, height = 80, max_altitude = 2000, buffer_altitude = max_altitude - 200;
        static const int max_up_speed = 15, max_down_speed = 5;
        //constructors
        Rocket(int x, int y);
        Rocket();

        /// @brief Draws therocket using the collectible draw function and the .pic file of the rocket
        //  written by: Allen
        void draw();

        /// @brief moved the rocket y value based off the parameter
        /// @param dy the interval at which to change the Y of the rocket
        //  Written by: Eashan
        void moveY(int dy);

        /// @brief moved the rocket x value based off the parameter
        /// @param dx the interval at which to change the X of the rocket
        //  Written by: Allen
        void moveX(int dx);
        
        /// @brief The function gets the x value of the rocket
        /// @return the x value of the rocket
        //  Written by: Eashan
        int getX();

        /// @brief The function gets the y value of the rocket
        /// @return the y value of the rocket
        //  Written by: Allen
        int getY();

        /// @brief get the starting x of the rocket
        /// @return returns the intial x of the rocket
        //  Written by Eashan
        int getInitialX();

        /// @brief get the starting Y of the rocket
        /// @return returns the intial Y of the rocket
        //Written by Allen
        int getInitialY();

        /// @brief checks if the rocket has reached the max height allowed
        /// @param altitude The altitude of the rocket
        /// @return  a boolean if the rocket has reached the max height 
        //  Written by Allen
        bool reachedMaxHeight(int altitude);
        
        /// @brief sets the altitude to a new value
        /// @param  any the new altitude
        //  Written by Eashan
        void setAltitude(int);

        /// @brief Resets the rocket to the intial location and values
        //  Written by Allen
        void reset();

        /// @brief gets the current fuel level of the rocket
        /// @return the fuel level
        //  Written by Eashan
        double getFuelLevel();
        /// @brief sets the fuel level to a new amount
        /// @param newFuel the new level the fuel is set to
        //  Written by Eashan
        void setFuelLevel(double newFuel);

        /// @brief Gets the current altitude of the rocket
        /// @return the altitude
        //  Written by Allen
        int getAltitude();
};
#endif
