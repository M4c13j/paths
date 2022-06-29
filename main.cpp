#include <string>
#include <iostream>

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

    // ------- GUI ---------
    Rectangle title{40,5,410,45};
    Rectangle clearRec{ (float)390-5, (float)screenHeight-128-5, 87, 34 };
    Rectangle bfsRec{ 30, 70, 100, 46};
    Rectangle asRec{ 30+100+20, 70, 152, 46 };
    Rectangle mazesRec{ 150+160+20, 70, 148, 46 };

    Tile menutiles[3];
    menutiles[0] = Tile( 50, Vector2{60, screenHeight-90}, 0, 0 );
    menutiles[0].type = 1;
    menutiles[1] = Tile( 50, Vector2{245, screenHeight-90}, 0, 2 );
    menutiles[1].type = 2;
    menutiles[2] = Tile( 50, Vector2{400, screenHeight-90}, 0, 3 );
    menutiles[2].type = 3;

    bool debug = true; // debugging mode status
    int mode = 0; // 1 - drawing, 2 - algorithm going
    int tileSelected = 0;
    bool mousePressed = false; // is mouse pressed?

    // ------- GUI ---------

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Drawing all tiles
            field.drawAll();

            // ------- menu section ---------

            // ---------- ALGORITHM SELECTION -----------
            // DrawRectangleGradientH( title.x, title.y, title.width, title.height, Color{0,255,62,255}, Color{0,147,255,255} );
            DrawRectangleGradientH( 0, 0, screenWidth-screenHeight, title.height+title.y, Color{0,255,62,255}, Color{0,147,255,255} );
            DrawText( "Pathfinding Algorithms", title.x+20, title.y+1, 36, BLACK );

            DrawRectangle( 0, title.y+title.height, screenWidth-screenHeight, 4, BLACK );

            DrawRectangleRounded( bfsRec, 0.4, 6, BLUE );
            DrawText( "BFS", bfsRec.x+6, bfsRec.y+4, 44, WHITE );
            if( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, bfsRec) )
                field.clearAll(); 
            
            DrawRectangleRounded( asRec, 0.4, 6, ORANGE );
            DrawText( "A star", asRec.x+6, asRec.y+4, 44, WHITE );
            if( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, asRec) )
                field.clearAll(); 
            
            DrawRectangleRounded( mazesRec, 0.4, 6, RED );
            DrawText( "Mazes", mazesRec.x+6, mazesRec.y+4, 44, WHITE );
            if( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, mazesRec) )
                field.clearAll(); 


            // ---------- EDITING AND DRAWING ------------
            DrawText( "Edit the map", 150, screenHeight-135, 36, BLACK );

            DrawRectangleRec( clearRec, RED );
            DrawText( "CLEAR", 390, screenHeight-126, 24, WHITE );
            if( IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, clearRec) )
                field.clearAll(); // if ok, set all tiles to white

            // Drawing stuff
            for( auto & el : menutiles ) 
                el.draw();
            DrawText( "Blocked tile", 20, screenHeight-35, 25, BLACK );
            DrawText( "Start tile", 220, screenHeight-35, 25, BLACK );
            DrawText( "End tile", 380, screenHeight-35, 25, BLACK );

            // check if drawing mode is enabled
            for( auto &el : menutiles ) {
                if( el.isClicked() ) {
                    mode = 1;
                    tileSelected = el.id[1];
                }
            }

            // drawing tiles  IF ALGORITHMS IS NOTRUNNIG!
            if( mode == 1 )
                field.detectCollision( tileSelected );


            // ------- end of menu ---------


            // --------- DEBUG --------
            DrawFPS(1, 1);

            // switch debug mode
            if( IsKeyPressed( KEY_SPACE ) ) debug = !debug;
            if( debug ) {
            int cx = GetMouseX(), cy = GetMouseY();
            std::string cords = "Mouse: " + std::to_string(cx) + "," + std::to_string(cy); 
            DrawText(cords.c_str(), 10, 30, 20, DARKGRAY);
            DrawText( (std::to_string(mode) +" "+ std::to_string(tileSelected)).c_str() , 10, 50, 20, DARKGRAY);
            
            }
            
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}