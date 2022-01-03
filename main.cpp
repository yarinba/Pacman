#include <windows.h>
#include <iostream>
#include <string>
#include "utils.h"
#include "GameManager.h"

int main(int argc, char* argv[]) {
	//FlagsMode flagMode = getMode(argc, argv);
	GameManager gameManager(FlagsMode::LOAD);

	return 0;
}