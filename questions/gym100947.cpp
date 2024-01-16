#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int t,n,m = N,d[10010],ans,nn;
int a[N];
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        m = N;
        ans = 0;
        memset(a,0,sizeof(a));
        scanf("%d",&n);
        int x;
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&x);
            m = max(m,x);
            d[j] = x;
            if(a[x])
            {
                d[j] = 0;
                j--;
                n--;
            }
            a[x] += 1;
        }
        for(int j=1;j<=n;j++)
        {
            if(a[d[j]]>=2)
            {
                ans += (a[d[j]]*(a[d[j]]-1))>>1;
            }
            for(int k = 2;d[j]*k<=m;k++)
            {
                ans += a[d[j]]*a[d[j]*k];
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}