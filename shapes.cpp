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

	//the point to identify, default(0,0)
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
	this->uniX = shp.uniX;
	this->uniY = shp.uniY;
}

void Shape::set(const int& size, const string& xStr, const string& yStr)
{
	this->size = size;
	for (int i=0; i<size; i++) {
		this->x[i] = xStr[i]-'0';
		this->y[i] = yStr[i]-'0';
	}
}

bool Shape::isshape(const int& x, const int& y)
{
	for (int i=0; i<this->size; i++) {
		if (x==this->x[i] && y==this->y[i])
			return true;
	}
	return false;
}

void Shape::flip()
{
	for (int i=0; i<5; i++)    //flip
		this->x[i] *= -1;
	this->uniX *= -1;
	//this->normalizeShape();
}

void Shape::turnClockwise()
{
	int tmp;
	for (int i=0; i<5; i++) {
		tmp = this->x[i];
		this->x[i] = this->y[i];
		this->y[i] = -1 * tmp;
	}
	tmp = uniX;
	uniX = uniY;
	uniY = -1 * tmp;
	//this->normalizeShape();
}

void Shape::turnCounter_Clockwise()
{
	int tmp;
	for (int i=0; i<5; i++) {
		tmp = this->x[i];
		this->x[i] = -1 * this->y[i];
		this->y[i] = tmp;
	}
	tmp = uniX;
	uniX = -1 * uniY;
	uniY = tmp;
	//this->normalizeShape();
}

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
	Shape tmp = *this;
	tmp.normalizeShape();
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if (tmp.isshape(i, j)) {
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

Shape assignshape_00()
{
	/*
	   O
	 */
	Shape tmp;
	tmp.set(1, "0", "0");
	return tmp;
}

Shape assignshape_01()
{
	/*
	   OO
	 */
	Shape tmp;
	tmp.set(2, "01", "00");
	return tmp;
}

Shape assignshape_02()
{
	/*
	   O
	   O
	   O
	 */
	Shape tmp;
	tmp.set(3, "012", "000");
	return tmp;
}

Shape assignshape_03()
{
	/*
	   O
	   OO
	 */
	Shape tmp;
	tmp.set(3, "011", "001");
	return tmp;
}

Shape assignshape_04()
{
	/*
	   O
	   O
	   O
	   O
	 */
	Shape tmp;
	tmp.set(4, "0123", "0000");
	return tmp;
}

Shape assignshape_05()
{
	/*
	   OOO
	   O
	 */
	Shape tmp;
	tmp.set(4, "0001", "0121");
	return tmp;
}

Shape assignshape_06()
{
	/*
	   OO
	   OO
	 */
	Shape tmp;
	tmp.set(4, "0011", "0112");
	return tmp;
}

Shape assignshape_07()
{
	/*
	   OO
	   OO
	 */
	Shape tmp;
	tmp.set(4, "0011", "0101");
	return tmp;
}

Shape assignshape_08()
{
	/*
	   O
	   O
	   OO
	 */
	Shape tmp;
	tmp.set(4, "0122", "0001");
	return tmp;
}

Shape assignshape_09()
{
	/*
	   O
	   O
	   O
	   O
	   O
	 */
	Shape tmp;
	tmp.set(5, "01234", "00000");
	return tmp;
}

Shape assignshape_10()
{
	/*
	   O
	   O
	   O
	   OO
	 */
	Shape tmp;
	tmp.set(5, "01233", "00001");
	return tmp;
}

Shape assignshape_11()
{
	/*
	   O O
	   OOO
	 */
	Shape tmp;
	tmp.set(5, "01110", "00122");
	return tmp;
}

Shape assignshape_12()
{
	/*
	   OO
	   O
	   OO
	 */
	Shape tmp;
	tmp.set(5, "00122", "01112");
	return tmp;
}

Shape assignshape_13()
{
	/*
	   OOO
	   O
	   O
	 */
	Shape tmp;
	tmp.set(5, "00012", "01211");
	return tmp;
}

Shape assignshape_14()
{
	/*
	   O
	   OOO
	   O
	 */
	Shape tmp;
	tmp.set(5, "000/1", "01211"); //  '/' - '0' = -1
	return tmp;
}

Shape assignshape_15()
{
	/*
	   OO
	   OO
	   O
	 */
	Shape tmp;
	tmp.set(5, "00112", "01122");
	return tmp;
}

Shape assignshape_16()
{
	/*
	   O
	   O
	   OOO
	 */
	Shape tmp;
	tmp.set(5, "01222", "00012");
	return tmp;
}

Shape assignshape_17()
{
	/*
	   O
	   OOO
	   O
	 */
	Shape tmp;
	tmp.set(5, "01112", "00121");
	return tmp;
}

Shape assignshape_18()
{
	/*
	   OO
	   OO
	   O
	 */
	Shape tmp;
	tmp.set(5, "00112", "01010");
	return tmp;
}

Shape assignshape_19()
{
	/*
	   OOOO
	   O
	 */
	Shape tmp;
	tmp.set(5, "00001", "01231");
	return tmp;
}

Shape assignshape_20()
{
	/*
	   OO
	   OOO
	 */
	Shape tmp;
	tmp.set(5, "00111", "01123");
	return tmp;
}


