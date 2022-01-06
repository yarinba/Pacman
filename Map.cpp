#include "Map.h"


void Map::init(string fileName) {
	numOfBreadCrumbs = 0;
	numOfGhosts = 0;
	for (int i = 0; i < MapBoundaries::Y; i++)
		strcpy(map[i], "                                                                                ");
	pacmanPos.set(-1, -1);
	dataPos.set(-1, -1);
	for (int i = 0; i < 4; i++)
		GhostPos[i].set(-1, -1);

	getBoard(fileName);
}

/*Reading a map from the requested file*/
void Map:: getBoard(string fileName)
{
	std::fstream myfile(fileName);
	std::string line;
	rowSize = 0;
	int i = 0, currMapCol = 0, searchData = 0;
	getline(myfile, line);
	colSize=line.size();
	while (!myfile.eof()) { 
		if (line.size()<colSize)  
		{
			std::cout << "Error: Unvalid board" << std::endl;
			exit(1);
		}
		else
		{
			while (currMapCol < colSize) {
				if (line[i] == '&') {
					handleLegend(myfile, line, currMapCol, i);
					dataPos.set(i, rowSize);
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
		}
		i = 0;
		getline(myfile, line);
	}

	myfile.close();

	checkMap();
	
}

/*inserting values to the map array and set the positions of pacman and the ghosts according to the signs in the file*/
void Map::handleChar(char value, int& currCol )
{
	try {
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
			if (GhostPos[3].getX() != -1)
				throw "There are more than 4 ghosts";
			map[rowSize][currCol] = '$';
			GhostPos[numOfGhosts].set(currCol, rowSize);
			numOfGhosts++;
			break;
		case '@':
			if (pacmanPos.getX() != -1)
				throw "There is more than one pacman";
			map[rowSize][currCol] = '@';
			pacmanPos.set(currCol, rowSize);
			break;
		default:
			break;
		}
	}
	catch (const char* error) {
		clear_screen();
		std::cout << "Error:" <<error<<std::endl;
		exit(1);
	}
	currCol++;
	
}

/*handles the & sign in the map*/
void Map::handleLegend(std::fstream& myfile,std::string &line,int &mapCol,int &currChar)
{
	if (dataPos.getX() != -1)
	{
		std::cout << "Error:There is more than one legend" << std::endl;
		exit(1);
	}
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
	}
}

/*This function drawing each symbol according to the color we set for it*/
void Map::draw() const {
	
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize+ 1; j++) {
			gotoxy(j,i);
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


void Map::checkMap() {
	if (pacmanPos.getX() == -1)
	{
		std::cout<<"Error: There is no Pacman symbol"<<std::endl;
		exit(1);
	}
	if (GhostPos[1].getX() == -1)
	{ 
		std::cout<<"Error: There are less than 2 ghosts"<<std::endl;
		exit(1);
	}
	if (dataPos.getX() == -1)
	{
		std::cout << "Error: There is no legend in the file" << std::endl;
		exit(1);
	}
	if((rowSize>25)||(colSize>80))
	{
		std::cout << "Error: The board is larger than the maximum size allowed" << std::endl;
		exit(1);
	}
}

