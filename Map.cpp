#include "Map.h"



void Map::init(const char* fileName) {
	for (int i = 0; i < MAP_BOUNDARIES::Y; i++)
		strcpy(map[i], "                                                             ");

	getBoard(fileName);

}

void Map:: getBoard(const char* fileName)
{
	std::fstream myfile(fileName);
	std::string line;
	int i = 0,currMapCol=0,searchData=0,len;
	getline(myfile, line);
	if ((line[i] == '&') && (size(line) <= 2)){
		mapStartingPoint.set(0, 3);
		getline(myfile, line);
	}

	colSize = size(line);


	while (rowSize < MAP_BOUNDARIES::Y) { //change to !eof
		while (currMapCol < colSize){
			if (line[i] == '&')
			{
				dataPos.set(i, rowSize);
				handleLegend(myfile, line, currMapCol, i);
			}
			else
				handleChar(line[i], currMapCol);

			i++;
		}
		rowSize++;
		currMapCol = 0;
		searchData = i;
		len = size(line);
		while (i < len)
		{
			if(line[i]=='&')
				handleLegend(myfile, line, currMapCol, i);
			i++;
		}
		i = 0;
		getline(myfile, line);
	}

	myfile.close();
}

void Map::handleChar(char value, int& currCol)
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
		pacmanPos.set(currCol, rowSize);
		map[rowSize][currCol] = '@';
		break;
	default:
		break;
	}
	currCol++;
}

void Map::handleLegend(std::fstream& myfile,std::string &line,int &mapCol,int &currChar)
{
	int xStart=currChar;
	if ((currChar == 0) && (size(line) > 2))//the map is on the right side of the legend
		mapStartingPoint.set(20, 0);
	else if ((currChar > 0) && (currChar < colSize))//if the legend is in the map
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 20; j++)
			{
				map[rowSize + i][xStart + j] = '!';
			}
			while (mapCol < colSize)
			{
				if (mapCol == xStart)
					mapCol += 20;
				else
					handleChar(line[mapCol], mapCol);
			}
			rowSize++;
			mapCol = 0;
			getline(myfile, line);
		}
		currChar = 0;
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






