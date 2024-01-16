#include<bits/stdc++.h>
using namespace std;
int f[10010],siz[10010],n,m;
int find(int a)
{
    if(f[a] == a) return a;
    return f[a] = find(f[a]);
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        f[i] = i;
        siz[i] = 1;
    }
    int z,x,y;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&z,&x,&y);
        int fx = find(x),fy = find(y);
        if(z == 1)
        {
            if(siz[fx] >= siz[fy]) swap(fx,fy);
            f[fx] = fy;
            siz[fy] += siz[fx];
        }
        else
        {
            if(find(x) == find(y)) printf("Y\n");
            else printf("N\n");
        }
    }
    return 0;
}