#include "Print.h"

void Print::menu() {
	clear_screen();
	setTextColor(Color::WHITE);
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> WELCOME TO PACAMAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "1. Start a new game (with colors)" << std::endl
		<< "2. Start a new game (without colors)" << std::endl
		<< "8. Present instructions and keys" << std::endl
		<< "9. EXIT" << std::endl;
}


void Print::instructions() {
	clear_screen();
	setTextColor(Color::WHITE);
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

void Print::lose() {
	clear_screen();
	setTextColor(Color::WHITE);
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> OH! TOO BAD - YOU LOSE <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;
}

void Print::won() {
	clear_screen();
	setTextColor(Color::WHITE);
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> CONGRATULATIONS - YOU WON! <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;

}

void Print::pause(const Game& game) {
	Point information(game.map.getDataPos());
	setTextColor(Color::WHITE);
	gotoxy(information.getX(), information.getY() + 2);
	std::cout << "Game Paused";
}

void Print::clearPause(const Game& game) {
	Point information(game.map.getDataPos());
	gotoxy(information.getX(), information.getY() + 2);
	std::cout << "           ";
}

void Print::chooseMode() {
	setTextColor(Color::WHITE);
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> Game Mode <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Please choose the mode of the game:" << std::endl
		<< "1. Play on all screens" << std::endl
		<< "2. Play on a specific screen" << std::endl;
}

void Print::chooseLevel() {
	setTextColor(Color::WHITE);
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> Difficulty Level <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Please choose the difficulty level of the game:" << std::endl
		<< "1 - Novice" << std::endl
		<< "2 - Good" << std::endl
		<< "3 - Best" << std::endl;
}

void Print::noFiles() {
	setTextColor(Color::WHITE);
	clear_screen();
	std::cout << "No files found!" << std::endl;
}

void Print::score(const Game& game) {
	Point information(game.map.getDataPos());
	gotoxy(information.getX(), information.getY());
	setTextColor(Color::WHITE);
	std::cout << "SCORE: ";

	if (game.isColored) setTextColor(Color::GREEN);
	std::cout << game.score;
}

void Print::lives(const Game& game) {
	Point information(game.map.getDataPos());
	gotoxy(information.getX(), information.getY() + 1);
	setTextColor(Color::WHITE);
	std::cout << "LIVES:    ";

	gotoxy(information.getX() + 7, information.getY() + 1);
	if (game.isColored) setTextColor(Color::RED);
	for (int i = 0; i < game.lives; i++) {
		std::cout << HEART;
	}
}

void Print::successfulTest() {
	setTextColor(Color::WHITE);
	clear_screen();
	std::cout << ">>> Test passed successfully ! <<<" << std::endl;
}

void Print::nextScreen() {
	setTextColor(Color::WHITE);
	clear_screen();
	std::cout << ">>> Move on to the next screen <<<" << std::endl;
}
 