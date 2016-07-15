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
	block set(string xStr, string yStr)
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
block assignBlock_00()
{
    /*
    O
    */
	block tmp;
	tmp.size = 1;
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_01()
{
    /*
    OO
    */
    block tmp;
	tmp.size = 2;
	tmp.set("01", "00");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_02()
{
	/*
	O
	O
	O
	*/
    block tmp;
	tmp.size = 3;
	tmp.set("012", "000");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_03()
{
    /*
    O
    OO
    */
    block tmp;
	tmp.size = 3;
	tmp.set("011", "001");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_04()
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
   // blocks.push_back(tmp);
    return tmp;
}
block assignBlock_05()
{
    /*
    OOO
     O
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0001", "0121");
   // blocks.push_back(tmp);
    return tmp;
}
block assignBlock_06()
{
    /*
    OO
     OO
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0011", "0112");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_07()
{
    /*
    OO
    OO
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0011", "0101");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_08()
{
    /*
    O
    O
    OO
    */
    block tmp;
	tmp.size = 4;
	tmp.set("0122", "0001");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_09()
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
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_10()
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
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_11()
{
    /*
    O O
    OOO
    */
    block tmp;
	tmp.size = 5;
	tmp.set("01110", "00122");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_12()
{
    /*
    OO
     O
     OO
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00122", "01112");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_13()
{
    /*
    OOO
     O
     O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00012", "01211");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_14()
{
    /*
     O
    OOO
     O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("000/1", "01211");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_15()
{
    /*
    OO
     OO
      O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00112", "01122");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_16()
{
    /*
    O
    O
    OOO
    */
    block tmp;
	tmp.size = 5;
	tmp.set("01222", "00012");
   // blocks.push_back(tmp);
    return tmp;
}
block assignBlock_17()
{
    /*
    O
    OOO
     O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("01112", "00121");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_18()
{
    /*
    OO
    OO
    O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00112", "01010");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_19()
{
    /*
    OOOO
     O
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00001", "01231");
    //blocks.push_back(tmp);
    return tmp;
}
block assignBlock_20()
{
    /*
    OO
     OOo
    */
    block tmp;
	tmp.size = 5;
	tmp.set("00111", "01123");
    //blocks.push_back(tmp);
    return tmp;
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


