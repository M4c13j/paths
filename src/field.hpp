#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include "tile.hpp"
#include "../include/raylib.h"

class Field {
public:
    int side = screenHeight;
    int n = 20; // number of tiles in 1 axis

    std::vector< std::vector<Tile> > cell;
    
    Field( int _n, int _side );
    void DrawAll();
};

Field::Field( int _n, int _side ) {
    n = _n;
    side = _side;

    cell.resize( n );
    
    Tile cand;
    for(int y=0;y<n;y++) {
        for(int x=0;x<n;x++) {
            cand = Tile( side, Vector2{ (float)x * side, (float)y * side }, y*n + x );
            cell[y].push_back( cand );
        }   
    }
}

#endif
