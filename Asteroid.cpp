#include <FEHImages.h>
#include "Asteroid.h"
#include "Rocket.h"
//constructor for astroid
Asteroid::Asteroid(){
    setRandomPos();
}

void Asteroid::draw(){
    //Width: 13 Height: 13
     // Declares an image for a fuel
    FEHImage asteroid;
    // Open the image
    asteroid.Open("AsteroidFEH.pic");
    // Draw a fuel in the top left corner
    asteroid.Draw(getX(), getY());
    // Close the image
    asteroid.Close();
}

int Asteroid::getWidth(){
    return width;
}

int Asteroid::getHeight(){
    return height;
}