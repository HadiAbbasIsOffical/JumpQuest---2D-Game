#ifndef MENU_H
#define MENU_H

#include <raylib.h>

class Menu
{
public:
    bool startGame = false;

    void Draw()
    {
        ClearBackground(DARKGRAY);
        DrawText("Coin Quest By ", GetScreenWidth() / 2 - MeasureText("Coin Quest By ", 40) / 2, 100, 40, WHITE);
        int titleHeight = 100 + 40;
        DrawText("Hadi-Minaal-Mishal", GetScreenWidth() / 2 - MeasureText("Hadi-Minaal-Mishal", 30) / 2, titleHeight + 10, 30, GREEN);

        // Draw menu options
        DrawText("1. Start Game", GetScreenWidth() / 2 - MeasureText("1. Start Game", 20) / 2, 250, 20, WHITE);
        DrawText("2. Instructions", GetScreenWidth() / 2 - MeasureText("2. Instructions", 20) / 2, 300, 20, WHITE);
        DrawText("3. Exit", GetScreenWidth() / 2 - MeasureText("3. Exit", 20) / 2, 350, 20, WHITE);

        // Highlight options when the mouse hovers over them
        HighlightOption(250, "1. Start Game");
        HighlightOption(300, "2. Instructions");
        HighlightOption(350, "3. Exit");
    }

    void HandleInput()
    {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Check if Start Game was clicked
            if (CheckCollisionPointRec(mousePos, (Rectangle){GetScreenWidth() / 2 - optionWidth / 2, 250, optionWidth, optionHeight}))
            {
                startGame = true;
            }
            // Check if Instructions was clicked
            else if (CheckCollisionPointRec(mousePos, (Rectangle){GetScreenWidth() / 2 - optionWidth / 2, 300, optionWidth, optionHeight}))
            {
                ShowInstructions();
            }
            // Check if Exit was clicked
            else if (CheckCollisionPointRec(mousePos, (Rectangle){GetScreenWidth() / 2 - optionWidth / 2, 350, optionWidth, optionHeight}))
            {
                CloseWindow();
            }
        }
    }

private:
    const float optionWidth = 200; // Width of clickable area
    const float optionHeight = 30; // Height of clickable area

    void HighlightOption(int y, const char *text)
    {
        Vector2 mousePos = GetMousePosition();
        Rectangle optionRect = {GetScreenWidth() / 2 - optionWidth / 2, (float)y, optionWidth, optionHeight};

        if (CheckCollisionPointRec(mousePos, optionRect))
        {
            DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 20) / 2, y, 20, YELLOW);
        }
    }

    void ShowInstructions()
    {
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("Instructions ", 50, 50, 40, GREEN);
            DrawText("Use Arrow Keys to move and Space to jump", 50, 120, 20, WHITE);
            DrawText("Avoid Touching enemies.", 50, 170, 20, WHITE);
            DrawText("Press ESC to return to the menu.", 50, 220, 20, YELLOW);

            if (IsKeyPressed(KEY_ESCAPE))
            {
                break;
            }

            EndDrawing();
        }
    }
};

#endif
