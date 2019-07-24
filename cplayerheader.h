#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "ccardheader.h"
//Player class for both players
class CPlayer {
private:
	std::string fileLoc;
	int mHealth = 30;

public:
	//Player deck
	std::string name;
	std::stack <CCard> deck;
	std::vector <CCard> hand;
	std::vector <CCard> table;
	CPlayer(std::string fileLocation, std::string name);
	void attackplayer(CPlayer* enemy);
	void readFromFile();
	void drawcard();
	void takedamage(int damage) {
		mHealth = mHealth - damage;
	};
	//Checks if player is dead
	bool isDead() {
		if (mHealth <= 0) {
			return true;
		}
		else {
			return false;
		}
	}
};

//Attack player function
void CPlayer::attackplayer(CPlayer* pEnemy) {
	//Random number generator
	int randomno = (rand() % (hand.size()));
	//Random card is chosen from hand to attack enemy player directly
	pEnemy->takedamage(hand[randomno].atk);
	//Displays card name and who it attacks
	std::cout << hand[randomno].cardName << " attacks " << pEnemy->name << " with " << hand[randomno].atk << std::endl;
	//Displays enemy's health
	std::cout << pEnemy->name << " health now " << pEnemy->mHealth << std::endl;



};

//File location
CPlayer::CPlayer(std::string filelocation, std::string playername) {
	fileLoc = filelocation;
	name = playername;
};
//Deck to hand
void CPlayer::drawcard() {
	//Gets a copy of the card at the top of the deck
	CCard card = deck.top();
	//Copies card from deck to hand
	hand.push_back(card);
	std::cout << deck.top().cardName << std::endl;
	//Removes card from deck
	deck.pop();
}

void CPlayer::readFromFile() {
	//stats for cards
	int stat1;
	int stat2;
	int stat3;
	//For extracting card information from file
	std::string cardInput;
	int cardType;
	std::string cardName;
	//Reads file
	std::ifstream infile(fileLoc);
	//Making a new object
	CCard cards;
	//Reading for a file loop
	while (!infile.eof()) {
		//Cardinput put into cardtype, cardname is left as it is
		infile >> cardInput >> cardName;

		cardType = stoi(cardInput);
		//First stat is put in
		infile >> cardInput;
		stat1 = stoi(cardInput);

		//Check if card type has two stats
		if (cardType == 1 || cardType == 4 || (cardType >= 6 && cardType <= 9)) {
			infile >> cardInput;
			stat2 = stoi(cardInput);
		}
		//Check if card type has three stats
		if (cardType == 5) {
			infile >> cardInput;
			stat2 = stoi(cardInput);
			infile >> cardInput;
			stat3 = stoi(cardInput);
		}

		//Copies card into deck
		if (cardType == 1) {
			cards.cardType = cardType;
			cards.cardName = cardName;
			cards.atk = stat1;
			cards.def = stat2;

			deck.push(cards);
		}
	}
	//Close stream
	infile.close();
}