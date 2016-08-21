#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include "shapes.h"
using namespace std;

Shape::Shape()
{
	this->size = 0;
	memset(this->x, 0, sizeof(this->x));
	memset(this->y, 0, sizeof(this->y));

	this->cornerSize = 0;
	memset(this->cornerX, 0, sizeof(this->cornerX));
	memset(this->cornerY, 0, sizeof(this->cornerY));

	this->edgeSize = 0;
	memset(this->edgeX, 0, sizeof(this->edgeX));
	memset(this->edgeY, 0, sizeof(this->edgeY));

	this->uniX = 0;
	this->uniY = 0;
}

Shape::Shape(const Shape& shp)
{
	this->size = shp.size;
	for (int i=0; i<5; i++) {
		this->x[i] = shp.x[i];
		this->y[i] = shp.y[i];
	}
	this->cornerSize = shp.cornerSize;
	for (int i=0; i<8; i++) {
		this->cornerX[i] = shp.cornerX[i];
		this->cornerY[i] = shp.cornerY[i];
	}
	this->edgeSize = shp.edgeSize;
	for (int i=0; i<12; i++) {
		this->edgeX[i] = shp.edgeX[i];
		this->edgeY[i] = shp.edgeY[i];
	}
	this->uniX = shp.uniX;
	this->uniY = shp.uniY;
}

void Shape::set(const int& size, const string& xStr, const string& yStr, const int& cSize, const string& cxStr, const string& cyStr, const int& eSize, const string& exStr, const string& eyStr)
{
	this->size = size;
	for (int i=0; i<size; i++) {
		this->x[i] = xStr[i] - '0';
		this->y[i] = yStr[i] - '0';
	}
	this->cornerSize = cSize;
	for (int i=0; i<cSize; i++) {
		this->cornerX[i] = cxStr[i] - '0';
		this->cornerY[i] = cyStr[i] - '0';
	}
	this->edgeSize = eSize;
	for (int i=0; i<eSize; i++) {
		this->edgeX[i] = exStr[i] - '0';
		this->edgeY[i] = eyStr[i] - '0';
	}
}

//Check if the assigned point belongs to the shape
bool Shape::isShape(const int& x, const int& y)
{
	for (int i=0; i<this->size; i++) {
		if (x==this->x[i] && y==this->y[i])
			return true;
	}
	return false;
}

void Shape::flip()
{
	for (int i=0; i<5; i++) {
		this->x[i] *= -1;
		this->cornerX[i] *= -1;
		this->edgeX[i] *= -1;
	}
}

void Shape::turnClockwise()
{
	int tmp;
	for (int i=0; i<5; i++) {
		tmp = this->x[i];
		this->x[i] = this->y[i];
		this->y[i] = -1 * tmp;

		tmp = this->cornerX[i];
		this->cornerX[i] = this->cornerY[i];
		this->cornerY[i] = -1 * tmp;

		tmp = this->edgeX[i];
		this->edgeX[i] = this->edgeY[i];
		this->edgeY[i] = -1 * tmp;
	}
}

// Help printShape() to print the object.
void Shape::normalizeShape()
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

void Shape::printShape()
{
	// The original uniX and uniY keep (0,0) after normalization.
	Shape tmp = *this;
	tmp.normalizeShape();
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if (tmp.isShape(i, j)) {
				if (i==tmp.uniX && j==tmp.uniY)
					cout << "*";
				else
					cout << "0";
			}
			else cout << " ";
		}
		cout << endl;
	}
}
void Shape::operator = (const Shape& shp)
{
	this->size = shp.size;
	for (int i=0; i<5; i++) {
		this->x[i] = shp.x[i];
		this->y[i] = shp.y[i];
	}
	this->cornerSize = shp.cornerSize;
	for (int i=0; i<8; i++) {
		this->cornerX[i] = shp.cornerX[i];
		this->cornerY[i] = shp.cornerY[i];
	}
	this->edgeSize = shp.edgeSize;
	for (int i=0; i<12; i++) {
		this->edgeX[i] = shp.edgeX[i];
		this->edgeY[i] = shp.edgeY[i];
	}
	this->uniX = shp.uniX;
	this->uniY = shp.uniY;
}

int Shape::getSize()
{
	return this->size;
}

int Shape::getPosX(const int& k)
{
	return this->x[k];
}

int Shape::getPosY(const int& k)
{
	return this->y[k];
}

//	'/' - '0' = -1
//	'.' - '0' = -2
Shape assignshape_00()
{
	/*
	  x x
	   O
	  x x
	*/
	Shape tmp;
	tmp.set(1, "0", "0", 4, "//11", "/1/1", 4, "/010", "0/01");
	return tmp;
}

Shape assignshape_01()
{
	/*
	  x x
	   O
	   O
	  x x
	*/
	Shape tmp;
	tmp.set(2, "01", "00", 4, "//22", "/1/1", 6, "/01210", "0//011");
	return tmp;
}

Shape assignshape_02()
{
	/*
	  x x
	   O
	   O
	   O
	  x x
	 */
	Shape tmp;
	tmp.set(3, "012", "000", 4, "//33", "/1/1/1", 8, "/0123210", "0///0111");
	return tmp;
}

Shape assignshape_03()
{
	/*
	  x x
	   O x 
	   OO
	  x  x
	 */
	Shape tmp;
	tmp.set(3, "011", "001", 5, "//022", "/122/", 7, "/012210", "0//0121");
	return tmp;
}

Shape assignshape_04()
{
	/*
	  x x
	   O
	   O
	   O
	   O
	  x x
	 */
	Shape tmp;
	tmp.set(4, "0123", "0000", 4, "//44", "/1/1", 10, "/012343210", "0////01111");
	return tmp;
}

Shape assignshape_05()
{
	/*
	  x   x
	   OOO
	  x O x
	   x x
	 */
	Shape tmp;
	tmp.set(4, "0001", "0121", 6, "//1221", "/3320/", 8, "///01210", "0123210/");
	return tmp;
}

Shape assignshape_06()
{
	/*
	  x  x
	   OO x
	  x OO
	   x  x
	 */
	Shape tmp;
	tmp.set(4, "0011", "0112", 6, "//0221", "/2330/", 8, "//012210", "0123210/");
	return tmp;
}

Shape assignshape_07()
{
	/*
	  x  x
	   OO
	   OO
	  x  x
	 */
	Shape tmp;
	tmp.set(4, "0011", "0101", 4, "//22", "/2/2", 8, "//012210", "012210//");
	return tmp;
}

Shape assignshape_08()
{
	/*
	  x x
	   O
	   O x
	   OO
	  x  x
	 */
	Shape tmp;
	tmp.set(4, "0122", "0001", 5, "//133", "/122/", 9, "/01233210", "0///01211");
	return tmp;
}

Shape assignshape_09()
{
	/*
	  x x
	   O
	   O
	   O
	   O
	   O
	  x x
	 */
	Shape tmp;
	tmp.set(5, "01234", "00000", 4, "//55", "/1/1", 12, "/01234543210", "0/////011111");
	return tmp;
}

Shape assignshape_10()
{
	/*
	  x x
	   O
	   O
	   O x
	   OO
	  x  x
	 */
	Shape tmp;
	tmp.set(5, "01233", "00001", 5, "//244", "/122/", 11, "/0123443210", "0////012111");
	return tmp;
}

Shape assignshape_11()
{
	/*
	  x x x
	   O O
	   OOO
	  x   x
	 */
	Shape tmp;
	tmp.set(5, "01110", "00122", 5, "///22", "/133/", 10, "/0/0122210", "01233210//");
	return tmp;
}

Shape assignshape_12()
{
	/*
	  x  x
	   OO
	  x O x
	    OO
	   x  x
	 */
	Shape tmp;
	tmp.set(5, "00122", "01112", 6, "//1331", "/2330/", 10, "//01233210", "012232100/");
	return tmp;
}

Shape assignshape_13()
{
	/*
	  x   x
	   OOO
	  x O x
	    O
	   x x
	 */
	Shape tmp;
	tmp.set(5, "00012", "01211", 6, "//1331", "/3320/", 10, "///0123210", "012322100/");
	return tmp;
}

Shape assignshape_14()
{
	/*
	  x x
	 x O x
	  *OO
	 x O x
	  x x
	 */
	Shape tmp;
	tmp.set(5, "000/1", "01211", 8, "/../1221", "/023320/", 8, "/./01210", "0123210/");
	return tmp;
}

Shape assignshape_15()
{
	/*
	  x  x
	   OO x
	  x OO
	   x O
	    x x
	 */
	Shape tmp;
	tmp.set(5, "00112", "01122", 7, "//03321", "/23310/", 9, "//0123210", "01233210/");
	return tmp;
}

Shape assignshape_16()
{
	/*
	  x x
	   O
	   O  x
	   OOO
	  x   x
	 */
	Shape tmp;
	tmp.set(5, "01222", "00012", 5, "//133", "/133/", 11, "/0112333210", "01123210///");
	return tmp;
}

Shape assignshape_17()
{
	/*
	  x x
	   O  x
	   OOO
	  x O x
	   x x
	 */
	Shape tmp;
	tmp.set(5, "01112", "00121", 7, "//02332", "/13320/", 9, "/00123210", "0123210//");
	return tmp;
}

Shape assignshape_18()
{
	/*
	  x  x
	   OO
	   OO
	   O x
	  x x
	 */
	Shape tmp;
	tmp.set(5, "00112", "01010", 5, "//233", "/221/", 9, "//0123210", "012210///");
	return tmp;
}

Shape assignshape_19()
{
	/*
	  x    x
	   OOOO
	  x O  x
	   x x
	 */
	Shape tmp;
	tmp.set(5, "00001", "01231", 6, "//1221", "/4420/", 10, "////011210", "012343210/");
	return tmp;
}

Shape assignshape_20()
{
	/*
	  x  x
	   OO  x
	  x OOO
	   x   x
	 */
	Shape tmp;
	tmp.set(5, "00111", "01123", 6, "//0221", "/2440/", 10, "//00122210", "012343210/");
	return tmp;
}
