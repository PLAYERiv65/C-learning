#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,p,s;
ll mi(ll a,ll b)
{
    ll ans = 1;
    while(b)
    {
        if(b&1)
        {
            ans *= a;
            ans %= p;
        }
        a *= a;
        a %= p;
        b >>= 1;
    }
    return ans;
}
ll main()
{
    scanf("%lld%lld%lld",&a,&b,&p);
    prllf("%lld^%lld mod %lld=%lld",a,b,p,mi(a,b));
    return 0;
}