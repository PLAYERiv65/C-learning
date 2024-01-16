#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
struct bian{
    int to,next;
}bi[N<<1];
int n,col[N],cnt,head[N];
bool tg = 0,tg2 = 0;
void pb(int a,int b)
{
    bi[++cnt].to = b;
    bi[cnt].next = head[a];
    head[a] =  cnt;
}
void dfs(int a,int fa)
{
    printf("%d ",a);
    if(tg || a!=1)
    {
        col[a] = 0-col[a];
        tg = 1;
    }
    bool tag = 0;
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        if(so == fa) continue;
        tag = 1;
        dfs(so,a);
        printf("%d ",a);
        col[a] = 0-col[a];
    }
    if(col[a]!=1 && a!=1)
    {
        col[a] = 1;
        col[fa] = 0-col[fa];
        printf("%d %d ",fa,a);
    }
    else if(col[a]!=1)
    {
        printf("%d %d %d",bi[head[a]].to,a,bi[head[a]].to);
    }
}
int main()
{
    memset(head,0xff,sizeof(head));
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&col[i]);
        if(col[i] != 1) tg2 = 1;
    }
    if(!tg2)
    {
        cout<<1;
        return 0;
    }
    int u,v;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        pb(u,v);
        pb(v,u);
    }
    dfs(1,0);
    return 0;
}