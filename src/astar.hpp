#ifndef ASTAR_HPP
#define ASTAR_HPP

#include <vector>
#include <utility> // pair lol
#include <queue>
#include <cmath>
#include "tile.hpp"
#include "constants.hpp"
#include "field.hpp"
#include "../include/raylib.h"

class Astar {
public:
    Field *field = NULL;
    int n;                 // number of tiles in 1 axis
    int dist = 0;          // how long is the shortest path
    std::priority_queue< std::pair<double,Point> > kol; // queue of the bfs

    Astar(int _n);                // constructor
    void reset();                 // remove everything from queue
    int init(Point first);        // clear the queue and the tiles, source tile
    double calcHeur(Point p, Point en);        // calculate heuristic distance
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
    field->cell[first.x][first.y].visited = true;
    field->cell[first.x][first.y].dist = 0;
    field->cell[first.x][first.y].heur = calcHeur( first, field->end );
    kol.push( { (-1)*calcHeur( first, field->end ) , first } );
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

double Astar::calcHeur( Point p, Point en ) {
    // // manhatan dist
    // double ans = abs(en.x - p.x);
    // ans += abs(en.y - p.y);
    // return ans;
    // // euclidean dist
    // double ans = std::pow(en.x - p.x,2);
    // ans += std::pow(en.y - p.y,2);
    // return std::sqrt(ans);
    // diagonal distance
    double dx = abs(en.x - p.x);
    double dy = abs(en.y - p.y);
    double ans = 1 * (dx + dy) + (std::sqrt(2)-2) * std::min(dx,dy);
    return ans;
}

int Astar::step() {
    if( kol.empty() ) return 0;

    int actdist = (-1)*kol.top().first;
    Point act = kol.top().second; kol.pop();
    if( field->cell[act.x][act.y].type != 2 )
        field->cell[act.x][act.y].type = 5; // make cell proccessed
    
    // Point poss[4] = {{0,1},{1,0},{-1,0},{0,-1}};
    Point poss[8] = {{0,1},{1,0},{-1,0},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
    
    
    int begSize = kol.size();
    for( Point nx : poss ) {
        Point temp( act.x+nx.x , act.y+nx.y);

        if( temp.x == field->end.x && temp.y == field->end.y ) {
            foundPath( act );
            return 2;
        }

        int tempdist = actdist + 1;
        if( actdist < 0 ) std::cout<< "EROREOROEOROEROER";
        if( checkCell( temp.x, temp.y ) && tempdist < field->cell[ temp.x ][ temp.y ].dist ) {
            field->cell[ temp.x ][ temp.y ].type = 4; // tile is now active
            field->cell[ temp.x ][ temp.y ].visited = true;
            field->cell[ temp.x ][ temp.y ].from = act;
            field->cell[ temp.x ][ temp.y ].dist = tempdist;
            field->cell[ temp.x ][ temp.y ].heur = calcHeur( temp, field->end ) + tempdist;
            kol.push( { (-1)*field->cell[ temp.x ][ temp.y ].heur, Point(temp.x, temp.y) } ); // add tile to queue
        }
    }

    return 1;
}


#endif
