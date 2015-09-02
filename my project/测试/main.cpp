#include <iostream>
#include <cmath>
#define PI 3.1415926
using namespace std;
class Geometric_shape
{
public:
    virtual double perimeter()=0;
    virtual double area()=0;
    virtual double volume()=0;
    virtual void Show()=0;
};

class Circle:public Geometric_shape
{
protected :
    double r;
public:
    Circle(double x=0) {r=x;}
    double perimeter ()
    {
        return 2*PI*r;
    }
    double area()
    {
        return PI*r*r;
    }
    double volume()
    {
        return 0;
    }
    void Show()
    {
        cout<<"这是一个圆"<<endl;
    }
};

class Rectangle:public Geometric_shape
{
protected:
    double x;
    double y;
public:
    Rectangle(double a=0,double b=0) {x=a;y=b;}
    double perimeter ()
    {
        return 2*(x+y);
    }
    double area()
    {
        return x*y;
    }
    double volume()
    {
        return 0;
    }
    void Show()
    {
        cout<<"这是一个矩形"<<endl;
    }

};

class Triangle:public Geometric_shape
{
protected:
    double a;
    double b;
    double c;
public:
    Triangle(double x=0,double y=0,double z=0) {a=x;b=y;c=z;}
    double perimeter ()
    {
        return a+b+c;
    }
    double area()
    {
        double p=(a+b+c)/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
    double volume()
    {
        return 0;
    }
    void Show()
    {
        cout<<"这是一个三角形"<<endl;
    }

};

class Box:public Rectangle
{
protected:
    double h;
public:
    Box (double q=0,double w=0,double e=0) :Rectangle(q,w){h=e;}
    double volume()
    {

        return h*area();
    }
    void Show()
    {
        cout<<"这是一个长方体"<<endl;
    }
};

class Cylinder:public Circle
{
protected :
    double h;
public:
    Cylinder(double q,double w) :Circle(q){h=w;}
    double volume()
    {
        return h*area();
    }
    void Show()
    {
        cout<<"这是一个圆柱"<<endl;
    }
};

class Cone:public Circle
{
protected :
    double h;
public:
    Cone(double q,double w) :Circle(q){h=w;}
    double volume()
    {
        return h*area()/3;
    }
    void Show()
    {
        cout<<"这是一个圆锥"<<endl;
    }

};

class T_pyramid:public Triangle
{
protected :
    double h;
public:
    T_pyramid(double q,double w,double e,double r) :Triangle(q,w,e){h=r;}
    double volume()
    {
        return h*area()/3;
    }
    void Show()
    {
        cout<<"这是一个三棱锥"<<endl;
    }
};

class T_prism:public Triangle
{
protected :
    double h;
public:
    T_prism (double q,double w,double e,double r) :Triangle(q,w,e){h=r;}
    double volume()
    {
        return h*area();
    }
    void Show()
    {
        cout<<"这是一个三棱柱"<<endl;
    }

};


int main()
{
	Geometric_shape * gs[]={new	Circle(10),new 	Rectangle(6,8),new	Triangle(3,4,5),
new Box(6,8,3),new	Cylinder(10,3),new 	Cone(10,3),new T_pyramid(3,4,5,3),new T_prism(3,4,5,3)};
    for (int i=0;i<8;i++)
	{
		gs[i]->Show();
        cout<<endl;
	}
	cout<<"平面图形："<<endl;
    for (int i=0;i<3;i++)
	   {
		   cout<<"图形周长："<<gs[i]->perimeter()<<'\t';
        cout<<"图形面积："<<gs[i]->area()<<'\t';
        cout<<"图形体积："<<gs[i]->volume()<<endl;
    }
	cout<<"立体图形："<<endl;
    for (int i=3;i<8;i++)
	   {
		   cout<<"图形底周长："<<gs[i]->perimeter()<<'\t';
        cout<<"图形底面积："<<gs[i]->area()<<'\t';
        cout<<"图形体积  ："<<gs[i]->volume()<<endl;
    }
	return 0;
}


