#pragma once

#include "Game.h"

class GameLoadMode : public Game {

public:
	void play() override { std::cout << "Need To Implement" << std::endl; };
	void run() override { std::cout << "Need To Implement" << std::endl; };
	void manageFruit(int numOfIterations) override { std::cout << "Need To Implement" << std::endl; };
	void handleGhostsMovement(int numOfIterations) override { std::cout << "Need To Implement" << std::endl; };
};