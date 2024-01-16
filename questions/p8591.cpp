#include<bits/stdc++.h>
using namespace std;
int n;
struct xd{
    int l,r;
}line[3010];
int dp[3010];
bool tag;
bool cmp(xd a,xd b){return a.l<b.l;}
bool xj(int a,int b)
{
    return line[a].l<=line[b].r && line[b].l<=line[a].r;
}
int main()
{
    memset(dp,0x3f,sizeof(dp));
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&line[i].l,&line[i].r);
    }
    sort(line+1,line+n+1,cmp);
    dp[0] = 0;
    line[0].r = -2e9;//如何用0来更新别的状态
    for(int i=1;i<=n;i++)
    {
        int zd = -2e9;
        for(int j=i-1;j>=0;j--)
        {
            if(xj(i,j) || line[j].r<zd) continue;
            zd = max(zd,line[j].l);
            dp[i] = min(dp[i],dp[j] + line[i].r-line[i].l);
        }
    }
    int ans = 2e9;
    for(int i=n;i>=1;i--)
    {
        if(line[i].r<line[n].l) break;
        ans = min(ans,dp[i]);
    }
    cout<<ans;
    return 0;
}