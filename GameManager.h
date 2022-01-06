#pragma once

#include "Enums.h"
#include "Game.h"
#include "GamePlayMode.h"
#include "GameLoadMode.h"

class GameManager {
	FlagsMode mode;
	Game* game = nullptr;
private:
	void playMode();
	void regular();
	void save();
	void load(); 
	void loadSilently();
public:
	GameManager(FlagsMode _mode);
	~GameManager() { delete game; }
};