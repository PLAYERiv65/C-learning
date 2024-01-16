#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct inout{
    int io,num;
}in[200010],out[200010];
ll t,n,a[200010],sum,av,mi[35],cnt;
map<ll,ll> fmi;
bool ist(ll a)
{
    while(a>1)
    {
		if(a&1) return 0;
        a >>= 1;
    }
    return 1;
}
bool cmp(inout a,inout b){return a.io > b.io;}
int main()
{
    mi[0] = 1;
    for(int i=1;i<=32;i++)
    {
		mi[i] = mi[i-1]<<1;
    }
    cin>>t;
    for(int i=1;i<=t;i++)
    {
    	cin>>n;
        sum = 0;
        cnt = 0;
        memset(in,0,sizeof(in));
        memset(out,0,sizeof(out));
        bool tag2 = 1;
        for(int j=1;j<=n;j++)
		{
            scanf("%lld",&a[j]);
            sum += a[j];
        }
        if(sum%n)
        {
            printf("No\n");
            continue;
        }
        av = sum/n;
        for(int j=1;j<=n;j++)
        {
          	ll d = abs(a[j]-av);
            bool tag = 0;
            if(ist(d))
            {
                tag = 1;
                if(a[j]-av<0)
                {
                    in[++cnt].io = d;
                    out[cnt].io = 0;
                    in[cnt].num = out[cnt].num = j;
                    goto aaa ;
                }
                else if(a[j]-av>0)
                {
                    in[++cnt].io = 0;
                    out[cnt].io = d;
                    in[cnt].num = out[cnt].num = j;
                    goto aaa ;
                }
            }
			for(int k=0;mi[k]<=d;k++)
            {
                if(!d)
                {
                    tag = 1;
                    goto aaa ;
                }
				if(ist(mi[k]+d))
                {
					tag = 1;
					if(a[j]-av<0)
                    {
                        in[++cnt].io = mi[k]+d;
                        out[cnt].io = mi[k];
                        in[cnt].num = out[cnt].num = j;
                    }
                    else if(a[j]-av>0)
                    {
                        in[++cnt].io = mi[k];
                        out[cnt].io = mi[k]+d;
                        in[cnt].num = out[cnt].num = j;
                    }
                    goto aaa ;
                }
            }
            aaa :
            if(!tag)
            {
                goto bbb;
            }
        }
        if(!tag2) continue;
        sort(in+1,in+cnt+1,cmp);
        sort(out+1,out+cnt+1,cmp);
        for(int j=1;j<=cnt;j++)
        {
            if(in[j].io != out[j].io)
            {
                goto bbb ;
            }
        }
        /*for(int j=cnt;j>=1;j--)
        {
            if(a[out[j].num] >= out[j].io)
            {
                st = out[j].num;
            }
            else 
            {
                tag2 = 0;
                break;
            }
        }*/
        printf("Yes\n");
        continue;
        bbb :
        printf("No\n");
    }
    return 0;
}