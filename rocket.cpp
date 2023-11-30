#include "rocket.h"
#include <FEHImages.h>
#include "Window.h"

Rocket::Rocket(int x, int y){
    this->x = x;
    this->y = y;
    fuelLevel = 100;
}

Rocket::Rocket(){
    x = Window::w_width/2-5;
    y = Window::w_height-100;
    fuelLevel = 100;
}

void Rocket::draw(){
     // Declares an image for a Rocket
    FEHImage Rocket;
    // Open the image
    Rocket.Open("RocketFEH.pic");
    // Draw a Rocket in the top left corner
    Rocket.Draw(x, y);
    // Close the image
    Rocket.Close();
}

int Rocket::getX(){
    return x;
}

int Rocket::getY(){
    return y;
}

void Rocket::moveY(int dy){
    y -= dy;
}

void Rocket::moveX(int dx){
    x += dx;
}