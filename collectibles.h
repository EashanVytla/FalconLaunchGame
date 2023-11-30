#include <vector>
#include "star.h"
#include "fuel.h"
#include "Collectible.h"

class Collectibles{
    private:
        std::vector<Collectible*> objects;
        int generate_rate; //Collectibles generated per second

    public:
        Collectibles();
        void generate(float time, int altitude);
        void draw();
        void remove(int i);
        bool checkCollectibleCollision(Rocket rocket);
};