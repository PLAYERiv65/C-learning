#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mod = 998244353, N = 1e6+10;
ll T,n,k,fac[N],invfac[N],A[N];

ll qp(ll ba,ll in){
    ll po = 1;
    while(in){
        if(in&1){
            po *= ba;
            po %= mod;
        }
        ba *= ba;
        ba %= mod;
        in >>= 1;
    }
    return po;
}

ll inv(ll a){
    return qp(a,mod-2);
}

ll C(ll n,ll m){
    return fac[n]*invfac[n-m]%mod*invfac[m]%mod;
}

void pre(){
    fac[0] = 1;
    invfac[0] = 1;
    for(ll i=1;i<=N-5;i++){
        fac[i] = (fac[i-1]*i)%mod;
        invfac[i] = inv(fac[i]);
    }
}

int main(){
    pre();
    cin>>T;
    while(T--){
        cin>>n>>k;
        ll tk = qp(2,k);
        A[n] = 1;
        for(ll i=n-1;i>=0;i--){
            A[i] = A[i+1]*(tk-i+mod)%mod;
        }

        ll ans = A[0]*(tk-n+mod)%mod,sum=0,o=1;
        for(int i=0;i<=n;i++){
            sum += (C(n,i)*A[i]*o%mod + mod)%mod;
            sum %= mod;
            o *= -1;
        }
        ans = ans*sum%mod*inv(tk)%mod;
        cout<<ans<<endl;
    }
    return 0;
}