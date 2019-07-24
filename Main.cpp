#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "ccardheader.h"
#include "cplayerheader.h"
#include "cgameheader.h"
using namespace std;

int main() {
	//Start a new game
	CGame newgame("wizard.txt", "sorceress.txt");
	newgame.startgame();
	while (!newgame.gameover()) {
		newgame.currentround();
	}
	system("pause");
}