#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include "raylib.h"
// constant variables
std::string TITLE = "Paths - pathfinding algorithms.";

const int screenWidth = 1300;
const int screenHeight = 800;
const int maxFPS = 60;

const int N = 20;

Color tileColors[] = {WHITE, BLACK, YELLOW, PINK, BLUE, GREEN, RED}; // available colors

// struct that is a vector2 but with integers
struct Point {
    int x,y;

    Point(){}; // empty constructor
    Point( Vector2 &lhs ) {
        x = (int)lhs.x;
        y = (int)lhs.y;
    }
    
    Point( int _x, int _y ) {
        x = _x;
        y = _y;
    }

    Vector2 ptov() {
        return Vector2{(float)x, (float)y};
    }

};

#endif