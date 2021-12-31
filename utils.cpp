#include "utils.h"

using namespace std;

#ifndef WINDOWS
void gotoxy(int x, int y) {}
int _getch(void) { return 0; }
int _kbhit(void) { return 0; }
void Sleep(unsigned long) {}
void setTextColor(Color color) {}
void hideCursor() {}
void clear_screen() {}
#else
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void clear_screen()
{
	system("cls");
}

char getDirChar(Direction dir) {
	switch (dir) {
	case Direction::DOWN:
		return 'D';
	case Direction::UP:
		return 'U';
	case Direction::RIGHT:
		return 'R';
	case Direction::LEFT:
		return 'L';
	case Direction::STAY:
		return 'S';
	case Direction::NONE:
	default:
		return 'N';
	}
}

Direction getDirEnum(char dir) {
	switch (dir) {
	case 'D':
		return Direction::DOWN;
	case 'U':
		return Direction::UP;
	case 'R':
		return Direction::RIGHT;
	case 'L':
		return Direction::LEFT;
	case 'S':
		return Direction::STAY;
	case 'N':
	default:
		return Direction::NONE;
	}
}

#endif


