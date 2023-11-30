// #include "collectibles.h"
// #include "rocket.h"

// Collectibles::Collectibles(){
//     generate_rate = 1;
// }

// void Collectibles::generate(float time, int altitude){
//     generate_rate = (1.0 - (float)altitude/Rocket::max_altitude) * 100.0;
//     int every = 60 / generate_rate;

//     if((int)time % every == 0){
//         objects.push_back()
//     }
// }

// void Collectibles::remove(int i){
//     delete objects[i];
//     objects.erase(objects.begin + i);
// }

// Collectibles::draw(){
//     for (const Collecibles* ptr : pointersVector) {
//         ptr->draw();
//     }
// }