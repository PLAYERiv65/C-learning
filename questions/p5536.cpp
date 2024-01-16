#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
struct bian{
    int to,next;
}bi[N<<1];
int n,k,head[N],cnt,rt,dis,pre[N],z1,z2,dep[N];
bool cmp(int a,int b){return a>b;}
void pb(int a,int b)
{
    bi[++cnt].to = b;
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
        pre[bi[i].to] = a;
        dfs(a,bi[i].to,d+1);
    }
    if(d > dis)
    {
        dis = d;
        z2 = a;
    }
}
int dfs2(int fa,int a)
{
    int dn = 1;
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        if(bi[i].to == fa) continue;
        dn = max(dn,dfs2(a,bi[i].to)+1);
    }
    dep[a] = dn;
    return dn;
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
    dfs(0,1,0);
    z1 = z2;
    z2 = 0;
    dis = 0;
    memset(pre,0,sizeof(pre));
    dfs(0,z1,0);
    rt = z2;
    for(int i=1;i<=dis>>1;i++)
    {
        rt = pre[rt];
    }
    dfs2(0,rt);
    sort(dep+1,dep+n+1,cmp);
    cout<<dep[k+1];
    return 0;
}