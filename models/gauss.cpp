#include<bits/stdc++.h>
using namespace std;
#define ld long double
const ld eps = 1e-9;
const int N = 110;

int n;
ld MA[N][N];

bool eq(ld a,ld b){
    return abs(a-b) < eps;
}

int gauss(ld (&MA)[N][N], int rn, int cn){
    int rank = 0;
    int mr = min(rn,cn); // max rank
    for(int p=1;p<=mr;p++){ // 主轴枚举位置
        int tr = rank+1; // 用于消元的那一行
        for(int row=rank+1;row<=rn;row++){
            if(abs(MA[row][p]) > abs(MA[tr][p])){
                tr = row;
            }
        }
        if(eq(MA[tr][p],0)) continue;
        rank ++;

        for(int col=1;col<=cn;col++){
            swap(MA[tr][col],MA[rank][col]);
        }
        for(int col=cn;col>=p;col--){
            MA[rank][col] /= MA[rank][p];
        }
        for(int row=rank+1;row<=rn;row++){
            if(eq(MA[row][p],0)) continue;
            for(int col=cn;col>=p;col--){
                MA[row][col] -= MA[rank][col]*MA[row][p]; 
            }
        }
    }
    if(rank < rn) return rank;

    for(int p=rank-1;p>=1;p--){ // 回代的主轴位置
        for(int row=p+1;row<=rn;row++){
            MA[p][cn] -= MA[row][cn]*MA[p][row];
            // 这里假设已经行满秩
        }
    }
    return rank;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            scanf("%Lf",&MA[i][j]);
        }
    }
    int rank = gauss(MA,n,n+1);
    
    if(rank < n){
        for(int row=rank+1;row<=n;row++){
            if(!eq(MA[row][n+1],0)){
                cout<<-1;
                return 0;
            }
        }
        cout<<0;
    }
    else{
        for(int i=1;i<=n;i++){
            printf("x%d=%.2Lf\n",i,MA[i][n+1]);
        }
    }
    return 0;
}