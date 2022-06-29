#ifndef TILE_HPP
#define TILE_HPP

#include "../include/raylib.h"
#include "constants.hpp"

#include <string>

class Tile {
public:
    int type = 0;                             // 0 - empty, 1 - blocked, 2 - start, 3 - end
    bool drawLetter;                          // draw letter inside
    int id[2];                                // position of the tile in the field
    int a;                                    // side lenght
    
    Color color = WHITE;                      // color of the inside
    Vector2 pos;                              // position of the top-left corner
    
    Tile();                                   // blank tile constructor
    Tile(int _a, Vector2 _pos, int x, int y); // tile constructor
    void draw();                              // draw a tile on the screen
    bool inside(int x, int y);                // check if point is inside tile;
    bool isClicked( );
};

Tile::Tile() {
    color = WHITE;
    pos = {0.0,0.0};
    id[0] = id[1] = 0;
    a = 0;
}

Tile::Tile( int _a, Vector2 _pos, int x, int y  ) {
    a = _a;
    pos = _pos;
    id[0] = x; id[1] = y;
    color = WHITE;
    drawLetter = 0;
}

void Tile::draw() {
    DrawRectangle( (int)pos.x, (int)pos.y, a, a, BLACK );
    DrawRectangle( (int)pos.x+2, (int)pos.y+2, a-4, a-4, tileColors[ type ] );
    // DrawText( std::to_string(id[1]).c_str() , (int)pos.x+9, (int)pos.y+4, 36, BLACK );
    if( !drawLetter ) return;
    std::string st = "S", en = "E";
    if( type == 2 )
        DrawText( st.c_str() , (int)pos.x+9, (int)pos.y+4, 36, BLACK );
    if( type == 3 )
        DrawText( en.c_str() , (int)pos.x+9, (int)pos.y+4, 36, BLACK );
}

bool Tile::inside( int x, int y ) {
    if( x >= pos.x && x <= pos.x+a  && y >= pos.y && y <= pos.y+a )
        return true;
    return false;
}
bool Tile::isClicked() {
    if( !IsMouseButtonDown( MOUSE_LEFT_BUTTON ) )
        return false;
    
    int x = GetMouseX();
    int y = GetMouseY();
    return inside( x, y );
}


#endif
