#pragma once

enum class Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15,
};

enum class Direction {
	NONE = -1,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STAY
};

enum MapBoundaries { X = 80, Y = 25 };

enum class ScreenMode {
	ALL_FILES,
	ONE_FILE
};

enum class FlagsMode {
	REGULAR,
	SAVE,
	LOAD,
	LOAD_SILENT
};

