#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include "shapes.h"

using namespace std;
vector<shape> shapes, shapesA, shapesB;

char board[14][14];
char tmpBoard[14][14];
int shoulder[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int side[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
ifstream ifs ("CurrentBoard.txt", ifstream::in);
ofstream ofs ("CurrentBoard.txt", ofstream::out);
void listShapes(char player)
{
    if(player == 'A')
    {
        for(int i=0;i<shapesA.size();i++)
        {
            cout<<i<<":"<<endl;
            printShape(shapesA[i]);
        }
    }
    else
    {
        for(int i=0;i<shapesB.size();i++)
        {
            cout<<i<<":"<<endl;
            printShape(shapesB[i]);
        }
    }
}
void printMap()
{
    cout<<"            1111"<<endl;
    cout<<"  ";
    for(int i=0;i<14;i++)
    {
        cout<<i%10;
    }

    cout<<endl;

    for(int i=0;i<14;i++)
    {
        if(i>=10)
            cout<<1;
        else
            cout<<" ";
        cout<<i%10;
        for(int j=0;j<14;j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}
bool isConnectedToShoulder(shape shp, int x, int y, char player)  // connected to a shoulder
{
    for(int i=0;i<5;i++)//each block of the shape
    {                //     block(x)                              block(y)                              board(x,y)
        for(int j=0;j<4;j++)//each shoulder of the block
        {
            if(board[shp.x[i]+x+shoulder[j][0]][shp.y[i]+y+shoulder[j][1]] == player)
                return true;
        }
    }
    cout<<"Unconneted!"<<endl;
    return false;
}

bool isTouchedBySelf(shape shp, int x, int y, char player)  // touched by itself
{
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
    return false;
}
bool isSpare(shape shp, int x, int y, char player)
{
    for(int i=0;i<5;i++)
    {
        if((shp.x[i]+x < 14 && shp.x[i]+x >= 0 && shp.y[i]+y <14 && shp.y[i]+y >= 0  && board[shp.x[i]+x][shp.y[i]+y] == '.')==false)// the block is in board range and unoccupied
            return false;
    }
    return true;
}
bool isLegalMove(shape shp, int x, int y, char player)
{
    if(isConnectedToShoulder(shp, x, y, player)==false || isTouchedBySelf(shp, x, y, player)==true|| isSpare(shp, x, y, player)==false )
        return false;
    return true;
}
bool playerMove(shape shp, int shapeID, char player)
{
//    string sX, sY;
    int x,y;
    char junk, cX, cY;
    printMap();
    cout<<player<<"'s turn."<<endl;
    cout<<"input x, y:";
    cin>>x>>y;
//    cin>>sX>>sY;
//    int x,y;
//    cX = sX[0]; cY = sY[0];
//    if(cX>='0' && cX<='13')
//    {
//        x = cX - '0';
//    }
//    else if(cX>='A' && cX <='D')
//    {
//        x = cX - 'A'+10;
//    }
//    else
//    {
//        cout<<"Illegal move!"<<endl;
//        return false;
//    }
//
//    if(cY>='0' && cY<='13')
//    {
//        y = cY - '0';
//    }
//    else if(cY>='A' && cY <='D')
//    {
//        y = cY - 'A'+10;
//    }
//    else
//    {
//        cout<<"Illegal move!"<<endl;
//        return false;
//    }
//

    if(isLegalMove(shp, x, y, player))
    {
        for(int i=0;i<5;i++)
        {
            board[shp.x[i]+x][shp.y[i]+y] = player;
        }
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


void init()
{
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<14;j++)
            board[i][j] = '.';
    }
    board[4][4] = 'A';
    board[9][9] = 'B';
    shapes.push_back(assignshape_00());shapes.push_back(assignshape_01());shapes.push_back(assignshape_02());shapes.push_back(assignshape_03());shapes.push_back(assignshape_04());
    shapes.push_back(assignshape_05());shapes.push_back(assignshape_06());shapes.push_back(assignshape_07());shapes.push_back(assignshape_08());shapes.push_back(assignshape_09());
    shapes.push_back(assignshape_10());shapes.push_back(assignshape_11());shapes.push_back(assignshape_12());shapes.push_back(assignshape_13());shapes.push_back(assignshape_14());
    shapes.push_back(assignshape_15());shapes.push_back(assignshape_16());shapes.push_back(assignshape_17());shapes.push_back(assignshape_18());shapes.push_back(assignshape_19());
    shapes.push_back(assignshape_20());
    shapesA = shapesB = shapes;
}

void command()
{

    string cmd="E";
    int shapeID, x, y;
    char junk, player;
    shape selected = shapes[0];
    bool legalMove = false;
    bool turn = true, isSelect = false;
    while(true)
    {
        system("cls");
        player = (turn)?'A':'B';
        // cout<<char('0'-1);
        cout<<player<<"'s turn."<<endl;
        cout<<"Select, Flip, Turn_clockwise, player_Move, Print_map, List_shapes, EXIT :";
        cin>>cmd;
        if(cmd=="EXIT")
            break;
        if(cmd == "S")
        {
            isSelect = true;
            cout<<"shape index:";
            cin>>shapeID;
            if(player == 'A')
                selected = shapesA[shapeID];
            else
                selected = shapesB[shapeID];
            printShape(selected);
        }
        else if(cmd == "T")
        {
            selected = turnClockwise(selected);
            printShape(selected);
        }
        else if(cmd == "F")
        {
            selected = flip(selected);
            printShape(selected);
        }
        else if(cmd == "M")
        {
            if(isSelect == false)//Hasn't selet yet
            {
                cout<<"Please Select a shape."<<endl;
                cout<<"shape index:";
                cin>>shapeID;
                if(player == 'A')
                    selected = shapesA[shapeID];
                else
                    selected = shapesB[shapeID];

            }
            printShape(selected);

            legalMove = playerMove(selected, shapeID, player);
            if(legalMove == true)
            {
                isSelect = false;
                turn = !turn;
            }

        }
        else if(cmd == "P")
        {
            printMap();
        }
        else if(cmd == "L")
        {
                listShapes(player);
        }
        else
        {
            cout<<"Not a command."<<endl;
        }
        cout<<"Input a char to continue:";
        cin>>junk;
    }

}
int main()
{
    bool flag = false;
    init();
    command();
    return 0;
}



