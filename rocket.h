#ifndef ROCKET_H
#define ROCKET_H
class Rocket{
    private:
        int x, y;
        int fuelLevel;
        int altitude;
    public:
        static const int width = 13, height = 80, max_altitude = 500;
        Rocket(int x, int y);
        Rocket();
        void draw();
        void moveY(int dy);
        void moveX(int dx);
        int getX();
        int getY();
        void setAltitude(int background_y);
        int getAltitude();
};
#endif