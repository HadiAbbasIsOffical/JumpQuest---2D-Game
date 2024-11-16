#include "Game.h"
#include "menu.h"
#include <raylib.h>

int main()
{
    // Initialize Raylib window (this internally initializes GLFW)
    InitWindow(1280, 720, "Coin Quest - 2D Platformer");
    SetTargetFPS(60);

    Game game;
    game.Init();
    Menu menu;

    bool inMenu = true;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (inMenu)
        {
            menu.Draw();
            menu.HandleInput();
            if (menu.startGame)  
            {
                inMenu = false;  
                game.running = true;  
                game.Init();  
            }
        }
        else
        {
            game.Update();

            if (game.running == false) 
            {
                menu.startGame=false;
                inMenu = true; 
                game.gameOver(); 
            }
            else
            {
                game.Draw();  // If the game is still running, draw the game
            }
        }

        EndDrawing();
    }

    // Close Raylib and clean up resources
    CloseWindow();
    return 0;
}
