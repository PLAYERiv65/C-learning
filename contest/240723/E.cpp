#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,m,son[N*N][2],siz[N*N],cnt=1;
double p,f[N][N],ans=1;

void pre(){
    f[0][0] = 1;
    for(int i=1;i<=n;i++){
        f[i][0] = f[0][i] = f[i-1][0]*p;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            f[i][j] = max(p*f[i-1][j]+(1-p)*f[i][j-1], p*f[i][j-1]+(1-p)*f[i-1][j]);
        }
    }
}

void dfs(int now){
    if(!now) return;
    int lsiz = siz[son[now][0]], rsiz = siz[son[now][1]];
    ans *= f[lsiz][rsiz];
    dfs(son[now][0]);
    dfs(son[now][1]);
}

int main(){
    cin>>n>>m>>p;
    int now;
    string s;
    for(int i=1;i<=n;i++){
        now = 1;
        cin>>s;
        for(int j=1;j<=m;j++){
            bool o = s[j-1]-'0';
            int& so = son[now][o];
            if(!so) so = ++cnt;
            siz[so]++;
            now = so;
        }
    }
    pre();
    dfs(1);
    printf("%.12f\n",ans);
    return 0;
}