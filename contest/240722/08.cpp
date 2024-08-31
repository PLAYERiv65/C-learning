#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 1e5+10;
const ll mo = 1e9+7;

struct edge{
    ll to,next;
}bi[N<<1];
ll T;
ll head[N],cnt,n,m,rd[N];
bool vis[N];

void pb(ll u,ll v)
{
    bi[++cnt].to = v;
    bi[cnt].next = head[u];
    head[u] = cnt;
}

ll na,nb,maxl,rt,ma,mb;
void dfs(ll now)
{
    ll tna=na,tnb=nb;
    if(rd[now]==2)
    {
        nb+=2;
    }
    else if(rd[now]>=3)
    {
        nb+=2;
        na+=rd[now]-2;
    }

    for(ll i=head[now];i!=-1;i=bi[i].next)
    {
        ll son = bi[i].to;
        if(vis[son]) continue;
        vis[son] = 1;
        dfs(son);
        vis[son] = 0;
    }

    if(rd[now]==1 && now!=1)
    {
        ll len;
        if(m<50)
        {
            len = (1<<(m-1))*(nb+2*na)-na;
        }
        else
        {
            len = (N*10)*(nb+2*na)+na+nb;
        }
        
        if(len > maxl)
        {
            maxl = len;
            ma = na;
            mb = nb;
            rt = now;
        }
    }
    na = tna,nb = tnb;
}

ll dis(ll a,ll b)
{
    ll mi = 1,ex = m-1,po=2;
    while(ex)
    {
        if(ex&1)
        {
            mi *= po;
            mi %= mo;
        }
        po *= po;
        po %= mo;
        ex >>= 1;
    }
    return ((mi*b)%mo + ((mi*2-1)*a)%mo + 2)%mo;
}

int main()
{
    //freopen("1008.in","r",stdin);
    //freopen("1008.ans","w",stdout);
    cin>>T;
    while(T--)
    {
        memset(head,0xff,sizeof(head));
        memset(rd,0,sizeof(rd));
        cnt = 0;
        cin>>n>>m;
        ll u,v;
        for(ll i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            pb(u,v);
            pb(v,u);
            rd[u]++;
            rd[v]++;
        }

        na = nb = ma = mb = maxl = rt = 0;
        memset(vis,0,sizeof(vis));
        dfs(1);
        na = nb = ma = mb = maxl = 0;
        memset(vis,0,sizeof(vis));
        dfs(rt);
        printf("%lld\n", dis(ma,mb));
        //cout<<n<<' '<<m<<endl;
    }

    //fclose(stdin);
    //fclose(stdout);
    return 0;
}