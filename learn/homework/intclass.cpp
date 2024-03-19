#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

class integer{
private:
    int n;
public:
    int get();
};

int integer::get()
{
    return n;
}