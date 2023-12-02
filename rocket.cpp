#include "rocket.h"
#include <FEHImages.h>
#include "Window.h"

Rocket::Rocket(int x, int y){
    this->x = x;
    this->y = y;
    fuelLevel = 100.0;
}

Rocket::Rocket(){
    x = Window::w_width/2-5;
    y = Window::w_height-100;
    fuelLevel = 100.0;
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
double Rocket::getFuelLevel(){
    if(fuelLevel > 100){
        fuelLevel = 100;
    }

    if(fuelLevel < 0){
        fuelLevel = 0;
    }

    return fuelLevel;
}
void Rocket::setFuelLevel(double newFuel){
    fuelLevel = newFuel;
}


void Rocket::moveY(int dy){
    y -= dy;
}

int Rocket::getAltitude(){
    //use the moving backgrounds position to output the rockets theoretical position
    //add the y of the rocket and subtract the ieght to get the bottom 
    return altitude;
}

void Rocket::setAltitude(int alt){
    altitude = alt;
}

void Rocket::moveX(int dx){
    x += dx;
}

bool Rocket::reachedMaxHeight(int altitude){
    //check if the rocket has reached an altitude of 1000
    bool reached = false;
    if(altitude > Rocket::max_altitude && altitude < Rocket::max_altitude +200){
        reached = true;
    }
    return reached;
}

void Rocket::reset(){
    altitude = 0;
    y =Window::w_height-100;
    x = Window::w_width/2-5;
}