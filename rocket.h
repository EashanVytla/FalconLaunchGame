class Rocket{
    private:
        int x, y;
        int fuelLevel;
    public:
        static const int width = 13, height = 80;
        Rocket(int x, int y);
        Rocket();
        void draw();
        void moveY(int dy);
        void moveX(int dx);
        int getX();
        int getY();
        int getAltitude(int background_y);
};