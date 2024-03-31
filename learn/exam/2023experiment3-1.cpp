#include<iostream>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
const double pi = 3.14;
class Circle{
private:
    float r;
public:
    Circle(float r):r(r){}
    float getr(){return r;}
    float gets(){return pi*r*r;}
    float getc(){return 2*pi*r;}
};
int main()
{
    float r;
    cin>>r;
    Circle c(r);
    cout<<c.getc()<<" "<<c.gets();
    return 0;
}