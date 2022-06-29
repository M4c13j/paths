#include <string>
#include "./include/raylib.h"
#include "./src/field.hpp"
#include "./src/tile.hpp"
#include "./src/constants.hpp"

int main() 
{

    InitWindow(screenWidth, screenHeight, TITLE.c_str() );


    SetTargetFPS( maxFPS ); // fps limit

    
    Field field( N, screenHeight/N, Vector2{ (float)screenWidth-screenHeight, 0.0 });
    
    field.clearAll();
    field.setStart( 0, 0 );
    field.setEnd( N-1, N-1 );

    Tile menutiles[3];
    menutiles[0] = Tile( 50, Vector2{60, screenHeight-90}, 0, 0 );
    menutiles[0].type = 1;
    menutiles[1] = Tile( 50, Vector2{245, screenHeight-90}, 0, 2 );
    menutiles[1].type = 2;
    menutiles[2] = Tile( 50, Vector2{400, screenHeight-90}, 0, 3 );
    menutiles[2].type = 3;

    int mode = 0; // 1 - drawing, 2 - algorithm going
    int tileSelected = 0;
    bool mousePressed = false; // is mouse pressed?
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Drawing all tiles
            field.drawAll();

            // ------- menu section ---------
            DrawText( "Edit the map", 150, screenHeight-135, 35, BLACK );
            for( auto & el : menutiles ) 
                el.draw();
        
            DrawText( "Blocked tile", 20, screenHeight-35, 25, BLACK );
            DrawText( "Start tile", 220, screenHeight-35, 25, BLACK );
            DrawText( "End tile", 380, screenHeight-35, 25, BLACK );

            for( auto &el : menutiles ) {
                if( el.isClicked() ) {
                    mode = 1;
                    tileSelected = el.id[1];
                }
            }

            if( mode == 1 )
                field.detectCollision( tileSelected );


            // ------- end of menu ---------
            // mouse cursor position & debug options
            DrawFPS(10, 10);

            int cx = GetMouseX(), cy = GetMouseY();
            std::string cords = "Mouse: " + std::to_string(cx) + "," + std::to_string(cy); 
            DrawText(cords.c_str(), 10, 30, 20, DARKGRAY);
            DrawText( (std::to_string(mode) +" "+ std::to_string(tileSelected)).c_str() , 10, 50, 20, DARKGRAY);
            
            
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}