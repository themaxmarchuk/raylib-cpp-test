#include "raylib.h"
#include <cmath>

Vector2 GetForwardVector(float rotation, float offset)
{
    return Vector2{
        sinf((rotation - offset) * DEG2RAD),
        cosf((rotation + offset) * DEG2RAD)
    };
}

class Player
{
public:
    float x, y, speed, rotation;
    int scale;
    const Texture2D& texture;

    Rectangle srcRect, destRect;
    Vector2 origin;

    Player(float x, float y, float speed, float rotation, int scale, const Texture2D& texture) :
        x(x), y(y), speed(speed), rotation(rotation), scale(scale), texture(texture)
    {
        srcRect = Rectangle{
            0.0f,
            0.0f,
            (float)texture.width,
            (float)texture.height
        };
        destRect = Rectangle{
            x,
            y,
            (float)texture.width * scale,
            (float)texture.height * scale
        };
        origin = Vector2{
            (float)texture.width * scale / 2,
            (float)texture.height * scale / 2
        };
    }

    void Move(int direction, float delta)
    {
        Vector2 fv = GetForwardVector(rotation, 90.0f);
        x += fv.x * delta * (float)direction * speed;
        y += fv.y * delta * (float)direction * speed;
        destRect.x = x;
        destRect.y = y;
    }

    void Tick(float delta)
    {
        if (IsKeyDown(KEY_W)) {
            Move(1, delta);
        }
        if (IsKeyDown(KEY_S)) {
            Move(-1, delta);
        }
        if (IsKeyDown(KEY_D)) {
            rotation += 5;
        }
        if (IsKeyDown(KEY_A)) {
            rotation -= 5;
        }
    }

    void Draw()
    {
        DrawTexturePro(texture, srcRect, destRect, origin, rotation, RAYWHITE);
    }
};

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "raylib-cpp");
    Texture2D shipTexture = LoadTexture("ship.png");
    SetTargetFPS(60);
    Player player(200.0f, 200.0f, 500.0f, 0.0f, 3, shipTexture);
    while (!WindowShouldClose())
    {
        player.Tick(GetFrameTime());
        BeginDrawing();
        ClearBackground(BLACK);
        player.Draw();
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
