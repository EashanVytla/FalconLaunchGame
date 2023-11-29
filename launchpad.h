class Launchpad{
    private:
        int x, y;
        const int width = 64;
        const int height = 80;
    public:
        Launchpad(int x, int y);
        Launchpad();
        void draw();
        void move(int dy);
};