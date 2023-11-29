#include "star.h"
#include <FEHImages.h>

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

bool Star::collision(int x, int y, int width, int height){
    //Allen implement code here
    return true;
}