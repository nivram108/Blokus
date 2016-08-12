#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "play.h"
using namespace std;

int main()
{
	Play play;
	srand(time(NULL));
	bool flag = false;
	int mode;

	cout << "Game Start." << endl << endl;
	cout << "|--------------------------------- |" << endl;
	cout << "|   " << endl << "| Select Mode:" << "\n|\n";
	cout << "|\t1) Player v.s Player" << endl;
	cout << "|\t2) Player v.s AI"<< endl;
	cout << "|\t3) AI     v.s AI" << endl;
	cout << "|\t4) See Priority Advantage\n|" << endl;
	cout << "|--------------------------------- \n";
	cout << "Blokus>>";

	cin >> mode;
	bool pause = false;
	if (mode == 1) {	// player
		play.twoPlayers();
		pause = true;
	}
	else if (mode == 2)
		play.playerAI();
	else if (mode == 3) {
		play.twoAIs();
	}
	else {
		play.priorityAdvantage();
		return 0;
	}

	string s = "";
	while (s != "seeResult" && pause) {
		cout << endl;
		cout << "|--------------------------------- |" << endl;
		cout << "|   " << endl << "| Please input string : seeResult" << endl;
		cout << "|" << endl;
		cout << "|--------------------------------- \nBlokus>>";
		cin >> s;
	}

	play.printBoard();
	cout << "|--------------------------------- |" << endl;
	cout << "|   " << endl << "| " << play.winner() << endl;
	cout << "|" << endl;
	cout << "|--------------------------------- \nBlokus>>";
	return 0;
}
