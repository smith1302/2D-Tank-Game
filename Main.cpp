#include "stdafx.h"
#include "World.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	bool playAgain = true;
	while (playAgain) {

		int width = 79;
		int height = 20;
		int numPlayers = 0;
		int gravity = 50;
		while (numPlayers < 2 || numPlayers > 5) {
			cout << "How many Players? (2-5)" << endl;
			cin >> numPlayers;
			if (numPlayers < 2 || numPlayers > 5) {
				cout << "Invalid Choice" << endl;
			}
		}

		World w(numPlayers, width, height, 4, 4, gravity);
		w.init();
		w.mainLoop();

		cout << endl << endl;

		cout << "Game Over!" << endl << "Congratulations, Player " << w.getWinningPlayer() << ", you won!" << endl;
		string response;
		cout << "Do you want to continue? (Y/N)";
		cin >> response;
		if (response == "N" || response == "n") {
			break;
			playAgain = false;
		}
		system("cls");
	}
	//l.showPositions();
}