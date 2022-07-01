#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <queue>
#include "tile.hpp"
#include "constants.hpp"
#include "field.hpp"
#include "../include/raylib.h"

class Astar {
public:
    Field *field = NULL;
    int n;                 // number of tiles in 1 axis
    int dist = 0;          // how long is the shortest path
    std::queue<Point> kol; // queue of the bfs

    Astar(int _n);      // constructor
    void reset();                 // remove everything from queue
    int init(Point first);        // clear the queue and the tiles, source tile
    int step();                   // make step. 0 - no step made, 1 - step made, 2 - found the way
    void foundPath(Point start);  // processing after finding the path
    bool checkCell(int a, int b); // check if cell can be entered
};

Astar::Astar( int _n ) {
    n = _n;
}

void Astar::reset() {
    while( !kol.empty() ) kol.pop();
    field->resetAll();
}

int Astar::init( Point first ) {
    reset();
    kol.push( first );
    field->cell[first.x][first.y].visited = true;
    return 0;
}

bool Astar::checkCell( int a, int b ) {
    
    bool inside = (a >=0 && a < n  && b >= 0 && b < n);
    if( !inside ) return false;
    bool startis = !( field->cell[a][b].visited );
    bool notempty = ( field->cell[a][b].type == 0 );
    return ( inside && startis && notempty );
}

void Astar::foundPath( Point pos ) {
    while( !kol.empty() )
        kol.pop();
    dist = 1;
    while( !(pos == field->start ) ) {
        std::cout << pos.x << " " << pos.y << "\n";
        field->cell[ pos.x ][ pos.y ].type = 6;
        pos = field->cell[ pos.x ][ pos.y ].from;
        dist++;
    }
}

int Astar::step() {
    if( kol.empty() ) return 0;

    Point act = kol.front(); kol.pop();
    if( field->cell[act.x][act.y].type != 2 )
        field->cell[act.x][act.y].type = 5; // make cell proccessed
    
    Point poss[4] = {{0,1},{1,0},{-1,0},{0,-1}};
    
    int begSize = kol.size();
    bool anyChange = false;
    for( Point nx : poss ) {
        Point temp( act.x+nx.x , act.y+nx.y);

        if( temp.x == field->end.x && temp.y == field->end.y ) {
            foundPath( act );
            return 2;
        }

        if( checkCell( temp.x, temp.y ) ) {
            kol.push( Point( temp.x, temp.y ) ); // add tile to queue

            field->cell[ temp.x ][ temp.y ].type = 4; // tile is now active
            field->cell[ temp.x ][ temp.y ].visited = true;
            field->cell[ temp.x ][ temp.y ].from = act;
        }
    }

    return 1;
}


#endif
