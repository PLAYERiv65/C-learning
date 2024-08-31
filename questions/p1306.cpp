#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll mo = 1e8;
ll n,m;
struct matrix{
    ll n,m;
    ll ma[10][10];

    matrix(ll n,ll m){
        this->n = n;
        this->m = m;
        memset(this->ma,0,sizeof(this->ma));
    }

    matrix operator*(matrix b){
        matrix pro = matrix(this->n,b.m);
        for(ll i=1;i<=pro.n;i++){
            for(ll j=1;j<=pro.m;j++){
                for(ll k=1;k<=this->m;k++){
                    pro.ma[i][j] += this->ma[i][k]*b.ma[k][j];
                }
                pro.ma[i][j] %= mo;
            }
        }
        return pro;
    }
};

ll gcd(ll a,ll b){
    if(!b) return a;
    return gcd(b,a%b);
}

ll fib(ll n){
    matrix f1 = matrix(2,1), dt = matrix(2,2);
    f1.ma[1][1] = f1.ma[2][1] = 1;
    dt.ma[1][1] = dt.ma[2][1] = dt.ma[1][2] = 1;
    ll ex = n-1;
    while(ex){
        if(ex&1){
            f1 = dt*f1;
        }
        dt = dt * dt;
        ex >>= 1;
    }
    return f1.ma[2][1];
}

int main(){
    cin>>n>>m;
    cout<<fib(gcd(n,m));
    return 0;
}