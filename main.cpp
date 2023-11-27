#include "FEHLCD.h"
void makeMenue();
int main()
{
    //make the menue from function
    makeMenue();
    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
}
void makeMenue(){
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
