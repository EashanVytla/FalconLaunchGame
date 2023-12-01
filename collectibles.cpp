#include "collectibles.h"
#include "rocket.h"
#include <FEHRandom.h>
#include <iostream>
#include <math.h>

Collectibles::Collectibles(){
    generate_rate = 1;
}

int prev_time = 0;

void Collectibles::generate(float time, int altitude){
    //TODO: Make sure this is designed for when the rocket is going down 
    generate_rate = sqrt((1.0 - (float)altitude/Rocket::max_altitude) * 30.0);
    int every = 60 / generate_rate;

    //75% of the collectibles will be Fuel and 25% will be Stars
    //Completely random selection process
    int whichCol = Random.RandInt()/24575;

    std::cout << every << std::endl;

    if(time - prev_time > every){
        if(whichCol == 0){
            Fuel *fuelPtr = new Fuel();
            objects.push_back(fuelPtr);
        }else{
            Star *starPtr = new Star();
            objects.push_back(starPtr);
        }

        prev_time = time;
    }
}

void Collectibles::update(){
    int index = 0;
    for (Collectible* ptr : objects) {
        ptr->move(1);
        if(ptr->getY() < ptr->getHeight()){
            std::cout << "removing index " << index << std::endl;
            remove(index);
        }
        index++;
    }
}

void Collectibles::clean(){
    for (Collectible* ptr : objects) {
        delete ptr;
    }
}

void Collectibles::remove(int i){
    delete objects[i];
    objects.erase(objects.begin() + i);
}

void Collectibles::draw(){
    for (Collectible* ptr : objects) {
        ptr ->draw();
    }
}