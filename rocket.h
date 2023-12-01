#ifndef ROCKET_H
#define ROCKET_H
class Rocket{
    private:
        int x, y;
        int fuelLevel;
        int altitude;
    public:
        static const int width = 13, height = 80, max_altitude = 2000, buffer_altitude = max_altitude - 200;
        static constexpr float max_up_speed = 7.0f, max_down_speed = 2.5f;
        
        Rocket(int x, int y);
        Rocket();
        void draw();
        void moveY(int dy);
        void moveX(int dx);
        int getX();
        int getY();
        bool reachedMaxHeight(int altitude);
        void setAltitude(int background_y);
        int getAltitude();
};
#endif