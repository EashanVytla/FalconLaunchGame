class Rocket{
    private:
        int x, y;
        int fuelLevel;
    public:
        static const int width = 13, height = 80;
        static const int max_altitude = 500, buffer_altitude = 300;
        static const float max_up_speed = 2, max_down_speed = 2;
        
        Rocket(int x, int y);
        Rocket();
        void draw();
        void moveY(int dy);
        void moveX(int dx);
        int getX();
        int getY();
        int getAltitude(int background_y);
        bool reachedMaxHeight(int altitude);
};