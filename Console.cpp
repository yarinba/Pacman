#include "Console.h"

void Console::printScore() const {
	gotoxy(0, 23);
	setTextColor(Color::WHITE);
	std::cout << "SCORE: ";

	if (gameObj.isColored) setTextColor(Color::GREEN);
	std::cout << gameObj.score;
}

void Console::printLives() const {
	gotoxy(0, 24);
	setTextColor(Color::WHITE);
	std::cout << "LIVES:    ";

	gotoxy(7, 24);
	if (gameObj.isColored) setTextColor(Color::RED);
	for (int i = 0; i < gameObj.lives; i++) {
		std::cout << HEART;
	}
}

void Console::printMenu() const {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> WELCOME TO PACAMAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "1. Start a new Console (with colors)" << std::endl
		<< "2. Start a new Console (without colors)" << std::endl
		<< "8. Present instructions and keys" << std::endl
		<< "9. EXIT" << std::endl;
}

void Console::printInstructions() const {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> Instructions <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Goal: Guide the Pacman around the maze and eat all the breadcrumbs while avoiding the ghosts." << std::endl
		<< "Keys :" << std::endl
		<< "W - Up" << std::endl
		<< "X - Down" << std::endl
		<< "D - Right" << std::endl
		<< "A - Left" << std::endl
		<< "S - Stay" << std::endl << std::endl
		<< "Press any key to continue :)" << std::endl;

	char key = _getch();
}

void Console::printLose() const {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> OH! TOO BAD - YOU LOSE <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;
}

void Console::printWon() const {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> CONGRATULATIONS - YOU WON! <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;

}

void Console::printPause() const {
	setTextColor(Color::WHITE);
	gotoxy(40, 23);
	std::cout << ">>>> Console Paused <<<<";
	gotoxy(40, 24);
	std::cout << "Press ESC to continue";
}

void Console::clearPause() const {
	gotoxy(40, 23);
	std::cout << "                     ";
	gotoxy(40, 24);
	std::cout << "                     ";
}