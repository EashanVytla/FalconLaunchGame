#include "collectible.h"

class Fuel : public Collectible{
    private:
        const int width = 13;
        const int height = 13;
    public:
        Fuel();
        void draw();
        bool collision(int x, int y);
};