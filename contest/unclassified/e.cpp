#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mo = 1000000007;
ll n,dp[2][100010],qz[2][100010],ans=1;
ll ny(ll a)
{
    ll mi = mo-2,nny = 1;
    while(mi)
    {
        if(mi&1) nny *= a;
        nny %= mo;
        a *= a;
        a %= mo;
        mi >>= 1;
    }
    return nny;
}
int main()
{
    cin>>n;
    ll t = n-1,mu = 2*n-1;
    while(t--)
    {
        ans *= mu;
        ans %= mo;
        mu--;
    }
    t = n-1;
    while(t)
    {
        ans *= ny(t);
        ans %= mo;
        t--;
    }
    cout<<(ans<<1)%mo-n;
    return 0;
}