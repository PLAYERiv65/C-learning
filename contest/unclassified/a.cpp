#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5+10;
struct bian{
    int to,next;
}bi[N<<1];
int n,k,cnt,head[N];
ll ans,tot[N][6],ls[6];
void pb(int a,int b)
{
    bi[++cnt].to = b;
    bi[cnt].next = head[a];
    head[a] = cnt;
}
void dfs1(int a,int fa)
{
    tot[a][0] = 1;
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        if(so == fa) continue;
        dfs1(so,a);
        for(int j=1;j<=k;j++)
        {
            tot[a][j%k] += tot[so][j-1];
        }
        tot[a][k] += tot[so][k-1] + tot[so][k];
    }
}
void dfs2(int a,int fa)
{
    memcpy(ls,tot[a],sizeof(ls));
    for(int j=1;j<=k;j++)
    {
        tot[a][j%k] += tot[fa][j-1] - ls[(j+k-2)%k];
    }
    tot[a][k] = tot[fa][k-1] - ls[(2*k-2)%k] + tot[fa][k] - ls[k-1];
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        if(so == fa) continue;
        dfs2(so,a);
    }
}
int main()
{
    memset(head,0xff,sizeof(head));
    cin>>n>>k;
    int u,v;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        pb(u,v);
        pb(v,u);
    }
    dfs1(1,0);
    for(int i=head[1];i!=-1;i=bi[i].next)
    {
        dfs2(bi[i].to,1);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            ans += tot[i][j];
        }
    }
    cout<<(ans>>1);
    return 0;
}