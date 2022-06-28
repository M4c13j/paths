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

    std::vector< std::vector<Tile> > cell; // all the tiles in the field
    
    Field( int _n, int _side ); 
    void drawAll(); // show all tile on the screen
    void clearAll();
};

Field::Field( int _n, int _side ) {
    n = _n;
    side = _side;

    cell.resize( n );
    
    Tile cand;
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            cand = Tile( side, Vector2{ (float)x * side, (float)y * side }, x, y );
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

#endif
