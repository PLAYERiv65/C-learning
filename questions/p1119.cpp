#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 210;
struct TIME{
    ll num,ti;
}tt[N];
bool operator<(const TIME a,TIME b){return a.ti<b.ti;}
ll n,m,dis[N][N],rd[N][N],q,cnt;//0循环到cnt-1
bool vi[N];
int main()
{
    memset(rd,0x3f,sizeof(rd));
    memset(dis,0x3f,sizeof(dis));
    ll inf = rd[0][0];
    cin>>n>>m;
    for(ll i=0;i<=n-1;i++)
    {
        scanf("%lld",&tt[i].ti);
        tt[i].num = i;
        rd[i][i] = dis[i][i] =0;
    }
    sort(tt,tt+n);
    ll u,v,w;
    for(ll i=1;i<=m;i++)
    {
        scanf("%lld%lld%lld",&u,&v,&w);
        rd[u][v] = rd[v][u] = w;
    }
    cin>>q;
    ll x,y,t;
    while(q--)
    {
        scanf("%lld%lld%lld",&x,&y,&t);
        while(tt[cnt].ti<=t && cnt<=n)
        {
            ll no = tt[cnt].num;
            cnt++;
            for(ll i=0;i<n-1;i++)
            {
                dis[no][i] = dis[i][no] = min(dis[i][no],rd[i][no]);
            }
            for(int k=1;k<=3;k++)
            {
                for(ll i=0;i<=n-1;i++)
                {
                    for(ll j=0;j<=n-1;j++)
                    {
                        dis[i][no] = dis[no][i] = min(dis[i][no],dis[i][j]+dis[j][no]);
                        dis[j][no] = dis[no][j] = min(dis[j][no],dis[j][i]+dis[i][no]);
                        dis[i][j] = dis[j][i] = min(dis[i][j],dis[i][no]+dis[no][j]);
                    }
                }
            }
        }
        if(dis[x][y] == inf) printf("-1\n");
        else printf("%lld\n",dis[x][y]);
    }
    return 0;
}