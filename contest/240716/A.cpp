#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 5e3+10;
ll n,m,q,c[N][N],ans=0;

ll ksm(ll ba,ll in){
    ll po = 1;
    while(in){
        if(in&1){
            po *= ba;
            po %= q;
        }
        ba *= ba;
        ba %= q;
        in >>= 1;
    }
    return po;
}

void pre(){
    c[0][0] = 1;
    for(int i=1;i<=n;i++){
        c[i][0] = 1;
        for(int j=1;j<=i;j++){
            c[i][j] = c[i-1][j] + c[i-1][j-1];
            c[i][j] %= q;
        }
    }
}

int main(){
    cin>>n>>m>>q;
    pre();
    for(int i=1;i<=n;i++){
        ans += (c[n][i]*ksm(((ksm(2,i)-1)*ksm(2,n-i))%q, m-1))%q;
        ans %= q;
    }
    cout<<ans<<endl;
    return 0;
}