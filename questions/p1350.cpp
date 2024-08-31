#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+10, mo = 1e5+3;
int a,b,c,d,k,dp[N*2][N];

int main(){
    cin>>a>>b>>c>>d>>k;
    dp[0][0] = 1;
    for(int i=1;i<=b+d;i++){
        dp[i][0] = 1;
        int len = i>b? a+c:a;
        for(int j=1;j<=k;j++){
            dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]*(len-(j-1)))%mo;
        }
    }
    cout<<dp[b+d][k];
    return 0;
}