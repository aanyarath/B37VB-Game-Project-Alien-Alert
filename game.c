#include "raylib.h"
#include "stdio.h"
#include <stdlib.h>

int spawnAlienX(void);
void spawnPlayer(int playerposx, int playerposy);
void endGame();

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(void)
{
    // Initialization
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    int playerposx = 400; // Initialize the player's position at the center of the screen
    int playerposy = 150;
    int movementSpeed = 10; // Set the movement speed of the player

    float bulletposx=0.0f; // Initialize the bullet's position and speed
    float bulletposy=0.0f;
    float bulletspeed=2.0f; 

    int alienposx = spawnAlienX(); // Initialize the alien's position
    float alienposy = 400.0f;
    float alienSpeed = 1.0f; // Movement speed of the alien

    
    int framesCounter = 0; // to count frames which can be used for time taken

    InitWindow(screenWidth, screenHeight, "Alien Alert!");
    
/*******************************************************************************************
*
*   raylib [textures] example - image loading
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
    
    Image image = LoadImage("resources/alienlogo.png"); // Loaded in CPU memory (RAM)
    Texture2D texture = LoadTextureFromImage(image); // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);

    GameScreen currentScreen = LOGO;

    SetTargetFPS(60); // Set desired framerate (frames-per-second)

    // Main game loop
/*******************************************************************************************
*
*   raylib [core] example - basic screen manager

*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        
        switch (currentScreen)
        {
            case LOGO:
            {

                framesCounter++;  // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // Main gameplay in next switch case statement
                
            } break;
            case ENDING:
            {
                
                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        
            BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
             
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
                    DrawText("ALIEN ALERT!", 250, 50, 45, DARKPURPLE);
                    DrawText("Loading game....", 280, 370, 30, DARKPURPLE);                     

                } break;
                case TITLE:
                {
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("PRESS ENTER or TAP to Start!", 240, 220, 20, DARKPURPLE);

                } break;
                case GAMEPLAY:
                {
                    int playerloss=0; // Counter for player loss
                    int score=0; // Initialize the player's score
                    int lives=3; // Initialize the player's lives
          
                    while(!WindowShouldClose())
                    {
                        
                        DrawText("Use A or D to move", 50, 50, 20, BLUE);
                        DrawText("Press SPACE to shoot", 50, 80, 20, BLUE);
                        DrawText(TextFormat("Score: %d", score), 50, 110, 20, BLUE);
                        DrawText(TextFormat("Lives Left: %d", lives-playerloss), 50, 140, 20, BLUE);
                       
                        
                        if (IsKeyPressed(KEY_A)) // Check if the A key is pressed- move to left
                        {
                            printf("left\n");
                            playerposx-=movementSpeed;       
                        }
                        if (IsKeyPressed(KEY_D)) // Check if the D key is pressed- move to right
                        {
                            printf("right\n");
                            playerposx+=movementSpeed;
                        }
                        if (IsKeyPressed(KEY_SPACE)) // Shoot bullet
                        {
                    
                            bulletposx=playerposx; // Initialize bullet position
                            bulletposy=playerposy;
                            
                            while (bulletposx<screenWidth && bulletposy<screenHeight && bulletposx>0 && bulletposy>0) // Move the bullet until it goes off-screen
                            {
                                bulletposy+=bulletspeed;
                                BeginDrawing(); 
                                ClearBackground(RAYWHITE);
                                DrawCircleV((Vector2){bulletposx, bulletposy}, 5, RED); // Draw the bullet as a red circle
                                spawnPlayer(playerposx, playerposy);
                                DrawCircleV((Vector2){alienposx, alienposy}, 10, PURPLE); // Draw alien as a purple circle
                                EndDrawing();
                                
                                if (CheckCollisionCircles((Vector2){bulletposx, bulletposy}, 5, (Vector2){alienposx, alienposy}, 10)) // Check for collision between the bullet and the alien
                                {
                                    BeginDrawing();
                                    ClearBackground(RAYWHITE);
                                    alienposx = spawnAlienX(); // Respawn the alien at a new random position
                                    alienposy=400; 
                                    DrawCircleV((Vector2){alienposx, alienposy}, 10, PURPLE); 
                                    EndDrawing();
                                    score++; // Increment the player's score
                                    break; // Exit the bullet movement loop
                                }
                                
                            }

                        }
                        BeginDrawing();
                        ClearBackground(RAYWHITE);
                        spawnPlayer(playerposx, playerposy); 
                        EndDrawing();
                        
                        if (alienposy<screenHeight)
                        {
                            
                            ClearBackground(RAYWHITE);        
                            alienposy-=alienSpeed; // for upward alien movement
                            DrawCircleV((Vector2){alienposx, alienposy}, 10, PURPLE);  // Draw alien as a purple circle
                            if (alienposy==0)
                            {
                                playerloss++;
                                alienposx = spawnAlienX(); // Respawn the alien at a new random position
                                alienposy=400;
                                BeginDrawing();
                                ClearBackground(RAYWHITE);
                                DrawCircleV((Vector2){alienposx, alienposy}, 10, PURPLE); 
                                EndDrawing();
                                
                            }
                            
                            
                        }
                       
                        if (playerloss==3) // when alien goes off screen 3 times, game over
                        {
                            
                            currentScreen = ENDING;
                            break;
                        }
                        printf("Playerloss: %d\n", playerloss);
                        
                        if (IsKeyPressed(KEY_ESCAPE))// To quit game
                        {
                            endGame();
                        }
                        
                        if (score==10) // increases alien speed when score hits 10
                        {
                            // round 2
                            alienSpeed=1.25;
                            
                        }
                        if (score==0 && playerloss==2) // helping the player if they're struggling
                        {
                            alienSpeed=0.5;
                        }
                      

                    }
            

                } break;
                case ENDING:
                {
                    
                    DrawRectangle(0, 0, screenWidth, screenHeight, RED);
                    DrawText("GAME OVER!", (screenWidth/2-125), (screenHeight/2-100), 40, BLACK);
                    
                    DrawText("Press ENTER or TAP to try again!", (screenWidth/2-180), (screenHeight/2+100), 20, BLACK);
                    DrawText("To exit, Press ESC", (screenWidth/2-110), (screenHeight/2+150), 20, BLACK);

                } break;
                default: break;
            }

        EndDrawing();

    }

    CloseWindow();       
   
    return 0;
}
int spawnAlienX(void)
{
    return 200 + rand() % 400; // Randomize alien's horizontal position
}

void spawnPlayer(int playerposx, int playerposy)
{
  DrawCircleV((Vector2){playerposx, playerposy}, 10, BLUE);  // Draw the player as a blue circle
}

void endGame()
{
    CloseWindow(); // End game
}