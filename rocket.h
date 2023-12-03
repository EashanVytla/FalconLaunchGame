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
        Rocket(int x, int y);
        Rocket();
        void draw();
        void moveY(int dy);
        void moveX(int dx);
        int getX();
        int getY();
        int getInitialX();
        int getInitialY();
        bool reachedMaxHeight(int altitude);
        void setAltitude(int);
        void reset();
        double getFuelLevel();
        void setFuelLevel(double newFuel);
        int getAltitude();
};
#endif
