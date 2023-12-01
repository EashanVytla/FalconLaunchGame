#include "collectibles.h"
#include "rocket.h"
#include <FEHRandom.h>
#include <iostream>
#include <math.h>

Collectibles::Collectibles(){
    generate_rate = 30;
}

int prev_time = 0;

void Collectibles::generate(float time, int altitude){
    //TODO: Make sure this is designed for when the rocket is going down 
    //generate_rate = sqrt((1.0 - (float)altitude/Rocket::max_altitude) * 30.0);
    int every = 60 / generate_rate;

    //75% of the collectibles will be Fuel and 25% will be Stars
    //Completely random selection process
    int whichCol = Random.RandInt()/24575;

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

void Collectibles::update(Rocket* rocket){
    int index = 0;

    while(index < objects.size()) {
        bool collision = false;
        Collectible* ptr = objects[index];
        ptr->move(2);

        if(ptr->collision(rocket->getX(), rocket->getY())){
            std::cout << "Collision: removing index " << index << std::endl;
            if(ptr->getHeight() == Star::height){
                rocket->setFuelLevel(rocket->getFuelLevel() + 20);
            }else{
                rocket->setFuelLevel(rocket->getFuelLevel() + 10);
            }
            remove(index);
            collision = true;
        }

        if(ptr->getY() < ptr->getHeight()){
            std::cout << "Reached EOS: removing index " << index << std::endl;
            std::cout << "Object Y: " << ptr->getY() << std::endl;
            std::cout << "Vector Size: " << objects.size() << std::endl;
            remove(index);
            collision = true;
        }
        
        if(!collision){
            index++;
        }
    }
}

void Collectibles::clean(){
    for (Collectible* ptr : objects) {
        delete ptr;
    }
}

void Collectibles::remove(int i){
    if (i <= 0 || i > objects.size())
        return;
    delete objects[i];
    objects.erase(objects.begin() + i);
}

void Collectibles::draw(){
    for (Collectible* ptr : objects) {
        ptr->draw();
    }
}