#include "collectibles.h"
#include "rocket.h"
#include <memory>
#include <FEHRandom.h>
#include <stdio.h>

Collectibles::Collectibles(){
    generate_rate = 1;
}

void Collectibles::generate(float time, int altitude){
    generate_rate = (1.0 - (float)altitude/Rocket::max_altitude) * 100.0;
    int every = 60 / generate_rate;

    //75% of the collectibles will be Fuel and 25% will be Stars
    //Completely random selection process
    int whichCol = Random.RandInt()/24575;

    if((int)time % every == 0){
        std::cout << "Creating new collectible..." << std::endl; 
        if(whichCol == 0){
            objects.push_back(std::make_unique<Fuel>());
            std::cout << "Created new Fuel!" << std::endl; 
        }else{
            objects.push_back(std::make_unique<Star>());
            std::cout << "Created new Fuel!" << std::endl; 
        }
    }
}

void Collectibles::update(){
    int index = 0;
    for (const std::unique_ptr<Collectible>& ptr : objects) {
        ptr->move(1);
        if(ptr->getY() < ptr->getWidth()){
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