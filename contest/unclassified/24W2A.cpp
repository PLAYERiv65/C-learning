#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5+10;
int t,n,m,head[N],cnt;
ll po[N];
bool v[N];
struct bian{
    int to,next;
    ll w;
}bi[N<<1];
struct pos{
    int h;
    ll p;
};
queue<pos>dl;
void pb(int a,int b,ll c)
{
    bi[++cnt].to = b;
    bi[cnt].next = head[a];
    bi[cnt].w = c;
    head[a] = cnt;
}
int main()
{
    cin>>t;
    while(t--)
    {
        cnt = 0;
        memset(head,0xff,sizeof(head));
        memset(bi,0,sizeof(bi));
        memset(po,0xff,sizeof(po));
        memset(v,0,sizeof(v));
        scanf("%d%d",&n,&m);
        int a,b;
        ll d;
        pos hd;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%lld",&a,&b,&d);
            pb(a,b,-d);//相反
            pb(b,a,d);
        }
        for(int i=1;i<=n;i++)
        {
            if(v[i]) continue;
            hd.h = i;
            po[hd.h] = 0;
            hd.p = 0;
            queue<pos>empty;
            swap(empty,dl);
            dl.push(hd);
            while(!dl.empty())
            {
                int h = dl.front().h;
                ll p = dl.front().p;
                dl.pop();
                if(v[h])
                {
                    if(p != po[h])
                    {
                        printf("NO\n");
                        goto aaa;
                    }
                    else continue;
                }
                v[h] = 1;
                po[h] = p;
                for(int i=head[h];i!=-1;i=bi[i].next)
                {
                    pos pp;
                    pp.h = bi[i].to,pp.p = po[h]+bi[i].w;
                    dl.push(pp);
                }
            }
        }
        printf("YES\n");
        aaa:;
    }
    return 0;
}