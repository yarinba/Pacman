#include "Map.h"


void Map::init(string fileName) {
	numOfBreadCrumbs = 0;
	numOfGhosts = 0;
	for (int i = 0; i < MapBoundaries::Y; i++)
		strcpy(map[i], "                                                                                ");

	getBoard(fileName);
}

/*Reading a map from the requested file*/
void Map:: getBoard(string fileName)
{
	std::fstream myfile(fileName);
	std::string line;
	rowSize = 0;
	int i = 0,currMapCol=0,searchData=0,len;

	getline(myfile, line);
	colSize=line.size();
	while (!myfile.eof()) { 
		
		if ((line[i] == '&') && (size(line) <= 2))  /*if the & is at the end of the file*/
		{
			dataPos.set(i, rowSize);
			handleLegend(myfile, line, currMapCol, i);
		}
		else
		{
		
			while (currMapCol < colSize) {
				if (line[i] == '&') {
					dataPos.set(i, rowSize);
					handleLegend(myfile, line, currMapCol, i);
				}
				else if (map[rowSize][currMapCol] != '!')
					handleChar(line[i], currMapCol);
				else
					currMapCol++;
				i++;
			}

			rowSize++;
			currMapCol = 0;
			searchData = i;
			len = size(line);
			while (i < len) /*if the & is on the right side of the map*/ {
				if (line[i] == '&')
				{
					handleLegend(myfile, line, currMapCol, i);
					dataPos.set(i, rowSize);
				}
				i++;
			}
		}
		i = 0;
		getline(myfile, line);
	}

	myfile.close();
}

/*inserting values to the map array and set the positions of pacman and the ghosts according to the signs in the file*/
void Map::handleChar(char value, int& currCol )
{
	switch (value)
	{
	case '#':
		map[rowSize][currCol] = '#';
		break;
	case '%':
		map[rowSize][currCol] = ' ';
		break;
	case ' ':
		numOfBreadCrumbs++;
		map[rowSize][currCol] = '*';
		break;
	case '$':
		map[rowSize][currCol] = '$';
		GhostPos[numOfGhosts].set(currCol, rowSize);
		numOfGhosts++;
		break;
	case '@':
		map[rowSize][currCol] = '@';
		pacmanPos.set(currCol ,rowSize);
		break;
	default:
		break;
	}
	currCol++;
}

/*handles the & sign in the map*/
void Map::handleLegend(std::fstream& myfile,std::string &line,int &mapCol,int &currChar)
{
	int xStart=currChar;
	if (((currChar > 0) && (currChar < colSize)) || ((currChar == 0) && (size(line) > 2) && (line.size() <= colSize)))//if the legend is in the map
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 20; j++)
			{
				map[rowSize + i][xStart + j] = '!';
			}

		}
		mapCol++;
		mapStartingPoint.set(0, 0);
	}
	else 
		mapStartingPoint.set(0,0);


}

/*This function drawing each symbol according to the color we set for it*/
void Map::draw() const {
	
	for (int i = 0; i < rowSize; i++) {
		gotoxy(mapStartingPoint.getX(), mapStartingPoint.getY()+i);
		for (int j = 0; j < colSize+ 1; j++) {
			switch (map[i][j])
			{
			case '#':
				if (isColored) setTextColor(Color::BLUE);
				break;
			case '*':
				if (isColored) setTextColor(Color::LIGHTGREY);
				break;
			case '@':
				if (isColored) setTextColor(Color::YELLOW);
				break;
			case '$':
				if (isColored) setTextColor(Color::LIGHTMAGENTA);
				break;
			default:
				break;
			}
			if (map[i][j] == '!')
				std::cout << ' ';
			else
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
	if (isColored) setTextColor(Color::WHITE);
}

void Map::setIsColored(bool _isColored) {
	isColored = _isColored;
}

// Get: Point coordinate and new char - set the new char in same coordinate on the map
void Map::setPoint(const Point& coord, char newVal) {
	map[coord.getY()][coord.getX()] = newVal;
}

/*
* Get: Point coordinate
* Return: current symbol in same coordinate on the map
*/
char Map::getPoint(const Point& coord) const {
	return map[coord.getY()][coord.getX()];
}

/*
* Get: current position and direction
* Return: Point represents the next move of given position
*/
Point Map::calculateNextPos(Point pos, Direction dir) const {

	Point nextPos;
	switch (dir)
	{
	case Direction::UP:
		nextPos.set(pos.getX(), pos.getY() - 1);
		break;
	case Direction::DOWN:
		nextPos.set(pos.getX(), pos.getY() + 1);
		break;
	case Direction::LEFT:
		nextPos.set(pos.getX() - 1, pos.getY());
		break;
	case Direction::RIGHT:
		nextPos.set(pos.getX() + 1, pos.getY());
		break;
	case Direction::STAY:
	case Direction::NONE:
		return pos;
		break;
	default:
		break;
	}
	return nextPos;
}

/*
* Get: current position, direction and boolean if the Player is Pacman or Ghost
* Return: true if the player will hit the wall, otherwise false
*/
bool Map::isWall(Point pos, Direction dir, bool isPacman) const {
	Point nextPos = calculateNextPos(pos, dir);
	//  Ghosts cannot cross in the invisible tunnels!
	if (!isPacman) {
		int x = nextPos.getX();
		int y = nextPos.getY();
		if (y == 0 || y == rowSize - 1 || x == 0 || x == colSize - 1)
			return true;
	}
	if (getPoint(nextPos) == '#')
		return true;
	return false;
}


