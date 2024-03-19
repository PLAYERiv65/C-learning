#include<bits/stdc++.h>
using namespace std;
const int N = 5010;
int n,pri[N];
int ans[N][2],ml=1,mn;//0长度，1方案数
bool v[N];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>pri[i];
        ans[i][0] = 1;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(pri[j]>pri[i])
            {
                ans[i][0] = max(ans[i][0],ans[j][0]+1);
                ml = max(ml,ans[i][0]);
            }
        }
        for(int j=1;j<i;j++)
        {
            if(ans[j][0]+1 == ans[i][0] && pri[j]>pri[i])//只需要更新最长的
            {
                ans[i][1] += ans[j][1];
            }
            if(ans[j][0] == ans[i][0] && pri[j] == pri[i])
            {
                ans[j][1] = 0;
            }
        }
        if(!ans[i][1]) ans[i][1] = 1;
    }
    for(int i=1;i<=n;i++)
    {
        if(ans[i][0] == ml) mn += ans[i][1];
    }
    cout<<ml<<" "<<mn;
    return 0;
}