#include "FEHLCD.h"

int main()
{
    //Draw the dividing borders of the menue screen
    LCD.SetFontColor(LIGHTGOLDENRODYELLOW);
    LCD.FillRectangle(155,0,10,239);
    LCD.FillRectangle(0,115,319,10);

    //Write Launch to the top left section of the menue
    LCD.WriteAt("Launch",40,50);
    //Write leaderboard to the top right section of the menue
    LCD.WriteAt("Leaderboard",180,50);
    //Write Credits to the bottom left section of the menue
    LCD.WriteAt("Leaderboard",180,50);

    while (1) {
        LCD.Update();
        // Never end
    }
    return 0;
}