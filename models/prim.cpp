#include<bits/stdc++.h>
using namespace std;
const ll M = 200010;
struct bian{
    ll u,v,w;
}bi[M];
bool cmp(bian a,bian b){return a.w<b.w;}
ll n,m,f[5010],cnt,ans;
ll find(ll a)
{
    if(f[a] == a) return a;
    return f[a] = find(f[a]);
}
ll main()
{
    cin>>n>>m;
    for(ll i=1;i<=n;i++){f[i]=i;}
    for(ll i=1;i<=m;i++)
    {
        scanf("%d%d%d",&bi[i].u,&bi[i].v,&bi[i].w);
    }
    sort(bi+1,bi+m+1,cmp);
    for(ll i=1;i<=m;i++)
    {
        if(find(bi[i].u) == find(bi[i].v)) continue;
        f[find(bi[i].u)] = find(bi[i].v);
        cnt++;
        ans += bi[i].w;
        if(cnt == n-1)
        {
            cout<<ans;
            return 0;
        }
    }
    cout<<"orz";
    return 0;
}