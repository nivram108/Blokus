#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "shapes.h"

using namespace std;
vector<block> blocks;

void init()
{
    blocks.push_back(assignBlock_00());blocks.push_back(assignBlock_01());blocks.push_back(assignBlock_02());blocks.push_back(assignBlock_03());blocks.push_back(assignBlock_04());
    blocks.push_back(assignBlock_05());blocks.push_back(assignBlock_06());blocks.push_back(assignBlock_07());blocks.push_back(assignBlock_08());blocks.push_back(assignBlock_09());
    blocks.push_back(assignBlock_10());blocks.push_back(assignBlock_11());blocks.push_back(assignBlock_12());blocks.push_back(assignBlock_13());blocks.push_back(assignBlock_14());
    blocks.push_back(assignBlock_15());blocks.push_back(assignBlock_16());blocks.push_back(assignBlock_17());blocks.push_back(assignBlock_18());blocks.push_back(assignBlock_19());



}

int main()
{
    bool flag = false;
    init();
    string cmd="E";
    int shape;
    char junk;
    block selected = blocks[0];

    while(cmd!="EXIT")
    {
        system("cls");
       // cout<<char('0'-1);
        cout<<"Select, FlipX, FlipY, TurnClockwise, TurnCounterClockwise, Print, Normalize, EXIT :";
        cin>>cmd;
        if(cmd == "S")
        {
            cout<<"Block index:";
            cin>>shape;
            selected = blocks[shape];
            printShape(selected);
        }
        else if(cmd == "FX")
        {
            selected = flipX(selected);
            printShape(selected);
        }
        else if(cmd == "P")
        {
            printShape(selected);
        }
        else if(cmd == "TC")
        {
            selected = turnClockwise(selected);
            printShape(selected);
        }
        cin>>junk;


    }

    return 0;
}
