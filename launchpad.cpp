#include "launchpad.h"
#include <FEHImages.h>
#include "window.h"
#include "rocket.h"


Launchpad::Launchpad(int x, int y){
    this->x = x;
    this->y = y;
}

Launchpad::Launchpad(){
    x = Window::w_width/2 - (width/4);
    y = Window::w_height - height;
}

void Launchpad::draw(){
    //width: 64 Height: 80
    int width = 64;
    int height = 80;
    // Declares an image for a Rocket
    FEHImage launchPad;
    // Open the image
    launchPad.Open("LaunchPadFEH.pic");
    // Draw a pad in the top left corner
    launchPad.Draw(x, y);
    // Close the image
    launchPad.Close();
}

void Launchpad::move(int dy){
    y += dy;
}

bool Launchpad::landed(int rocketX){
    int left = rocketX;
    int right = rocketX + Rocket::width;
    bool inBetween = false;
    if(rocketX > left && rocketX < right){
        inBetween = true;
    }
    return inBetween;
}