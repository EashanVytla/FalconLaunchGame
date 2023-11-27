#include "FEHLCD.h"
#include "FEHUtility.h"

void AnimationTraining();
void GravityTraining();

/*
    SDP Training Minigame #1
  
    Make the shapes race across the ​screen.​
    Change their colors when they reach​ the finish line.​
*/
void AnimationTraining() {
    //Intializing shape positions
    int x1 = 50, y1 = 50;
    int x2 = 50, y2 = 100;
    int r = 10;

    // Draw Racer 1
    LCD.SetFontColor(RED);
    LCD.DrawCircle(x1, y1, r);
    LCD.FillCircle(x1, y1, r);

    // Draw Racer 2
    LCD.SetFontColor(BLUE);
    LCD.DrawCircle(x2, y2, r);
    LCD.FillCircle(x2, y2, r);

    LCD.Update();

    // Make racers move across the screen
    while (x1 < 319 - r && x2 < 319 - r) {
        Sleep(0.01);
        // Draw finish line
        LCD.SetFontColor(WHITE);
        LCD.DrawLine(300, 10, 300, 220); 
        
        
        // Clear previous racers by drawing black over them
        // Draw Racer 1
        LCD.SetFontColor(BLACK);
        LCD.DrawCircle(x1, y1, r);
        LCD.FillCircle(x1, y1, r);

        // Draw Racer 2
        LCD.SetFontColor(BLACK);
        LCD.DrawCircle(x2, y2, r);
        LCD.FillCircle(x2, y2, r);

        // Update racer coordinates
        x1++;
        x2++;

        // Redraw racers with different colors - don't forget to sleep!
        if(x1 > 300){
            // Draw Racer 1
            LCD.SetFontColor(GREEN);
            LCD.DrawCircle(x1, y1, r);
            LCD.FillCircle(x1, y1, r);

            // Draw Racer 2
            LCD.SetFontColor(YELLOW);
            LCD.DrawCircle(x2, y2, r);
            LCD.FillCircle(x2, y2, r);
        }else{
            // Draw Racer 1
            LCD.SetFontColor(RED);
            LCD.DrawCircle(x1, y1, r);
            LCD.FillCircle(x1, y1, r);

            // Draw Racer 2
            LCD.SetFontColor(BLUE);
            LCD.DrawCircle(x2, y2, r);
            LCD.FillCircle(x2, y2, r);
        }

        LCD.Update();
    }
}

/*
    SDP Training Minigame #2
  
    Make the shape jump up and then fall back down modeling gravity
*/
void GravityTraining(){
    int x1 = 159, y1 = 229;
    int r = 10;

    // Draw Racer 1
    LCD.SetFontColor(RED);
    LCD.DrawCircle(x1, y1, r);
    LCD.FillCircle(x1, y1, r);

    Sleep(1.0);

    while(y1 > 239.0/2.0){
        Sleep(0.01);
        // Clear previous racers by drawing black over them
        // Draw Racer 1
        LCD.SetFontColor(BLACK);
        LCD.DrawCircle(x1, y1, r);
        LCD.FillCircle(x1, y1, r);

        y1--;

        // Draw Racer 1
        LCD.SetFontColor(RED);
        LCD.DrawCircle(x1, y1, r);
        LCD.FillCircle(x1, y1, r);
    }

    Sleep(1.0);

    while(y1 < 229){
        Sleep(0.01);
        // Clear previous racers by drawing black over them
        // Draw Racer 1
        LCD.SetFontColor(BLACK);
        LCD.DrawCircle(x1, y1, r);
        LCD.FillCircle(x1, y1, r);

        y1++;

        // Draw Racer 1
        LCD.SetFontColor(RED);
        LCD.DrawCircle(x1, y1, r);
        LCD.FillCircle(x1, y1, r);
    }
} 

int main() {
    // Clear background
    LCD.SetBackgroundColor(BLACK);
    LCD.Clear();

    //Telling user training animation is starting
    LCD.WriteLine("Starting Animation Training...");
    LCD.Update();

    Sleep(1.5);

    //Clearing the screen
    LCD.Clear();

    //Running the animation training module
    AnimationTraining();

    Sleep(1.0);
    
    LCD.Clear();

    //Telling user gravity animation is starting
    LCD.WriteLine("Starting Gravity Training...");
    LCD.Update();

    Sleep(1.5);

    //Clearing the screen
    LCD.Clear();

    //Running the gravity traning module
    GravityTraining();

    Sleep(1.0);

    LCD.Clear();

    return 0;
}