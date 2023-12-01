#include "collectible.h"
#include <FEHRandom.h>
#include "window.h"

int Collectible::getX(){
    return x;
}

int Collectible::getY(){
    return y;
}

void Collectible::setRandomPos(){
    x = Random.RandInt()/100;
    y = Window::w_height - getHeight();
}

void Collectible::setX(int x){
    this->x = x;
}

void Collectible::setY(int y){
    this->y = y;
}

void Collectible::move(int dy){
    y += dy;
}