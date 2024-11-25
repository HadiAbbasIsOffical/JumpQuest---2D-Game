#include "Game.h"
#include "menu.h"
#include <win.h>
#include <lose.h>
#include <raylib.h>
#include <iostream>

int main() {
    InitWindow(1280, 720, "Coin Quest - Hadi, Mishaal, Minaal");
    SetTargetFPS(60);

    Game game;
    Menu menu;
    WinScreen winscr;
    LoseScreen LSscr;

    enum GameState { MENU, GAME, WIN_SCREEN, LOSE_SCREEN };  // Renamed LSscr to LOSE_SCREEN
    GameState currentState = MENU;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
        case MENU:
            menu.Draw();
            menu.HandleInput();
            if (menu.startGame) {
                currentState = GAME;
                game.SetDifficulty(menu.difficulty);
                game.InitLevel(menu.selectedLevel); // Initialize the selected level
                game.running = true;
            }
            break;

        case GAME:
            if (game.running) {
                game.Update();
                game.Draw();

                if (game.levelCompleted) {
                    game.running = false;
                    currentState = WIN_SCREEN;
                }

                // Assuming you have a condition for losing in your Game class, like:
                if (game.gameover) { // You need to define gameOver in your Game class
                    game.running = false;
                    currentState = LOSE_SCREEN;
                }
            }
            break;

        case WIN_SCREEN:
            winscr.Update();
            winscr.Draw(game.score);

            if (winscr.goToMenu) {
                currentState = MENU;
                winscr.goToMenu = false; // Reset the flag for future use
                menu.startGame = false;
                menu.difficulty = 0;
                menu.viewScores = false;
                menu.selectedLevel = 0;
            }
            break;

        case LOSE_SCREEN: // Added LOSE_SCREEN logic
            LSscr.Update();
            LSscr.Draw(game.score);

            if (LSscr.goToMenu) {
                currentState = MENU;
                LSscr.goToMenu = false; // Reset the flag for future use
                menu.startGame = false;
                menu.difficulty = 0;
                menu.viewScores = false;
                menu.selectedLevel = 0;
            }
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
