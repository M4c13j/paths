#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include "tile.hpp"
#include "constants.hpp"
#include "../include/raylib.h"

class Field {
public:
    int side; // side lenght of a single tile
    int n; // number of tiles in 1 axis
    Vector2 pos;
    std::vector< std::vector<Tile> > cell; // all the tiles in the field

    int start[2] = {0,0};
    int end[2] = {0,0};
    
    Field( int _n, int _side, Vector2 _pos ); 
    void drawAll(); // show all tile on the screen
    void clearAll();
    void randomColors();
    int setStart( int x, int y );
    int setEnd( int x, int y );
    void detectCollisions( int selected ); // drawing function;
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
            cell[y].push_back( cand );
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
            cell[ x ][ y ].color = WHITE;
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
    if( x >= n && y >= n )
        return 1; // wrong cords;)
    if( cell[x][y].type == 3 )
        return 3; // tile is end field.
    cell[ x ][ y ].type = 2;
    cell[ x ][ y ].drawLetter = true;
    start[0] = x; start[1] = y;
    return 0; // everything ok;
}

int Field::setEnd( int x, int y ) {
    if( x >= n && y >= n )
        return 1; // wrong cords;)
    if( cell[x][y].type == 2 )
        return 2; // tile is start field.
    cell[ x ][ y ].type = 3;
    cell[ x ][ y ].drawLetter = true;

    end[0] = x; end[1] = y;
    return 0; // everything ok;
}

void Field::detectCollisions( int selected ) {
    Tile auxtile(side, pos, 0, 0 );
    
    int x = GetMouseX();
    int y = GetMouseY();
    
    if( !IsMouseButtonPressed( MOUSE_LEFT_BUTTON ) || !auxtile.inside( x, y ) )
        return;
    
    x -= pos.x;
    y -= pos.y;

    x /= (side/n);
    y /= (side/n);

    if( selected == 0 ) {
        if( cell[x][y].type == 1 )
            cell[x][y].type == 0;
    }
}
#endif
