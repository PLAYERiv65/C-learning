#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int main()
{
    cin>>n>>m;
    ans += (n/2) * (m/2);
    if(n%2) ans += m/2;
    if(m%2) ans += n/2;
    if(n%2 && m%2) ans += 1;
    cout<<ans;
    return 0;
}