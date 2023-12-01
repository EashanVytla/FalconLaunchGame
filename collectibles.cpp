#include "collectibles.h"
#include "rocket.h"
#include <memory>
#include <FEHRandom.h>
#include <iostream>
#include <math.h>
#include "star.h"
#include "fuel.h"

Collectibles::Collectibles(){
    generate_rate = 1;
}

int prev_time = 0;

void Collectibles::generate(float time, int altitude){
    //TODO: Make sure this is designed for when the rocket is going down NOT UP
    generate_rate = sqrt((1.0 - (float)altitude/Rocket::max_altitude) * 30.0);
    int every = 60 / generate_rate;
    //75% of the collectibles will be Fuel and 25% will be Stars
    //Completely random selection process
    int whichCol = Random.RandInt()/24575;

    std::cout << every << std::endl;

    if(time - prev_time > every){
        if(whichCol == 0){
            objects.push_back(std::make_unique<Fuel>());
        }else{
            objects.push_back(std::make_unique<Star>());
        }

        prev_time = time;
    }
}

void Collectibles::update(){
    int index = 0;
    for (const std::unique_ptr<Collectible>& ptr : objects) {
        ptr->move(1);
        if(ptr->getY() < ptr->getHeight()){
            std::cout << "removing index " << index << std::endl;
            remove(index);
        }
        index++;
    }
}

void Collectibles::remove(int i){
    objects.erase(objects.begin() + i);
}

void Collectibles::draw(){
    for (const std::unique_ptr<Collectible>& ptr : objects) {
        ptr->draw();
    }
}