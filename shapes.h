#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

int shapeChoises[21];

struct shape
{
    int size;
    int x[5];
    int y[5];

    //the point to identify
    int uniX;
    int uniY;

    shape();
	void set(string xStr, string yStr);
};

bool isshape(shape shp, int x, int y);

shape flip(shape shp);

shape turnClockwise(shape shp);

shape turnCounter_Clockwise(shape shp);

shape normalizeshape(shape shp);

void printShape(shape shp);

shape assignshape_00();
shape assignshape_01();
shape assignshape_02();
shape assignshape_03();
shape assignshape_04();
shape assignshape_05();
shape assignshape_06();
shape assignshape_07();
shape assignshape_08();
shape assignshape_09();
shape assignshape_10();
shape assignshape_11();
shape assignshape_12();
shape assignshape_13();
shape assignshape_14();
shape assignshape_15();
shape assignshape_16();
shape assignshape_17();
shape assignshape_18();
shape assignshape_19();
shape assignshape_20();

#endif
