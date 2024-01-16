#include<bits/stdc++.h>
using namespace std;
const int N = 3e2+10;
int n,m,ml[N][N][2],ans;//0右1下
bool bl[N][N];
bool lt(int x1,int y1,int x2,int y2)
{
    if(ml[x1][y1][0] <= y2-y1 || ml[x1][y1][1] <= x2-x1) return 0;
    if(ml[x2][y1][0] <= y2-y1 || ml[x1][y2][1] <= x2-x1) return 0;
    return 1;
}
int main()
{
    cin>>n>>m;
    char ma;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>ma;
            if(ma == 'X') bl[i][j] = 1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k1=j;k1<=m+1;k1++)
            {
                if(bl[i][k1] || k1 == m+1)
                {
                    ml[i][j][0] = k1-j;
                    break;
                }
            }
            for(int k2=i;k2<=n+1;k2++)
            {
                if(bl[k2][j] || k2 == n+1)
                {
                    ml[i][j][1] = k2-i;
                    break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=ml[i][j][0];k*ml[i][j][1]>ans;k--)
            {
                for(int w=ml[i][j][1];k*w>ans;w--)
                {
                    if(lt(i,j,i+w-1,j+k-1))
                    {
                        ans = max(ans,k*w);
                    }
                }
            }
        }
    }
    cout<<ans;
    return 0;
}