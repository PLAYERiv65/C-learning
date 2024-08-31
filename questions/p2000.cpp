#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define N 400005
#define M 800005
#define ll long long
#define ull unsigned long long
#define a hz.w
#define b kz.w
#define c kzkz.w
#define d kzzf.w
#define e BigNumber_e
#define f BigNumber_f
#define ten BigNumber_ten
#define lim BigNumber_lim
#define s BigNumber_s
#define G BigNumber_G
#define rev BigNumber_rev
#define P 998244353
#define inv(x) ksm(x,P-2)
#define IT vector<int> :: iterator
using namespace std;
const ll BigNumber_lim=922337203685477578;
char BigNumber_s[N];
int BigNumber_rev[M];
int BigNumber_G[2][25]={{0,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141,267099868,15311432},{0,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804,382752275,469870224}};
int BigNumber_e[M],BigNumber_f[M];
ll BigNumber_ten[25]={0,1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,100000000000,1000000000000,10000000000000,100000000000000,1000000000000000,10000000000000000,100000000000000000,1000000000000000000};
int ksm(int x,int y);
void NTT(int *g,int t,int s);
struct BigNumber
{
    vector<int>w;
    BigNumber ()
    {
        w.clear(),w.push_back(1),w.push_back(0);
    }
    bool zero()
    {
        return w.size()>=2 && w[0]==1 && w[1]==0;
    }
    void set0()
    {
        w.clear();
        w.push_back(1),w.push_back(0);
    }
    void set1()
    {
        w.clear();
        w.push_back(1),w.push_back(1);
    }
    template<typename T>
    void setNum(T x)
    {
        if (!x)
        {
            set0();
            return;
        }
        w.clear();
        w.push_back(0);
        int g=0;
        while (x)
        {
            w.push_back(x%10);
            x/=10;
            g++;
        }
        w[0]=g;
    }
    void read()
    {
        scanf("%s",s);
        w.clear();
        w.push_back(strlen(s));
        for (int i=w[0]-1;i>=0;i--)
            w.push_back(s[i]-'0');
    }
    void write()
    {
        for (int i=w[0];i>=1;i--)
            putchar(w[i]+'0');
        putchar('\n');
    }
};
BigNumber kz,kzkz,kzzf;
void read(BigNumber &kz)
{
    scanf("%s",s);
    b.clear();
    b.push_back(strlen(s));
    for (int i=b[0]-1;i>=0;i--)
        b.push_back(s[i]-'0');
}
void write(BigNumber kz)
{
    for (int i=b[0];i>=1;i--)
        putchar(b[i]+'0');
    putchar('\n');
}
ll BigNumber_Turn_Number(BigNumber kz);
template<typename T>
bool operator < (BigNumber hz,T x)
{
    if (hz.zero())
        return 0<x;
    if (a[0]>19 || x<ten[a[0]])
        return false;
    if (x>=ten[a[0]+1])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]<x/ten[i]%10;
    return false;
}
template<typename T>
bool operator <= (BigNumber hz,T x)
{
    if (hz.zero())
        return 0<=x;
    if (a[0]>19 || x<ten[a[0]])
        return false;
    if (x>=ten[a[0]+1])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]<x/ten[i]%10;
    return true;
}
template<typename T>
bool operator > (BigNumber hz,T x)
{
    if (hz.zero())
        return 0>x;
    if (a[0]>19 || x<ten[a[0]])
        return true;
    if (x>=ten[a[0]+1])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]>x/ten[i]%10;
    return false;
}
template<typename T>
bool operator >= (BigNumber hz,T x)
{
    if (hz.zero())
        return 0>=x;
    if (a[0]>19 || x<ten[a[0]])
        return true;
    if (x>=ten[a[0]+1])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]>x/ten[i]%10;
    return true;
}
template<typename T>
bool operator == (BigNumber hz,T x)
{
    if (hz.zero())
        return 0==x;
    if (a[0]>19 || x<ten[a[0]])
        return false;
    if (x>=ten[a[0]+1])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return false;
    return true;
}
template<typename T>
bool operator != (BigNumber hz,T x)
{
    if (hz.zero())
        return 0!=x;
    if (a[0]>19 || x<ten[a[0]])
        return true;
    if (x>=ten[a[0]+1])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return true;
    return false;
}
template<typename T>
bool operator < (T x,BigNumber hz)
{
    if (hz.zero())
        return x<0;
    if (a[0]>19 || x<ten[a[0]])
        return true;
    if (x>=ten[a[0]+1])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]>x/ten[i]%10;
    return false;
}
template<typename T>
bool operator <= (T x,BigNumber hz)
{
    if (hz.zero())
        return x<=0;
    if (a[0]>19 || x<ten[a[0]])
        return true;
    if (x>=ten[a[0]+1])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]>x/ten[i]%10;
    return true;
}
template<typename T>
bool operator > (T x,BigNumber hz)
{
    if (hz.zero())
        return x>0;
    if (a[0]>19 || x<ten[a[0]])
        return false;
    if (x>=ten[a[0]+1])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]<x/ten[i]%10;
    return false;
}
template<typename T>
bool operator >= (T x,BigNumber hz)
{
    if (hz.zero())
        return x>=0;
    if (a[0]>19 || x<ten[a[0]])
        return false;
    if (x>=ten[a[0]+1])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return a[i]<x/ten[i]%10;
    return true;
}
template<typename T>
bool operator == (T x,BigNumber hz)
{
    if (hz.zero())
        return x==0;
    if (a[0]>19 || x<ten[a[0]])
        return false;
    if (x>=ten[a[0]+1])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return false;
    return true;
}
template<typename T>
bool operator != (T x,BigNumber hz)
{
    if (hz.zero())
        return x!=0;
    if (a[0]>19 || x<ten[a[0]])
        return true;
    if (x>=ten[a[0]+1])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=x/ten[i]%10)
            return true;
    return false;
}
bool operator < (BigNumber hz,BigNumber kz)
{
    if (a[0]!=b[0])
        return a[0]<b[0];
    for (int i=a[0];i>=1;i--)
        if (a[i]!=b[i])
            return a[i]<b[i];
    return false;
}
bool operator <= (BigNumber hz,BigNumber kz)
{
    if (a[0]!=b[0])
        return a[0]<b[0];
    for (int i=a[0];i>=1;i--)
        if (a[i]!=b[i])
            return a[i]<b[i];
    return true;
}
bool operator > (BigNumber hz,BigNumber kz)
{
    if (a[0]!=b[0])
        return a[0]>b[0];
    for (int i=a[0];i>=1;i--)
        if (a[i]!=b[i])
            return a[i]>b[i];
    return false;
}
bool operator >= (BigNumber hz,BigNumber kz)
{
    if (a[0]!=b[0])
        return a[0]>b[0];
    for (int i=a[0];i>=1;i--)
        if (a[i]!=b[i])
            return a[i]>b[i];
    return true;
}
bool operator == (BigNumber hz,BigNumber kz)
{
    if (a[0]!=b[0])
        return false;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=b[i])
            return false;
    return true;
}
bool operator != (BigNumber hz,BigNumber kz)
{
    if (a[0]!=b[0])
        return true;
    for (int i=a[0];i>=1;i--)
        if (a[i]!=b[i])
            return true;
    return false;
}
template<typename T>
BigNumber operator + (BigNumber hz,T x)
{
    for (int i=1;i<=a[0];i++)
    {
        x+=a[i];
        a[i]=x%10;
        x/=10;
    }
    while (x)
        a[0]++,a.push_back(x%10),x/=10;
    return hz;
}
template<typename T>
BigNumber operator - (BigNumber hz,T x)
{
    for (int i=1;i<=a[0];i++)
    {
        a[i]-=x%10;
        if (a[i]<0)
            a[i]+=10,a[i+1]--;
        x/=10;
    }
    IT it=a.end()-1;
    while (!(*it) && a[0]>1)
    {
        a[0]--;
        a.erase(it--);
    }
    return hz;
}
template<typename T>
BigNumber operator * (BigNumber hz,T x)
{
    ll jw=0;
    if (x<=lim)
    {
        for (int i=1;i<=a[0];i++)
        {
            jw+=x*a[i];
            a[i]=jw%10;
            jw/=10;
        }
        while (jw)
            a[0]++,a.push_back(jw%10),jw/=10;
    } else
    {
        ll rx=x/10;
        int tx=x%10,ri;
        for (int i=1;i<=a[0];i++)
        {
            ri=a[i];
            a[i]=a[i]*tx+jw%10;
            jw=jw/10+rx*ri+a[i]/10;
            a[i]%=10;
        }
        while (jw)
            a[0]++,a.push_back(jw%10),jw/=10;
    }
    return hz;
}
template<typename T>
BigNumber operator / (BigNumber hz,T x)
{
    e[0]=0;
    ll y=0;
    if (x<=lim)
    {
        for (int i=a[0];i;i--)
        {
            y=y*10+a[i];
            if (e[0] || y>=x)
                e[++e[0]]=y/x,y%=x;
        }
    } else
    {
        ull s;
        int ct;
        for (int i=a[0];i;i--)
        {
            if (y<=lim)
            {
                y=y*10+a[i];
                if (e[0] || y>=x)
                    e[++e[0]]=y/x,y%=x;
            } else
            {
                s=a[i],ct=0;
                for (int j=1;j<=10;j++)
                {
                    s+=y;
                    if (s>=x)
                        s-=x,ct++;
                }
                y=s;
                if (e[0] || ct)
                    e[++e[0]]=ct;
            }
        }
    }
    if (!e[0])
        e[0]++,e[1]=0;
    a.clear();
    a.push_back(e[0]);
    for (int i=e[0];i;i--)
        a.push_back(e[i]);
    return hz;
}
template<typename T>
BigNumber operator % (BigNumber hz,T x)
{
    ll y=0;
    if (x<=lim)
    {
        for (int i=a[0];i;i--)
            y=(y*10+a[i])%x;
    } else
    {
        ull s;
        for (int i=a[0];i;i--)
        {
            if (y<=lim)
                y=(y*10+a[i])%x; else
                {
                    s=a[i];
                    for (int j=1;j<=10;j++)
                    {
                        s+=y;
                        if (s>=x)
                            s-=x;
                    }
                    y=s;
                }
        }
    }
    hz.setNum(y);
    return hz;
}
template<typename T>
BigNumber operator + (T x,BigNumber hz)
{
    for (int i=1;i<=a[0];i++)
    {
        x+=a[i];
        a[i]=x%10;
        x/=10;
    }
    while (x)
        a[0]++,a.push_back(x%10),x/=10;
    return hz;
}
template<typename T>
BigNumber operator - (T x,BigNumber hz)
{
    x-=BigNumber_Turn_Number(hz);
    hz.setNum(x);
    return hz;
}
template<typename T>
BigNumber operator * (T x,BigNumber hz)
{
    ll jw=0;
    if (x<=lim)
    {
        for (int i=1;i<=a[0];i++)
        {
            jw+=x*a[i];
            a[i]=jw%10;
            jw/=10;
        }
        while (jw)
            a[0]++,a.push_back(jw%10),jw/=10;
    } else
    {
        ll rx=x/10;
        int tx=x%10,ri;
        for (int i=1;i<=a[0];i++)
        {
            ri=a[i];
            a[i]=a[i]*tx+jw%10;
            jw=jw/10+rx*ri+a[i]/10;
            a[i]%=10;
        }
        while (jw)
            a[0]++,a.push_back(jw%10),jw/=10;
    }
    return hz;
}
template<typename T>
BigNumber operator / (T x,BigNumber hz)
{
    if (x<hz)
    {
        hz.set0();
        return hz;
    }
    x/=BigNumber_Turn_Number(hz);
    hz.setNum(x);
    return hz;
}
template<typename T>
BigNumber operator % (T x,BigNumber hz)
{
    if (x<hz)
    {
        hz.setNum(x);
        return hz;
    }
    x%=BigNumber_Turn_Number(hz);
    hz.setNum(x);
    return hz;
}
BigNumber operator + (BigNumber hz,BigNumber kz)
{
    int ws=max(a[0],b[0]);
    int jw=0;
    for (int i=1;i<=ws;i++)
    {
        if (b[0]<i)
        {
            b[0]++;
            b.push_back(0);
        }
        if (a[0]>=i)
            b[i]+=a[i];
        b[i]+=jw;
        jw=b[i]/10;
        b[i]%=10;
    }
    while (jw)
    {
        b[0]++;
        b.push_back(jw%10);
        jw/=10;
    }
    return kz;
}
BigNumber operator - (BigNumber hz,BigNumber kz)
{
    int ws=max(a[0],b[0]);
    for (int i=1;i<=ws;i++)
    {
        if (b[0]<i)
            b.push_back(a[i]); else
            b[i]=a[i]-b[i];
        if (b[i]<0)
        {
            b[i]+=10;
            a[i+1]--;
        }
    }
    IT it=b.end()-1;
    while (!(*it) && ws>1)
    {
        ws--;
        b.erase(it--);
    }
    b[0]=ws;
    return kz;
}
BigNumber operator * (BigNumber hz,BigNumber kz)
{
	if (hz.zero() || kz.zero())
	{
		hz.set0();
		return hz;
	}
    int la=a[0],lb=b[0];
    int s=1,l=0;
    while (s<la+lb)
    {
        s <<=1;
        l++;
    }
    rev[0]=0;
    for (int i=1;i<s;i++)
        rev[i]=(rev[i >> 1] >> 1) | ((i & 1) << (l - 1));
    e[0]=f[0]=0;
    for (int i=1;i<=la;i++)
        e[i-1]=a[i];
    for (int i=1;i<=lb;i++)
        f[i-1]=b[i];
    for (int i=la;i<s;i++)
        e[i]=0;
    for (int i=lb;i<s;i++)
        f[i]=0;
    NTT(e,0,s);
    NTT(f,0,s);
    for (int i=0;i<s;i++)
        e[i]=(ll)e[i]*f[i]%P;
    NTT(e,1,s);
    int invs=inv(s);
    for (int i=s;i>=1;i--)
        e[i]=(ll)e[i-1]*invs%P;
    e[0]=0;
    for (int i=1;i<=la+lb;i++)
    {
        e[i+1]+=e[i]/10;
        e[i]%=10;
    }
    a[0]=la+lb;
    while (!e[a[0]] && a[0]>1)
        a[0]--;
    for (int i=1;i<=a[0];i++)
        if (la<i)
            a.push_back(e[i]); else
            a[i]=e[i];
    return hz;
}
BigNumber operator / (BigNumber hz,BigNumber kz)
{
    c.clear();
    c.push_back(0);
    for (int i=1;i<=a[0];i++)
        c.push_back(0);
    c[0]=a[0];
    kzzf.set0();
    for (int i=a[0];i>=1;i--)
    {
        if (!(d[0]==1 && d[1]==0))
        {
            d.push_back(0);
            for (int i=d[0];i>=1;i--)
                d[i+1]=d[i];
            d[1]=a[i];
            d[0]++;
        } else
            d[1]=a[i];
        while (kzzf>=kz)
        {
            kzzf=kzzf-kz;
            c[i]++;
        }
    }
    IT it=c.end()-1;
    while (!(*it) && c[0]>1)
    {
        c[0]--;
        c.erase(it--);
    }
    return kzkz;
}
BigNumber operator % (BigNumber hz,BigNumber kz)
{
    kzzf.set0();
    for (int i=a[0];i>=1;i--)
    {
        if (!(d[0]==1 && d[1]==0))
        {
            d.push_back(0);
            for (int i=d[0];i>=1;i--)
                d[i+1]=d[i];
            d[1]=a[i];
            d[0]++;
        } else
            d[1]=a[i];
        while (kzzf>=kz)
            kzzf=kzzf-kz;
    }
    return kzzf;
}
template<typename T>
void operator += (BigNumber &kz,T hz)
{
    kz=kz+hz;
}
template<typename T>
void operator -= (BigNumber &kz,T hz)
{
    kz=kz-hz;
}
template<typename T>
void operator *= (BigNumber &kz,T hz)
{
    kz=kz*hz;
}
template<typename T>
void operator /= (BigNumber &kz,T hz)
{
    kz=kz/hz;
}
template<typename T>
void operator %= (BigNumber &kz,T hz)
{
    kz=kz%hz;
}
template<typename T>
void operator += (T &kz,BigNumber hz)
{
    kz=kz+BigNumber_Turn_Number(hz);
}
template<typename T>
void operator -= (T &kz,BigNumber hz)
{
    kz=kz-BigNumber_Turn_Number(hz);
}
template<typename T>
void operator *= (T &kz,BigNumber hz)
{
    kz=kz*BigNumber_Turn_Number(hz);
}
template<typename T>
void operator /= (T &kz,BigNumber hz)
{
    kz=kz/BigNumber_Turn_Number(hz);
}
template<typename T>
void operator %= (T &kz,BigNumber hz)
{
    kz=kz%BigNumber_Turn_Number(hz);
}
void operator += (BigNumber &kz,BigNumber hz)
{
    kz=kz+hz;
}
void operator -= (BigNumber &kz,BigNumber hz)
{
    kz=kz-hz;
}
void operator *= (BigNumber &kz,BigNumber hz)
{
    kz=kz*hz;
}
void operator /= (BigNumber &kz,BigNumber hz)
{
    kz=kz/hz;
}
void operator %= (BigNumber &kz,BigNumber hz)
{
    kz=kz%hz;
}
BigNumber Number_Turn_BigNumber(ll x)
{
    if (x==0)
    {
        kz.set0();
        return kz;
    }
    b.clear();
    b.push_back(0);
    while (x)
    {
        b[0]++;
        b.push_back(x%10);
        x/=10;
    }
    return kz;
}
ll BigNumber_Turn_Number(BigNumber kz)
{
    ll y=0;
    for (int i=b[0];i>=1;i--)
        y=y*10+b[i];
    return y;
}
void NTT(int *q,int t,int s)
{
    for (int i=0;i<s;i++)
        if (i<rev[i])
            swap(q[i],q[rev[i]]);
    for (int mid=1,o=1;mid<s;mid <<=1,o++)
        for (int j=0;j<s;j+=(mid << 1))
        {
            int g=1;
            for (int k=0;k<mid;k++,g=(ll)g*G[t][o]%P)
            {
                int x=q[j+k],y=(ll)g*q[j+k+mid]%P;
                q[j+k]=(x+y)%P;
                q[j+k+mid]=(x-y+P)%P;
            }
        }
}
int ksm(int x,int y)
{
    int ans=1;
    while (y)
    {
        if (y & 1)
            ans=(ll)ans*x%P;
        x=(ll)x*x%P;
        y >>=1;
    }
    return ans;
}
#undef N
#undef M
#undef a
#undef b
#undef c
#undef d
#undef e
#undef f
#undef ten
#undef lim
#undef s
#undef G
#undef rev
#undef P
#undef inv
#undef IT
BigNumber s,t;
int main()
{
    read(s);
    write((s+4)*(s+3)*(s+2)*(s+1)/24);
    return 0;
}