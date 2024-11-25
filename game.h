#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include <string>

class Player {
public:
    Vector2 position;
    float speed;
    float jumpHeight;
    bool isJumping;
    float gravity;
    float velocityY;
    Rectangle boundingBox;
    Color color;

    Player(Vector2 startPos, Color playerColor)
        : position(startPos), speed(5.0f), jumpHeight(10.0f), isJumping(false),
          gravity(0.5f), velocityY(0.0f), boundingBox{startPos.x, startPos.y, 40, 40},
          color(playerColor) {}

    void Update(const std::vector<Rectangle>& platforms) {
        if (IsKeyDown(KEY_LEFT)) position.x -= speed;
        if (IsKeyDown(KEY_RIGHT)) position.x += speed;

        if (position.x < 0) position.x = 0;
        if (position.x > GetScreenWidth() - boundingBox.width)
            position.x = GetScreenWidth() - boundingBox.width;

        if (IsKeyPressed(KEY_SPACE) && !isJumping) {
            isJumping = true;
            velocityY = -jumpHeight;
        }

        if (isJumping) {
            velocityY += gravity;
            position.y += velocityY;

            bool onGround = false;
            for (const auto& platform : platforms) {
                if (CheckCollisionRecs(boundingBox, platform) && velocityY >= 0) {
                    position.y = platform.y - boundingBox.height;
                    isJumping = false;
                    velocityY = 0;
                    onGround = true;
                    break;
                }
            }

            if (!onGround && position.y >= float(GetScreenHeight() - boundingBox.height)) {
                position.y = float(GetScreenHeight() - boundingBox.height);
                isJumping = false;
            }
        } else {
            bool onGround = false;
            for (const auto& platform : platforms) {
                if (CheckCollisionRecs(boundingBox, platform)) {
                    position.y = platform.y - boundingBox.height;
                    velocityY = 0;
                    onGround = true;
                    break;
                }
            }

            if (!onGround) {
                velocityY += gravity;
                position.y += velocityY;
            }
        }

        boundingBox.x = position.x;
        boundingBox.y = position.y;
    }

    void Draw() const {
        DrawRectangleRec(boundingBox, color);
    }
};


class Coin {
public:
    Vector2 position;
    Rectangle boundingBox;
    bool isCollected;
    Coin(Vector2 pos)
        : position(pos), boundingBox{pos.x, pos.y, 20, 20}, isCollected(false) {}

    void Draw() const {
        if (!isCollected) {
            DrawRectangleRec(boundingBox, YELLOW);
        }
    }
};
class Platform {
public:
    Vector2 position;
    Rectangle boundingBox;

    Platform(Vector2 pos, float width)
        : position(pos), boundingBox{pos.x, pos.y, width, 10} {}

    void Draw() const {
        DrawRectangleRec(boundingBox, DARKGRAY);
    }
};

class Enemy {
public:
    Vector2 position;
    float speed;
    int direction;
    float velocityY;
    bool isJumping;
    float gravity;
    Rectangle boundingBox;

    Enemy(Vector2 pos, float enemySpeed)
        : position(pos), speed(enemySpeed), direction(1), velocityY(0.0f),
          isJumping(false), gravity(0.5f), boundingBox{pos.x, pos.y, 20, 20} {}

    void Update(const std::vector<Rectangle>& platforms) {
        position.x += direction * speed;

        if (position.x < 0 || position.x > GetScreenWidth() - boundingBox.width) {
            direction *= -1;
        }

        if (isJumping) {
            velocityY += gravity;
            position.y += velocityY;

            bool onGround = false;
            for (const auto& platform : platforms) {
                if (CheckCollisionRecs(boundingBox, platform) && velocityY >= 0) {
                    position.y = platform.y - boundingBox.height;
                    isJumping = false;
                    velocityY = 0;
                    onGround = true;
                    break;
                }
            }

            if (!onGround && position.y >= float(GetScreenHeight() - boundingBox.height)) {
                position.y = float(GetScreenHeight() - boundingBox.height);
                isJumping = false;
            }
        }

        boundingBox.x = position.x;
        boundingBox.y = position.y;
    }

    void Draw() const {
        DrawRectangleRec(boundingBox, RED);
    }
};

class Game {
public:
    Player player;
    std::vector<Coin> coins;
    int coinCounts;
    std::vector<Platform> platforms;
    std::vector<Enemy> enemies;
    int score;
    bool running;
    int level;
    int difficulty;
    bool levelCompleted;
    bool gameover;

    Game(Color playerColor = BLUE)
        : player(Vector2{100, float(GetScreenHeight() - 100)}, playerColor),
          score(0), running(true), level(1), difficulty(1), levelCompleted(false) {}
    
    void SetDifficulty(int difficultyLevel) {
    difficulty = difficultyLevel;
}

    void InitLevel(int lvl) {
        level = lvl;
        score = 0;
        levelCompleted = false;
        platforms.clear();
        coins.clear();
        enemies.clear();

        switch (level) {
        case 1:
            InitLevel1();
            break;
        case 2:
            InitLevel2();
            break;
        case 3:
            InitLevel3();
            break;
        default:
            break;
        }
    }

    void InitLevel1() {
        platforms.push_back(Platform(Vector2{0, float(GetScreenHeight() - 50)}, float(GetScreenWidth())));
        platforms.push_back(Platform(Vector2{200, float(GetScreenHeight() - 150)}, 300));
        platforms.push_back(Platform(Vector2{500, float(GetScreenHeight() - 250)}, 200));

        coins.push_back(Coin(Vector2{300, float(GetScreenHeight() - 220)}));
        coins.push_back(Coin(Vector2{600, float(GetScreenHeight() - 370)}));
        coins.push_back(Coin(Vector2{800, float(GetScreenHeight() - 400)}));
        this->coinCounts=3;
        enemies.push_back(Enemy(Vector2{350, float(GetScreenHeight() - 200)}, 2.0f));
        enemies.push_back(Enemy(Vector2{600, float(GetScreenHeight() - 100)}, 4.0f));

    }

    void InitLevel2() {
        platforms.push_back(Platform(Vector2{0, float(GetScreenHeight() - 50)}, float(GetScreenWidth())));
        platforms.push_back(Platform(Vector2{200, float(GetScreenHeight() - 150)}, 300));
        platforms.push_back(Platform(Vector2{500, float(GetScreenHeight() - 250)}, 200));
        platforms.push_back(Platform(Vector2{800, float(GetScreenHeight() - 350)}, 250));
        
        coins.push_back(Coin(Vector2{300, float(GetScreenHeight() - 220)}));
        coins.push_back(Coin(Vector2{600, float(GetScreenHeight() - 370)}));
        coins.push_back(Coin(Vector2{850, float(GetScreenHeight() - 400)}));
        this->coinCounts=3;

        enemies.push_back(Enemy(Vector2{350, float(GetScreenHeight() - 200)}, 3.0f));
        enemies.push_back(Enemy(Vector2{650, float(GetScreenHeight() - 320)}, 3.0f));
    }

    void InitLevel3() {
        platforms.push_back(Platform(Vector2{0, float(GetScreenHeight() - 50)}, float(GetScreenWidth())));
        platforms.push_back(Platform(Vector2{200, float(GetScreenHeight() - 150)}, 300));
        platforms.push_back(Platform(Vector2{500, float(GetScreenHeight() - 250)}, 200));
        platforms.push_back(Platform(Vector2{800, float(GetScreenHeight() - 350)}, 250));
        platforms.push_back(Platform(Vector2{1200, float(GetScreenHeight() - 450)}, 200));

        coins.push_back(Coin(Vector2{300, float(GetScreenHeight() - 220)}));
        coins.push_back(Coin(Vector2{600, float(GetScreenHeight() - 370)}));
        coins.push_back(Coin(Vector2{850, float(GetScreenHeight() - 400)}));
        coins.push_back(Coin(Vector2{1200, float(GetScreenHeight() - 470)}));
        this->coinCounts=4;

        enemies.push_back(Enemy(Vector2{350, float(GetScreenHeight() - 200)}, 4.0f));
        enemies.push_back(Enemy(Vector2{650, float(GetScreenHeight() - 320)}, 4.0f));
        enemies.push_back(Enemy(Vector2{950, float(GetScreenHeight() - 370)}, 4.0f));
    }

    void Update() {
        std::vector<Rectangle> platformRectangles;
        for (const auto& platform : platforms) {
            platformRectangles.push_back(platform.boundingBox);
        }

        player.Update(platformRectangles);

        for (auto& coin : coins) {
            if (!coin.isCollected && CheckCollisionRecs(player.boundingBox, coin.boundingBox)) {
                score += 10;
                coin.isCollected = true;
                coinCounts--;
                
            }
        }

        for (auto& enemy : enemies) {
            enemy.Update(platformRectangles);
            if (CheckCollisionRecs(player.boundingBox, enemy.boundingBox)) {
                GameOver();
            }
        }

        if (coins.empty() || coinCounts==0) {
            levelCompleted = true;
        }
    }

    void Draw() const {
        player.Draw();
        for (const auto& platform : platforms) platform.Draw();
        for (const auto& coin : coins) coin.Draw();
        for (const auto& enemy : enemies) enemy.Draw();
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);

        if (levelCompleted) {
            DrawText("Level Completed!", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 40, GREEN);
            DrawText("Press SPACE to continue", GetScreenWidth() / 2 - 130, GetScreenHeight() / 2 + 40, 20, WHITE);
        }
    }

    void GameOver() {
        gameover=true;
        running = false;
     
    }

    void Start() {
        running = true;
        levelCompleted = false;
    }
};

#endif
