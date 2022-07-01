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
}

void Bfs::reset() {
    while( !kol.empty() ) kol.pop();
    path.clear();
    field->resetAll();
}

int Bfs::init( Point first ) {
    reset();
    kol.push( first );
    field->cell[first.x][first.y].visited = true;
    return 0;
}

bool Bfs::checkCell( int a, int b ) {
    
    bool inside = (a >=0 && a < n  && b >= 0 && b < n);
    if( !inside ) return false;
    bool startis = !( field->cell[a][b].visited );
    bool notempty = ( field->cell[a][b].type == 0 );
    return ( inside && startis && notempty );
}

void Bfs::foundPath( Point start ) {
    std::cout << "ASDASD\n";
    return;
}

int Bfs::step() {
    if( kol.empty() ) return 0;
    std::cout << "step\n";

    Point act = kol.front(); kol.pop();
    if( field->cell[act.x][act.y].type != 2 )
        field->cell[act.x][act.y].type = 5; // make cell proccessed
    
    Point poss[4] = {{0,1},{1,0},{-1,0},{0,-1}};
    
    for( Point nx : poss ) {
        Point temp( act.x+nx.x , act.y+nx.y);
        if( checkCell( temp.x, temp.y ) ) {
            kol.push( Point( temp.x, temp.y ) );
            if( temp.x == field->end.x && temp.y == field->end.y ) {
                foundPath( Point( temp.x , temp.y ) );
                return 2;
            }
            field->cell[ temp.x ][ temp.y ].type = 4; // tile is now active
            field->cell[ temp.x ][ temp.y ].visited = true;
        }
    }

    return 1;
}


#endif
