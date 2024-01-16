#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int n,m,k,a[N],cnt;
int nu[N<<1],dp[N<<1][2];//0历史1当前
bool v[N<<1];
bool val(int a){return a>0 && a<2e6+10;}
int main()
{
    cin>>n>>k;
    int x;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        a[i] = x+N;
        v[a[i]] = 1;
        nu[a[i]] ++;
    }
    for(int i=1;i<=n;i++)
    {
        int no = a[i];
        if(val(no-k) && v[no-k] && dp[no][1]>0)
        {
            dp[no][1] --;
        }
        if(val(no+k) && v[no+k])
        {
            dp[no+k][1] ++;
            dp[no+k][0] = max(dp[no+k][0],dp[no+k][1]);
        }
    }
    int ans = 0;
    for(int i=1;i<=2e6;i++)
    {
        ans = max(ans,dp[i][0]+nu[i]);
    }
    cout<<ans;
    return 0;
}