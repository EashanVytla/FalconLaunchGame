#ifndef ROCKET_H
#define ROCKET_H
#include "window.h"
class Rocket{
    private:
        int x, y;
        int fuelLevel;
        int altitude;
        const int initialY = Window::w_width/2-5;
        //const int initialX = Window::w_height-100;
    public:
        static const int width = 13, height = 80, max_altitude = 2000, buffer_altitude = max_altitude - 200;
        static const float max_up_speed = 7, max_down_speed = 2.5;
        
        Rocket(int x, int y);
        Rocket();
        void draw();
        void moveY(int dy);
        void moveX(int dx);
        int getX();
        int getY();
        bool reachedMaxHeight(int altitude);
        void setAltitude(int background_y);
        void reset();
        int getAltitude();
};
#endif