#include <FEHImages.h>
#include "fuel.h"

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

bool Fuel::collision(int x, int y, int width, int height){
    //Allen implement the code for this
    return true;
}