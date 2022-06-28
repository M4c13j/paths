#ifndef TILE_HPP
#define TILE_HPP

#include "../include/raylib.h"

class Tile {
public:
    int id = 0;
    int a = 20; // side lenght
    Color color = WHITE; // color of the inside
    Vector2 pos{0.0,0.0}; // position of the top-left corner
    
    Tile();
    Tile( int _a, Vector2 _pos, int _id );
    void Draw();
};

Tile::Tile() {
    color = WHITE;
}

Tile::Tile( int _a, Vector2 _pos, int _id ) {
    a = _a;
    pos = _pos;
    id = _id;
}

void Tile::Draw() {

}

#endif
