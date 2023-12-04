#include "collectibles.h"
#include "rocket.h"
#include <FEHRandom.h>
#include "Asteroid.h"
#include <iostream>
#include <math.h>

//constructor for collectibles
Collectibles::Collectibles(){
    generate_rate = 40;
}

int prev_time = 0;

void Collectibles::generate(float time, int altitude){ 
    //generate_rate = sqrt((1.0 - (float)altitude/Rocket::max_altitude) * 30.0);
    int every = 60 / generate_rate;

    //37% of the collectibles will be Fuel, 25% will be Stars, 37% will be asteroids
    //Completely random selection process

    int whichCol = Random.RandInt()/4095;
    //if the elapsed time is greater than the rate
    if(time - prev_time > every){
        if(whichCol <= 2){
            //of col less than 2 then create a fuel
            Fuel *fuelPtr = new Fuel();
            objects.push_back(fuelPtr);
        }else if(whichCol <= 5){
            //if col is less than 5 create asteroid
            Asteroid *astPtr = new Asteroid();
            objects.push_back(astPtr);
        }else{
            //creaate a star otherwise
            Star *starPtr = new Star();
            objects.push_back(starPtr);
        }
        //update time
        prev_time = time;

    }
}

void Collectibles::update(Rocket* rocket){
    int index = 0;
    //while there are objects in the vector
    while(index < objects.size()) {
        //initialize collision as false
        bool collision = false;
        //pointer to a objects vector
        Collectible* ptr = objects[index];
        //move the object 2 pixels
        ptr->move(2);
        //if the objext has collided with the rocket
        if(ptr->collision(rocket->getX(), rocket->getY())){
            std::cout << "Collision: removing index " << index << std::endl;
            //if the object is a star
            if(ptr->getHeight() == Star::height){
                //add 20 the the fuel
                rocket->setFuelLevel(rocket->getFuelLevel() + 20);
            //if object is fuel
            }else if(ptr->getHeight() == Fuel::height){
                //add 10 to the fuel
                rocket->setFuelLevel(rocket->getFuelLevel() + 10);
            //if object is an asteroid
            }else{
                //subtract 20 from the fuel
                rocket->setFuelLevel(rocket->getFuelLevel() - 20);
            }
            //remove the object from the vector
            remove(index);
            //set collision to true;
            collision = true;
        //If collectible didnt collide and reached the end of the screen
        }else if(ptr->getY() < ptr->getHeight()){
            std::cout << "Reached EOS: removing index " << index << std::endl;
            std::cout << "Object Y: " << ptr->getY() << std::endl;
            std::cout << "Vector Size: " << objects.size() << std::endl;
            //remove object from the screen by removing from the vector
            remove(index);
            collision = true;
        }
        //the object hasnt collided move on to next
        if(!collision){
            index++;
        }
    }
}

void Collectibles::clean(){
    std::cout << "Cleaning up all collectibles" << std::endl;
    prev_time = 0;
    //while the vector is not empty
    while(objects.size() != 0) {
        std::cout << "POP" << std::endl;
        //remove the first object
        remove(0);
    }
    std::cout << "Collectibles size: " << objects.size() << std::endl;
}

void Collectibles::remove(int i){
    //if the index is not viable then exit
    if (i < 0 || i > objects.size())
        return;
    //delete the collectible at the index
    delete objects[i];
    objects.erase(objects.begin() + i);
}

void Collectibles::draw(){
    for (Collectible* ptr : objects) {
        ptr->draw();
    }
}