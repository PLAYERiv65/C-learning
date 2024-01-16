#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
struct bian{
    int to,next,w;
}bi[N<<1];
int n,cnt,head[N],dp[N][2],ans=-2e9;
void pb(int a,int b,int c)
{
    bi[++cnt].to = b;
    bi[cnt].w = c;
    bi[cnt].next = head[a];
    head[a] = cnt;
}
void dfs(int a,int fa)
{
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        if(so == fa) continue;
        dfs(so,a);
        if(bi[i].w>dp[a][0])
        {
            dp[a][1] = dp[a][0];
            dp[a][0] = bi[i].w;
        }
        else if(bi[i].w>dp[a][1])
        {
            dp[a][1] = bi[i].w;
        }
        if(dp[so][0] + bi[i].w>dp[a][0])
        {
            dp[a][1] = dp[a][0];
            dp[a][0] = dp[so][0]+bi[i].w;
        }
        else if(dp[so][0]+bi[i].w>dp[a][1])
        {
            dp[a][1] = dp[so][0]+bi[i].w;
        }
    }
    ans = max(ans,dp[a][0]+dp[a][1]);
}
int main()
{
    memset(head,0xff,sizeof(head));
    memset(dp,0xc0,sizeof(dp));
    cin>>n;
    int u,v,w;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        pb(u,v,w);
        pb(v,u,w);
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}