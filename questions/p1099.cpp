#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
struct bian{
    int to,w,next;
}bi[N<<1];
int n,s,head[N],cnt,ans=2e9,zj;
int dd1,dd2,zd1,zd2,pre[N][2];
int dl[N][2],hd=1,tl;
bool d,on[N];
void pb(int a,int b,int c)
{
    bi[++cnt].to = b;
    bi[cnt].w = c;
    bi[cnt].next = head[a];
    head[a] = cnt;
}
void dfsz(int a,int fa,int d)
{
    if(d >= zj)
    {
        dd2 = a;
        zj = d;
    }
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        if(so == fa) continue;
        pre[so][0] = a;
        pre[so][1] = bi[i].w;
        dfsz(so,a,d+bi[i].w);
    }
}
int dfsd(int a,int fa)
{
    int md = 0;
    for(int i=head[a];i!=-1;i=bi[i].next)
    {
        int so = bi[i].to;
        if(so == fa) continue;
        md = max(md,dfsd(so,a)+bi[i].w);
    }
    return md;
}
int main()
{
    memset(head,0xff,sizeof(head));
    cin>>n>>s;
    int u,v,w;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        pb(u,v,w);
        pb(v,u,w);
    }
    dfsz(1,0,0);
    dd1 = dd2;
    dd2 = 0;
    zj = 0;
    memset(pre,0,sizeof(pre));
    dfsz(dd1,0,0);
    int pin = dd2,fat = -1,ti=0,th=1,suml=0;
    int hm = zj,yj = 0;
    bool tag;
    queue<int> len;
    memset(dl,0x3f,sizeof(dl));
    while(pin)
    {
        ti += 1;
        int dz = 0;
        tag = 0;
        for(int i=head[pin];i!=-1;i=bi[i].next)
        {
            int so = bi[i].to;
            if(so == pre[pin][0] || so == fat) continue;
            dz = max(dz,bi[i].w+dfsd(so,pin));
        }
        while(tl>=hd && dl[tl][0]<=dz)
        {
            tl--;
        }
        dl[++tl][0] = dz;
        dl[tl][1] = ti;
        ans = min(ans,max(dl[hd][0],max(yj,hm)));
        hm -= pre[pin][1];
        suml += pre[pin][1];
        len.push(pre[pin][1]);
        while(suml>s)
        {
            suml -= len.front();
            yj += len.front();
            len.pop();
            th++;
        }
        while(tl>=hd && dl[hd][1]<th)
        {
            hd++;
        }
        fat = pin;
        pin = pre[pin][0];
    }
    cout<<ans;
    return 0;
}