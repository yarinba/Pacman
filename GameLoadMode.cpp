#include "GameLoadMode.h"

int GameLoadMode::getNumberFromLine(string line) {
	auto it = line.find(':');
	string tempLine = line.substr(it + 1);
	int res = std::stoi(tempLine);
	return res;
}

void GameLoadMode::getDataFromResultFile() {
	iterationsOfDeath.clear();
	string line;
	while (!resultFile.eof()) {
		getline(resultFile, line);
		auto it = line.find(':');
		// D symbolize Died
		if (line[0] == 'D') {
			iterationsOfDeath.push_back(getNumberFromLine(line));
		} 
		// D symbolize Finished
		else if (line[0] == 'F') {
			interationOfFinish = getNumberFromLine(line);
		}
	}
}

void GameLoadMode::getStepsAndResultFiles() {
	stepsFilesNames.clear();
	resultFilesNames.clear();
	string path = "./";
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		string str = entry.path().string();
		if (str.find(".steps") != string::npos) {
			string str1 = str;
			stepsFilesNames.push_back(str1);
		}
		else if (str.find(".result") != string::npos) {
			string str1 = str;
			resultFilesNames.push_back(str1);
		}
	}
}

void GameLoadMode::openRecordingFiles(string stepsFileName) {
	stepsFile.open(stepsFileName, std::fstream::in);
	string resultFileName = std::regex_replace(stepsFileName, std::regex("steps"), "result"); // replace 'steps' -> 'result'
	resultFile.open(resultFileName, std::fstream::in);
}

string GameLoadMode::getScreenFile(string stepsFileName) {
	return std::regex_replace(stepsFileName, std::regex("steps"), "screen"); // replace 'steps' -> 'screen'
}

void GameLoadMode::play() {
	getScreenFiles();
	getStepsAndResultFiles();
	init();
	int filesSize = stepsFilesNames.size();

	while ((currFile < filesSize) && (!isLose)) {
		openRecordingFiles(stepsFilesNames[currFile]);

		eatenBreadcrumbs = 0;
		isWon = false;
		map.init(getScreenFile(stepsFilesNames[currFile]));

		initCreatures();
		setGhostsLevel('1'); // Set to novice - Irrelevant
		getDataFromResultFile();
		try {
			run();
		}
		catch (string& err) {
			string screenName = getScreenFile(stepsFilesNames[currFile]);
			throw string("Test Failed at screen " + screenName + " - " + err);
		}
		closeRecordingFiles();
		currFile++;
	}
	Print::successfulTest();
}

void GameLoadMode::handleGhostMovement(string line) {
	Direction ghostDir = getDirEnum(line.back());
	int ghostNum = line[5] - '0';
	bool isBreadcrumbPos = (map.getPoint(ghosts[ghostNum]->getPos()) == '*');
	ghosts[ghostNum]->Creature::move(ghostDir, isBreadcrumbPos, isSilentMode);
}

void GameLoadMode::handlePacmanMovement(string line) {
	Direction pacmanDir = getDirEnum(line.back());
	pacman.setDirection(pacmanDir);
	pacman.move(map.getRowSize(), map.getColSize(), isSilentMode);
}

void GameLoadMode::manageFruit(string line) {
	//Fruit Appearance
	if (line.find("Appearance") != string::npos) {
		size_t openBracket = line.find_last_of('(');
		size_t comma = line.find_last_of(',');
		size_t closeBracket = line.find_last_of(')');

		string x = line.substr(openBracket + 1, comma - openBracket - 1);
		string y = line.substr(comma + 1, closeBracket - comma - 1);

		fruit.create(line[17], stoi(x), stoi(y));
	}
	//Fruit Disappearance
	else if (line.find("Disappearance") != string::npos) {
		// Check Pacman hit Fruit
		if (pacman.getPos() == fruit.getPos())
			increaseScore(fruit.getFruitVal(), isSilentMode);
		fruit.setIsAlive(false, map.getPoint(fruit.getPos()) == '*');
	}
	//Fruit Move
	else {
		Direction fruitDir = getDirEnum(line.back());
		bool isBreadcrumbPos = (map.getPoint(fruit.getPos()) == '*');
		fruit.Creature::move(fruitDir, isBreadcrumbPos, isSilentMode);
	}
}

void GameLoadMode::run() {
	int numOfIterations = 0;
	string line;

	if (!isSilentMode) {
		clear_screen();
		map.draw();
		Print::score(*this);
		Print::lives(*this);
	}

	while (!isLose && !isWon && !stepsFile.eof()) {
		getline(stepsFile, line);
		switch (line[0]) {
		case 'P':
			handlePacmanMovement(line);
			numOfIterations++;
			break;
		case 'G':
			handleGhostMovement(line);
			break;
		case 'F':
			manageFruit(line);
			break;
		default:
			break;
		}

		// Check if pacman ate breadcrumb
		if (isBreadcrumb()) {
			map.setPoint(pacman.getPos(), ' ');
			eatenBreadcrumbs++;
			increaseScore(isSilentMode);
			if (eatenBreadcrumbs == map.getNumOfBreadCrumbs())
				isWon = true;
		}

		// Check if pacman hit ghost
		if (isGhost()) {
			handleHitGhost(isSilentMode);
			if (lives) {
				if (!isSilentMode) Print::lives(*this);
				bool isValidTestOfDeath = std::count(iterationsOfDeath.begin(), iterationsOfDeath.end(), numOfIterations);
				if (!isValidTestOfDeath)
					throw string(std::to_string(numOfIterations) + " is not a Death Iteration");
			}
			else {
				isLose = true;
				bool isValidTestOfFinish = interationOfFinish == numOfIterations;
				if (!isValidTestOfFinish)
					throw string(std::to_string(numOfIterations) + " is not a Finish Iteration");
			}
		}

		if (!isSilentMode) Sleep(30);
	}

	// free allocations;
	for (int i = 0; i < map.getNumOfGhosts(); i++)
		delete ghosts[i];

	if (!isSilentMode && isLose) {
		Print::lose();
		Sleep(1000);
	}
	else if (isWon) {
		bool isValidTestOfFinish = interationOfFinish == numOfIterations;
		if (!isValidTestOfFinish)
			throw string(std::to_string(numOfIterations) + " is not a Finish Iteration");

		if (!isSilentMode) {
			Print::nextScreen();
			Sleep(1000);
		}

		if (currFile >= screenFilesNames.size()) {
			if (!isSilentMode) Print::won();
		}
	}
}