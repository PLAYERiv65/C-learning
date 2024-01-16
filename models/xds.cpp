#include<bits/stdc++.h>
#define ll long long
const ll N = 1e5+10;
using namespace std;
ll n,m,d[N];
ll sum[N<<2],add[N<<2];
void bd(ll l,ll r,ll rt)
{
    if(l == r)
    {
        sum[rt] = d[r];
        return;
    }
    ll mid = (l+r)>>1;
    bd(l,mid,rt<<1);
    bd(mid+1,r,rt<<1|1);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void pd(ll rt,ll ln,ll rn)
{
    add[rt<<1] += add[rt];
    add[rt<<1|1] += add[rt];
    sum[rt<<1] += add[rt] * ln;
    sum[rt<<1|1] += add[rt] * rn;
    add[rt] = 0;
}
void ad(ll lu,ll ru,ll v,ll l,ll r,ll rt)
{
    if(lu <= l && r <= ru)
    {
        add[rt] += v;
        sum[rt] += v*(r-l+1);
        return ;
    }
    ll mid = (l+r)>>1;
    pd(rt,mid-l+1,r-mid);
    if(lu <= mid) ad(lu,ru,v,l,mid,rt<<1);
    if(ru > mid) ad(lu,ru,v,mid+1,r,rt<<1|1);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
ll cx(ll lc,ll rc,ll l,ll r,ll rt)
{
    if(lc <= l && r <= rc)
    {
        return sum[rt];
    }
    ll mid = (l+r)>>1;
    ll ans = 0;
    pd(rt,mid-l+1,r-mid);
    if(lc <= mid) ans += cx(lc,rc,l,mid,rt<<1);
    if(rc > mid) ans += cx(lc,rc,mid+1,r,rt<<1|1);
    return ans;
}
int main()
{
    cin>>n>>m;
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&d[i]);
    }
    bd(1,n,1);
    ll o,x,y,k;
    for(ll i=1;i<=m;i++)
    {
        scanf("%d",&o);
        if(o == 1)
        {
            scanf("%d%d%d",&x,&y,&k);
            ad(x,y,k,1,n,1);
        }
        else
        {
            scanf("%d%d",&x,&y);
            printf("%lld\n",cx(x,y,1,n,1));
        }
    }
    return 0;
}