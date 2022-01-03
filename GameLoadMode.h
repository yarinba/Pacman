#pragma once

#include "Game.h"

class GameLoadMode : public Game {
private:
	bool isSilentMode = false;
	vector <string> stepsFilesNames;
	vector <string> resultFilesNames;
	void getStepsAndResultFiles();
	void openRecordingFiles(string screenFileName) override;
	string getScreenFile(string stepsFileName);
public:
	void setIsSilentMode(bool _isSilentMode) { isSilentMode = _isSilentMode; }
	void play() override;
	void run() override;
	void manageFruit(string line);
	void handleGhostMovement(string line);
	void handlePacmanMovement(string line);
};