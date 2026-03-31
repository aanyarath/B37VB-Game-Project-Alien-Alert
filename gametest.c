#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#define GAMEPLAY 0
#define GAME_OVER 1

int spawnAlienX(void);
void spawnAlien(int alienposx, int alienposy, float alienSpeed);
void spawnPlayer(int playerposx, int playerposy);
void endGame();

int main(void)
{
   
    int screenWidth = 800; // Set the window dimensions
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "balls"); // Initialize the window

    int playerposx = 400; // Initialize the player's position at the center of the screen
    int playerposy = 150;
    int movementSpeed = 10; // Set the movement speed of the player

    float bulletposx=0.0f; // Initialize the bullet's position and speed
    float bulletposy=0.0f;
    float bulletspeed=0.25f; 

    int alienposx = spawnAlienX(); // Initialize the alien's position
    float alienposy = 400;
    float alienSpeed = 0.03125f; // Movement speed of the alien
    bool alienState = false; // State of the alien (true for alive, false for dead)

    int score=0; // Initialize the player's score
    
    int playerloss=0;
    
    int currentScreen = GAMEPLAY;
    int playerHealth = 100;

    
    
    while(!WindowShouldClose())
    {
        
        DrawText("Use WASD to move the ball", 50, 50, 20, BLUE);
        DrawText("Press SPACE to shoot", 50, 80, 20, BLUE);
        DrawText(TextFormat("Score: %d", score), 50, 110, 20, BLUE);
       
        if (IsKeyPressed(KEY_W)) // Check if the W key is pressed
        {
            playerposy-=movementSpeed;
            printf("forward\n");
        }
        if (IsKeyPressed(KEY_S)) // Check if the S key is pressed
        {
            printf("backward\n");
            playerposy+=movementSpeed;
                    
        }
        if (IsKeyPressed(KEY_A)) // Check if the A key is pressed
        {
            printf("left\n");
            playerposx-=movementSpeed;       
        }
        if (IsKeyPressed(KEY_D)) // Check if the D key is pressed
        {
            printf("right\n");
            playerposx+=movementSpeed;
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            DrawCircleV((Vector2){bulletposx, bulletposy}, 5, RED); // Draw the bullet as a red circle
            bulletposx=playerposx;
            bulletposy=playerposy;
            while (bulletposx<screenWidth && bulletposy<screenHeight && bulletposx>0 && bulletposy>0) // Move the bullet until it goes off-screen
            {
                //bulletposx+=bulletspeed;
                bulletposy+=bulletspeed;
                BeginDrawing(); 
                ClearBackground(RAYWHITE);
                DrawCircleV((Vector2){bulletposx, bulletposy}, 5, RED); // Draw the bullet as a red circle
                spawnPlayer(playerposx, playerposy);
                spawnAlien(alienposx, alienposy, alienSpeed);
                EndDrawing();
                if (CheckCollisionCircles((Vector2){bulletposx, bulletposy}, 5, (Vector2){alienposx, 400}, 10)) // Check for collision between the bullet and the alien
                {
                    alienState = false; // Set the alien's state to false (dead)
                    alienposx = spawnAlienX(); // Respawn the alien at a new random position
                    alienposy=400;
                    BeginDrawing();
                    ClearBackground(RAYWHITE);
                    spawnAlien(alienposx, alienposy, alienSpeed);
                    EndDrawing();
                    score++; // Increment the player's score
                    break; // Exit the bullet movement loop
                }
                else
                {
                    
                }
                
                
            }
            
            
            

        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        spawnPlayer(playerposx, playerposy);
        spawnAlien(alienposx, alienposy, alienSpeed);
        EndDrawing();
     

    }
    
    endGame();
    
    return 0;
}
//function to spawn the alien at a random position within a certain range on the screen
int spawnAlienX(void)
{
    return 200 + rand() % 400;
}
void spawnAlien(int alienposx, int alienposy, float alienSpeed)
{
    
    if (alienposy<GetScreenHeight)
    {
        
        ClearBackground(RAYWHITE);        
        alienposy-=alienSpeed;
        DrawCircleV((Vector2){alienposx, alienposy}, 10, GREEN);  // Draw alien as a green circle
        
    }
    
    
}
void spawnPlayer(int playerposx, int playerposy)
{
  DrawCircleV((Vector2){playerposx, playerposy}, 10, BLUE);  
}

void endGame()
{
    ClearBackground(RAYWHITE); 
    DrawText(" Game Over!   ", 100, 100, 40,BLUE);
    EndDrawing();
    CloseWindow();
}



