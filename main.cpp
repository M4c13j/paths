#include <string>
#include <iostream>

#include "./include/raylib.h"
#include "./src/field.hpp"
#include "./src/tile.hpp"
#include "./src/constants.hpp"
#include "./src/bfs.hpp"
#include "./src/astar.hpp"

int main() 
{

    InitWindow(screenWidth, screenHeight, TITLE.c_str() );


    SetTargetFPS( maxFPS ); // fps limit

    
    Field field( N, screenHeight/N, Vector2{ (float)screenWidth-screenHeight, 0.0 });
    field.clearAll();
    field.setStart( 0, 0 );
    field.setEnd( N-1, N-1 );

    Bfs bfs( field, N );
    bfs.field = &field;
    bfs.reset();
    

    // ------- GUI ---------
    Rectangle title{40,5,410,45};
    Rectangle clearRec{ (float)390-5, (float)screenHeight-128-5, 87, 34 };
    Rectangle bfsRec{ 30, 70, 100, 46};
    Rectangle asRec{ 30+100+20, 70, 152, 46 };
    Rectangle mazesRec{ 150+160+20, 70, 148, 46 };

    Rectangle runRec{ 70, 560, 130, 60 };
    Rectangle resRec{ 250, 560, 190, 60 };

    std::string algoName = "None";
    Color algoNameCol = BLACK;
    std::string algoFeedback = "No path beetween points.";
    Color algoFeedbackCol = MAROON;

    Tile menutiles[3];
    menutiles[0] = Tile( 50, Vector2{60, screenHeight-90}, 0, 0 );
    menutiles[0].type = 1;
    menutiles[1] = Tile( 50, Vector2{245, screenHeight-90}, 0, 2 );
    menutiles[1].type = 2;
    menutiles[2] = Tile( 50, Vector2{400, screenHeight-90}, 0, 3 );
    menutiles[2].type = 3;

    int tileSelected = 0;
    bool debug = false;        // debugging mode status
    int mode = 0;              // 1 - drawing, 2 - algorithm going
    bool mousePressed = false; // is mouse pressed?
    int algorithm = 0;         // which algorithm is chosen
    bool algorun = false;      // if algorithm is running
    int dist = 0;              // lenght of thie shortest path
    float algoDelay = 0.0;     // delay beetwen picking algos
    float stepDelay = 1.0/6;     // delay beetwen steps
    float lastStepTime = 0.0;  // time of the last step of algo
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

            // BFS
            DrawRectangleRounded( bfsRec, 0.4, 6, BLUE );
            DrawText( "BFS", bfsRec.x+6, bfsRec.y+4, 44, WHITE );
            float tim = GetTime();
            if( tim-algoDelay >= 0.3 && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, bfsRec) ) {
                bfs.init( field.start );
                algorithm = 1;
                algoDelay = tim;
                algoName = "BFS";
                algoNameCol = BLUE;
            }
            // a star
            DrawRectangleRounded( asRec, 0.4, 6, ORANGE );
            DrawText( "A star", asRec.x+6, asRec.y+4, 44, WHITE );
            if( tim-algoDelay >= 0.3 && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, asRec) ){ 
                bfs.init( field.start );
                algorithm = 2;
                algoDelay = tim;
                algoName = "A star";
                algoNameCol = ORANGE;
            }
            // maze
            DrawRectangleRounded( mazesRec, 0.4, 6, DARKPURPLE );
            DrawText( "Mazes", mazesRec.x+6, mazesRec.y+4, 44, WHITE );
            if( tim-algoDelay >= 0.3 && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, mazesRec) ){ 
                bfs.init( field.start );
                algorithm = 3;
                algoDelay = tim;
                algoName = "Mazes";
                algoNameCol = DARKPURPLE;
            }

            // which algorithm ???
            DrawText( "Algorithm:" , 40, 160, 26, BLACK );
            DrawText( (algoName).c_str() , 175, 160, 26, algoNameCol );
            // distance
            DrawText( ("Lenght of the shortest path: " + (dist==0?"+oo":std::to_string(dist)) ).c_str() , 40, 200, 26, BLACK );
            // return message
            DrawText( ( algoFeedback ).c_str() , 40, 240, 34, algoFeedbackCol );



            DrawRectangleRec( runRec, GREEN );
            DrawText( "Run", runRec.x+10, runRec.y+4, 60, BLACK );
            if( tim-algoDelay >= 0.3 && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, runRec) ){ 
                if( algorun ) {
                    bfs.reset();

                    mode = 1;
                } else mode = 2;

                algorun = !algorun;
                algoDelay = tim;
            }
            DrawRectangleRec( resRec, RED );
            DrawText( "Reset", resRec.x+10, resRec.y+4, 60, BLACK );
            if( tim-algoDelay >= 0.3 && IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) && CheckCollisionPointRec(Vector2{(float)GetMouseX(),(float)GetMouseY()}, resRec) ){ 
                if( !algorun ) {
                    field.resetAll();
                    mode = 1;
                    algoDelay = tim;
                }
            }
            


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

            // ------- end of menu ---------
            // ------ ALGORITHM RUNNING --------

            // drawing tiles  IF ALGORITHMS IS NOTRUNNIG!
            if( mode == 1 )
                field.detectCollision( tileSelected );

            if( mode == 2 && algorun && tim - lastStepTime >= stepDelay ) {
                lastStepTime = tim;
                int odp=0 , howmany;

                if( algorithm == 1 ) howmany = bfs.kol.size();
                else if( algorithm == 2 ) howmany = bfs.kol.size();
                else if( algorithm == 3 ) howmany = bfs.kol.size();

                while( howmany>=0 ) {
                    if( howmany > 0 ) {
                        if( algorithm == 1 ) odp = bfs.step();
                        else if( algorithm == 2 ) odp = bfs.step();
                        else if( algorithm == 3 ) odp = bfs.step();
                    }
                    howmany--;
                    if( odp != 1 ) {
                        if( odp == 2 ) {
                            algoFeedback = "Shortest path found!";
                            algoFeedbackCol = DARKGREEN;
                            dist = bfs.dist;
                        } else if( odp == 0 ) {
                            algoFeedback = "No path beetween points.";
                            algoFeedbackCol = MAROON;
                        }
                        mode = 0;
                        algorun = false;
                        howmany = -100;
                    }
                }
            }





            // ------ ALGORITHM END ---------
            // --------- DEBUG --------
            DrawFPS(1, 1);

            // switch debug mode
            if( IsKeyPressed( KEY_SPACE ) ) debug = !debug;
            if( debug ) {
            int cx = GetMouseX(), cy = GetMouseY();
            std::string cords = "Mouse: " + std::to_string(cx) + "," + std::to_string(cy); 
            DrawText(cords.c_str(), 10, 30, 20, DARKGRAY);
            DrawText( (std::to_string(mode) +" "+ std::to_string(algorithm)+" "+ std::to_string(algorun)).c_str() , 10, 50, 20, DARKGRAY);
            
            }
            
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}