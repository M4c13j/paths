#include "./include/raylib.h"
#include "./src/field.hpp"
#include "./src/tile.hpp"
#include "./src/constants.hpp"

int main() 
{

    InitWindow(screenWidth, screenHeight, TITLE.c_str() );


    SetTargetFPS( maxFPS ); // fps limit

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        

    return 0;
}