#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
ll y,r,ansb,lb,rb;
bool tag = 0,tag2 = 0;
ll ck(ll b)
{
    ll yt = y,ti = 1,ans = 0;
    while(yt)
    {
        if(yt%b > 9) return 0;
        ans += ti * (yt%b);
        yt /= b;
        ti *= 10;
    }
    if(ans < r) return 0;
    return 1;
}
bool ckr(ll b,ll r=r)
{
    ll ans = 0,rt = r,bt = 1;
    while(rt)
    {
        ans += bt * (rt%10);
        if(ans > y) return 1;
        rt /= 10;
        bt *= b;
    }
    if(ans == y)
    {
        tag2 = 1;
    }
    return 0;
}
int main()
{
    cin>>y>>r;
    for(ll b=1e5;b>=10;b--)
    {
        if(ck(b))
        {
            ansb = max(ansb,b);
            break;
        }
    }
    lb = 1e5;
    rb = 1e18;
    while(rb-lb > 1)
    {
        ll mid = (lb+rb)>>1;
        bool c = ckr(mid);
        if(c) rb = mid;
        else lb = mid;
    }
    lb = 1e5;
    rb += 10;
    for(ll rt=0;rt<=1e4;rt++)
    {
        ll lbt = lb,rbt = rb;
        if(rt>=100) rbt = min(rbt,(ll)1e9);
        if(rt>=1000) rbt = min(rbt,(ll)1e6);//防止直接爆ll，无法与y正常比大小
        if(rt<r) continue;
        while(rbt-lbt > 1)
        {
            ll mid = (lbt+rbt)>>1;
            bool c = ckr(mid,rt);
            if(c) rbt = mid;
            else lbt = mid;
        }
        tag2 = 0;
        ckr(lbt,rt);
        if(tag2) ansb = max(ansb,lbt);
        tag2 = 0;
        ckr(rbt,rt);
        if(tag2) ansb = max(ansb,rbt);
    }
    cout<<ansb;
    return 0;
}