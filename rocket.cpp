#include "rocket.h"
#include <FEHImages.h>
#include "Window.h"

Rocket::Rocket(int x, int y){
    this->x = x;
    this->y = y;
    fuelLevel = 100.0;
}

Rocket::Rocket(){
    x = getInitialX();
    y = getInitialY();
    fuelLevel = 100.0;
}

int Rocket::getInitialX(){
    return Window::w_width/2-5;
}

int Rocket::getInitialY(){
    return Window::w_height-100;
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
    //makes sure fuel level does not go above 100 or below 0
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
    return altitude;
}

void Rocket::setAltitude(int background_y){
    //use the moving backgrounds position to output the rockets theoretical position
    //add the y of the rocket and subtract the hieght to get the bottom 
    altitude = background_y;
}

void Rocket::moveX(int dx){
    x += dx;
}

bool Rocket::reachedMaxHeight(int altitude){
    bool reached = false;
    //check if the rocket has reached a max altitude
    if(altitude > Rocket::max_altitude && altitude < Rocket::max_altitude + 200){
        reached = true;
    }
    return reached;
}

void Rocket::reset(){
    //sets rocket to initial values
    altitude = 0;
    y = getInitialY();
    x = getInitialX();
}