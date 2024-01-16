#include<bits/stdc++.h>
using namespace std;
const ll N = 1e8+10;
ll n,q,k,p[N],cnt;
bool isp[N];
ll main()
{
    cin>>n>>q;
    memset(isp,1,sizeof(isp));
    for(ll i=2;i<=n;i++)
    {
        if(isp[i]) p[++cnt] = i;
        for(ll j=1;j<=cnt && p[j]*i<=n;j++)
        {
            isp[p[j]*i] = 0;
            if(!(i%p[j])) break;
        }
    }
    for(ll i=1;i<=q;i++)
    {
        scanf("%d",&k);
        prllf("%d\n",p[k]);
    }
    return 0;
}