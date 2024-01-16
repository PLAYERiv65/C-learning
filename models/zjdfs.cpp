#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
struct bian{
    int to,next,w;
}bi[N<<1];
bool tg;
int n,k,head[N],cnt,rt,dis,pre[N],z1,z2,dep[N];
bool cmp(int a,int b){return a>b;}
void pb(int a,int b,int c)
{
    bi[++cnt].to = b;
    bi[cnt].w = c;
    bi[cnt].next = head[a];
    head[a] = cnt;
}
void dfs(int fa,int a,int d)
{
    bool tag = 0;
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        if(bi[i].to == fa) continue;
        tag = 1;
        tg = 1;
        pre[bi[i].to] = a;
        dfs(a,bi[i].to,d+bi[i].w);
    }
    if(d > dis && tg)
    {
        dis = d;
        z2 = a;
    }
}
int main()
{
    memset(head,0xff,sizeof(head));
    dis = -2e9;
    cin>>n;
    int u,v,w;
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        pb(u,v,w);
        pb(v,u,w);
    }
    tg = 0;
    dfs(0,1,0);
    z1 = z2;
    dis = -2e9;
    tg = 0;
    dfs(0,z1,0);
    rt = z2;
    cout<<dis;
    return 0;
}