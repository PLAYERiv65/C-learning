#include<bits/stdc++.h>
using namespace std;
int N,op[21][10000][2],cnt[210],cnt2[210],ti,val[100],vis[100],rec[100],op2[21][10000][2];

void solve(){
    for(int i=1;i<=14;i++){
        int itv = 1<<i;
        for(int j=0;j<16384;j+=itv){
            for(int k=0;k<itv/2;k++){
                if(j+k+itv/2<N){
                    op2[i][++cnt2[i]][0] = j+k;
                    op2[i][cnt2[i]][1] = j+k+itv/2;
                }

                if(j+itv-k-1<N){
                    op[i][++cnt[i]][0] = j+k;
                    op[i][cnt[i]][1] = j+itv-k-1;
                }
            }
        }

    }
}

void doing(int p, int id){
    if(p == 0) return;
    // doing(p - 1, id);
    if(id == 0 && cnt[p] != 0){
        ++ti;
    }
    else if(id == 1 && cnt[p] != 0){
        printf("%d ",cnt[p]);
        for(int k=1;k<=cnt[p];k++){
            printf("%d %d ",op[p][k][0],op[p][k][1]);
        }
        printf("\n");
    }
    for(int i=p;i>=1;i--){
        if(!cnt2[i]) continue;
        if(!id) ti++;
        else{
            printf("%d ",cnt2[i]);
            for(int k=1;k<=cnt2[i];k++){
                printf("%d %d ",op2[i][k][0],op2[i][k][1]);
            }
            printf("\n");
        }
    }
}

bool check(){
    for(int i = 0; i < N - 1; i ++)
        if(val[i] > val[i + 1]) return 0;
    return 1;
}

void dfs(int dep){
    if(dep == N){
        for(int i = 0; i < N; i ++)
            val[i] = rec[i];
        for(int i=1;i<=14;i++){
            if((1 << (i - 1)) > N) break;
            doing(i, 2);
        }
        if(!check()){
            printf("wtf??? ");
            for(int i = 0; i < N; i ++){
                printf("%d ", rec[i]);
            }
            printf("\n now= ");
            for(int i = 0; i < N; i ++){
                printf("%d ", val[i]);
            }
            printf("\n");
        }
        return;
    }
    for(int i = 0; i < N; i ++){
        if(vis[i]) continue;
        vis[i] = 1;
        rec[dep] = i;
        dfs(dep + 1);
        vis[i] = 0;
    }
}

int main(){
    cin>>N;
    solve();
    // dfs(0);
    if(N>1) ti += 1;
    for(int i=1;i<=14;i++){
        if((1 << (i - 1)) > N) break;
        doing(i, 0);
    }

    cout<<ti<<endl;
    if(N==1) return 0;
    cout<<cnt2[1]<<" ";
    for(int k=1;k<=cnt2[1];k++){
        printf("%d %d ",op2[1][k][0],op2[1][k][1]);
    }
    cout<<endl;
    for(int i=1;i<=14;i++){
        if((1 << (i - 1)) > N) break;
        doing(i, 1);
    }
    return 0;
}