#include "Print.h"

void Print::menu() {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> WELCOME TO PACAMAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "1. Start a new game (with colors)" << std::endl
		<< "2. Start a new game (without colors)" << std::endl
		<< "8. Present instructions and keys" << std::endl
		<< "9. EXIT" << std::endl;
}

void Print::instructions() {
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

void Print::lose() {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> OH! TOO BAD - YOU LOSE <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;
}

void Print::won() {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> CONGRATULATIONS - YOU WON! <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;

}

void Print::pause() {
	setTextColor(Color::WHITE);
	gotoxy(40, 23);
	std::cout << ">>>> Game Paused <<<<";
	gotoxy(40, 24);
	std::cout << "Press ESC to continue";
}

void Print::clearPause() {
	gotoxy(40, 23);
	std::cout << "                     ";
	gotoxy(40, 24);
	std::cout << "                     ";
}

void Print::noFiles()
{
	clear_screen();
	std::cout << "No files found" << std::endl;
}

void Print::score(const Game& game) {
	gotoxy(0, 23);
	setTextColor(Color::WHITE);
	std::cout << "SCORE: ";

	if (game.isColored) setTextColor(Color::GREEN);
	std::cout << game.score;
}

void Print::lives(const Game& game) {
	gotoxy(0, 24);
	setTextColor(Color::WHITE);
	std::cout << "LIVES:    ";

	gotoxy(7, 24);
	if (game.isColored) setTextColor(Color::RED);
	for (int i = 0; i < game.lives; i++) {
		std::cout << HEART;
	}
}

 