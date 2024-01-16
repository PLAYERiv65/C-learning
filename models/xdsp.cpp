#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 1e5+10;
ll n,q,m,d[N];
ll sum[N<<2],add[N<<2],mul[N<<2];
void bd(ll l,ll r,ll rt)
{
    if(l == r)
    {
        sum[rt] = d[l];
        return ;
    }
    ll mid = (l+r)>>1;
    bd(l,mid,rt<<1);
    bd(mid+1,r,rt<<1|1);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
    sum[rt] %= m;
    mul[rt] = 1;
}
void pd(ll rt,ll ln,ll rn)
{
    add[rt<<1] = (add[rt<<1]*mul[rt] + add[rt]) % m;
    add[rt<<1|1] = (add[rt<<1|1]*mul[rt] + add[rt]) % m;
    mul[rt<<1] = (mul[rt<<1]*mul[rt]) % m;
    mul[rt<<1|1] = (mul[rt<<1|1]*mul[rt]) % m;
    sum[rt<<1] = (sum[rt<<1]*mul[rt] + ln * add[rt]) % m;
    sum[rt<<1|1] = (sum[rt<<1|1]*mul[rt] + rn * add[rt]) % m;
    add[rt] = 0;
    mul[rt] = 1;
}
void ad(ll lu,ll ru,ll v,ll l,ll r,ll rt)
{
    if(lu <= l && r <= ru)
    {
        add[rt] = (add[rt] + v) % m;
        sum[rt] = (sum[rt] + (r-l+1)*v) % m;
        return ;
    }
    ll mid = (l+r)>>1;
    pd(rt,mid-l+1,r-mid);
    if(lu <= mid) ad(lu,ru,v,l,mid,rt<<1);
    if(ru > mid) ad(lu,ru,v,mid+1,r,rt<<1|1);
    sum[rt] = (sum[rt<<1] + sum[rt<<1|1]) % m;
}
void mu(ll lu,ll ru,ll v,ll l,ll r,ll rt)
{
    if(lu <= l && r <= ru)
    {
        add[rt] = (add[rt] * v) % m;
        mul[rt] = (mul[rt] * v) % m;
        sum[rt] = (sum[rt] * v) % m;
        return ;
    }
    ll mid = (l+r)>>1;
    pd(rt,mid-l+1,r-mid);
    if(lu <= mid) mu(lu,ru,v,l,mid,rt<<1);
    if(ru > mid) mu(lu,ru,v,mid+1,r,rt<<1|1);
    sum[rt] = (sum[rt<<1] + sum[rt<<1|1]) % m;
}
ll cx(ll lu,ll ru,ll l,ll r,ll rt)
{
    if(lu <= l && r <= ru)
    {
        return sum[rt];
    }
    ll mid = (l+r)>>1,ans=0;
    pd(rt,mid-l+1,r-mid);
    if(lu <= mid) ans += cx(lu,ru,l,mid,rt<<1);
    if(ru > mid) ans += cx(lu,ru,mid+1,r,rt<<1|1);
    ans %= m;
    return ans;
}
int main()
{
    cin>>n>>q>>m;
    for(ll i=1;i<=n;i++)
    {
        scanf("%lld",&d[i]);
    }
    bd(1,n,1);
    ll o,x,y,k;
    for(ll i=1;i<=q;i++)
    {
        scanf("%lld%lld%lld",&o,&x,&y);
        if(o == 1)
        {
            scanf("%lld",&k);
            mu(x,y,k,1,n,1);
        }
        else if(o == 2)
        {
            scanf("%lld",&k);
            ad(x,y,k,1,n,1);
        }
        else
        {
            printf("%lld\n",cx(x,y,1,n,1)%m);
        }
    }
    return 0;
}