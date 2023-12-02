#include "collectibles.h"
#include "rocket.h"
#include <FEHRandom.h>
#include "Asteroid.h"
#include <iostream>
#include <math.h>

Collectibles::Collectibles(){
    generate_rate = 40;
}

int prev_time = 0;

void Collectibles::generate(float time, int altitude){
    //TODO: Make sure this is designed for when the rocket is going down 
    //generate_rate = sqrt((1.0 - (float)altitude/Rocket::max_altitude) * 30.0);
    int every = 60 / generate_rate;

    //37% of the collectibles will be Fuel, 25% will be Stars, 37% will be asteroids
    //Completely random selection process
    int whichCol = Random.RandInt()/4095;

    std::cout << "Time" << time << std::endl; 
    if(time - prev_time > every){
        std::cout << "Time: " << time << std::endl;
        if(whichCol <= 2){
            Fuel *fuelPtr = new Fuel();
            objects.push_back(fuelPtr);
        }else if(whichCol <= 5){
            Asteroid *astPtr = new Asteroid();
            objects.push_back(astPtr);
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
            }else if(ptr->getHeight() == Fuel::height){
                rocket->setFuelLevel(rocket->getFuelLevel() + 10);
            }else{
                rocket->setFuelLevel(rocket->getFuelLevel() - 20);
            }
            remove(index);
            collision = true;
        }else if(ptr->getY() < ptr->getHeight()){
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
    prev_time = 0;
    while(objects.size() != 0) {
        remove(0);
    }
}

void Collectibles::remove(int i){
    if (i < 0 || i > objects.size())
        return;
    delete objects[i];
    objects.erase(objects.begin() + i);
}

void Collectibles::draw(){
    for (Collectible* ptr : objects) {
        ptr->draw();
    }
}