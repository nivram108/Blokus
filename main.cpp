#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "shapes.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */

using namespace std;

int bestA, bestB;
vector<shape> shapes, shapesA, shapesB;

int first_step_flag_A = 0;
int first_step_flag_B = 0;
int *first_step_pointer;

int pieces_A[21] = {0};
int pieces_B[21] = {0};
int *pieces_pointer;

void command()
{
    // string cmd="E";
    int instr;
    int instr_counter = 0;
    int shapeID, x, y;
    char junk, player;
    shape selected = shapes[0];
    bool legalMove = false;
    bool turn = true, isSelect = false;
    first_step_pointer = &first_step_flag_A;

    int endCounter = 0;
    while (true) {
    	cout << endl;
        player = (turn)?'A':'B';
        pieces_pointer = (player == 'A')? pieces_A : pieces_B;

        // check if player still have move to implement.
        if (endCounter == 2) {
            cout<<"Game is ended."<<endl;
            return;
        }
        if (checkgame(player) == false) {
            isSelect = false;
            turn = !turn;
            endCounter++;
        }
        else {
            endCounter = 0;
	        cout << "| [instruction #" << instr_counter << "] you can press 1~7:" <<"\n|\n";
	        cout << "|\t1) Select Shape\n|\t2) Flip\n|\t3) Turn_clockwise\n|\t4) player_Move\n|\t5) Print_map\n|\t6) List_shapes\n|\t7) check condition\n|\t999) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";

	        cin >> instr;
	        if (instr == 999)
	            break;
	        if (instr == 1) {		// select shape.
	            isSelect = true;
	            cout<<"shape index:";
	            int tmpID;
	            cin>>tmpID;

	            if (checkindex (tmpID)) {
	            	if (pieces_pointer[tmpID] == 0) {
	            		cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
	            		continue;
	            	}
	            	else {
	            	    shapeID = tmpID;
			            if(player == 'A')
			                selected = shapesA[shapeID];
			            else
			                selected = shapesB[shapeID];
			            selected.printShape();
	            	}
	            }
	            else {
	            	cout << "no this index! re do instruction!." << endl;
	            	continue;
	            }
	        }
	        else if (instr == 2) {	// Flip
	        	if (isSelect == false) {
	        		cout << "Please Select a shape." << endl;
	                continue;
	        	}
	            selected.flip();
	            selected.printShape();
	        }
	        else if (instr == 3) { // Turn
	        	if (isSelect == false) {
	        		cout << "Please Select a shape." << endl;
	                continue;
	        	}
	            selected.turnClockwise();
	            selected.printShape();
	        }
	        else if (instr == 4) { //player_move.
	            cout << "shapeID:" << shapeID << endl;
	            printMap();
	            if (isSelect == false) {	//Hasn't select yet
	                cout << "Please Select a shape." << endl;
	                continue;
	            }
	            selected.printShape();
	            int x, y;
                cout << "[ " << player << "'s turn ] input x, y:";
                cin >> x >> y;
	            legalMove = playerMove(selected, shapeID, player, x, y);
	            if (legalMove == true) {
	                pieces_pointer[shapeID] = 0;
	            	instr_counter++;
	                isSelect = false;
	                turn = !turn;
	            }
	        }
	        else if (instr == 5) {	//map.
	            printMap();
	        }
	        else if (instr == 6) {	//list shape.
	            listShapes(player);
	        }
	        else if (instr == 7) {
	        	checkgame(player);
	        }
	        else {
	            cout<<"Not a command."<<endl;
	        }
	    }
    }

}

void PK()
{
    int instr;
    int instr_counter = 0;
    int shapeID, x, y;
    char junk, player;
    shape selected = shapes[0];
    bool legalMove = false;
    bool turn = true, isSelect = false;
    first_step_pointer = &first_step_flag_A;
    int endCounter = 0;
    while (true) {
        if (turn == 0) {
            autoPlay('B');
            turn = !turn;
            continue;
        }
    	cout << endl;
        player = (turn)?'A':'B';
        pieces_pointer = (player == 'A')? pieces_A : pieces_B;

        // check if player still have move to implement.
        if (endCounter == 2) {
            cout << "Game is ended." << endl;
            return;
        }
        if (checkgame(player) == false) {
            isSelect = false;
            turn = !turn;
            endCounter++;
        }
        else {
            endCounter = 0;
	        cout << "| [instruction #" << instr_counter << "] you can press 1~7:" <<"\n|\n";
	        cout << "|\t1) Select Shape\n|\t2) Flip\n|\t3) Turn_clockwise\n|\t4) player_Move\n|\t5) Print_map\n|\t6) List_shapes\n|\t7) check condition\n|\t999) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";

	        cin >> instr;
	        if (instr == 999)
	            break;
	        if (instr == 1) {		// select shape.
	            isSelect = true;
	            cout << "shape index:";
	            int tmpID;
	            cin >> tmpID;

	            if (checkindex (tmpID)) {
	            	if (pieces_pointer[tmpID] == 0) {
	            		cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
	            		continue;
	            	}
	            	else {
	            	    shapeID = tmpID;

			            if (player == 'A')
			                selected = shapesA[shapeID];
			            else
			                selected = shapesB[shapeID];
			            selected.printShape();
	            	}
	            }
	            else {
	            	cout << "no this index! re do instruction!." << endl;
	            	continue;
	            }
	        }
	        else if (instr == 2) {	// Flip
	            selected.flip();
	            selected.printShape();
	        }
	        else if (instr == 3) { // Turn
	            selected.turnClockwise();
	            selected.printShape();
	        }
	        else if (instr == 4) { //player_move.
	            cout << "shapeID:" << shapeID << endl;
	            printMap();
	            if (isSelect == false) {	//Hasn't select yet
	                cout<<"Please Select a shape."<<endl;
	                continue;
	            }
	            selected.printShape();

	            int x, y;
                cout << "[ " << player << "'s turn ] input x, y:";
                cin >> x >> y;
	            legalMove = playerMove(selected, shapeID, player, x, y);
	            if (legalMove == true) {
	                pieces_pointer[shapeID] = 0;

	            	instr_counter++;
	                isSelect = false;
	                turn = !turn;
	            }
	        }
	        else if (instr == 5) {	//map.
	            printMap();
	        }
	        else if (instr == 6) {	//list shape.
	            listShapes(player);
	        }
	        else if (instr == 7) {
	        	checkgame(player);
	        }
	        else {
	            cout<<"Not a command."<<endl;
	        }
	    }
    }
}

int main()
{
    srand(time(NULL));
    bool flag = false;
    init();
    int mode;

    cout << "Game Start." << endl << endl;
    cout << "|--------------------------------- |" << endl;
    cout << "|   " << endl << "| Select Mode:" << "\n|\n";
    cout << "|\t1) Player\n|\t2) Auto\n|\t3) PK\n|\t4) See Priority Advantage\n|" << endl;
    cout << "|--------------------------------- \n";
    cout << "Blokus>>";

    cin >> mode;
    bool pause = false;
    if (mode == 1) {	// player
        command();
        pause = true;
    }
    else if (mode == 2)
        autoGame();
    else if (mode == 3)
        PK();
    else {
        int winA = 0, winB = 0, games;
        cout << "|---------------------------------|" << endl;
        cout << "|   "<<endl<<"| Select Number of Games:" << "\n|\n";
        cout << "|\t1) 1K\n|\t2) 10K\n|\t3) 100K\n|" << endl;
        cout << "|--------------------------------- \n";
        cout << "Blokus>>";

        cin >> games;
        if (games == 1) games = 1000;
        else if (games == 2) games = 10000;
        else if (games == 3) games = 100000;

        bool change = false;
        while (games--) {
            init();
            autoGame();
            cout << games << " to go....";
            if (winner() == "A")
                winA++;
            else
                winB++;
            change = !change;
        }

        cout << "|---------------------------------| " << endl;
        cout << "|   " << endl << "| Result :" << "\n|\n";
        cout << "| " << winA << " : " << winB << "\n|" << endl;
        cout << "|   " << endl << "| Best Game :" << "\n|\n";
        cout << "| " << bestA << " : " << bestB << "\n|" << endl;
        cout << "|--------------------------------- \n";
    }
    string s = "";

    while (s != "seeResult" && pause) {
        cout << endl;
        cout << "|--------------------------------- |" << endl;
        cout << "|   " << endl << "| Please input string : seeResult" << "\n";
        cout << "|" << endl;
        cout << "|--------------------------------- \nBlokus>>";
        cin >> s;
    }

    printMap();
    cout << "|--------------------------------- |" << endl;
    cout << "|   " << endl << "| Player " << winner() << " wins." << "\n";
    cout << "|" << endl;
    cout << "|--------------------------------- \nBlokus>>";
    return 0;
}
