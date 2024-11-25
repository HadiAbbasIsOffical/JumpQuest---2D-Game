#ifndef LOSE_H
#define LOSE_H
#include <raylib.h>
#include "game.h"

class LoseScreen {
public:
    bool goToMenu; // Flag to signal going back to the menu

    LoseScreen() : goToMenu(false) {}

    void Update() {
        // Check if the user clicks the "Go to Menu" button
        Rectangle menuButton = {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 50, 200, 50};
        if (CheckCollisionPointRec(GetMousePosition(), menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            goToMenu = true;
        }
    }

    void Draw(int score) const {
        // Draw the win screen
        ClearBackground(RAYWHITE);
        DrawText("You lose!", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 100, 40, RED);
        DrawText(TextFormat("Your Score: %d", score), GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 30, 30, BLACK);

        // Draw the "Go to Menu" button
        Rectangle menuButton = {GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 50, 200, 50};
        DrawRectangleRec(menuButton, LIGHTGRAY);
        DrawText("Go to Menu", GetScreenWidth() / 2 - 70, GetScreenHeight() / 2 + 65, 20, DARKGRAY);
    }
};

#endif
