#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
short int n,fz[N][N][2];
short int dp[N][N][2];
int main()
{
    cin>>n;
    int d;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&d);
            while(!d%2)
            {
                d >>= 1;
                fz[i][j][0]++;
            }
            while(!d%5)
            {
                d /= 5;
                fz[i][j][1]++;
            }
        }
    }
    return 0;
}