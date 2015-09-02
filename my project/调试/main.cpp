#include <iostream>
#include <cmath>

using namespace std;
class myPoint {
public:
   myPoint(double x0=0.0,double y0=0.0):x(x0),y(y0) {}
   myPoint(myPoint &np):x(np.x),y(np.y) {}
   double GetX() { return x;}
   double GetY() {return y;}
   void SetX(double x0) {x=x0;}
   void SetY(double y0) {x=y0;}
   void SetPoint(double x0,double y0) {x=x0;y=y0;}
   void SetPoint(myPoint &np) { x=np.x; y=np.y;}
   double  GetLength(myPoint p) {
     return sqrt((x-p.x)*(x-p.x) +(y-p.y)*(y-p.y));
   }
   void Printit() { cout<<" ("<<x<<","<<y<<") ";}
private:
   double x ,y;
};

class myTriangle
{
private:
    myPoint p1;
    myPoint p2;
    myPoint p3;
public :
    myTriangle (int x1=0,int y1=0,int x2=0,int y2=0,int x3=0,int y3=0):p1(x1,y1),p2(x2,y2),p3(x3,y3){;}
    double GetRound()
    {
        double a,b,c;
        a=p1.GetLength(p2);
        b=p2.GetLength(p3);
        c=p3.GetLength(p1);
        return a+b+c;
    }
    double GetArea()
    {
        double a,b,c;
        a=p1.GetLength(p2);
        b=p2.GetLength(p3);
        c=p3.GetLength(p1);
        double p=(a+b+c)/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));

    }
};

int main()
{
    myTriangle mt(0,0,0,3,4,0);
    cout<<"面积为:"<<mt.GetArea()<<endl;
    cout<<"周长为"<<mt.GetRound()<<endl;
    return 0;
}
