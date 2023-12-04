#include "collectible.h"
#include <FEHRandom.h>
#include "window.h"
#include "rocket.h"
#include <iostream>

int Collectible::getX(){
    return x;
}

int Collectible::getY(){
    return y;
}

void Collectible::setRandomPos(){
    //get a random x value using RandInt
    x = Random.RandInt()/100;
    //set Y to window height minus collectible height
    y = Window::w_height - getHeight();
}

void Collectible::setX(int x){
    this->x = x;
}

void Collectible::setY(int y){
    this->y = y;
}

void Collectible::move(int dy){
    //move the y by subtracting dy from it
    y -= dy;
}

bool Collectible::collision(int x, int y){
    //intitialize a bool if the collectible has collided
    bool collided = false;
    //if the pos is in between between the x and y of the collectible
    if (getX() + getWidth() > x && getX() < x + Rocket::width &&
        getY() + getHeight() > y && getY() < y + Rocket::height) {
        //set collision to be true
        collided = true;
        std::cout << "Collided" << std::endl;
    }
    return collided;
}