#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H
class Collectible{
    private:
        int x;
        int y;
    public:

        /**This function returns the x value of the collectible
        **/
        int getX();

        /**This function returns the y value of the collectible
        **/
        int getY();

        /**Sets the position of the collectible to a random number
        **/
        void setRandomPos();

        /**Sets the x position of the collectible
        **/
        void setX(int x);

        /**Sets the y position of the collectible
        **/
        void setY(int y);

        /**draws the collectible to the screen
         * The function is virtual void so it can be overrided by extending classes
         * The code was written by: Eashan
        **/
        virtual void draw() = 0;

        /**checks if the collectible has collided with anything
         * The returns a boolean and intput an x and y postion as parameters
         * The code was written by: Allen
        **/
        bool collision(int x, int y);

        /**This function returns the width of the collectible
         * The function is virtual void so it can be overrided by extending classes
        **/
        virtual int getWidth() = 0;

        /**This function returns the height of the collectible
         * The function is virtual void so it can be overrided by extending classes
        **/
        virtual int getHeight() = 0;

        /**This function moves the collectible based off the change in Y as the parameter
         * The function takes a change in y as the paramter
        **/
        void move(int dy);
};
#endif