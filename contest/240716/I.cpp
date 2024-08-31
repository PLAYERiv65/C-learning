#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+10;
struct pos{
    int x,y,di;
};
int n,m,q,grid[N][N];
int dx[5] = {0,0,1,0,-1},dy[5] = {0,1,0,-1,0};
map<string,int>mir;
map<pair<int,int>,int>re;

void pre(){
    mir["|"] = 1;
    mir["-"] = 2;
    mir["/"] = 3;
    mir["\\"] = 4;
    mir["above"] = 1;
    mir["right"] = 2;
    mir["below"] = 3;
    mir["left"] = 4;
    re[{1,1}] = 1;
    re[{1,2}] = 3;
    re[{1,3}] = 2;
    re[{1,4}] = 4;
    re[{2,1}] = 4;
    re[{2,2}] = 2;
    re[{2,3}] = 1;
    re[{2,4}] = 3;
    re[{3,1}] = 3;
    re[{3,2}] = 1;
    re[{3,3}] = 4;
    re[{3,4}] = 2;
    re[{4,1}] = 2;
    re[{4,2}] = 4;
    re[{4,3}] = 3;
    re[{4,4}] = 1;
}

pos nxt(pos p){
    pos n;
    n.x = p.x + dx[p.di];
    n.y = p.y + dy[p.di];
    n.di = re[{p.di,grid[n.x][n.y]}];
    return n;
}

int main(){
    cin>>n>>m;
    string s;
    for(int i=1;i<=n;i++){
        cin>>s;
        for(int j=1;j<=m;j++){
            grid[i][j] = mir[string(1, s[j-1])];
        }
    }
    return 0;
}