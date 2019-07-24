#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "ccardheader.h"
#include "cplayerheader.h"

//Game class
class CGame {
private:
	int mRound = 0;
	int mRoundlimit = 30;
	CPlayer* wizard;
	CPlayer* sorceress;
public:
	void startgame();
	CGame(std::string wizardfileLoc, std::string sorceressfileLoc);
	//Counts each round
	int currentround();
	//Checks if game meets game over conditions
	bool gameover();
};

//Start of a new game
void CGame::startgame() {
	std::cout << "Aadil Mohammed	Firebrick" << std::endl;
	std::cout << std::endl << "Start game!" << std::endl;
	sorceress->readFromFile();
	wizard->readFromFile();
	std::cout << "Sorceress begins with	";
	sorceress->drawcard();
	std::cout << "Wizard begins with	";
	wizard->drawcard();
}

//Copies player and passes file location
CGame::CGame(std::string wizardfileLoc, std::string sorceressfileLoc) {
	wizard = new CPlayer(wizardfileLoc, "Wizard");
	sorceress = new CPlayer(sorceressfileLoc, "Sorceress");
}

//Counts each round
int CGame::currentround() {
	//Round 1
	mRound++;
	std::cout << std::endl << "Round	" << mRound << std::endl;

	//Sorceress' turn
	std::cout << "Sorceress draws	";
	sorceress->drawcard();
	sorceress->attackplayer(wizard);
	//Wizard's turn
	std::cout << "Wizard draws	";
	wizard->drawcard();
	wizard->attackplayer(sorceress);
	return mRound;
}
//Checks if game meets game over conditions
bool CGame::gameover() {
	if (mRound == mRoundlimit || wizard->isDead() || sorceress->isDead()) {
		return true;
	}
	return false;
}
