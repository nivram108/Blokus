#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <string>
#include "shapes.h"
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define MAGENTA "\033[45m"      /* Magenta */

using namespace std;
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
            	printShape(shapesA[i]);        		
        	} 
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
            	printShape(shapesB[i]);        		
        	} 
        	// else {
        	// 	cout << i << ": already used." << endl;
        	// }
        }
    }
}
void printMap()
{	
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
}

bool chackindex(int i) {
	if ( i >= 0 && i <= 20) return true;
	else return false;
}

bool isConnectedToShoulder(shape shp, int x, int y, char player)  // connected to a shoulder
{	
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
	                cout<<"Touch!"<<endl;
	                return true;
	            }
	        }
	    }
	}
    return false;
}
bool isSpare(shape shp, int x, int y, char player)
{	
	//cout << "in spare move" << endl;
	if (*first_step_pointer == 0) {
		// cout << "judge by spare." << endl;
		return true;
	} else {
	    for(int i=0;i<5;i++)
	    {
	        if((shp.x[i]+x < 14 && shp.x[i]+x >= 0 && shp.y[i]+y <14 && shp.y[i]+y >= 0  && board[shp.x[i]+x][shp.y[i]+y] == '.')==false ) // the block is in board range and unoccupied
	            return false;
	    }	
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
bool playerMove(shape shp, int shapeID, char player)
{
    int x,y;
    char junk, cX, cY;
    printMap();
    cout<< "[ " << player << "'s turn ] input x, y:";
    cin >> x >> y;
    first_step_pointer = (player == 'A')? &first_step_flag_A : &first_step_flag_B;
    pieces_pointer = (player == 'A')? pieces_A : pieces_B;

    // cout << player << " <- flag: " << *first_step_pointer << endl;

    // 1. check if piece alredy been used.
    // if (pieces_pointer[shapeID] == 0) {
    // 	cout << "shapeID: " << shapeID << " already on the board, choose other one." << endl;
    // 	return false;
    // } else {

    	// 2. check if this step is first step.
		if(player == 'A' && *first_step_pointer == 0 && (x != 4 || y != 4)) {	// first time.
	    	cout << "player A must start from original point (4,4)." << endl;
	    } else if (player == 'B' && *first_step_pointer == 0 && (x != 9 || y != 9)) {
	    	cout << "player B must start from original point (9,9)." << endl;
	    } else {

	    	// check if legal.
		    if(isLegalMove(shp, x, y, player))
		    {
		        for(int i=0;i<5;i++)
		        {
		            board[shp.x[i]+x][shp.y[i]+y] = player;
		        }
		        *first_step_pointer = 1;
		        pieces_pointer[shapeID] = 0;
		        system("cls");
		        printMap();
		        return true;
		    }
		    else
		    {
		        cout<<"Illegal move!"<<endl;
		        return false;
		    }
	    }	
    // }
}

bool checkpieces(int id, char player){
	
	// loop though all board.
	shape selected;

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
				for (int clockwise = 0; clockwise < 4; clockwise++){

					if (clockwise > 0) selected = turnClockwise(selected);

					if(isLegalMove(shapesA[0], i, j, player)) {
						// if this piece can put => return 0.
						return 0;
					} else {
						continue;
					}
				}
			}
		}
	}
	return 1; // if this piece can`t   => return 1.
}

bool checkgame(char player){
	cout << "\n\nstart check...\n" << endl;
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
		}
	}
	if (counter == 0 || cannot_put_any_pieces) {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << "You have no more pieces or you can`t place any more.\n|" << endl;
		return false;
	} else {
		cout << "|--------------------------------- \n|" << endl;
		cout << "| " << player << ": " << counter << " pieces left. Keep going.\n|" << endl;
		return true;
	}
	return true;
}

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
	            break;
	        if(instr == 1)		// select shape.
	        {
	            isSelect = true;
	            cout<<"shape index:";
	            cin >> shapeID;
	            if (chackindex (shapeID)) {
	            	if (pieces_pointer[shapeID] == 0) {
	            		cout << "shapeID: " << shapeID << " already on the board, choose other one." << endl;
	            		continue;
	            	} else {
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
int main()
{
    bool flag = false;
    init();
    command();
    return 0;
}



