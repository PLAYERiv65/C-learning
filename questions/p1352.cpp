#include<bits/stdc++.h>
using namespace std;
const int N = 1e4;
struct bian{
    int to,next;
}bi[N<<1];
int n,r[N],cnt,head[N],dp[N][2],ma;
bool v[N];
void pb(int a,int b)
{
    bi[++cnt].to = b;
    bi[cnt].next = head[a];
    head[a] = cnt;
}
void dfs(int a,int fa)
{
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        dfs(so,a);
        dp[a][0] += max(dp[so][0],dp[so][1]);
        dp[a][1] += dp[so][0];
    }
    dp[a][1] += r[a];
}
int main()
{
    memset(head,0xff,sizeof(head));
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&r[i]);
    }
    int l,k;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&l,&k);
        pb(k,l);
        v[l] = 1;
    }
    for(int i=1;i<=n;i++)
    {
        if(!v[i]) ma = i;
    }
    dfs(ma,0);
    cout<<max(dp[ma][1],dp[ma][0]);
    return 0;
}