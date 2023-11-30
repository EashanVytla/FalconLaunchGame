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
        virtual bool collision(int x, int y) = 0;
        virtual int getWidth();
        virtual int getHeight();
        void move(int dy);
};
#endif