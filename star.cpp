#include "star.h"
#include <FEHImages.h>
#include "Rocket.h"

Star::Star(){
    setRandomPos();
}

void Star::draw(){
    //Width: 7 Height: 7
     // Declares an image for a star
    FEHImage star;
    // Open the image
    star.Open("StarFEH.pic");
    // Draw a fuel in the top left corner
    star.Draw(getX(), getY());
    // Close the image
    star.Close();
}

int Star::getWidth(){
    return width;
}

int Star::getHeight(){
    return height;
}