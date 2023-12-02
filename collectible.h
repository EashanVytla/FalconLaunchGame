#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H
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
        bool collision(int x, int y);
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        void move(int dy);
};
#endif