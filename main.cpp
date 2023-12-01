#include "FEHLCD.h"
#include <FEHImages.h>
#include "rocket.h"
#include "window.h"
#include "launchpad.h"
#include "star.h"
#include <iostream>
#include "fuel.h"
#include <vector>
#include <csignal>
#include "Collectibles.h"
#include <FEHUtility.h>

//Function prototypes
//Displays the menu
void displayMenu();
//Displays leaderboard from SD card
void displayLeaderBoard();
//Displays the developer names
void displayCredits();
//Displays the instructions of the game
void displayInstructions();
//Draws background
void drawBackground();
//move background pixel
void moveBackgroundUp(int alt);
//move background pixel
void moveBackgroundDown(int alt);
//draw fuel level bar
void drawProgressBar(double barWidth);

void gameUpdate();

void handleSigInt(int signum);

//background x and y
float background_x = 0;
float background_y = 0;

//Returns true if a button is clicked and sets x and y variables to the position of the click
//Ignores a button hold! If the button is held only the first loop cycle is counted
bool detectButtonClick(int *x, int *y);

//Storing the middle of the menu as constants
const int menu_x_split = 155;
const int menu_y_split = 115;

//Storing the back to menu button position as constants
const int back_menu_x = 229;
const int back_menu_y = 219;

//Initializing the previous touch boolean to false
bool prev_touch = false;

//Progess bar width/ Fuel level
double fuelLevel = 100;

//Initializing a temporary placeholder for the leaderboard
//In the final version this would be read from a file
char leaderboard[10][21] = {"Eashan - 10%", "Allen - 9%", "Joe - 8%", "Stephanie - 7%", "Aidan - 6%", "Josh - 5%", "Marvin - 4%", "Charlie - 3%", "Gavin - 2%", "Sid - 1%"};

// if the Rocket is on the way down
bool landing = false;

//0 - Game
//1 - Leaderboard
//2 - Credit
//3 - Instructions
//4 - Menu
//5 - IDLE Game
int game_state = 4;
//Global variable to handle when the SIGINT is recieved.
//This is volatile to be accessed accross threads.
volatile bool sigintReceived = false;

int main()
{
    //Registering SIGINT handler for proper destruction of our collectible pointers
    std::signal(SIGINT, handleSigInt);

    //Initializing the x and y position of the screen press to 0
    int press_x = 0;
    int press_y = 0;

    //Initialize drag x and y to calculate the user mouse drag
    int drag_x = 0;
    int drag_y = 0;

    //Initialize prev x and y to calculate the user mouse drag
    int drag_prev_x = 0;
    int drag_prev_y = 0;

    Rocket rocket;
    Launchpad launchpad;
    Collectibles collectibles;

    //make the menue from function
    displayMenu();

    float initialTime = 0;

    while (!sigintReceived) {
        //Keeping track of user click and position of the click
        bool button_press = detectButtonClick(&press_x, &press_y);

        if(LCD.Touch(&drag_x, &drag_y)){
            rocket.moveX(drag_x - drag_prev_x);
        }

        //If the user clicked the screen (Only first loop cycle of click is counted)
        if(button_press){
            LCD.Clear();
            //If the menu state is menu, go to the selected state
            if(game_state == 4){
                if(press_x < menu_x_split){
                    if(press_y < menu_y_split){
                        //If Play Game is pressed
                        //TODO: After merging with Allen's branch make sure this is associated with the game_state = 0;

                        initialTime = TimeNow();
                        game_state = 5;
                        rocket.reset();
                    }else{
                        //If the Credits is pressed
                        game_state = 2;
                    }
                }else{
                    if(press_y < menu_y_split){
                        //If the Leaderboard is pressed
                        game_state = 1;
                    }else{
                        //If the Instructions is pressed
                        game_state = 3;
                    }
                }
            }else if(game_state != 4){
                //If the menu state is any of the others, bring it back to the menu
                if(press_x > back_menu_x && press_y > back_menu_y){
                    game_state = 4;
                }
            }
    
            switch(game_state){
                case 0:
                    break;
                case 1:
                    //Displaying the leaderboard
                    displayLeaderBoard();
                    break;
                case 2:
                    //Displaying the credits
                    displayCredits();
                    break;
                case 3:
                    //Displaying the instructions
                    displayInstructions();
                    break;
                case 5:
                    //Allen:
                    //Display the launch button
                    LCD.SetFontColor(0x005288);
                    LCD.WriteAt("LAUNCH", 0,Window::w_height-20);
                    //Display logo

                    //Display rocket and launchpad
                    launchpad.draw();
                    rocket.draw();
                    //If the Launch button is pressed, then set game_state to 0       
                    if(press_x > 0 && press_y > Window::w_height-20){
                        game_state = 0;
                        background_y = 0;
                        rocket.setFuelLevel(100.0);
                        landing = false;
                        rocket.reset();
                        
                    }
                    break;
                case 4:
                    //Displaying the menu
                    displayMenu();
                    break;
            }

            //If the menu state is anything other than the menu, draw a back to menu option on the screen
            if(game_state != 4){
                LCD.SetFontColor(0x005288);
                LCD.WriteAt("Menu ->", back_menu_x, back_menu_y);
            }
        }

        if(game_state == 0){
            float gameTime = TimeNow() - initialTime;
            //Gameplay
            drawBackground();

            rocket.setAltitude(background_y);
            LCD.SetFontColor(0x005288);
            LCD.WriteAt(rocket.getAltitude(),0,0);
            LCD.WriteAt("Menu ->", back_menu_x, back_menu_y);
            if(rocket.reachedMaxHeight(rocket.getAltitude())){
                LCD.SetFontColor(0x005288);
                LCD.WriteAt("Landing",Window::w_width/2-50,0);
                landing = true;
            }
            drawProgressBar(rocket.getFuelLevel());
            rocket.setFuelLevel(-.25);
 
            if(rocket.getY() > Window::w_height/2){
                rocket.moveY(1);
                launchpad.draw();
            }else{
                if(landing){
                    moveBackgroundUp(rocket.getAltitude());
                    collectibles.generate(gameTime,rocket.getAltitude());
                    collectibles.update();
                    collectibles.draw();
                    
                }else{

                    moveBackgroundDown(rocket.getAltitude());
                }
            }

            
            rocket.draw();
        }

        drag_prev_x = drag_x;
        drag_prev_y = drag_y;

        //Update the screen
        LCD.Update();
    }

    collectibles.clean();

    return 0;
}

void handleSigInt(int signum) {
    std::cout << "SIGINT received. Cleaning up and exiting.\n" << std::endl;
    sigintReceived = true;
}

void displayLeaderBoard(){
    //Write Leaderboard as a title
    LCD.WriteLine("Leaderboard");
    
    //Loop through all top ten scores and display them
    for(int i = 0; i < 10; i++){
        LCD.WriteLine(leaderboard[i]);
    }
}

bool checkCollectibleCollision(std::vector<Collectible*> collectibles, Rocket rocket){
    int rate = rocket.getAltitude();

    return true;
}

void displayInstructions(){ 
    //Display all the instructions
    LCD.WriteLine("Instructions");
    LCD.WriteLine("1) Click Launch");
    LCD.WriteLine("2) Wait till rocket gets max alt");
    LCD.WriteLine("3) Drag on x axis to collect fuel");
    LCD.WriteLine("4) Maintain > 0% fuel");
    LCD.WriteLine("5) At end, land rocket");
}

void displayCredits(){
    //Display credits to the developers of the game
    LCD.WriteLine("Credits");
    LCD.WriteLine("Developers:");
    LCD.WriteLine("Eashan Vytla");
    LCD.WriteLine("Allen Thomas");
}

//Run in loop to find button press
//This method is used to prevent bugs in the future with finicky button press issues
bool detectButtonClick(int *x, int *y){
    //Current touch result
    bool touch = LCD.Touch(x, y);

    //Is the current loop cycle pressed? true and the previous loop cycle pressed? is false
    bool val = touch == true && touch != prev_touch;

    //Storing the previous loop cycles touch
    prev_touch = touch;

    //Returning the boolean of if the button was pressed
    return val;
}

void displayMenu(){
    //Draw the dividing borders of the menue screen
    LCD.SetFontColor(0x005288);
    LCD.FillRectangle(155,0,10,239);
    LCD.FillRectangle(0,115,319,10);
    LCD.SetFontColor(0xA7A9AC);
    //Write Launch to the top left section of the menue
    LCD.WriteAt("Start",40,50);
    //Write leaderboard to the top right section of the menue
    LCD.WriteAt("Leaderboard",175,50);
    //Write Credits to the bottom left section of the menue
    LCD.WriteAt("Credit",40,170);
    //Write instructions at the bottom right section of the menue
    LCD.WriteAt("Instructions",170,170);
}

void drawBackground(){
    //width:  Height: 
    // Declares an image for a background
    FEHImage launchPad;
    // Open the image
    launchPad.Open("BackgroundFEH.pic");
    // Draw a pad in the top left corner
    launchPad.Draw(background_x,background_y);
    // Close the image
    launchPad.Close();
}

void moveBackgroundUp(int alt){

    // Define variables to store the initial and final values for changeInY
    float initialChangeInY = 0.4;
    float finalChangeInY = Rocket::max_down_speed;
    float changeInY = .4;

        
    // Check if the altitude is within the specified range
    if (alt >= Rocket::buffer_altitude && alt <= Rocket::max_altitude + 50) {
        // Calculate changeInY based on altitude
        // Linear interpolation between initialChangeInY and finalChangeInY based on the rocket's altitude
        changeInY = initialChangeInY + ((Rocket::max_altitude - alt) / 150.0) * (finalChangeInY - initialChangeInY);
        // Update the background position based on the calculated changeInY
        background_y -= changeInY;
    }

    // Check if the altitude is below the buffer altitude
    if (alt < Rocket::buffer_altitude) {
        // If below buffer altitude, update the background position using the maximum downward speed
        background_y -= Rocket::max_down_speed;
    }
}

void moveBackgroundDown(int alt){
    // Define a variable to store the change in background_y
    float changeInY = Rocket::max_up_speed; 

    // Check if the altitude is greater than or equal to the buffer altitude
    if (alt >= Rocket::buffer_altitude) {
        // Calculate changeInY based on the rocket's altitude
        // Linear interpolation between Rocket::max_up_speed and 0 based on the difference between the current altitude and buffer altitude
        changeInY = Rocket::max_up_speed - ((alt - Rocket::buffer_altitude) / 50.0);
        // Check if the altitude is close to the maximum altitude (within the last 20 units)
        if (alt > Rocket::max_altitude - 20) {
            changeInY = 0.4; // If close to the maximum altitude, set changeInY to a constant value of 0.4
        }
    }

    // Move the background by the calculated change in Y
    background_y += changeInY;
}
void drawProgressBar(double barWidth){
    LCD.SetFontColor(0x005288);
    //create rectangle based of input width
    
    LCD.FillRectangle(Window::w_width-110,0,barWidth,10);
}
