#include<bits/stdc++.h>
using namespace std;
const int N = 60;
int m,n,dp[N][N][N][N],ww[N][N];
int main()
{
    cin>>m>>n;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>ww[i][j];
        }
    }
    for(int x=1;x<=m;x++)
    {
        for(int y=1;y<=n;y++)
        {
            for(int z=1;z<=m;z++)
            {
                for(int w=1;w<=n;w++)
                {
                    dp[x][y][z][w] = max(max(dp[x-1][y][z-1][w],dp[x][y-1][z][w-1]),max(dp[x-1][y][z][w-1],dp[x][y-1][z-1][w])) + ww[x][y] + ww[z][w];
                    if(x==z && y==w && !(x==m && y==n)) dp[x][y][z][w] = -1;
                }
            }
        }
    }
    cout<<dp[m][n][m][n];
    return 0;
}