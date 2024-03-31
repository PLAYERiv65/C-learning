#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    bool tag = 0;
    int m=-2e9,n=0;
    while(1)
    {
        if(!(cin>>n)) break;
        if(n==0)
        {
            if(tag) cout<<endl<<m;
            else 
            {
                tag = 1;
                cout<<m;
            }
            m = -2e9;
            continue;
        }
        m = max(m,n);
    }
    return 0;
}