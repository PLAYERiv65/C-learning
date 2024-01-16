#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mo = 998244353;
ll n,jc,w,ans;
ll ny(ll a)
{
    ll mi = mo-2,n=1;
    while(mi)
    {
        if(mi&1)
        {
            n*=a;
            n%=mo;
        }
        mi = mi>>1;
        a = a*a%mo;
    }
    return n;
}
int main()
{
    cin>>n;
    jc = 1;
    for(int i=1;i<=n;i++)
    {
        jc = (jc*i)%mo;
    }
    for(int i=1;i<=n-1;i++)
    {
        ll mul = (jc*ny(n-i+1))%mo;
        for(int j=i;j<=n;j++)
        {
            scanf("%lld",&w);
            ans += mul*w%mo;
            ans %= mo;
        }
    }
    cout<<ans%mo;
    return 0;
}