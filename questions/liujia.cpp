#include<bits/stdc++.h>
using namespace std;
int main()
{
    //计算积分近似值,2的x次方除x的积分，从1到2
    double sum=0;
    for(double i=1;i<=2;i+=0.0001)
    {
        sum+=0.0001*(pow(2,i)/i);
    }
    cout<<sum<<endl;
    return 0;
}