#ifndef TILE_HPP
#define TILE_HPP

#include "../include/raylib.h"

class Tile {
public:
    int id[2]; // position of the tile in the field
    int a; // side lenght
    Color color = WHITE; // color of the inside
    Vector2 pos; // position of the top-left corner

    Tile(); // blank tile constructor
    Tile( int _a, Vector2 _pos, int x, int y  ); // tile constructor
    void draw(); // draw a tile on the screen
};

Tile::Tile() {
    color = WHITE;
    pos = {0.0,0.0};
    id[0] = id[1] = 0;
    a = 0;
}

Tile::Tile( int _a, Vector2 _pos, int x, int y  ) {
    Color cols[] = {GREEN,YELLOW,RED,WHITE,BLUE};
    a = _a;
    pos = _pos;
    id[0] = x; id[1] = y;
    color = cols[ GetRandomValue(0,4)];
}

void Tile::draw() {
    DrawRectangle( (int)pos.x, (int)pos.y, a, a, BLACK );
    DrawRectangle( (int)pos.x+2, (int)pos.y+2, a-4, a-4, color );
}

#endif
