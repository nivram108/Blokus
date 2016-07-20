#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string>
#include "shapes.h"
<<<<<<< HEAD
#define RESET   ""
#define RED     ""      /* Red */
#define YELLOW  ""      /* Yellow */
#define MAGENTA ""      /* Magenta */
=======
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5

using namespace std;
int biggestRange = 0, bestA, bestB;
vector<shape> shapes, shapesA, shapesB;

char board[14][14];
char tmpBoard[14][14];
int shoulder[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int side[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};

int first_step_flag_A = 0;
int first_step_flag_B = 0;
int *first_step_pointer;

int pieces_A[21] = {0};
int pieces_B[21] = {0};
int *pieces_pointer;

ifstream ifs ("CurrentBoard.txt", ifstream::in);
ofstream ofs ("CurrentBoard.txt", ofstream::out);


void listShapes(char player)
{
	pieces_pointer = (player == 'A'? pieces_A : pieces_B);
    if(player == 'A')
    {
        for(int i=0;i<shapesA.size();i++)
        {
        	if(pieces_pointer[i] == 1) {
				cout << i << ":" << endl;
<<<<<<< HEAD
            	printShape(shapesA[i]);
        	}
=======
            	printShape(shapesA[i]);        		
        	} 
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
        	// else {
        	// 	cout << i << ": already used.\n\n" << endl;
        	// }
        }
    }
    else
    {
        for(int i=0;i<shapesB.size();i++)
        {
        	if(pieces_pointer[i] == 1) {
				cout << i << ":" << endl;
<<<<<<< HEAD
            	printShape(shapesB[i]);
        	}
=======
            	printShape(shapesB[i]);        		
        	} 
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
        	// else {
        	// 	cout << i << ": already used." << endl;
        	// }
        }
    }
}
void printMap()
<<<<<<< HEAD
{
=======
{	
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	cout << "|---------------------------------\n| [Map]" << endl;
    cout <<"|\t            1111"<<endl;
    cout <<"|\t  ";
    for(int i=0;i<14;i++)
    {
    	if (i == 4 || i == 9) {
    		cout << MAGENTA << i%10 << RESET;
    	} else {
    		cout << i%10;
    	}
<<<<<<< HEAD

=======
       
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
    }

    cout<<endl;

    for(int i=0;i<14;i++)
    {
        if(i>=10) {
            cout << "|\t" << 1;
        } else {
            cout << "|\t ";
        }
    	if (i == 4 || i == 9) {
    		cout << MAGENTA << i%10 << RESET;
    	} else {
    		cout << i%10;
    	}
        for(int j=0;j<14;j++)
        {
        	if(board[i][j] == 'A') {
        		cout << YELLOW << board[i][j] << RESET;
        	} else if (board[i][j] == 'B'){
        		cout << RED << board[i][j] << RESET;
        	} else {
        		cout << board[i][j];
        	}
        }
        printf("\n");
    }
    cout << "|\n|---------------------------------\n" << endl;
<<<<<<< HEAD
}

bool chackindex(int i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

bool isConnectedToShoulder(shape shp, int x, int y, char player)  // connected to a shoulder
{
=======
}

bool chackindex(int i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

bool isConnectedToShoulder(shape shp, int x, int y, char player)  // connected to a shoulder
{	
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	//cout << "*->" << *first_step_pointer << endl;
	//cout << "yo" << endl;
	if (player == 'A' && *first_step_pointer == 0 && x == 4 && y == 4){ //first move of A;
		// cout << "in connect move" << endl;
		return true;
	} else if (player == 'B' && *first_step_pointer == 0 && x == 9 && y == 9){ //first move of B;
		return true;
	} else {
	    for(int i=0;i<5;i++)//each block of the shape
	    {                //     block(x)                              block(y)                              board(x,y)
	        for(int j=0;j<4;j++)//each shoulder of the block
	        {
	            if(board[shp.x[i]+x+shoulder[j][0]][shp.y[i]+y+shoulder[j][1]] == player)
	                return true;
	        }
	    }
	}
    // cout<<"Unconneted!"<<endl;
    return false;
}

bool isTouchedBySelf(shape shp, int x, int y, char player)  // touched by itself
{
	//cout << "in touch move" << endl;
	if (player == 'A' && *first_step_pointer == 0 && x == 4 && y == 4){ //first move of A;
		return false;
	} else if (player == 'B' && *first_step_pointer == 0 && x == 9 && y == 9){ //first move of B;
		return false;
	} else {

	    for(int i=0;i<5;i++)//each block of the beside
	    {                //     block(x)                              block(y)                              board(x,y)
	        for(int j=0;j<4;j++)//each side of the block
	        {
	            if(board[shp.x[i]+x+side[j][0]][shp.y[i]+y+side[j][1]] == player)
	            {
<<<<<<< HEAD

=======
	                cout<<"Touch!"<<endl;
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	                return true;
	            }
	        }
	    }
	}
    return false;
}
bool isSpare(shape shp, int x, int y, char player)
<<<<<<< HEAD
{
=======
{	
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	//cout << "in spare move" << endl;
	if (*first_step_pointer == 0) {
		// cout << "judge by spare." << endl;
		return true;
	} else {
	    for(int i=0;i<5;i++)
	    {
	        if((shp.x[i]+x < 14 && shp.x[i]+x >= 0 && shp.y[i]+y <14 && shp.y[i]+y >= 0  && board[shp.x[i]+x][shp.y[i]+y] == '.')==false ) // the block is in board range and unoccupied
	            return false;
<<<<<<< HEAD
	    }
=======
	    }	
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	}
    return true;
}
bool isLegalMove(shape shp, int x, int y, char player)
{
	// cout << "in legal move" << endl;
    if( isConnectedToShoulder(shp, x, y, player)==false || isTouchedBySelf(shp, x, y, player)==true || isSpare(shp, x, y, player) ==false ){
        // cout << isConnectedToShoulder(shp, x, y, player) << ", " << isTouchedBySelf(shp, x, y, player) << ", " << isSpare(shp, x, y, player) << endl;
        return false;
    }
    // cout << isConnectedToShoulder(shp, x, y, player) << ", " << isTouchedBySelf(shp, x, y, player) << ", " << isSpare(shp, x, y, player) << endl;
    return true;
}
bool playerMove(shape shp, int shapeID, char player, int x, int y)
{
<<<<<<< HEAD
    //int x,y;
    char junk, cX, cY;
    //printMap();

=======
    int x,y;
    char junk, cX, cY;
    printMap();
    cout<< "[ " << player << "'s turn ] input x, y:";
    cin >> x >> y;
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
    first_step_pointer = (player == 'A')? &first_step_flag_A : &first_step_flag_B;
    pieces_pointer = (player == 'A')? pieces_A : pieces_B;

    // cout << player << " <- flag: " << *first_step_pointer << endl;

    // 1. check if piece alredy been used.
<<<<<<< HEAD
     if (pieces_pointer[shapeID] == 0) {
     	//cout << "shapeID: " << shapeID << " already on the board, choose other one." << endl;
     	return false;
     } else {

    	// 2. check if this step is first step.
		if(player == 'A' && *first_step_pointer == 0 && (x != 4 || y != 4)) {	// first time.
	    	//cout << "player A must start from original point (4,4)." << endl;
	    } else if (player == 'B' && *first_step_pointer == 0 && (x != 9 || y != 9)) {
	    	//cout << "player B must start from original point (9,9)." << endl;
=======
    // if (pieces_pointer[shapeID] == 0) {
    // 	cout << "shapeID: " << shapeID << " already on the board, choose other one." << endl;
    // 	return false;
    // } else {

    	// 2. check if this step is first step.
		if(player == 'A' && *first_step_pointer == 0 && (x != 4 || y != 4)) {	// first time.
	    	cout << "player A must start from original point (4,4)." << endl;
	    } else if (player == 'B' && *first_step_pointer == 0 && (x != 9 || y != 9)) {
	    	cout << "player B must start from original point (9,9)." << endl;
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	    } else {

	    	// check if legal.
		    if(isLegalMove(shp, x, y, player))
		    {
		        for(int i=0;i<5;i++)
		        {
		            board[shp.x[i]+x][shp.y[i]+y] = player;
		        }
		        *first_step_pointer = 1;
<<<<<<< HEAD


		        //system("cls");
		        //printMap();
=======
		        pieces_pointer[shapeID] = 0;
		        system("cls");
		        printMap();
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
		        return true;
		    }
		    else
		    {
<<<<<<< HEAD
		        //cout<<"Illegal move!"<<endl;
		        return false;
		    }
	    }
     }
}

bool checkpieces(int id, char player){

	// loop though all board.
	shape selected;
    int counter  = 0;
=======
		        cout<<"Illegal move!"<<endl;
		        return false;
		    }
	    }	
    // }
}

bool checkpieces(int id, char player){
	
	// loop though all board.
	shape selected;

>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
    if(player == 'A')
        selected = shapesA[id];
    else
        selected = shapesB[id];
<<<<<<< HEAD

	for (int i = 0; i < 14; i++) {

		for (int j = 0; j < 14; j++) {

=======
    
	for (int i = 0; i < 14; i++) {

		for (int j = 0; j < 14; j++) {
			
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
			// two flip.
			for (int f = 0; f < 2; f++) {

				if (f > 0) selected = flip(selected);

				// and four direction.
<<<<<<< HEAD
				for (int clockwise = 0; clockwise < 4; clockwise++)
                {

					if (clockwise > 0) selected = turnClockwise(selected);

					if(isLegalMove(selected, i, j, player))
                    {
						// if this piece can put => return true.
						return true;
					}

=======
				for (int clockwise = 0; clockwise < 4; clockwise++){

					if (clockwise > 0) selected = turnClockwise(selected);

					if(isLegalMove(shapesA[0], i, j, player)) {
						// if this piece can put => return 0.
						return 0;
					} else {
						continue;
					}
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
				}
			}
		}
	}
<<<<<<< HEAD
	return false; // if this piece can`t   => return false.
=======
	return 1; // if this piece can`t   => return 1.
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
}

bool checkgame(char player){
	cout << "\n\nstart check...\n" << endl;
<<<<<<< HEAD
	int counter = 0;
	bool cannot_put_any_pieces = false;
				//counter++;
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
	for(int i = 0;i < 21; i++)
    {
		if(pieces_pointer[i] == 1)
        {
			counter++;
		}
	}
	for(int i = 0;i < 21; i++)
    {
		if(pieces_pointer[i] == 1)
		{
			// cout << "call for "  << i << endl;1
 			if (checkpieces(i,player) == false)
            {
                cannot_put_any_pieces = true;
              //  cout<<i<<", ";
            }
            else
            {
                cannot_put_any_pieces = false;
            }
=======
	int counter = 0, cannot_put_any_pieces = 1;
				counter++;
	for(int i = 0;i < 21; i++){
		if(pieces_pointer[i] == 1) {
			counter++;
		}
	}
	for(int i = 0;i < 21 && cannot_put_any_pieces; i++){
		if(pieces_pointer[i] == 1) {
			// cout << "call for "  << i << endl;
 			if (checkpieces(i,player) == 0) cannot_put_any_pieces = 0;
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
		}
	}
	if (counter == 0 || cannot_put_any_pieces) {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << "You have no more pieces or you can`t place any more.\n|" << endl;
<<<<<<< HEAD
		cout<<counter<<endl;
=======
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
		return false;
	} else {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;
	}
	return true;
}
<<<<<<< HEAD
bool checkgameClear(char player){
	//cout << "\n\nstart check...\n" << endl;
	int counter = 0;
	bool cannot_put_any_pieces = false;
				//counter++;
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
	for(int i = 0;i < 21; i++)
    {
		if(pieces_pointer[i] == 1)
        {
			counter++;
		}
	}
	for(int i = 0;i < 21; i++)
    {
		if(pieces_pointer[i] == 1)
		{
			// cout << "call for "  << i << endl;1
 			if (checkpieces(i,player) == false)
            {
                cannot_put_any_pieces = true;
              //  cout<<i<<", ";
            }
            else
            {
                cannot_put_any_pieces = false;
            }
		}
	}
	if (counter == 0 || cannot_put_any_pieces) {
		//cout << "|--------------------------------- \n|" << endl;
		//cout << "| " << player << "You have no more pieces or you can`t place any more.\n|" << endl;
		//cout<<counter<<endl;
		return false;
	} else {
		//cout << "|--------------------------------- \n|" << endl;
		//cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;
	}
	return true;
}
=======
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5

void init()
{
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<14;j++)
            board[i][j] = '.';
    }
    board[4][4] = 'A';
    board[9][9] = 'B';
    for (int i = 0; i < 21; i++){
    	pieces_A[i] = 1;
    	pieces_B[i] = 1;
    }

    shapes.push_back(assignshape_00());shapes.push_back(assignshape_01());shapes.push_back(assignshape_02());shapes.push_back(assignshape_03());shapes.push_back(assignshape_04());
    shapes.push_back(assignshape_05());shapes.push_back(assignshape_06());shapes.push_back(assignshape_07());shapes.push_back(assignshape_08());shapes.push_back(assignshape_09());
    shapes.push_back(assignshape_10());shapes.push_back(assignshape_11());shapes.push_back(assignshape_12());shapes.push_back(assignshape_13());shapes.push_back(assignshape_14());
    shapes.push_back(assignshape_15());shapes.push_back(assignshape_16());shapes.push_back(assignshape_17());shapes.push_back(assignshape_18());shapes.push_back(assignshape_19());
    shapes.push_back(assignshape_20());
    shapesA = shapesB = shapes;
}

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
<<<<<<< HEAD
    int endCounter = 0;
    while(true)
    {
    	cout << endl;
        //system("cls");
        player = (turn)?'A':'B';
        pieces_pointer = (player == 'A')? pieces_A : pieces_B;
        // cout<<char('0'-1);

        // check if player still have move to implement.
        if(endCounter == 2)
        {
            cout<<"Game is ended."<<endl;
            return;
        }
        if (checkgame(player) == false) {
            isSelect = false;
            turn = !turn;
            endCounter++;
        } else {
            endCounter = 0;
	        cout << "| [instruction #" << instr_counter << "] you can press 1~7:" <<"\n|\n";
	        cout << "|\t1) Select Shape\n|\t2) Flip\n|\t3) Turn_clockwise\n|\t4) player_Move\n|\t5) Print_map\n|\t6) List_shapes\n|\t7) check condition\n|\t999) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";
	        cin>>instr;
	        if(instr == 999)
	            break;
	        if(instr == 1)		// select shape.
	        {
	            isSelect = true;
	            cout<<"shape index:";
	            int tmpID;
	            cin>>tmpID;

	            if (chackindex (tmpID)) {
	            	if (pieces_pointer[tmpID] == 0) {
	            		cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
	            		continue;
	            	} else {
	            	    shapeID = tmpID;
			            if(player == 'A')
			                selected = shapesA[shapeID];
			            else
			                selected = shapesB[shapeID];
			            printShape(selected);
	            	}
	            } else {
	            	cout << "no this index! re do instruction!." << endl;
	            	continue;
	            }
	        }
	        else if(instr == 2)	// Flip
	        {
	            selected = flip(selected);
	            printShape(selected);
	        }
	        else if(instr == 3) // Turn
	        {
	            selected = turnClockwise(selected);
	            printShape(selected);
	        }
	        else if(instr == 4) //player_move.
	        {
	            cout<<"shapeID:"<<shapeID<<endl;
	            printMap();
	            if(isSelect == false)//Hasn't select yet
	            {
	                cout<<"Please Select a shape."<<endl;
	                continue;
//	                cout<<"shape index:";
//	                cin >> shapeID;
//	                if (chackindex(shapeID)) {
//		                if(player == 'A')
//		                    selected = shapesA[shapeID];
//		                else
//		                    selected = shapesB[shapeID];
//	                } else {
//	                	cout << "no this index! re do instruction!." << endl;
//	                	continue;
//	                }
	            }
	            printShape(selected);
	            int x, y;
                cout<< "[ " << player << "'s turn ] input x, y:";
                cin >> x >> y;
	            legalMove = playerMove(selected, shapeID, player, x, y);
	            if(legalMove == true)
	            {
	                pieces_pointer[shapeID] = 0;
	            	instr_counter++;
	                isSelect = false;
	                turn = !turn;
	            }

	        }
	        else if(instr == 5)	//map.
	        {
	            printMap();
	        }
	        else if(instr == 6)	//list shape.
	        {
	            listShapes(player);
	        }
	        else if (instr == 7) {
	        	checkgame(player);
	        }
	        else
	        {
	            cout<<"Not a command."<<endl;
	        }
	        // cout<<"\nInput a 1~7 num to continue:";
	        // cin>>junk;
	    }
    }

}
void autoPlace(int id, char player)
{
    shape selected;
    int counter  = 0;
    if(player == 'A')
        selected = shapesA[id];
    else
        selected = shapesB[id];

	for (int i = 0; i < 14; i++) {

		for (int j = 0; j < 14; j++) {

			// two flip.
			for (int f = 0; f < 2; f++) {

				if (f > 0) selected = flip(selected);

				// and four direction.
				for (int clockwise = 0; clockwise < 4; clockwise++)
                {

					if (clockwise > 0) selected = turnClockwise(selected);

					if(isLegalMove(selected, i, j, player))
                    {
						// if this piece can put => return true.
						playerMove(selected, id, player, i, j);
						return ;
					}

				}
			}
		}
	}
	return; // if this piece can`t   => return false.
}

void autoPlay(char player)
{
    if(checkgameClear(player) == false)
        return;
    //init
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
    vector <shape> autoShape = (player == 'A') ? shapesA : shapesB;
    shape selected;
    //select a shape
    int shapeID = rand()%21;
    while(pieces_pointer[shapeID] == 0 || checkpieces(shapeID, player) == false ) // shape is unavailable
    {                                                                             // or shape can't be placed
        shapeID = rand()%21;
    }
    selected = autoShape[shapeID];
    //rand flip
    if(rand()%2 == 1)
        selected = flip(selected);
    //rand turn
    int turn = rand()%4;
    for(int i=0;i<turn;i++)
        selected = turnClockwise(selected);
    //rand place
    int x = rand()%14, y = rand()%14;
    int struggle = 196;
    while(playerMove(selected, shapeID, player, x, y) == false ) // move is illegal
    {
        struggle -- ;
        if(struggle == 0)
        {
            autoPlace(shapeID, player);
            break;
        }
        //cout<<struggle
        x = rand()%14;
        y = rand()%14;
    }
    pieces_pointer[shapeID] = 0;
    return;
}

void autoGame()
{
    bool turn = 0;// A
    char player = (turn == 0) ? 'A' : 'B';
    first_step_pointer = &first_step_flag_A;
    pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
    while(checkgameClear('A') == true || checkgameClear('B') == true)
    {

        pieces_pointer = (player == 'A') ? pieces_A : pieces_B;
        autoPlay(player);
        turn = !turn;
        player = (turn == 0) ? 'A' : 'B';
    }
}

void PK()
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
    while(true)
    {
        if(turn == 0)
        {
            autoPlay('B');
            turn = !turn;
            continue;
        }
    	cout << endl;
        //system("cls");
        player = (turn)?'A':'B';
        pieces_pointer = (player == 'A')? pieces_A : pieces_B;
        // cout<<char('0'-1);

        // check if player still have move to implement.
        if(endCounter == 2)
        {
            cout<<"Game is ended."<<endl;
            return;
        }
        if (checkgame(player) == false) {
            isSelect = false;
            turn = !turn;
            endCounter++;
        } else {
            endCounter = 0;
	        cout << "| [instruction #" << instr_counter << "] you can press 1~7:" <<"\n|\n";
	        cout << "|\t1) Select Shape\n|\t2) Flip\n|\t3) Turn_clockwise\n|\t4) player_Move\n|\t5) Print_map\n|\t6) List_shapes\n|\t7) check condition\n|\t999) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";
	        cin>>instr;
	        if(instr == 999)
=======
    while(true)
    {
    	cout << endl;
        system("cls");
        player = (turn)?'A':'B';
        pieces_pointer = (player == 'A')? pieces_A : pieces_B;
        // cout<<char('0'-1);

        // check if player still have move to implement.
        if (checkgame(player) == false) {
            isSelect = false;
            turn = !turn;
        } else {

	        cout << "| [instruction #" << instr_counter << "] you can press 1~7:" <<"\n|\n";
	        cout << "|\t1) Select Shape\n|\t2) Flip\n|\t3) Turn_clockwise\n|\t4) player_Move\n|\t5) Print_map\n|\t6) List_shapes\n|\t7) check condition\n|\t8) EXIT\n|\n";
	        cout << "|--------------------------------- " << endl;
	        cout << " Blockus >> ";
	        cin>>instr;
	        if(instr == 8)
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	            break;
	        if(instr == 1)		// select shape.
	        {
	            isSelect = true;
	            cout<<"shape index:";
<<<<<<< HEAD
	            int tmpID;
	            cin>>tmpID;

	            if (chackindex (tmpID)) {
	            	if (pieces_pointer[tmpID] == 0) {
	            		cout << "shapeID: " << tmpID << " already on the board, choose other one." << endl;
	            		continue;
	            	} else {
	            	    shapeID = tmpID;
=======
	            cin >> shapeID;
	            if (chackindex (shapeID)) {
	            	if (pieces_pointer[shapeID] == 0) {
	            		cout << "shapeID: " << shapeID << " already on the board, choose other one." << endl;
	            		continue;
	            	} else {
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
			            if(player == 'A')
			                selected = shapesA[shapeID];
			            else
			                selected = shapesB[shapeID];
<<<<<<< HEAD
			            printShape(selected);
=======
			            printShape(selected);      		
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	            	}
	            } else {
	            	cout << "no this index! re do instruction!." << endl;
	            	continue;
	            }
	        }
	        else if(instr == 2)	// Flip
	        {
	            selected = flip(selected);
	            printShape(selected);
	        }
	        else if(instr == 3) // Turn
	        {
	            selected = turnClockwise(selected);
	            printShape(selected);
	        }
	        else if(instr == 4) //player_move.
	        {
<<<<<<< HEAD
	            cout<<"shapeID:"<<shapeID<<endl;
	            printMap();
	            if(isSelect == false)//Hasn't select yet
	            {
	                cout<<"Please Select a shape."<<endl;
	                continue;
//	                cout<<"shape index:";
//	                cin >> shapeID;
//	                if (chackindex(shapeID)) {
//		                if(player == 'A')
//		                    selected = shapesA[shapeID];
//		                else
//		                    selected = shapesB[shapeID];
//	                } else {
//	                	cout << "no this index! re do instruction!." << endl;
//	                	continue;
//	                }
	            }
	            printShape(selected);
	            int x, y;
                cout<< "[ " << player << "'s turn ] input x, y:";
                cin >> x >> y;
	            legalMove = playerMove(selected, shapeID, player, x, y);
	            if(legalMove == true)
	            {
	                pieces_pointer[shapeID] = 0;
=======
	            if(isSelect == false)//Hasn't selet yet
	            {
	                cout<<"Please Select a shape."<<endl;
	                cout<<"shape index:";
	                cin >> shapeID;
	                if (chackindex(shapeID)) {
		                if(player == 'A')
		                    selected = shapesA[shapeID];
		                else
		                    selected = shapesB[shapeID];
	                } else {
	                	cout << "no this index! re do instruction!." << endl;
	                	continue;
	                }
	            }
	            printShape(selected);

	            legalMove = playerMove(selected, shapeID, player);
	            if(legalMove == true)
	            {
>>>>>>> 24b6e647304512a1f7c09acb2a49c656f18925c5
	            	instr_counter++;
	                isSelect = false;
	                turn = !turn;
	            }

	        }
	        else if(instr == 5)	//map.
	        {
	            printMap();
	        }
	        else if(instr == 6)	//list shape.
	        {
	            listShapes(player);
	        }
	        else if (instr == 7) {
	        	checkgame(player);
	        }
	        else
	        {
	            cout<<"Not a command."<<endl;
	        }
	        // cout<<"\nInput a 1~7 num to continue:";
	        // cin>>junk;
	    }
    }

}
string winner()
{
    int ALeft = 0, BLeft = 0;
    for(int i=0;i<21;i++)
    {
        if(pieces_A[i] == 1)
            ALeft += shapesA[i].size;
        if(pieces_B[i] == 1)
            BLeft += shapesB[i].size;
    }
    if(ALeft - BLeft > biggestRange || BLeft - ALeft > biggestRange)
    {
        biggestRange = ALeft - BLeft;
        bestA = ALeft;bestB = BLeft;
    }
    cout<<ALeft<<" : "<<BLeft<<endl;
    return (ALeft < BLeft) ? "A" : "B";
}
int main()
{
    srand(time(NULL));
    bool flag = false;
    init();
    int mode;
    cout<<"Game Start."<<endl<<endl;
   // printf("Select mode: \n\"player\" / \"auto\" :");
    cout << "|--------------------------------- \ " << endl;
    cout << "|   "<<endl<<"| Select Mode:" <<"\n|\n";
    cout << "|\t1) Player\n|\t2) Auto\n|\t3) See Priority Advantage\n|"<<endl;
    cout << "|--------------------------------- \n";
    cout<<"Blokus>>";
    cin>>mode;
    bool pause = false;
    if(mode == 1)// player
    {
        command();
        pause = true;
    }
    else if(mode == 2)
        autoGame();
    else
    {
        int winA = 0, winB = 0, games;
        cout << "|--------------------------------- \ " << endl;
        cout << "|   "<<endl<<"| Select Number of Games:" <<"\n|\n";
        cout << "|\t1) 1K\n|\t2) 10K\n|\t3) 100K\n|"<<endl;
        cout << "|--------------------------------- \n";
        cout<<"Blokus>>";
        cin>>games;
        if(games == 1) games = 1000;
        else if(games == 2) games = 10000;
        else if(games == 3) games = 100000;
        while(games--)
        {
            init();
            autoGame();
            cout<<games<<" to go....";
            if(winner() =="A")
                winA++;
            else
                winB++;
        }
        cout << "|--------------------------------- \ " << endl;
        cout << "|   "<<endl<<"| Result :" <<"\n|\n";
        cout << "| "<<winA<<" : "<<winB<< "\n|"<<endl;
        cout << "|   "<<endl<<"| Best Game :" <<"\n|\n";
        cout << "| "<<bestA<<" : "<<bestA<< "\n|"<<endl;
        cout << "|--------------------------------- \n";

    }
    string s = "";

    while(s != "seeResult" && pause)
    {
        cout<<endl;
        cout << "|--------------------------------- \ " << endl;
        cout << "|   "<<endl<<"| Please input string : seeResult" <<"\n";
        cout << "|"<<endl;
        cout << "|--------------------------------- \nBlokus>>";
        cin>>s;
    }

    printMap();
    cout << "|--------------------------------- \ " << endl;
    cout << "|   "<<endl<<"| Player "<<winner()<<" wins." <<"\n";
    cout << "|"<<endl;
    cout << "|--------------------------------- \nBlokus>>";
//    cin>>s;
//    listShapes('A');
//    cout<<endl<<endl<<"----------------------"<<endl;
//    listShapes('B');
    return 0;
}



