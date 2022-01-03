#include <windows.h>
#include <iostream>
#include <string>
#include "utils.h"
#include "GameManager.h"

int main(int argc, char* argv[]) {
	try {
		FlagsMode flagMode = getMode(argc, argv);
		GameManager gameManager(flagMode);
	}
	catch (string& err) {
		clear_screen();
		std::cerr << "Error: " << err << std::endl;
	}
	catch (...) {
		clear_screen();
		std::cerr << "Unknown error" << std::endl;
	}

	return 0;
}