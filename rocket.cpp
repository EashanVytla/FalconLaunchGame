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

int Rocket::getAltitude(){
    //use the moving backgrounds position to output the rockets theoretical position
    //add the y of the rocket and subtract the ieght to get the bottom 
    return altitude;
}

void Rocket::setAltitude(int background_y){
    altitude = background_y + y - height;
}

void Rocket::moveX(int dx){
    x += dx;
}