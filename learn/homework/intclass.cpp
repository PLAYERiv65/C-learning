#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 1e6+10;
int pri[N],rk[N];//质数表

void pre()
{
    for(int i=2;i<N;i++)
    {
        if(!pri[i]) pri[++pri[0]]=i;
        for(int j=1;j<=pri[0]&&pri[j]*i<N;j++)
        {
            pri[pri[j]*i]=1;
            if(i%pri[j]==0) break;
        }
    }
    for(int i=1,pin=1;i<N;i++)
    {
        rk[i]=rk[i-1];
        if(i==pri[pin]) rk[i]++,pin++;
    }
}

class integer{
private:
    int n,mp;
    int* ex;
    bool ne;
public:
    integer(int n=0);
    
    int get();
    void change(int n);
    void rediv();
    //friend gcd,lcm
    friend int gcd(integer a,integer b);
    friend int lcm(integer a,integer b);
};

void integer::rediv()
{
    int n = this->n;
    ex = new int[rk[n]+1];
    memset(ex,0,(rk[n]+1)<<2);//不能用sizeof(ex)/sizeof(int)因为ex是指针
    if(n<=1) return;
    for(int i=1;i<=pri[0];i++)
    {
        while(n%pri[i]==0)
        {
            ex[i]++;
            n/=pri[i];
        }
        if(n==1)
        {
            mp = i;
            break;
        }
        if(pri[i]*pri[i]>n)
        {
            mp = rk[n];
            ex[rk[n]]++;
            break;
        }
    }
}

void integer::change(int n)
{
    ne = false;
    if(n<0)
    {
        ne=true;
        n=-n;
    }
    this->n=n;
    rediv();
}

int integer::get()
{
    return ne?-n:n;
}

integer::integer(int n)
{
    ne = false;
    if(n<0)
    {
        ne=true;
        n=-n;
    }
    this->n=n;
    rediv();
}

//operator
integer operator*(integer a,integer b)
{
    return integer(a.get()*b.get());
}

integer operator/(integer a,integer b)
{
    return integer(a.get()/b.get());
}

integer operator+(integer a,integer b)
{
    return integer(a.get()+b.get());
}

integer operator-(integer a,integer b)
{
    return integer(a.get()-b.get());
}

integer operator%(integer a,integer b)
{
    return integer(a.get()%b.get());
}
//special implementation
int gcd(integer a,integer b)
{
    int ans=1,minp=min(a.mp,b.mp);
    for(int i=1;i<=minp;i++)
    {
        ans*=pow(pri[i],min(a.ex[i],b.ex[i]));
    }
    return ans;
}

int lcm(integer a,integer b)
{
    int ans=1,minp=min(a.mp,b.mp);
    for(int i=1;i<=minp;i++)
    {
        ans*=pow(pri[i],max(a.ex[i],b.ex[i]));
    }
    if(a.mp<b.mp) swap(a,b);
    for(int i=minp+1;i<=a.mp;i++)
    {
        ans*=pow(pri[i],a.ex[i]);
    }
    return ans;
}

int main()
{
    pre();
    int a,b;
    cin>>a>>b;
    integer x(a),y(b);
    cout<<x.get()<<" "<<y.get()<<endl;
    //show operation
    cout<<x.get()<<"+"<<y.get()<<"="<<(x+y).get()<<endl;
    cout<<x.get()<<"-"<<y.get()<<"="<<(x-y).get()<<endl;
    cout<<x.get()<<"*"<<y.get()<<"="<<(x*y).get()<<endl;
    cout<<x.get()<<"/"<<y.get()<<"="<<(x/y).get()<<endl;
    cout<<x.get()<<"%"<<y.get()<<"="<<(x%y).get()<<endl;
    cout<<"gcd:"<<gcd(x,y)<<endl;
    cout<<"lcm:"<<lcm(x,y)<<endl;
    return 0;
}