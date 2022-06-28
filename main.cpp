#include <string>
#include "./include/raylib.h"
#include "./src/field.hpp"
#include "./src/tile.hpp"
#include "./src/constants.hpp"

int main() 
{

    InitWindow(screenWidth, screenHeight, TITLE.c_str() );


    SetTargetFPS( maxFPS ); // fps limit

    Field field( 20, screenHeight/20 );
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
            DrawFPS(10, 10);

            // mouse cursor position
            int cx = GetMouseX(), cy = GetMouseY();
            std::string cords = "Mouse: " + std::to_string(cx) + "," + std::to_string(cy); 
            DrawText(cords.c_str(), 10, 60, 20, DARKGRAY);

            field.drawAll();

            
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}