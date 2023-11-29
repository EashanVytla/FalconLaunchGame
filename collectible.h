class Collectible{
    private:
        int x;
        int y;
    public:
        int getX();
        int getY();
        void setRandomPos();
        void setX(int x);
        void setY(int y);
        virtual void draw() = 0;
        virtual bool collision(int x, int y, int width, int height) = 0;
        void move(int dy);
};