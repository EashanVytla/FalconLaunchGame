#include "FEHLCD.h"

void displayMenu();
void displayLeaderBoard();
void displayCredits();
void displayInstructions();

bool detectButtonClick(int *x, int *y);

const int w_height = 239;
const int w_width = 329;

const int menu_x_split = 155;
const int menu_y_split = 115;

const int back_menu_x = 229;
const int back_menu_y = 219;

bool prev_touch = false;

char leaderboard[10][21] = {"Eashan - 10%", "Allen - 9%", "Joe - 8%", "Stephanie - 7%", "Aidan - 6%", "Josh - 5%", "Marvin - 4%", "Charlie - 3%", "Gavin - 2%", "Sid - 1%"};

//0 - Game
//1 - Leaderboard
//2 - Credit
//3 - Instructions
//4 - Menu
int menu_state = 4;

int main()
{
    int press_x = 0;
    int press_y = 0;

    //make the menue from function
    displayMenu();
    while (1) {
        bool button_press = detectButtonClick(&press_x, &press_y);
        if(button_press){
            LCD.Clear();

            if(menu_state == 4){
                if(press_x < menu_x_split){
                    if(press_y < menu_y_split){
                        menu_state = 0;
                    }else{
                        menu_state = 2;
                    }
                }else{
                    if(press_y < menu_y_split){
                        menu_state = 1;
                    }else{
                        menu_state = 3;
                    }
                }
            }else{
                if(press_x > back_menu_x && press_y > back_menu_y){
                    menu_state = 4;
                }
            }

            switch(menu_state){
                case 0:
                    LCD.WriteLine("Play game here");
                    break;
                case 1:
                    displayLeaderBoard();
                    break;
                case 2:
                    displayCredits();
                    break;
                case 3:
                    displayInstructions();
                    break;
                default:
                    displayMenu();
                    break;
            }

            if(menu_state < 4){
                LCD.WriteAt("Menu ->", back_menu_x, back_menu_y);
            }
        }

        LCD.Update();
    }
    return 0;
}

void displayLeaderBoard(){
    LCD.WriteLine("Leaderboard");
    
    for(int i = 0; i < 10; i++){
        LCD.WriteLine(leaderboard[i]);
    }
}

void displayInstructions(){ 
    LCD.WriteLine("Instructions");
    LCD.WriteLine("1) Click Launch");
    LCD.WriteLine("2) Wait till rocket gets max alt");
    LCD.WriteLine("3) Drag on x axis to collect fuel");
    LCD.WriteLine("4) Maintain > 0% fuel");
    LCD.WriteLine("5) At end, land rocket");
}

void displayCredits(){
    LCD.WriteLine("Credits");
    LCD.WriteLine("Developers:");
    LCD.WriteLine("Eashan Vytla");
    LCD.WriteLine("Allen Thomas");
}

//Run in loop
bool detectButtonClick(int *x, int *y){
    bool touch = LCD.Touch(x, y);

    bool val = touch == true && touch != prev_touch;

    prev_touch = touch;

    return val;
}

void displayMenu(){
    //Draw the dividing borders of the menue screen
    LCD.SetFontColor(LIGHTGOLDENRODYELLOW);
    LCD.FillRectangle(155,0,10,239);
    LCD.FillRectangle(0,115,319,10);

    //Write Launch to the top left section of the menue
    LCD.WriteAt("Start",40,50);
    //Write leaderboard to the top right section of the menue
    LCD.WriteAt("Leaderboard",175,50);
    //Write Credits to the bottom left section of the menue
    LCD.WriteAt("Credit",40,170);
    //Write instructions at the bottom right section of the menue
    LCD.WriteAt("Instructions",170,170);
}
