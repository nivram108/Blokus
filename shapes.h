#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

class Shape
{
private:
    int size;
    int x[5];
    int y[5];

    //the point to identify
    int uniX;
    int uniY;
	bool isshape(const int& x, const int& y);
	void normalizeShape();

public:
    Shape();
    Shape(const Shape& shp);
	void set(const int& size, const string& xStr, const string& yStr);
	void flip();
	void turnClockwise();
	void turnCounter_Clockwise();
	void printShape();
	void operator = (const Shape& shp);
	int getSize();
	int getPosX(const int& k);
	int getPosY(const int& k);
};

Shape assignshape_00();
Shape assignshape_01();
Shape assignshape_02();
Shape assignshape_03();
Shape assignshape_04();
Shape assignshape_05();
Shape assignshape_06();
Shape assignshape_07();
Shape assignshape_08();
Shape assignshape_09();
Shape assignshape_10();
Shape assignshape_11();
Shape assignshape_12();
Shape assignshape_13();
Shape assignshape_14();
Shape assignshape_15();
Shape assignshape_16();
Shape assignshape_17();
Shape assignshape_18();
Shape assignshape_19();
Shape assignshape_20();

#endif
