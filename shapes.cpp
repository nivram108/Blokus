#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include "shapes.h"
using namespace std;

shape::shape() 
{
    this->size = 0;
    memset(this->x, 0, sizeof(this->x));
    memset(this->y, 0, sizeof(this->y));

    //the point to identify, default(0,0)
    this->uniX = 0;
    this->uniY = 0;
}

void shape::set(int size, string xStr, string yStr)
{
    this->size = size;
	for (int i=0; i<size; i++) {
			this->x[i] = xStr[i]-'0';
			this->y[i] = yStr[i]-'0';
	}
}

bool shape::isshape(int x, int y)
{
    for (int i=0; i<this->size; i++) {
        if (x==this->x[i] && y==this->y[i])
            return true;
    }
    return false;
}

void shape::flip()
{
    for (int i=0; i<5; i++)    //flip
        this->x[i] = -1 * this->x[i];
}

void shape::turnClockwise()
{
    int tmp;
    for (int i=0; i<5; i++) {
        tmp = this->x[i];
        this->x[i] = this->y[i];
        this->y[i] = -1 * tmp;
    }
}

void shape::turnCounter_Clockwise()
{
    int tmp;
    for (int i=0; i<5; i++) {
        tmp = this->x[i];
        this->x[i] = -1 * this->y[i];
        this->y[i] = tmp;
    }
}

void shape::normalizeshape()
{
    int minX = 0, minY = 0;
    for (int i=0; i<5; i++) {
        minX = (this->x[i] < minX) ? this->x[i] : minX;
        minY = (this->y[i] < minY) ? this->y[i] : minY;
    }
    for (int i=0; i<5; i++) {
        this->x[i] -= minX;
        this->y[i] -= minY;
    }
    this->uniX -= minX;
    this->uniY -= minY;
}


void shape::printShape()
{
    this->normalizeshape();
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (this->isshape(i, j)) {
                if (i==this->uniX && j==this->uniY)
                    cout << "*";
                else
                    cout << "0";
            }
            else cout << " ";
        }
        cout << endl;
    }
}
void shape::operator = (const shape& shp)
{
    this->size = shp.size;
    for (int i=0; i<5; i++) {
        this->x[i] = shp.x[i];
        this->y[i] = shp.y[i];
    }
    this->uniX = shp.uniX;
    this->uniY = shp.uniY;
}

shape assignshape_00()
{
    /*
    O
    */
	shape tmp;
    tmp.set(1, "0", "0");
    return tmp;
}

shape assignshape_01()
{
    /*
    OO
    */
    shape tmp;
	tmp.set(2, "01", "00");
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
	tmp.set(3, "012", "000");
    return tmp;
}

shape assignshape_03()
{
    /*
    O
    OO
    */
    shape tmp;
	tmp.set(3, "011", "001");
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
	tmp.set(4, "0123", "0000");
    return tmp;
}

shape assignshape_05()
{
    /*
    OOO
     O
    */
    shape tmp;
	tmp.set(4, "0001", "0121");
    return tmp;
}

shape assignshape_06()
{
    /*
    OO
     OO
    */
    shape tmp;
	tmp.set(4, "0011", "0112");
    return tmp;
}

shape assignshape_07()
{
    /*
    OO
    OO
    */
    shape tmp;
	tmp.set(4, "0011", "0101");
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
	tmp.set(4, "0122", "0001");
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
	tmp.set(5, "01234", "00000");
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
	tmp.set(5, "01233", "00001");
    return tmp;
}

shape assignshape_11()
{
    /*
    O O
    OOO
    */
    shape tmp;
	tmp.set(5, "01110", "00122");
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
	tmp.set(5, "00122", "01112");
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
	tmp.set(5, "00012", "01211");
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
	tmp.set(5, "000/1", "01211"); //  '/' - '0' = -1
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
	tmp.set(5, "00112", "01122");
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
	tmp.set(5, "01222", "00012");
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
	tmp.set(5, "01112", "00121");
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
	tmp.set(5, "00112", "01010");
    return tmp;
}

shape assignshape_19()
{
    /*
    OOOO
     O
    */
    shape tmp;
	tmp.set(5, "00001", "01231");
    return tmp;
}

shape assignshape_20()
{
    /*
    OO
     OOo
    */
    shape tmp;
	tmp.set(5, "00111", "01123");
    return tmp;
}


