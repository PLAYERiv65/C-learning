#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
int n = 10,i1,i2;
char c1,c2;
float f1,f2;
double d1,d2,pai;
string s1;
float sum[N<<2],add[N<<2];
void bd(int l,int r,int rt)
{
    if(l == r)
    {
        sum[rt] = 0.1;
        return ;
    }
    int mid = (l+r)>>1;
    bd(l,mid,rt<<1);
    bd(mid+1,r,rt<<1|1);
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
float ksm(float a,int mi)
{
    float ans = 1;
    while(mi)
    {
        if(mi & 1)
        {
            ans *= a;
        }
        mi >>= 1;
        a *= a;
    }
    return ans;
}
void pp()
{
    int u = 1;
    double fm = 1;
    pai = 0;
    for(int i=1;i<=N<<2;i++)
    {
        pai += u*(4/fm);
        fm += 2;
        u *= -1;
    }
}
int main()
{
    pp();
    i1 = int(pai*1000);
    i2 = ksm(int(pai*100),2);
    printf("%d %d\n",i1,i2);
    c1 = 'a';
    c2 = 'B';
    printf("%c %c %d %d\n",c1,c2,c1,c2);
    c1 -= ksm(2,5);
    c2 += ksm(2,5);
    printf("%c %c\n",c1,c2);
    bd(1,n,1);
    printf("%.20f\n",sum[1]);
    cin>>s1;
    cout<<sizeof(s1)<<endl;
    for(int i=0;i<s1.length();i++)
    {
        if(s1[i]>=65 && s1[i]<=90) printf("%c",char(s1[i]+ksm(2,5)));
        else if(s1[i]>=97 && s1[i]<=122) cout<<'*';
        else printf("%x ",s1[i]);
    }
    cout<<endl;
    float a,b,c;
    cin>>a>>b>>c;
    cout<<(2*a*b+2*b*c+2*a*c)<<endl;
    float r;
    cin>>r;
    cout<<(pai*ksm(r,2))<<endl;
    return 0;
}