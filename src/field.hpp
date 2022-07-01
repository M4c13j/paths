#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <iostream>
#include "tile.hpp"
#include "constants.hpp"
#include "../include/raylib.h"

class Field {
public:
    int side;                            // side lenght of a single tile
    int n;                               // number of tiles in 1 axis
    Vector2 pos;                         // position of top-left corner
    std::vector<std::vector<Tile>> cell; // all the tiles in the field

    Point start;
    Point end;

    Vector3 lastedited;                     // last edited tile and time of it
    Field(int _n, int _side, Vector2 _pos); // constructor
    void drawAll();                         // show all tile on the screen
    void clearAll();                        // set all non-start/end tiles to empty
    void resetAll();                        // reset all meta-data like from, visited etc
    void randomColors();                    // fill all the tiles with random color ( not working! )
    int setStart(int x, int y);             // place end tile
    int setEnd(int x, int y);               // place start tile
    void detectCollision(int selected);     // drawing function;
};

Field::Field( int _n, int _side, Vector2 _pos  ) {
    n = _n;
    side = _side;
    pos = _pos;
    cell.resize( n );
    
    Tile cand;
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            cand = Tile( side, Vector2{ (float)x * side + pos.x, (float)y * side + pos.y }, x, y );
            cell[x].push_back( cand );
        }   
    }
}

void Field::drawAll() {
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            cell[ x ][ y ].draw();
        }   
    }
}

void Field::clearAll() {
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            if( cell[x][y].type == 2 || cell[x][y].type == 3 )
                continue;

            cell[ x ][ y ].type = 0;
            cell[ x ][ y ].drawLetter = 0;
        }   
    }
}

void Field::resetAll() {
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            cell[ x ][ y ].from = Point(-1,-1);
            cell[ x ][ y ].visited = false;
            cell[ x ][ y ].dist = 1e9;
            cell[ x ][ y ].heur = 1e9;

            // 
            if( !(cell[ x ][ y ].type >= 1 && cell[ x ][ y ].type <= 3 ) )
                cell[ x ][ y ].type = 0;
        }   
    }
}

void Field::randomColors() {
    Color cols[] = {GREEN,YELLOW,RED,WHITE,BLUE};
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            cell[ x ][ y ].color = cols[ GetRandomValue(0,4)];
        }   
    }
}


int Field::setStart( int x, int y ) {
    if( x >= n || y >= n )
        return 1; // wrong cords;)
    if( cell[x][y].type == 3 )
        return 3; // tile is end field.

    cell[ x ][ y ].type = 2;
    cell[ x ][ y ].drawLetter = true;

    start.x = x; start.y = y;
    return 0; // everything ok;
}

int Field::setEnd( int x, int y ) {
    if( x >= n || y >= n )
        return 1; // wrong cords;)
    if( cell[x][y].type == 2 )
        return 2; // tile is start field.

    cell[ x ][ y ].type = 3;
    cell[ x ][ y ].drawLetter = true;

    end.x = x; end.y = y;
    return 0; // everything ok;
}

void Field::detectCollision( int selected ) {
    Tile auxtile(side*n, pos, 0, 0 );
    
    int x = GetMouseX();
    int y = GetMouseY();
    
    if( !IsMouseButtonDown( MOUSE_LEFT_BUTTON ) || !auxtile.inside( x, y ) )
        return;
    
    x -= pos.x;
    y -= pos.y;

    x /= side;
    y /= side;

    // eliminate unwanted changing of tile every frame
    float timediff = GetTime() - lastedited.z;
    if( (float) x == lastedited.x && (float)y == lastedited.y && timediff < 0.5 )
        return;
    // we dont want to edit end/start tiles ( cause of possible mistakes)
    if( cell[x][y].type == 2 || cell[x][y].type == 3 )
        return;
    
    // swirch blocked/empty tiles
    if( selected == 0 ) {
        int initstate = cell[x][y].type;
        if( initstate == 1 )
            cell[x][y].type = 0;
        else
            cell[x][y].type = 1;
        
        lastedited = { (float)x , (float)y , (float)GetTime()};
        return;
    }

    cell[x][y].type = selected;
    cell[x][y].drawLetter = 1;

    if( selected == 2 ) {
        cell[start.x][start.y].type = 0;
        cell[start.x][start.y].drawLetter = false;
        start.x = x; start.y = y;
    }

    if( selected == 3 ) {
        cell[end.x][end.y].type = 0;
        cell[end.x][end.y].drawLetter = false;
        end.x = x; end.y = y;
    }
}
#endif
