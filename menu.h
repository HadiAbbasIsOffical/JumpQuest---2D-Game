#ifndef MENU_H
#define MENU_H

#include <raylib.h>

class Menu {
public:
    bool startGame = false;
    bool viewScores = false;
    int difficulty = 0; // 0 = not selected, 1 = Easy, 2 = Medium, 3 = Hard
    int selectedLevel = 0; // 0 = not selected, 1 = Level 1, 2 = Level 2, 3 = Level 3
    bool showInstructions = false;
    int score=0;

    void setScore(int score){
        this->score+=score;
    }

    
    void Draw() {
        ClearBackground(DARKGRAY);
        if(viewScores){
            DrawScoreBoard();
        }else{
        if (!showInstructions && difficulty == 0) {
            DrawMainMenu();
        } else if (!showInstructions && difficulty > 0 && selectedLevel == 0) {
            DrawDifficultyMenu();
        } else if (!showInstructions && selectedLevel > 0) {
            DrawLevelMenu();
        } else {
            DrawInstructions();
        }
    }
}
    void HandleInput() {
        Vector2 mousePos = GetMousePosition();
        if(viewScores){
                 DrawScoreBoard();
        }         
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!showInstructions && difficulty == 0) {
                HandleMainMenuInput(mousePos);
            } else if (!showInstructions && difficulty > 0 && selectedLevel == 0) {
                HandleDifficultyMenuInput(mousePos);
            } else if (!showInstructions && selectedLevel > 0) {
                HandleLevelMenuInput(mousePos);
            } else if (showInstructions) {
                showInstructions = false;
                startGame = true; // Start the game after instructions
            }
        }
    }

private:
    const float optionWidth = 300;
    const float optionHeight = 30;

    void DrawMainMenu() {
        DrawText("Coin Quest", GetScreenWidth() / 2 - MeasureText("Coin Quest", 40) / 2, 100, 40, WHITE);
        DrawText("Hadi - Minaal - Mishaal", GetScreenWidth() / 2 - MeasureText("Hadi - Minaal - Mishaal", 20) / 2, 150, 20, GREEN);
        DrawText("1. Start Game", GetScreenWidth() / 2 - MeasureText("1. Start Game", 20) / 2, 250, 20, WHITE);
        DrawText("2. View Scores", GetScreenWidth() / 2 - MeasureText("2. View Scores", 20) / 2, 300, 20, WHITE);
        DrawText("3. Exit", GetScreenWidth() / 2 - MeasureText("3. Exit", 20) / 2, 350, 20, WHITE);

        HighlightOption(250, "1. Start Game");
        HighlightOption(300, "2. View Scores");
        HighlightOption(350, "3. Exit");
    }

  void DrawScoreBoard() {
    ClearBackground(DARKGRAY);
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    const char* title = "Scoreboard";
    int titleFontSize = 50;
    int titleWidth = MeasureText(title, titleFontSize);
    const char* scoreText = TextFormat("Your Score: %d", score);
    int scoreFontSize = 30;
    int scoreWidth = MeasureText(scoreText, scoreFontSize);

    Rectangle menuButton = {screenWidth / 2 - 100, screenHeight / 2 + 80, 200, 50};

    DrawText(title, screenWidth / 2 - titleWidth / 2, screenHeight / 2 - 150, titleFontSize, GREEN);
    DrawText(scoreText, screenWidth / 2 - scoreWidth / 2, screenHeight / 2 - 70, scoreFontSize, GREEN);

    DrawRectangleRec(menuButton, LIGHTGRAY);
    DrawText("Back to Menu", screenWidth / 2 - MeasureText("Back to Menu", 20) / 2, screenHeight / 2 + 95, 20, DARKGRAY);

    if (CheckCollisionPointRec(GetMousePosition(), menuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
           viewScores=false;
    }
}

    void DrawDifficultyMenu() {
        DrawText("Select Difficulty", GetScreenWidth() / 2 - MeasureText("Select Difficulty", 30) / 2, 100, 30, WHITE);
        DrawText("1. Easy", GetScreenWidth() / 2 - MeasureText("1. Easy", 20) / 2, 200, 20, WHITE);
        DrawText("2. Medium", GetScreenWidth() / 2 - MeasureText("2. Medium", 20) / 2, 250, 20, WHITE);
        DrawText("3. Hard", GetScreenWidth() / 2 - MeasureText("3. Hard", 20) / 2, 300, 20, WHITE);
        DrawText("Back To Menu", GetScreenWidth() / 2 - MeasureText("Back To Menu", 20) / 2, 400, 20, BLACK);

        HighlightOption(200, "1. Easy");
        HighlightOption(250, "2. Medium");
        HighlightOption(300, "3. Hard");
        HighlightOption(400, "Back To Menu");

    }

    void DrawLevelMenu() {
        DrawText("Select Level", GetScreenWidth() / 2 - MeasureText("Select Level", 30) / 2, 100, 30, WHITE);
            DrawText("1. Level 1", GetScreenWidth() / 2 - MeasureText("1. Level 1", 20) / 2, 200, 20, WHITE);
            DrawText("2. Level 2", GetScreenWidth() / 2 - MeasureText("2. Level 2", 20) / 2, 250, 20, WHITE);
            DrawText("3. Level 3", GetScreenWidth() / 2 - MeasureText("3. Level 3", 20) / 2, 300, 20, WHITE);

        HighlightOption(200, "1. Level 1");
        HighlightOption(250, "2. Level 2");
        HighlightOption(300, "3. Level 3");
    }

    void DrawInstructions() {
        ClearBackground(BLACK);
        DrawText("Instructions", 50, 50, 40, GREEN);
        DrawText("Press SPACE to jump", 50, 120, 20, WHITE);
        DrawText("Use LEFT and RIGHT keys to move", 50, 150, 20, WHITE);
        DrawText("Avoid enemies and reach the checkpoint", 50, 180, 20, WHITE);
        DrawText("Press any key to start!", 50, 240, 20, YELLOW);
    }

    void HandleMainMenuInput(const Vector2 &mousePos) {
        if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 250, optionWidth, optionHeight})) {
            difficulty = 1;
        } else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 300, optionWidth, optionHeight})) {
            viewScores = true; 
        } else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 350, optionWidth, optionHeight})) {
            CloseWindow(); // Exit
        }
    }

    void HandleDifficultyMenuInput(const Vector2 &mousePos) {
        if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 200, optionWidth, optionHeight})) {
            difficulty = 1; // Easy
            selectedLevel = 1; 
        } else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 250, optionWidth, optionHeight})) {
            difficulty = 2; // Medium
            selectedLevel = 2; 
        } else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 300, optionWidth, optionHeight})) {
            difficulty = 3; // Hard
            selectedLevel = 3; 
        }
         else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 400, optionWidth, optionHeight})) {
           viewScores=false;
           difficulty = 0;
    }
    }

    void HandleLevelMenuInput(const Vector2 &mousePos) {
        if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 200, optionWidth, optionHeight})) {
            if (selectedLevel == 1 || (selectedLevel > 1 && difficulty >= selectedLevel)) {
                showInstructions = true; 
            } else {
                selectedLevel = 2;
            }
        } else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 250, optionWidth, optionHeight})) {
            if (selectedLevel >= 2) {
                showInstructions = true; 
            } else {
                selectedLevel = 3; 
            }
        } else if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, 300, optionWidth, optionHeight})) {
            if (selectedLevel >= 3) {
                showInstructions = true;
            } else {
                selectedLevel = 4; 
            }
        }
    }

    void HighlightOption(float yPos, const char* text) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, {GetScreenWidth() / 2 - optionWidth / 2, yPos, optionWidth, optionHeight})) {
            DrawRectangle(GetScreenWidth() / 2 - optionWidth / 2, yPos, optionWidth, optionHeight, LIGHTGRAY);
        }
    }
};

#endif