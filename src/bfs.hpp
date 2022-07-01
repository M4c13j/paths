#ifndef BFS_HPP
#define BFS_HPP

#include <vector>
#include <queue>
#include "tile.hpp"
#include "constants.hpp"
#include "field.hpp"
#include "../include/raylib.h"

class Bfs {
public:
    int n; // number of tiles in 1 axis
    Field *field = NULL;
    std::queue<Point> kol;        // queue of the bfs
    std::vector<Point> path;      // path from source to destination
    
    Bfs(Field pole, int _n);      // constructor
    void reset();                 // remove everything from queue
    int init(Point first);        // clear the queue and the tiles, source tile
    int step();                   // make step. 0 - no step made, 1 - step made, 2 - found the way
    void foundPath(Point start);  // processing after finding the path
    bool checkCell(int a, int b); // check if cell can be entered
};

Bfs::Bfs( Field pole, int _n ) {
    n = _n;
    field = &pole;
}

void Bfs::reset() {
    while( !kol.empty() ) kol.pop();
    path.clear();
    field->resetAll();
}

int Bfs::init( Point first ) {
    reset();
    kol.push( first );
}

bool Bfs::checkCell( int a, int b ) {
    Tile aux( n, {0,0}, 0,0 ); // simplify checking if tile is valid
    
    return (aux.inside( a, b) && !field->cell[a][b].visited );
}

void Bfs::foundPath( Point start ) {
    return;
}

int Bfs::step() {
    if( path.empty() ) return 0;

    Point act = kol.front(); kol.pop();
    field->cell[act.x][act.y].type = 5; // make cell proccessed
    
    Point poss[4] = {{0,1},{1,0},{-1,0},{0,-1}};
    
    for( Point &nx : poss ) {
        Point temp( act.x+nx.x , act.y+nx.y);
        if( checkCell( temp.x, temp.y ) ) {
            kol.push( Point( temp.x, temp.y ) );
            if( temp.x == field->end.x && temp.y == field->end.y ) {
                foundPath( Point( temp.x , temp.y ) );
                return 2;
            }
            field->cell[ temp.x ][ temp.y ].type = 4; // tile is now active
        }
    }

    return 1;
}


#endif
