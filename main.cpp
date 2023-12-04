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
/**This function displays the menue screen on the LCD screen
 * the function takes no parameters and returns nothing
 * The code was written by: Allen
**/
void displayMenu();

/**This function displays the leaderboard on the LCD screen
 * the function takes no parameters and returns nothing
 * The code was written by: Eashan
**/
void displayLeaderBoard();

/**This function displays the names of the Developers on the LCD screen
 * the function takes no parameters and returns nothing
 * The code was written by: Eashan
**/
void displayCredits();

/**This function displays the intructions on the LCD screen
 * the function takes no parameters and returns nothing
 * The code was written by: Eashan
**/
void displayInstructions();

/**This function adds the background on the LCD screen
 * the function takes no parameters and returns nothing
 * The code was written by: Allen
**/
void drawBackground();

/**This function moved the background up based off the the current altitude and a speed scalar
 * The function uses rocket altitude as a parameter and a speed scalar as another parameter
 * The code was written by: Allen
**/
void moveBackgroundUp(int alt, float = 1.0);

/**This function moved the background down based off the the current altitude and a speed scalar
 * The function uses rocket altitude as a parameter and a speed scalar as another parameter
 * The code was written by: Allen
**/
void moveBackgroundDown(int alt, float = 1.0);

/**This function draws the fuel progress bar based off the current fuel level
 * The function uses the fuel Level of the rocket as a parameter which is then used as the width
 * The code was written by: Allen
**/
void drawProgressBar(double barWidth);

/**This function lets the program close in a safe manner when the command ctrl C is pressed
 * the function takes no parameters and returns nothing
 * The code was written by: Eashan
**/
void handleSigInt(int signum);

/**This function displays the Game over screen
 * the function takes no parameters and returns nothing
 * The code was written by: Allen
**/
void displayGameOver();

/**This function displays the Game over screen
 * the function takes the score as a parameter
 * The code was written by: Eashan
**/
void displayGameWon(int score = 0);

//background x and y
float background_x = 0;
float background_y = 0;

//The reason for losing the game
char reasonGameOver[40] = "Game Over";

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

//Initializing a temporary placeholder for the leaderboard
//In the final version this would be read from a file
int highScore = 0;

// if the Rocket is on the way down
bool descent = false;
//if rocket is near lanch pad
bool landing = false;

//0 - Game
//1 - Leaderboard
//2 - Credit
//3 - Instructions
//4 - Menu
//5 - IDLE Game
//6 - Loss
//7 - Won
int game_state = 4;

//0 - Takeoff
//1 - Coast
//2 - Pre-landing
//3 - Land
int rocket_state = 0;

//Global variable to handle when the SIGINT is recieved.
//This is volatile to be accessed accross threads.
volatile bool sigintReceived = false;

//The change in Y for the rocket
float changeInY = .4;

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
    
    //creating objects for rocket, launchpad, and collectibles
    Rocket rocket;
    Launchpad launchpad;
    Collectibles collectibles;

    //make the menue from function
    displayMenu();
    
    //set the inital time to 0
    float initialTime = 0;

    //intiialize game over as false
    bool game_over = false;
    
    while (!sigintReceived && !LCD.closed) {
        //Keeping track of user click and position of the click
        bool button_press = detectButtonClick(&press_x, &press_y);
        
        //let the Rocket be able to be dragged if the game is playing and not launching off
        if(game_state == 0 && rocket_state >= 1 && LCD.Touch(&drag_x, &drag_y)){
            rocket.moveX(drag_x - drag_prev_x);
        }

        //If the user clicked the screen (Only first loop cycle of click is counted)
        if(button_press || game_over){
            LCD.Clear();
            //If the menu state is menu, go to the selected state
            if(game_state == 4){
                if(press_x < menu_x_split){
                    if(press_y < menu_y_split){
                        //If Play Game is pressed
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
                    //reseting collectibles once leaving game screen
                    collectibles.clean();
                    rocket_state = 0;
                    game_state = 4;
                }
            }
            //Checking which game state it currently is
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
                    //Display the launch button
                    LCD.SetFontColor(0x005288);
                    LCD.WriteAt("LAUNCH", 0,Window::w_height-20);

                    //Display rocket and launchpad
                    launchpad.draw();
                    rocket.draw();
                    //If the Launch button is pressed, then set game_state to 0       
                    if(press_x > 0 && press_y > Window::w_height-20){
                        //resetting values for new attempt
                        game_state = 0;
                        initialTime = TimeNow();
                        background_y = 0;
                        rocket.setFuelLevel(100.0);
                        descent = false;
                        rocket.reset();
                    }
                    break;
                case 4:
                    //Displaying the menu
                    displayMenu();
                    break;
                case 6:
                    game_over = false;
                    displayGameOver();
                    break;
                case 7:
                    game_over = false;
                    displayGameWon(rocket.getFuelLevel());
                    break;
            }

            //If the menu state is anything other than the menu, draw a back to menu option on the screen
            if(game_state != 4){
                LCD.SetFontColor(0x005288);
                LCD.WriteAt("Menu ->", back_menu_x, back_menu_y);
            }
        }
        //if the game is playing
        if(game_state == 0){
            if(rocket.getFuelLevel() == 0){
                //game over if the rocket fuel hits 0
                game_state = 6;
                game_over = true;
                strcpy(reasonGameOver, "Ran out of fuel.");
            }
            //set the time to elapsed time
            float gameTime = TimeNow() - initialTime;

            //Gameplay
            //______________________________
            //draw background first so all objects are in front
            drawBackground();

            //set the altitude of the rocket based off the current background Y value
            rocket.setAltitude(background_y);
            LCD.SetFontColor(0x005288);
            //Display the altitude in the top left corner
            LCD.WriteAt(rocket.getAltitude(),0,0);
            //display menue button in bottom right;
            LCD.WriteAt("Menu ->", back_menu_x, back_menu_y);

            //switch case for the current rocket state
            switch(rocket_state){
                case 0:
                    //Takeoff
                    rocket.moveY(1);
                    launchpad.draw();
                    //move rocket until the rocket reaches the middle of the screen
                    if(rocket.getY() < Window::w_height/2){
                        rocket_state = 1;
                    }
                    break;
                case 1:
                    //Coast
                    if(rocket.reachedMaxHeight(rocket.getAltitude())){
                        //rockets coasts up until the max height is reached
                        //descent becomes true after max height
                        descent = true;
                    }
                    //if the rocket is in descent 
                    if(descent){
                        //the background moves up to make the rocket seem like it is going down
                        moveBackgroundUp(rocket.getAltitude());
                        //generate the items based off gameTime and altitude
                        collectibles.generate(gameTime,rocket.getAltitude());
                        //checks if any collectibles have collided or reached the end of the screen
                        collectibles.update(&rocket);
                        //draw collectible
                        collectibles.draw();
                        //draw the progress bar
                        drawProgressBar(rocket.getFuelLevel());
                        rocket.setFuelLevel(rocket.getFuelLevel() - .3);
                        //if the rocket is on its way up
                    }else if(!descent){
                        //move the background down so the rocket seems to be moving up
                        moveBackgroundDown(rocket.getAltitude());
                    }
                    //if the rocket isb landing and is near the launchpad
                    if(rocket.getAltitude() < 50 && descent){
                        //set the game state to the landing version
                        rocket_state = 2;
                    }
                    break;
                case 2:
                    //Pre-Land
                    //slow the background down by 30%
                    moveBackgroundUp(rocket.getAltitude(), 0.7);
                    rocket.moveY(Rocket::max_down_speed);
                    //rocket y value goes below 0
                    if(rocket.getY() <= 1){
                        //set rocket state to landed
                        rocket_state = 3;
                    }
                    break;
                case 3:
                //landing
                    //move the rocket down at the same speed
                    rocket.moveY(-Rocket::max_down_speed);
                    //draw in the launchpad
                    launchpad.draw();
                    
                    //if the rocket past the intial starting y
                    if(rocket.getY() >= rocket.getInitialY()){
                        //end the game by setting game over to true
                        game_over = true;
                        if(launchpad.landed(rocket.getX())){
                            //if it landed sucessfuly set game state to win
                            game_state = 7;
                        }else{
                            //set game state to game over for failed landing
                            strcpy(reasonGameOver, "Failed landing.");
                            game_state = 6;
                        }
                    }
                    break;
            }
            
            rocket.draw();
        }
        //set new position values for drag functionality
        drag_prev_x = drag_x;
        drag_prev_y = drag_y;

        //Update the screen
        LCD.Update();
    }
    //clean all collectibles up at the end
    collectibles.clean();

    return 0;
}

void handleSigInt(int signum) {
    //output signal recieved when ctrl C is inputted
    std::cout << "SIGINT received. Cleaning up and exiting.\n" << std::endl;
    sigintReceived = true;
}

void displayLeaderBoard(){
    //Write Leaderboard as a title
    LCD.WriteLine("Leaderboard");
    //write the high score to the screen
    LCD.WriteLine("Highscore: " + std::to_string(highScore));
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

void displayGameOver(){
    LCD.WriteAt("GAME OVER",Window::w_width/2-60, Window::w_height/2-50);
    LCD.WriteAt(std::string(reasonGameOver),Window::w_width/2-90, Window::w_height/2 + 50);
}

void displayGameWon(int score){
    LCD.WriteAt("You Landed!",Window::w_width/2-100, Window::w_height/2 - 50);
    LCD.WriteAt("Score: " + std::to_string(score), Window::w_width/2-100, Window::w_height/2);
    if(score > highScore){
        highScore = score;
        LCD.WriteAt("Saved as highscore!", Window::w_width/2-100, Window::w_height/2 + 50);
    }
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

void moveBackgroundUp(int alt, float speedScalar){
    // Define variables to store the initial and final values for changeInY
    float initialChangeInY = 0.4;
    float finalChangeInY = Rocket::max_down_speed;

    // Check if the altitude is within the specified range
    if (alt >= Rocket::buffer_altitude && alt <= Rocket::max_altitude + 50) {
        // Calculate changeInY based on altitude
        // Linear interpolation between initialChangeInY and finalChangeInY based on the rocket's altitude
        changeInY = initialChangeInY + ((Rocket::max_altitude - alt) / 150.0) * (finalChangeInY - initialChangeInY);
        // Update the background position based on the calculated changeInY
        background_y -= changeInY * speedScalar;
    }

    // Check if the altitude is below the buffer altitude
    if (alt < Rocket::buffer_altitude) {
        // If below buffer altitude, update the background position using the maximum downward speed
        background_y -= Rocket::max_down_speed * speedScalar;
    }
}

void moveBackgroundDown(int alt, float speedScalar){
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
    background_y += changeInY * speedScalar;
}
void drawProgressBar(double barWidth){
    if(barWidth < 20){
         LCD.SetFontColor(RED);
        LCD.FillRectangle(Window::w_width-110,0,barWidth,10);
    }else{
        LCD.SetFontColor(0x005288);
        LCD.FillRectangle(Window::w_width-110,0,barWidth,10);
    }
}
