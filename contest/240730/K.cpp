#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e3+10,bi = 15;
ll dp[N][N][(bi<<1)+10],pos[N][(bi<<1)+10];
ll n,a[N],inf;

ll check(int l,int r,int mid,int c){
    ll d = dp[mid+1][r][c+1] - dp[l][mid][c-1] >> 1;
    if(a[mid+1]>=d && a[mid]+1<=d) return (dp[mid+1][r][c+1]+dp[l][mid][c-1]+1)>>1;
    else if(a[mid]+1>d) return dp[l][mid][c-1] + a[mid] + 1;
    else return dp[mid+1][r][c+1] - a[mid+1];
}

ll ts(int l,int r,int c){
    int ln=l,rn=r,midl,midr;
    while(rn-ln>2){
        midl = ln + (rn-ln)/3;
        midr = ln + ceil((rn-ln)*2/3);
        if(check(l,r,midl,c)>check(l,r,midr,c)) ln = midl;
        else rn = midr;
    }
    return min(check(l,r,ln+1,c),min(check(l,r,ln,c),check(l,r,rn,c)));
}

int main(){
    memset(dp,0x3f,sizeof(dp));
    inf = dp[0][0][0];
    cin>>n;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }

    for(int i=1;i<=n;i++){
        for(int c=-bi;c<=bi;c++){
            ll C = c+bi;
            dp[i][i][C] = c*a[i];
            pos[i][C] = i;
        }
    }

    for(int len=2;len<=n;len++){
        for(int l=1;l<=n-len+1;l++){
            int r = l+len-1;
            for(int c=-bi;c<=bi;c++){
                ll C = c+bi;
                ll& po = pos[l][C];
                while(check(l,r,po,C)>check(l,r,po+1,C) && po+1<r) po++;
                dp[l][r][C] = min(dp[l][r][C], check(l,r,po,C));
                //cout<<l<<" "<<r<<" "<<c<<" "<<dp[l][r][C]<<endl;
            }
        }
    }

    cout<<dp[1][n][bi];
    return 0;
}