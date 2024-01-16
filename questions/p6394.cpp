#include<bits/stdc++.h>
using namespace std;
const int mo = 10086001;
int n,k,s[5010],sum,ans;
int dp[5010],qz[5010];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        scanf("%d",&s[i]);
        sum += s[i];
    }
    if(sum < n)
    {
        cout<<"impossible";
        return 0;
    }
    dp[0] = 1;
    qz[0] = 1;
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            qz[j] = qz[j-1] + dp[j];
            qz[j] %= mo;
        }
        for(int j=n;j>=1;j--)
        {
            if(j <= s[i]) dp[j] = qz[j];
            else dp[j] = qz[j] - qz[j-s[i]-1];
            dp[j] %= mo;
        }
        ans += dp[n];
        ans %= mo;
    }
    while(ans<0){ans += mo;}
    cout<<ans;
    return 0;
}