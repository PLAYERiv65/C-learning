#include<bits/stdc++.h>
using namespace std;
const int mo = 10000,N=60;
int n,m,st,ed,k,nf,tfish[12][N],lj[N][N];
struct jz{
    int mar[N][N],n,m;
    jz(){memset(mar,0,sizeof(mar));}
    jz operator*(const jz b)const
    {
        jz ans;
        ans.n=this->n;
        ans.m=b.m;
        for(int i=1;i<=this->n;i++)
        {
            for(int j=1;j<=b.m;j++)
            {
                for(int k=1;k<=this->m;k++)
                {
                    ans.mar[i][j] += this->mar[i][k]*b.mar[k][j];
                    ans.mar[i][j] %= mo;
                }
            }
        }
        return ans;
    }
};
int main()
{
    jz xh[15],e;
    cin>>n>>m>>st>>ed>>k;
    st ++;
    ed ++;
    int x,y;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        lj[x+1][y+1] = lj[y+1][x+1] = 1;
    }
    cin>>nf;
    for(int i=1;i<=nf;i++)
    {
        int t;
        scanf("%d",&t);
        for(int j=0;j<12;j++)
        {
            if(j<t)
            {
                scanf("%d",&tfish[j][i]);
                tfish[j][i]++;
                continue;
            }
            tfish[j][i] = tfish[j-t][i];//j时刻i鱼的位置
        }
    }
    e.n = e.m = n;
    for(int i=1;i<=n;i++){e.mar[i][i] = 1;}
    xh[12] = e;
    for(int i=0;i<12;i++)
    {
        xh[i].m = xh[i].n = n;
        memcpy(xh[i].mar,lj,sizeof(lj));
        for(int j=1;j<=nf;j++)
        {
            for(int k=1;k<=n;k++)
            {
                int p = tfish[i][j];
                xh[i].mar[k][p] = 0;
            }
        }
        if(i) xh[12] = xh[12]*xh[i];
    }
    xh[12] = xh[12]*xh[0];
    int ti = k/12;
    jz ans = e;
    while(ti)
    {
        if(ti&1)
        {
            ans = ans*xh[12];
        }
        ti>>=1;
        xh[12] = xh[12] * xh[12];
    }
    for(int i=1;i<=k%12;i++)
    {
        ans = ans * xh[i];
    }
    cout<<ans.mar[st][ed];
    return 0;
}