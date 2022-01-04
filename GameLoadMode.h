#pragma once

#include "Game.h"

class GameLoadMode : public Game {
private:
	bool isSilentMode = false;
	int interationOfFinish;
	vector <int> iterationsOfDeath;
	vector <string> stepsFilesNames;
	vector <string> resultFilesNames;
	void getStepsAndResultFiles();
	void openRecordingFiles(const string& screenFileName) override;
	void getDataFromResultFile();
	int getNumberFromLine(const string& line);
	string getScreenFile(const string& stepsFileName);
public:
	void setIsSilentMode(bool _isSilentMode) { isSilentMode = _isSilentMode; }
	void play() override;
	void run() override;
	void manageFruit(const string& line);
	void handleGhostMovement(const string& line);
	void handlePacmanMovement(const string& line);
};