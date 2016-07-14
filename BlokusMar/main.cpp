#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
int blockChoises[21];
struct block
{
    int size=0;
    int x[5]={0};
    int y[5]={0};
	void set(string xStr, string yStr)
	{

		for(int i=0;i<size;i++)
		{
		    cout<<"Set:";
			x[i] = xStr[i]-'0';
			y[i] = yStr[i]-'0';
			cout<<xStr[i]<<", "<<yStr[i]<<endl;
		}
	}
};
vector <block> blocks;
void assignBlock_00()
{
    /*
    O
    */
	block tmp;
	tmp.size = 1;
    blocks.push_back(tmp);
}
void assignBlock_01()
{
    /*
    OO
    */
    block tmp;
	tmp.size = 2;
	tmp.set("01", "00");
    blocks.push_back(tmp);
}
void assignBlock_02()
{
	/*
	O
	O
	O
	*/
    block tmp;
	tmp.size = 3;
	tmp.set("012", "000");
    blocks.push_back(tmp);

}
void assignBlock_03()
{
    /*
    O
    OO
    */
    block tmp;
	tmp.size = 3;
	tmp.set("011", "001");
    blocks.push_back(tmp);
}
void assignBlock_04()
{
    /*
    O
    O
    O
    O
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0123", "0000");
    blocks.push_back(tmp);
}
void assignBlock_05()
{
    /*
    OOO
     O
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0001", "0121");
    blocks.push_back(tmp);
}
void assignBlock_06()
{
    /*
    OO
     OO
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0011", "0112");
    blocks.push_back(tmp);
}
void assignBlock_07()
{
    /*
    OO
    OO
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0011", "0101");
    blocks.push_back(tmp);
}
void assignBlock_08()
{
    /*
    O
    O
    OO
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0122", "0001");
    blocks.push_back(tmp);
}
void assignBlock_09()
{
    /*
    O
    O
    O
    O
    O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("01234", "00000");
    blocks.push_back(tmp);
}
void assignBlock_10()
{
    /*
    O
    O
    O
    OO
    */
    block tmp;
	tmp.size = 5;
	tmp.set("01233", "00001");
    blocks.push_back(tmp);
}
void assignBlock_11()
{
    /*
    O O
    OOO
    */
    block tmp;
	tmp.size = 5;
	tmp.set("01110", "00122");
    blocks.push_back(tmp);
}
void assignBlock_12()
{
    /*
    OO
     O
     OO
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00122", "01112");
    blocks.push_back(tmp);
}
void assignBlock_13()
{
    /*
    OOO
     O
     O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00012", "01211");
    blocks.push_back(tmp);
}
void assignBlock_14()
{
    /*
     O
    OOO
     O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("000/1", "01211");
    blocks.push_back(tmp);
}
void assignBlock_15()
{
    /*

    */
    block tmp;
	tmp.size = 5;
	tmp.set("000/1", "01211");
    blocks.push_back(tmp);
}
void assignBlock_16();
void assignBlock_17();
void assignBlock_18();
void assignBlock_19();
void assignBlock_20();
void assignBlock_21();

void init()
{
    assignBlock_00();assignBlock_01();assignBlock_02();assignBlock_03();assignBlock_04();
    assignBlock_05();assignBlock_06();assignBlock_07();assignBlock_08();assignBlock_09();
    assignBlock_10();assignBlock_11();assignBlock_12();assignBlock_13();assignBlock_14();
    //assignBlock_15();assignBlock_16();assignBlock_17();assignBlock_18();assignBlock_19();
}
bool isBlock(block blk, int x, int y)
{
    for(int i=0;i<blk.size;i++)
    {
        if(x==blk.x[i] && y == blk.y[i])
            return true;
    }
    return false;
}

block flipX(block blk)
{
    int minX = 5;
    for(int i=0; i<5; i++)    //flip
    {
        blk.x[i] = -1 * blk.x[i];
        minX = (blk.x[i] < minX)? blk.x[i] : minX;
    }
    return blk;
}

block flipY(block blk)
{

    for(int i=0; i<5; i++)    //flip
    {
        blk.y[i] = -1 * blk.y[i];
    }
    return blk;
}
block turnClockwise(block blk)
{
    int tmp[5] = {0};
    for(int i=0; i<5; i++)
    {
        tmp[i] = blk.x[i];
        blk.x[i] = blk.y[i];
        blk.y[i] = -1 * tmp[i];
    }
    return blk;
}

block turnCounter_Clockwise(block blk)
{
    int tmp[5] = {0};
    for(int i=0; i<5; i++)
    {
        tmp[i] = blk.x[i];
        blk.x[i] = -1 * blk.y[i];
        blk.y[i] = tmp[i];
    }
    return blk;
}

block normalizeBlock(block blk)
{
    int minX = 0, minY = 0;
    for(int i=0; i<5; i++)
    {
        minX = (blk.x[i] < minX) ? blk.x[i] : minX;
        minY = (blk.y[i] < minY) ? blk.y[i] : minY;
    }
    for(int i=0; i<5; i++)
    {
        blk.x[i] -= minX;
        blk.y[i] -= minY;
    }
    return blk;
}

void printMap()
{
    bool flag = false;
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<14;j++)
        {
            for(int b=0;b<blocks[0].size;b++)
            {
                if(i==blocks[0].x[b] && j==blocks[0].y[b])
                {
                    flag = true;
                    break;
                }
                else
                    flag = false;
            }
            if(flag)
                cout<<"*";
            else
                cout<<"0";
        }
        cout<<endl;
    }
}

void printShape(block blk)
{
    blk = normalizeBlock(blk);
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(isBlock(blk, i, j))
                cout<<"*";
            else cout<<"0";
        }
        cout<<endl;
    }
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
