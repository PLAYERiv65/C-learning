#include<bits/stdc++.h>
using namespace std;
int l1,r1=2e9,l2,r2=2e9,n,m;
int main()
{
    cin>>n;
    int l,r;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&l,&r);
        l1 = max(l1,l);
        r1 = min(r1,r);
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&l,&r);
        l2 = max(l2,l);
        r2 = min(r2,r);
    }
    cout<<max(0,max(l2-r1,l1-r2));
    return 0;
}