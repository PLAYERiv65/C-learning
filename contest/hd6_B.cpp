#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+10,M = 1e5+10;
struct EDGE{
    int to,next;
}ed[M<<1];
int T,n,m,cnt,head[N],us[N],dgn[N],edn[N],afd;

void pe(int u,int v){
    ed[++cnt].to = v;
    ed[cnt].next = head[u];
    head[u] = cnt;
}

int nxp(int now,int pa){
    for(int i=head[now];i!=-1;i=ed[i].next){
        if(ed[i].to != pa) return ed[i].to;
    }
    return 0;
}

int find(int x){
    if(us[x] == x) return x;
    return us[x] = find(us[x]);
}

void merge(int x,int y){
    int fx = find(x),fy = find(y);
    edn[fy] ++;
    if(fx != fy){
        dgn[fy] += dgn[fx];
        edn[fy] += edn[fx];
        us[fx] = fy;
    }
}

void jud(int p){
    int deg[N];
    for(int i=1;i<=n;i++) us[i] = i,deg[i] = dgn[i] = edn[i] = 0;
    
    for(int poi=1;poi<=n;poi++){
        for(int i=head[poi];i!=-1;i=ed[i].next){
            int so = ed[i].to;
            if(so == p || poi == p) continue;
            deg[so] ++;
        }
    }
    for(int i=1;i<=n;i++) if(deg[i]==1) dgn[i] = 1;

    for(int poi=1;poi<=n;poi++){
        for(int i=head[poi];i!=-1;i=ed[i].next){
            int so = ed[i].to;
            if(so == p || poi == p) continue;
            merge(poi,so);
        }
    }

    for(int i=1;i<=n;i++){
        if(us[i] != i) continue;
        //cout<<p<<" "<<i<<" "<<edn[i]<<" "<<dgn[i]<<endl;
        if(edn[i]/2>dgn[i]) return;
    }
    afd = 1;
    cout<<p<<" ";
}

int main(){
    cin>>T;
    while(T--){
        scanf("%d%d",&n,&m);
        cnt = 0;
        for(int i=0;i<=n;i++) head[i] = -1;

        int u,v;
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            pe(u,v);
            pe(v,u);
        }

        int x=0,y=0,a=1,b;
        bool fd = 0;
        for(a=1;a<=n;a++){
            for(int i=head[a];i!=-1;i=ed[i].next){
                b = ed[i].to;
                x = nxp(a,b), y = nxp(b,a);
                if(x && y){
                    fd = 1;
                    break;
                }
            }
            if(fd) break;
        }
        if(!fd){
            for(int i=1;i<=n;i++){
                printf("%d ",i);
            }
            cout<<endl;
            continue;
        }
        if(x==y) y = 0;
        
        afd = 0;
        int st[5] = {0,x,y,a,b};
        sort(st,st+5);
        for(int i=1;i<=4;i++) jud(st[i]);
        if(!afd) cout<<-1;
        cout<<endl;
    }
    return 0;
}