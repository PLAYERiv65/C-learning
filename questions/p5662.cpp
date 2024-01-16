#include<bits/stdc++.h>
using namespace std;
int t,n,m,pri[110][110];
int dp[10010];
int main()
{
    cin>>t>>n>>m;
    for(int i=1;i<=t;i++)
    {
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&pri[i][j]);
        }
    }
    for(int i=2;i<=t;i++)
    {
        memset(dp,0,sizeof(dp));
        for(int j=1;j<=m;j++)
        {
            dp[j] = j; 
        }
        for(int j=1;j<=n;j++)
        {
            for(int k=pri[i-1][j];k<=m;k++)
            {
                dp[k] = max(dp[k],dp[k-pri[i-1][j]]+pri[i][j]);
            }
        }
        m = dp[m];
    }
    cout<<m;
    return 0;
}