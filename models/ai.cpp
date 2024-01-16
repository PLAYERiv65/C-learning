#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int d[N],sum[N<<2],add[N<<2],n,m;
//线段树建树
void bd(int l,int r,int rt)
{
    if(l == r)
    {
        sum[rt] = d[l];
        return;
    }
    int mid = (l + r) >> 1;
    bd(l,mid,rt<<1);
    bd(mid+1,r,rt<<1|1);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
//线段树下传标记
void pd(int ln,int rn,int rt)
{
    
}