class Rocket{
    private:
        int x, y;
        int fuelLevel;
    public:
        const int width = 13, height = 80;
        Rocket(int x, int y);
        Rocket();
        void draw();
        void move(int dy);
};