#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a,b,ans;
int main()
{
    cin>>a>>b;
    while(a != b)
    {
        if(a == 0 || b == 0)
        {
            cout<<ans;
            return 0;
        }
        if(a<b) swap(a,b);
        ll t = a/b;
        ans += t;
        a -= b*t;
    }
    cout<<ans +1;
    return 0;
}