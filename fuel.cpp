#include <FEHImages.h>
#include "fuel.h"
#include "Rocket.h"
void Fuel::draw(){
    //Width: 13 Height: 13
     // Declares an image for a fuel
    FEHImage fuel;
    // Open the image
    fuel.Open("FuelFEH.pic");
    // Draw a fuel in the top left corner
    fuel.Draw(getX(), getY());
    // Close the image
    fuel.Close();
}

bool Fuel::collision(int x, int y){
    bool collided = false;
    if (getX() + width > x && getX() < x + Rocket::width &&
        getY() + height > y && getY() < y + Rocket::height) {
        collided = true;
    }
    return collided;
}