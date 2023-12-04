#include <FEHImages.h>
#include "fuel.h"
#include "Rocket.h"

Fuel::Fuel(){
    setRandomPos();
}

void Fuel::draw(){
    //Rocket Fuel: https://www.cleanpng.com/png-clip-art-fuel-computer-icons-vector-graphics-porta-6594439/download-png.html
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

int Fuel::getWidth(){
    return width;
}

int Fuel::getHeight(){
    return height;
}
