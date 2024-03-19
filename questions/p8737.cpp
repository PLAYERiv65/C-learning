#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 1010;
const ll mod = 1e9+7;
int n,m,w;
ll ans;
int r1,c1,h1,r2,c2,h2;
int p[N],way[N][N],MN,C[N*3][N*3],jc[N*3],ny[N*3];//第i个数长度为j的表达方案数,用质数的和表达,C组合数

//快速幂
ll ksm(ll a,ll ex)
{
    ll ans = 1;
    while(ex)
    {
        if(ex&1) ans = (ll)ans*a%mod;
        a = (ll)a*a%mod;
        ex >>= 1;
    }
    return ans;
}
void pre()
{
    //线性筛
    for(int i=2;i<=MN;i++)
    {
        if(!p[i]) p[++p[0]]=i;
        for(int j=1;j<=p[0] && p[j]*i<=MN;j++)
        {
            p[p[j]*i]=1;
            if(!(i%p[j])) break;
        }
    }
    //递推组合
    C[0][0] = 1;
    for(int i=1;i<=MN*3;i++)
    {
        C[i][0] = 1;
        for(int j=1;j<=i;j++)
        {
            C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
        }
    }
    //阶乘
    jc[0] = 1;
    for(int i=1;i<=MN*3;i++)
    {
        jc[i] = ((ll)jc[i-1]*i)%mod;
    }
    //逆元
    ny[MN*3] = ksm(jc[MN*3],mod-2);
    for(int i=MN*3-1;i>=0;i--)
    {
        ny[i] = ((ll)ny[i+1]*(i+1))%mod;
    }
    //递推表达
    way[0][0] = 1;
    for(int i=2;i<=MN;i++)//要表示的数
    {
        for(int j=1;j<=(i>>1);j++)//长度
        {
            for(int k=1;p[k]<=i && k<=p[0];k++)
            {
                way[i][j] = (way[i][j] + way[i-p[k]][j-1])%mod;
            }
        }
    }
}

ll solve(int x,int y,int z)//分别表示向每个方向走的步数
{
    if(x*y*z < 0) return 0;
    ll ansp = 0;
    for(int sum = 0;sum<=(x+y>>1)+1;sum++)
    {
        ll ans1 = 0,ans2 = 0;
        for(int i = 0;i<=(x>>1)+1;i++)
        {
            int j = sum - i;
            if(j<0) break;
            ans1 = (ans1 + (((ll)way[x][i]*ny[i])%mod)*(((ll)way[y][j]*ny[j])%mod))%mod;
        }
        for(int k = 0;k<=(z>>1);k++)
        {
            ans2 = (ans2 + jc[sum+k]*(((ll)way[z][k]*ny[k])%mod))%mod;
        }
        ansp = (ansp + ((ll)ans1*ans2)%mod)%mod;
    }
    return ansp;
}

int main()
{
    cin>>n>>m>>w;
    MN = max(n,m);
    MN = max(MN,w);
    MN += 5;
    cin>>r1>>c1>>h1>>r2>>c2>>h2;
    pre();

    ans = (ans + solve(n-1,m-1,w-1))%mod;
    ans = (ans - ((ll)solve(r1-1,c1-1,h1-1)*(ll)solve(n-r1,m-c1,w-h1))%mod + (mod<<1))%mod;
    ans = (ans - ((ll)solve(r2-1,c2-1,h2-1)*(ll)solve(n-r2,m-c2,w-h2))%mod + (mod<<1))%mod;
    //容斥原理
    ans = (ans + (((ll)solve(r1-1,c1-1,h1-1)*(ll)solve(r2-r1,c2-c1,h2-h1))%mod*(ll)solve(n-r2,m-c2,w-h2))%mod)%mod;
    ans = (ans + (((ll)solve(r2-1,c2-1,h2-1)*(ll)solve(r1-r2,c1-c2,h1-h2))%mod*(ll)solve(n-r1,m-c1,w-h1))%mod)%mod;

    cout<<ans<<endl;
    return 0;
}