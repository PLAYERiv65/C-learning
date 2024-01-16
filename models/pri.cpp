#include<bits/stdc++.h>
using namespace std;
const ll M = 200010,inf = 2e9;
struct bian{
    ll to,next,w;
}bi[M<<1];
struct dist{
    ll po,di;
};
priority_queue <dist> dis;
bool operator < (const dist a,dist b)
{
    return a.di > b.di;
}
ll n,m,head[M],cnt,dise[5010];
bool v[5010];
void pb(ll a,ll b,ll c)
{
    bi[++cnt].to = b;
    bi[cnt].w = c;
    bi[cnt].next = head[a];
    head[a] = cnt;
}
ll main()
{
    cin>>n>>m;
    memset(dise,0x7f,sizeof(dise));
    memset(head,0xff,sizeof(head));
    ll a,b,c;
    for(ll i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        pb(a,b,c);
        pb(b,a,c);
    }
    dis.push(dist({1,0}));
    dise[1] = 0;
    ll tot = 0,ans = 0;
    ll hb,db;
    while(tot < n)
    {
        if(dis.empty())
        {
            cout<<"orz";
            return 0;
        }
        hb = dis.top().po;
        db = dis.top().di;
        dis.pop();
        if(v[hb]) continue;
        v[hb] = 1;
        tot += 1;
        ans += db;
        for(ll i=head[hb];i!=-1;i=bi[i].next)
        {
            ll so = bi[i].to;
            if(bi[i].w < dise[so])
            {
                dise[so] = bi[i].w;
                dis.push(dist({so,dise[so]}));
            }
        }
    }
    cout<<ans;
    return 0;
}