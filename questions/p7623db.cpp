#include<bits/stdc++.h>
using namespace std;
int pl[20],pll[20],ti[20][20],cnt;
bool v[20];
void dfs(int n)
{
    if(cnt == n)
    {
        memcpy(pll,pl,sizeof(pl));
        for(int i=1;i<=n-1;i++)
        {
            for(int j=i;j<=n;j++)
            {
                if(pl[j] == i)
                {
                    for(int k=1;k<=(j-i+1)>>1;k++)
                    {
                        swap(pl[i+(k-1)],pl[j-(k-1)]);
                    }
                    ti[i][j] += 1;
                }
            }
        }
        memcpy(pl,pll,sizeof(pl));
        return;
    }
    for(int i=1;i<=n;i++)
    {
        if(v[i]) continue;
        v[i] = 1;
        pl[++cnt] = i;
        dfs(n);
        pl[cnt--] = 0;
        v[i] = 0;
    }
}
int main()
{
    for(int i=1;i<=10;i++)
    {
        memset(ti,0,sizeof(ti));
        memset(v,0,sizeof(v));
        dfs(i);
        for(int j=1;j<=i;j++)
        {
            for(int k=1;k<=i;k++)
            {
                cout<<ti[j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    return 0;
}