#pragma once

#include "Game.h"

class GamePlayMode : public Game {
private:
	enum class ResultType { DIE, FINISH };
	bool isSaveMode = false;
	void writeSteps(string creatureName, Direction dir, bool FruitAppearance = false, bool FruitDisappearance = false);
	void writeResult(ResultType type, int pointOfTime);
	void openRecordingFiles(string screenFileName) override;
public:
	void play() override;
	void run() override;
	void manageFruit(int numOfIterations);
	void handleGhostsMovement(int numOfIterations);
	void setIsSaveMode(bool _isSaveMode) { isSaveMode = _isSaveMode; }
};
