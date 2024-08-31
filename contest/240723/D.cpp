#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+10;
int n,card[N][2],cnt2,ans[N][2],cnta;
typedef pair<int,int>pr;
map<int,int>ls;
priority_queue<pr>q;

int main(){
    cin>>n;
    int x,y;
    for(int i=1;i<=n;i++){
        scanf("%d%d",&x,&y);

        if(x == y){
            ls[x]++;
        }else{
            cnt2++;
            card[cnt2][0] = x, card[cnt2][1] = y;
        }
    }

    for(map<int,int>::iterator it = ls.begin();it != ls.end();++it){
        q.push((pr){it->second,it->first});
    }
    int last = 0;
    pr top1,top2;
    while(!q.empty()){
        top1 = q.top();
        q.pop();
        if(top1.second == last){
            if(q.empty()){
                q.push(top1);
                break;
            }
            top2 = q.top();
            q.pop();

            q.push(top1);
            top2.first--;
            cnta++;
            ans[cnta][0] = ans[cnta][1] = top2.second;
            if(top2.first) q.push(top2);
            last = top2.second;
        }else{
            top1.first--;
            cnta++;
            ans[cnta][0] = ans[cnta][1] = top1.second;
            if(top1.first) q.push(top1);
            last = top1.second;
        }
    }

    if(!q.empty()){
        pr top = q.top();
        int pin = 1;
        for(int i=1;i<=top.first;i++){
            while(card[pin][0]==top.second || card[pin][1]==top.second){
                pin++;
                if(pin > cnt2){
                    cout<<"No";
                    return 0;
                }
            }
            cnta++;
            ans[cnta][0] = card[pin][0], ans[cnta][1] = card[pin][1];
            card[pin][0] = card[pin][1] = 0;
            pin++;
            if(pin > cnt2){
                cout<<"No";
                return 0;
            }
            cnta++;
            ans[cnta][0] = ans[cnta][1] = top.second;
        }
    }

    for(int i=1;i<=cnt2;i++){
        if(!card[i][0]) continue;
        if(card[i][0] == ans[cnta][1]) swap(card[i][0],card[i][1]);
        cnta++;
        ans[cnta][0] = card[i][0], ans[cnta][1] = card[i][1];
    }

    cout<<"Yes"<<endl;
    for(int i=1;i<=n;i++){
        printf("%d %d\n",ans[i][0],ans[i][1]);
    }
    return 0;
}