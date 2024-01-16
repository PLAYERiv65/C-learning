#include<bits/stdc++.h>
using namespace std;
struct pj{
    int d,v;
}p[1010];
bool operator<(const pj a,pj b){return a.d<b.d;}
int n,m,k,cnt,md;
int rq[40][40],mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
bool dp[400][5010];
int main()
{
    for(int i=1;i<=12;i++)
    {
        for(int j=1;j<=mon[i];j++)
        {
            rq[i][j] = ++cnt;
        }
    }
    cin>>n>>m>>k;
    int mm,d,v;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&mm,&d,&v);
        p[i].d = rq[mm][d];
        md = max(md,p[i].d);
        p[i].v = v;
    }
    sort(p+1,p+n+1);
    for(int i=0;i<=365;i++)
    {
        dp[i][0] = 1;
    }
    int dpin = 0;
    for(int i=1;i<=n;i++)
    {
        if(dpin != p[i].d)
        {
            for(int j=dpin+1;j<=p[i].d-1;j++)
            {
                memcpy(dp[j],dp[dpin],sizeof(dp[j]));//memcpy大法好
            }
            dpin = p[i].d;
        }
        for(int j=0;j<=m;j++)
        {
            dp[p[i].d][j] |= dp[p[i].d-1][j];
            if(j-p[i].v>=0) dp[p[i].d][j] |= dp[max(p[i].d-k,0)][j-p[i].v];
        }
    }
    for(int i=m;i>=0;i--)
    {
        if(dp[md][i])
        {
            cout<<i;
            return 0;
        }
    }
    return 0;
}