#include<bits/stdc++.h>
using namespace std;
int t,n,a[110],m,ans;
bool v[50010],vm[50010];
bool cmp(int a,int b){return a<b;}
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>n;
        m = 0;
        ans = n;
        for(int j=1;j<=n;j++)
        {
            cin>>a[j];
            m = max(a[j],m);
        }
        memset(v,0,sizeof(v));
        v[0] = 1;
        sort(a+1,a+n+1,cmp);
        for(int j=1;j<=n;j++)
        {
            memset(vm,0,sizeof(vm));
            if(v[a[j]])
            {
                ans -= 1;
                continue;
            }
            for(int k=0;k<=m;k++)
            {
                if(!v[k] || vm[k%a[j]]) continue;
                vm[k%a[j]] = 1;
                for(int x=1;k+x*a[j]<=m;x++)
                {
                    v[k+x*a[j]] = 1;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}