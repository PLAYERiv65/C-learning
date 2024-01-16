#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mo = 998244353;
ll n,p[100010][2];
ll xs=0,cs=0;
ll ny(ll a)
{
    ll mi = mo-2,ans = 1;
    while(mi)
    {
        if(mi&1) ans *= a;
        a *= a;
        ans %= mo;
        a %= mo;
        mi >>= 1;
    }
    return ans;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&p[i][0],&p[i][1]);
    }
    for(int i=n-1;i>=0;i--)
    {
        xs = xs*(p[i+1][1]-p[i+1][0])%mo*ny(p[i+1][1])%mo;
        cs = cs*(p[i+1][1]-p[i+1][0])%mo*ny(p[i+1][1])%mo;
        xs = (xs+p[i+1][0]*ny(p[i+1][1])%mo)%mo;
        cs = (cs+1)%mo;
    }
    cout<<(mo-cs)*ny(xs-1)%mo;
    return 0;
}