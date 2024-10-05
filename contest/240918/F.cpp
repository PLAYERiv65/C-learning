#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld eps=0;
int T;
ld x,y,r,dx,dy,k;
ld lx,ly,rx,ry;

ld ny(ld nx){
    return y+k*(nx-x);
}

ld nx(ld ny){
    return x+(ny-y)/k;
}

int main(){
    cin>>T;
    while(T--){
        cin>>x>>y>>r>>dx>>dy;
        cin>>lx>>ly>>rx>>ry;

        if(min(rx-lx,ry-ly)<2*r){
            cout<<"No"<<endl;
            continue;
        }

        if(dx==0){
            if(((dy>0-eps && ry-r>=y-eps) || (dy<0+eps && ly+r<=y+eps)) && (x>=lx+r) && (x<=rx-r)){
                cout<<"Yes"<<endl;
            }
            else cout<<"No"<<endl;
            continue;
        }

        if(dy==0){
            if(((dx>0-eps && rx-r>=x-eps) || (dx<0+eps && lx+r<=x+eps)) && (y>=ly+r) && (y<=ry-r)){
                cout<<"Yes"<<endl;
            }
            else cout<<"No"<<endl;
            continue;
        }
        
        k = dy/dx;

        if(dx>0){
            if(k>0){
                ld rny = ny(rx-r), rnx = nx(ry-r);
                if((rny>=ly+r && rny<=ry-r && y>=rny) || (rnx>=lx+r && rnx<=rx-r && x>=rnx)){
                    cout<<"Yes"<<endl;
                }
                else cout<<"No"<<endl;
            }
            else{
                ld rny = ny(rx-r), rnx = nx(ly+r);
                if((rny>=ly+r && rny<=ry-r && y<=rny) || (rnx>=lx+r && rnx<=rx-r && x>=rnx)){
                    cout<<"Yes"<<endl;
                }
                else cout<<"No"<<endl;
            }
        }
        else{
            if(k>0){
                ld rny = ny(lx+r), rnx = nx(ly-r);
                if((rny>=ly+r && rny<=ry-r && y>=rny) || (rnx>=lx+r && rnx<=rx-r && x<=rnx)){
                    cout<<"Yes"<<endl;
                }
                else cout<<"No"<<endl;
            }
            else{
                ld rny = ny(lx+r), rnx = nx(ry-r);
                if((rny>=ly+r && rny<=ry-r && y<=rny) || (rnx>=lx+r && rnx<=rx-r && x<=rnx)){
                    cout<<"Yes"<<endl;
                }
                else cout<<"No"<<endl;
            }
        }
    }
}