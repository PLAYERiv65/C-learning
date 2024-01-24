#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MP = 1e7+10;
int phi[MP],t;//欧拉函数
void pre()
{
    phi[1] = 1;
    for(int i = 2; i < MP; i++)
    {
        if(!phi[i])
        {
            for(int j = i; j < MP; j += i)
            {
                if(!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}
int ksm(ll a,ll p,ll mo)//快速幂
{
    ll ans = 1;
    while(p)
    {
        if(p&1) ans *= a, ans %= mo;
        a *= a, a %= mo;
        p >>= 1;
    }
    return ans;
}
int solve(ll mo)//无穷次%mo是多少
{
    if(mo == 1) return 0;
    return ksm(2,solve(phi[mo])+phi[mo],mo);
}
int main()
{
    pre();
    scanf("%d",&t);
    while(t--)
    {
        ll p;
        scanf("%lld",&p);
        printf("%d\n",solve(p));
    }
    return 0;
}