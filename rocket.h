class Rocket{
    private:
        int x, y;
        int fuelLevel;
    public:
        static const int width = 13, height = 80;
        Rocket(int x, int y);
        Rocket();
        void draw();
        void move(int dy);
        int getX();
        int getY();
        int getAltitude(int background_y);
};