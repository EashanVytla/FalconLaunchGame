class Launchpad{
    private:
        int x, y;
        const int width = 64;
        const int height = 80;
    public:
        Launchpad(int x, int y);
        Launchpad();

        /// @brief draws the fuel using the .pic and the draw function from collectible
        /// The code was written by: Allen
        void draw();
        /// @brief moves the launch pad based off the inpute
        /// @param dy the interval to change the y at
        /// Written by Eashan
        void move(int dy);

        /// @brief Checks if the rocket has landed on the launchpad
        /// @param rocketX the x pos of the rocket
        /// @return returns a boolean if the rocket landed or not
        /// Written by Allen
        bool landed(int rocketX);
};