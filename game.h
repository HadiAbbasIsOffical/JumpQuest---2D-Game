#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>
#include <cstdlib>  // For random direction 
#include <ctime>    // For random logic, not implemented yet , random coin generation
class Player
{
public:
    Vector2 position;
    float speed = 5.0f;
    float jumpHeight = 10.0f;
    bool isJumping = false;
    float gravity = 0.5f;
    float velocityY = 0.0f;

    Rectangle boundingBox;

    Player(Vector2 startPos)
    {
        position = startPos;
        boundingBox = {position.x, position.y, 40, 40}; // player size :: 40x40
    }

void Update(const std::vector<Rectangle>& platforms)
{
    // Player movement (left-right)
    if (IsKeyDown(KEY_LEFT)) position.x -= speed;
    if (IsKeyDown(KEY_RIGHT)) position.x += speed;

    // Prevent player from going off the screen horizontally
    if (position.x < 0) position.x = 0;
    if (position.x > GetScreenWidth() - boundingBox.width) position.x = GetScreenWidth() - boundingBox.width;

    // Jump logic
    if (IsKeyPressed(KEY_SPACE) && !isJumping)  
    {
        isJumping = true;
        velocityY = -jumpHeight;  
    }

    // Gravity and fall handling
    if (isJumping)
    {
        velocityY += gravity;  // Apply gravity
        position.y += velocityY; 

        bool onGround = false;
        for (const auto& platform : platforms)
        {
            if (CheckCollisionRecs(boundingBox, platform) && velocityY >= 0) 
            {
                position.y = platform.y - boundingBox.height;
                isJumping = false; 
                velocityY = 0; 
                onGround = true; 
                break; // Exit the loop as we found a platform to land on
            }
        }

        if (!onGround && position.y >= GetScreenHeight() - boundingBox.height)
        {
            position.y = GetScreenHeight() - boundingBox.height;
            isJumping = false;  
        }
    }

    boundingBox.x = position.x; 
    boundingBox.y = position.y;
}


    void Draw()
    {
        DrawRectangleRec(boundingBox, BLUE);
    }
};

class Coin
{
public:
    Vector2 position;
    Rectangle boundingBox;
    bool isCollected = false;

    Coin(Vector2 pos)
    {
        position = pos;
        boundingBox = {position.x, position.y, 20, 20}; // Coin size 20x20
    }

    void Draw()
    {
        if (!isCollected)
        {
            DrawRectangleRec(boundingBox, YELLOW);
        }
    }
};

class Platform
{
public:
    Vector2 position;
    Rectangle boundingBox;

    Platform(Vector2 pos, float width)
    {
        position = pos;
        boundingBox = {position.x, position.y, width, 10}; // Platform size 10px high
    }

    void Draw()
    {
        DrawRectangleRec(boundingBox, DARKGRAY);
    }
};

class Enemy
{
public:
    Vector2 position;
    float speed = 3.0f;
    int direction = 1; // 1 for moving right, -1 for moving left
    float velocityY = 0.0f;
    bool isJumping = false;
    float gravity = 0.5f;
    Rectangle boundingBox;

    Enemy(Vector2 pos)
    {
        position = pos;
        boundingBox = {position.x, position.y, 20, 20}; //enemy size currently
    }

    void Update(const std::vector<Rectangle>& platforms)
    {
        position.x += direction * speed;

        // Prevent enemy from going off-screen
        if (position.x < 0 || position.x > GetScreenWidth() - boundingBox.width)
        {
            direction *= -1; 
        }

        // Gravity and jumping logic for enemy
        if (isJumping)
        {
            velocityY += gravity;
            position.y += velocityY;

            // Check for collision with platforms
            bool onGround = false;
            for (const auto& platform : platforms)
            {
                if (CheckCollisionRecs(boundingBox, platform) && velocityY >= 0)
                {
                    position.y = platform.y - boundingBox.height;
                    isJumping = false;
                    velocityY = 0;
                    onGround = true;
                    break;
                }
            }

            if (!onGround && position.y >= GetScreenHeight() - boundingBox.height)
            {
                position.y = GetScreenHeight() - boundingBox.height;
                isJumping = false;
            }
        }

        boundingBox.x = position.x;
        boundingBox.y = position.y;
    }

    void Draw()
    {
        DrawRectangleRec(boundingBox, RED);
    }
};

class Game
{
public:
    Player player;
    std::vector<Coin> coins;
    std::vector<Platform> platforms;
    std::vector<Enemy> enemies;
    int score = 0;
    bool running=true;

    Game() : player(Vector2{100, GetScreenHeight() - 100}) {}

    void Init()     //this function just initilizes all the entities of the game ^-^
    {
        platforms.push_back(Platform(Vector2{0, GetScreenHeight() - 50}, GetScreenWidth())); // Ground platform
        platforms.push_back(Platform(Vector2{200, GetScreenHeight() - 150}, 300)); // Upper platform
        platforms.push_back(Platform(Vector2{500, GetScreenHeight() - 250}, 200)); // Another platform

        coins.push_back(Coin(Vector2{300, GetScreenHeight() - 220}));   //2 coins currently 
        coins.push_back(Coin(Vector2{600, GetScreenHeight() - 370}));

        enemies.push_back(Enemy(Vector2{800, GetScreenHeight() - 100}));    //2 enemies
        enemies.push_back(Enemy(Vector2{700, GetScreenHeight() - 370}));
    }

    void Update()
    {
        std::vector<Rectangle> platformRectangles;
        for (auto& platform : platforms)
        {
            platformRectangles.push_back(platform.boundingBox);
        }

        player.Update(platformRectangles);

        for (auto& coin : coins)
        {
            if (!coin.isCollected && CheckCollisionRecs(player.boundingBox, coin.boundingBox))
            {
                score++;
                coin.isCollected = true; // Mark coin as collected
            }
        }

        // Update enemies
        for (auto& enemy : enemies)
        {
            enemy.Update(platformRectangles); 
            if (CheckCollisionRecs(player.boundingBox, enemy.boundingBox))
            {
                gameOver(); // If the player collides with an enemy, trigger game over
            }
        }
    }

    void Draw()
    {
        player.Draw();

        // Draw platforms
        for (auto& platform : platforms)
        {
            platform.Draw();
        }

        // Draw coins
        for (auto& coin : coins)
        {
            coin.Draw();
        }

        // Draw enemies
        for (auto& enemy : enemies)
        {
            enemy.Draw();
        }

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
    }

    void gameOver()
    {
        running = false;
        score = 0;

        // Reset player position
        player.position = Vector2{100, GetScreenHeight() - 100};
        player.isJumping = false;
        player.velocityY = 0.0f;

        // Reset platforms, coins, enemies (if needed)
        for (auto& coin : coins)
        {
            coin.isCollected = false;
        }

        for (auto& enemy : enemies)
        {
            enemy.position = Vector2{800, GetScreenHeight() - 100};  // Reset enemies' positions as an example
            enemy.velocityY = 0.0f;
            enemy.isJumping = false;
        }
    }


};

#endif
