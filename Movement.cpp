#include "Movement.h"

string Movement::pathMoves(const Map& map, const Point& src, const Point& dest) {
    // Stores the moves of the directions of adjacent cells
    const int dRow[4] = { -1, 0, 0, 1 };
    const int dCol[4] = { 0, -1, 1, 0 };
    const int rowSize = map.getRowSize();
    const int colSize = map.getColSize();

    // Stores the distance for each cell from the source cell
    int d[MapBoundaries::Y][MapBoundaries::X];
    memset(d, -1, sizeof d);

    // Distance of source cell is 0
    d[src.getY()][src.getX()] = 0;

    // Initialize a visited array
    bool visited[MapBoundaries::Y][MapBoundaries::X];
    memset(visited, false, sizeof visited);

    // Mark source cell as visited
    visited[src.getY()][src.getX()] = true;

    // Create a queue for BFS
    queue<Node> q;

    // Distance of source cell is 0
    Node s = { src, 0 };

    // Enqueue source cell
    q.push(s);

    // Iterate until queue is not empty
    while (!q.empty()) {

        // Deque front of the queue
        Node curr = q.front();
        Point pt = curr.pt;
         
        // If the destination cell is reached, then find the path
        if (pt == dest) {

            int xx = pt.getX(), yy = pt.getY();
            int dist = curr.dist;

            // Assign the distance of destination to the distance matrix
            d[pt.getY()][pt.getX()] = dist;

            // Stores the smallest path
            string pathmoves = "";

            // Iterate until source is reached
            while (xx != src.getX() || yy != src.getY()) {

                // Append D
                if (yy > 0 && d[yy - 1][xx] == dist - 1) {
                    pathmoves += 'D';
                    yy--;
                }

                // Append U
                if (yy < rowSize - 1 && d[yy + 1][xx] == dist - 1) {
                    pathmoves += 'U';
                    yy++;
                }

                // Append R
                if (xx > 0 && d[yy][xx - 1] == dist - 1) {
                    pathmoves += 'R';
                    xx--;
                }

                // Append L
                if (xx < colSize - 1 && d[yy][xx + 1] == dist - 1) {
                    pathmoves += 'L';
                    xx++;
                }
                dist--;
            }

            // Reverse the backtracked path
            reverse(pathmoves.begin(), pathmoves.end());

            return pathmoves;
        }

        // Pop the start of queue
        q.pop();

        // Explore all adjacent directions
        for (int i = 0; i < 4; i++) {
            int row = pt.getY() + dRow[i];
            int col = pt.getX() + dCol[i];

            // If the current cell is valid cell and can be traversed
            if (map.isInBoundaries(row, col) &&
                (map.getPoint(Point(col, row)) != '#') && 
                !visited[row][col]) {

                // Mark the adjacent cells as visited
                visited[row][col] = true;

                // Enqueue the adjacent cells
                Node adjCell = { Point(col, row), curr.dist + 1 };
                q.push(adjCell);

                // Update the distance of the adjacent cells
                d[row][col] = curr.dist + 1;
            }
        }
    }

    // If the destination is not reachable
    return "NONE";
}

Direction Movement::calculateNextMoveBFS(const Map& map, const Point& src, const Point& dest) {
    string path = pathMoves(map, src, dest);
    switch (path[0]) {
    case 'D':
        return Direction::DOWN;
    case 'U':
        return Direction::UP;
    case 'R':
        return Direction::RIGHT;
    case 'L':
        return Direction::LEFT;
    case 'N':
    default:
        return Direction::NONE;
    }
}

/*
* (*) Will change direction of entity if one of the following occurs:
*		1. Every 20 iterations
*		2. if the entity hit a wall / invisible tunnel
*		3. currrent direction is NONE
*/
bool Movement::noviceMove(Creature& entity, const Map& map, int iterationNumber) {
    bool everyTwentyIterations = !(iterationNumber % 20);
    bool noDirection = entity.getDirection() == Direction::NONE ? true : false;

    if (everyTwentyIterations || noDirection)
        entity.setDirection();

    bool isWall = map.isWall(entity.getPos(), entity.getDirection(), false);
    bool isInBoundaries = map.isInBoundaries(entity.getPos().getY(), entity.getPos().getY());
    while (isWall || !isInBoundaries) {
        entity.setDirection();
        isWall = map.isWall(entity.getPos(), entity.getDirection(), false);
        isInBoundaries = map.isInBoundaries(entity.getPos().getY(), entity.getPos().getY());
    }

    bool isBreadcrumbPos = (map.getPoint(entity.getPos()) == '*');
    return isBreadcrumbPos;
}