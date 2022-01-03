#include "GamePlayMode.h"

void GamePlayMode::openRecordingFiles(string screenFileName) {
	string stepsFileName = std::regex_replace(screenFileName, std::regex("screen"), "steps"); // replace 'screen' -> 'steps'
	stepsFile.open(stepsFileName, std::fstream::trunc | std::fstream::out);
	string resultFileName = std::regex_replace(screenFileName, std::regex("screen"), "result"); // replace 'screen' -> 'result'
	resultFile.open(resultFileName, std::fstream::trunc | std::fstream::out);
}

// Runs the game according to the mode the user chose
void GamePlayMode::play() {
	string screen;
	bool found = false;
	int filesSize = screenFilesNames.size();
	int i = 0;
	
	if (mode == ScreenMode::ONE_FILE) {
		do {
			clear_screen();
			std::cout << "Enter the screen file name" << std::endl;
			std::cin >> screen;
			while (i < filesSize) {
				if ("./" + screen == screenFilesNames[i]) {
					found = true;
					break;
				}
				i++;
			}
			i = 0;
		} while (!found);

		if (isSaveMode) openRecordingFiles(screen);

		init();
		map.init(screen);
		initCreatures();
		setGhostsLevel(ghostLevel);
		run();

		if (isSaveMode) closeRecordingFiles();
	}
	else {
		init();

		while ((currFile < filesSize) && (!isLose)) {
			if (isSaveMode) openRecordingFiles(screenFilesNames[currFile]);

			eatenBreadcrumbs = 0;
			isWon = false;
			map.init(screenFilesNames[currFile]);

			initCreatures();
			setGhostsLevel(ghostLevel);
			run();

			if (isSaveMode) closeRecordingFiles();
		}
	}
}

void GamePlayMode::
writeSteps(string creatureName, Direction dir, bool FruitAppearance, bool FruitDisappearance) {

	if (FruitAppearance) {
		string x = std::to_string(fruit.getPos().getX());
		string y = std::to_string(fruit.getPos().getY());
		string fruitVal(1, fruit.getSymbol());

		string strAppear = "Appearance " + fruitVal + " (" + x + "," + y + ")";

		stepsFile << creatureName << " " << strAppear << std::endl;
	}
	else if (FruitDisappearance)
		stepsFile << creatureName << " " << "Disappearance" << std::endl;
	else
		stepsFile << creatureName << " " << getDirChar(dir) << std::endl;
}

void GamePlayMode::writeResult(ResultType type, int pointOfTime) {
	if (type == ResultType::DIE)
		resultFile << "Died: " << pointOfTime << std::endl;
	else if (type == ResultType::FINISH)
		resultFile << "Finished: " << pointOfTime << std::endl;
}

void GamePlayMode::manageFruit(int numOfIterations) {
	bool iteration100 = numOfIterations % 200 == 100;
	bool alreadyExist = fruit.getIsAlive();
	if (!alreadyExist && iteration100) {
		createFruit();
		if (isSaveMode) writeSteps("Fruit", Direction::NONE, true);
	}
	else if (alreadyExist) {
		if (fruit.getNumOfMoves() == 60 || handleHitFruit()) {
			fruit.setIsAlive(false, map.getPoint(fruit.getPos()) == '*');
			if (isSaveMode) writeSteps("Fruit", Direction::NONE, false, true);
		} 
		else {
			if (!(numOfIterations % 3)) {
				fruit.move(map, numOfIterations);
				if (isSaveMode) writeSteps("Fruit", fruit.getDirection());
			}
		}
	}
}

/*
* Get: the number of the current iteration in the game loop
* Execute only every second loop beacuse the pace of Ghost is half the pace of the Pacman
*/
void GamePlayMode::handleGhostsMovement(int numOfIterations) {
	int numofGhosts = map.getNumOfGhosts();
	if (!(numOfIterations % 2)) {
		for (int i = 0; i < numofGhosts; i++) {
			ghosts[i]->move(map, pacman.getPos(), numOfIterations);
			if (isSaveMode) writeSteps("Ghost" + std::to_string(i), ghosts[i]->getDirection());
		}
	}
}

void GamePlayMode::run() {
	char key = ' ';
	int numOfIterations = 0;
	Direction dir;

	clear_screen();
	map.draw();
	Print::score(*this);
	Print::lives(*this);

	while (!isLose && !isWon) {
		// Move the ghosts every 2nd iteration
		handleGhostsMovement(numOfIterations);
		if (isGhost()) {
			handleHitGhost();
			if (lives) {
				Print::lives(*this);
			}
			else {
				isLose = true;
			}
			if (isSaveMode) writeResult(ResultType::DIE, numOfIterations);
		}

		manageFruit(numOfIterations);

		if (_kbhit()) {
			key = _getch();
			if (key == ESC) {
				hitESC(pacman.getDirection()); /*pause the game*/
			}
			else if ((dir = pacman.getDirection(key)) != Direction::NONE) {
				pacman.setDirection(dir);
			}
		}

		/*if pacman hits a wall than he will stop*/
		if (map.isWall(pacman.getPos(), pacman.getDirection())) {
			pacman.setDirection(Direction::STAY);
		}
		else {
			pacman.move(map.getRowSize(), map.getColSize());
		}
		if (isSaveMode) writeSteps("Pacman", pacman.getDirection());

		// Check if pacman ate breadcrumb
		if (isBreadcrumb()) {
			map.setPoint(pacman.getPos(), ' ');
			eatenBreadcrumbs++;
			increaseScore();
			if (eatenBreadcrumbs == map.getNumOfBreadCrumbs())
				isWon = true;
		}
		// Check if pacman hit ghost
		if (isGhost()) {
			handleHitGhost();
			if (lives) {
				Print::lives(*this);
			}
			else {
				isLose = true;
			}
			if (isSaveMode) writeResult(ResultType::DIE, numOfIterations);
		}
		
		numOfIterations++;
		Sleep(150);
	}

	// free allocations;
	for (int i = 0; i < map.getNumOfGhosts(); i++)
		delete ghosts[i];

	if (isLose)
	{
		Print::lose();
		key = _getch();
	}
	else if (isWon) {
		if (isSaveMode) writeResult(ResultType::FINISH, numOfIterations);
		if (mode == ScreenMode::ONE_FILE) {
			Print::won();
			key = _getch();
		}
		else if (mode == ScreenMode::ALL_FILES) {
			currFile++;
			if (currFile >= screenFilesNames.size()) {
				Print::won();
				key = _getch();
			}
		}
	}
}
