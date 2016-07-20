#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
int shapeChoises[21];
struct shape
{
    int size=0;
    int x[5]={0};
    int y[5]={0};
    //the point to identify
    int uniX = 0;
    int uniY = 0;
	void set(string xStr, string yStr)
	{

		for(int i=0;i<size;i++)
		{
			x[i] = xStr[i]-'0';
			y[i] = yStr[i]-'0';
		}
	}
};
shape assignshape_00()
{
    /*
    O
    */
	shape tmp;
	tmp.size = 1;
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_01()
{
    /*
    OO
    */
    shape tmp;
	tmp.size = 2;
	tmp.set("01", "00");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_02()
{
	/*
	O
	O
	O
	*/
    shape tmp;
	tmp.size = 3;
	tmp.set("012", "000");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_03()
{
    /*
    O
    OO
    */
    shape tmp;
	tmp.size = 3;
	tmp.set("011", "001");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_04()
{
    /*
    O
    O
    O
    O
    */
    shape tmp;
	tmp.size = 4;
	tmp.set("0123", "0000");
   // shapes.push_back(tmp);
    return tmp;
}
shape assignshape_05()
{
    /*
    OOO
     O
    */
    shape tmp;
	tmp.size = 4;
	tmp.set("0001", "0121");
   // shapes.push_back(tmp);
    return tmp;
}
shape assignshape_06()
{
    /*
    OO
     OO
    */
    shape tmp;
	tmp.size = 4;
	tmp.set("0011", "0112");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_07()
{
    /*
    OO
    OO
    */
    shape tmp;
	tmp.size = 4;
	tmp.set("0011", "0101");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_08()
{
    /*
    O
    O
    OO
    */
    shape tmp;
	tmp.size = 4;
	tmp.set("0122", "0001");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_09()
{
    /*
    O
    O
    O
    O
    O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("01234", "00000");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_10()
{
    /*
    O
    O
    O
    OO
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("01233", "00001");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_11()
{
    /*
    O O
    OOO
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("01110", "00122");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_12()
{
    /*
    OO
     O
     OO
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("00122", "01112");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_13()
{
    /*
    OOO
     O
     O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("00012", "01211");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_14()
{
    /*
     O
    OOO
     O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("000/1", "01211");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_15()
{
    /*
    OO
     OO
      O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("00112", "01122");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_16()
{
    /*
    O
    O
    OOO
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("01222", "00012");
   // shapes.push_back(tmp);
    return tmp;
}
shape assignshape_17()
{
    /*
    O
    OOO
     O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("01112", "00121");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_18()
{
    /*
    OO
    OO
    O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("00112", "01010");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_19()
{
    /*
    OOOO
     O
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("00001", "01231");
    //shapes.push_back(tmp);
    return tmp;
}
shape assignshape_20()
{
    /*
    OO
     OOo
    */
    shape tmp;
	tmp.size = 5;
	tmp.set("00111", "01123");
    //shapes.push_back(tmp);
    return tmp;
}


bool isshape(shape shp, int x, int y)
{
    for(int i=0;i<shp.size;i++)
    {
        if(x==shp.x[i] && y == shp.y[i])
            return true;
    }
    return false;
}

shape flip(shape shp)
{
    int minX = 5;
    for(int i=0; i<5; i++)    //flip
    {
        shp.x[i] = -1 * shp.x[i];
        minX = (shp.x[i] < minX)? shp.x[i] : minX;
    }
    return shp;
}

shape turnClockwise(shape shp)
{
    int tmp[5] = {0};
    for(int i=0; i<5; i++)
    {
        tmp[i] = shp.x[i];
        shp.x[i] = shp.y[i];
        shp.y[i] = -1 * tmp[i];
    }
    return shp;
}

shape turnCounter_Clockwise(shape shp)
{
    int tmp[5] = {0};
    for(int i=0; i<5; i++)
    {
        tmp[i] = shp.x[i];
        shp.x[i] = -1 * shp.y[i];
        shp.y[i] = tmp[i];
    }
    return shp;
}

shape normalizeshape(shape shp)
{
    int minX = 0, minY = 0;
    for(int i=0; i<5; i++)
    {
        minX = (shp.x[i] < minX) ? shp.x[i] : minX;
        minY = (shp.y[i] < minY) ? shp.y[i] : minY;
    }
    for(int i=0; i<5; i++)
    {
        shp.x[i] -= minX;
        shp.y[i] -= minY;
    }
    shp.uniX -= minX; shp.uniY -= minY;
    return shp;
}


void printShape(shape shp)
{
    shp = normalizeshape(shp);
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(isshape(shp, i, j))
            {
                if(i==shp.uniX && j==shp.uniY)
                    cout<<"*";
                else
                    cout<<"0";
            }
            else cout<<" ";
        }
        cout<<endl;
    }
}


