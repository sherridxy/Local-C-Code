#ifndef _MYCOMPLEX_H_
#define _MYCOMPLEX_H_
#include <iostream>
using namespace std;
class Complex
{
private :
	double real;
	double img;
public :
	Complex(double r,double i);
	Complex(double value);
	Complex operator +(const Complex &b);
	Complex operator -(const Complex &b);
	Complex operator *(const Complex &b);
	friend ostream & operator<<(ostream &os, const Complex &c);
};
#endif
