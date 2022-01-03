#include "GameManager.h"

GameManager::GameManager(FlagsMode _mode) : mode(_mode) {
	switch (mode) {
	case FlagsMode::REGULAR:
		regular();
		break;
	case FlagsMode::SAVE:
		save();
		break;
	case FlagsMode::LOAD:
		load();
		break;
	case FlagsMode::LOAD_SILENT:
		loadSilently();
		break;
	}
}

void GameManager::playMode() {
	bool isStartPressed = false;
	while (true) {
		do {
			isStartPressed = game->menu();
		} while (!isStartPressed);
		game->play();
	}
}

void GameManager::regular() {
	game = new GamePlayMode;
	((GamePlayMode*)game)->setIsSaveMode(false);

	playMode();
}

void GameManager::save() {
	game = new GamePlayMode;
	((GamePlayMode*)game)->setIsSaveMode(true);

	playMode();
}

void GameManager::load() {
	game = new GameLoadMode;
	((GameLoadMode*)game)->setIsSilentMode(false);

	game->play();
}

void GameManager::loadSilently() {

}

