#pragma once

#include "Point.h"
#include "Map.h"
#include "Creature.h"
#include "Enums.h"
#include "utils.h"
#include<queue>
#include<string>

using std::string;
using std::queue;

class Point;
class Map;

class Movement {
private:
    // Stores coordinates of a cell and its distance
    struct Node {
        Point pt;
        int dist;
    };

    // Function to find the shortest path from the
    // source to destination in the given  matrix
    static string pathMoves(const Map& map, const Point& src, const Point& dest);
public:
    static Direction calculateNextMoveBFS(const Map& map, const Point& src, const Point& dest);
    static bool noviceMove(Creature& entity, const Map& map, int iterationNumber);
};