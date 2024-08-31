#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll s,n;
int p1,q1,p2,q2;
ll ans = 0,maxn = 0;
int dp[12000][4090];

ll csum(ll t,ll tt,ll p,ll q){
    ll res = 0;
    res += (t-tt+1)*(t+tt)*q/2;
    res -= (t-tt+1)*p;
    return res;
}

int main(){
    cin>>s>>n;
    cin>>p1>>q1;
    cin>>p2>>q2;
    if(p1>s && p2>s){
        cout<<s;
        return 0;
    }
    ll t1 = ceil(double(p1)/double(q1)),t2 = ceil(double(p2)/double(q2));
    if(t1>t2){
        swap(p1,p2);
        swap(q1,q2);
        swap(t1,t2);
    }

    memset(dp,0xff,sizeof(dp));
    dp[0][0] = s;

    ll mst=11000,step,mq,fst=-1;
    ll quit = 0;
    for(step=1;step<=min(mst,n);step++){
        for(int j=4089;j>=0;j--){
            if(dp[step-1][j] != -1) dp[step][j] = max(dp[step][j],dp[step-1][j]+j);
            if(j-q1>=0 && dp[step-1][j-q1]-p1>=0 && n-step+1>=t1) dp[step][j] = max(dp[step][j],dp[step-1][j-q1]+j-p1);
            if(j-q2>=0 && dp[step-1][j-q2]-p2>=0 && n-step+1>=t2) dp[step][j] = max(dp[step][j],dp[step-1][j-q2]+j-p2);
            if(j-(q1+q2)>=0 && dp[step-1][j-(q1+q2)]-(p1+p2)>=0 && n-step+1>=max(t1,t2)) dp[step][j] = max(dp[step][j],dp[step-1][j-(q1+q2)]+j-(p1+p2));
            
            if(dp[step][j]<0) continue;
            ll sum = dp[step][j] + j*(n-step);
            if(fst == -1 && j>=p1+p2) fst = step;
            if(j>=p1+p2 && n-step+1>=t2 && step == fst){
                sum += csum(n-step,t1,p1,q1) + csum(n-step,t2,p2,q2);
            }
            /*else if(j>=p1 && n-step+1>=t1){
                sum += csum(n-step,t1,p1,q1);
            }*/
            ans = max(ans,sum);
        }
    }

    /*for(int j=4089;j>=0;j--){
        ans = max(ans,(ll)dp[n][j]);
    }
    cout<<ans;
    return 0;

    bbb:;
    for(int j=4089;j>=0;j--){
        if(dp[step][j] < 0) continue;
        ans = max(ans, dp[step][j] + j*(n-step) + csum(n-step,t1,p1,q1) + csum(n-step,t2,p2,q2));
    }
    cout<<ans;*/

    cout<<ans;
    return 0;
}