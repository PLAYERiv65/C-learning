#include<bits/stdc++.h>

using namespace std;

const int N = 4010;

int n,ro[N],co[N],rh[N],ch[N];//ro和co很大
bool pu[N][N];//是否保留

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            char op;
            cin>>op;
            if(op == '+')
            {
                ro[i] += 1;
                co[j] += 1;
                pu[i][j] = 1;
            }
        }
    }
    for(int i=1;i<=n;i++) cin>>rh[i];
    for(int i=1;i<=n;i++) cin>>ch[i];

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n && ro[i]>rh[i];j++)
        {
            if(ch[j]<co[j])
            {
                pu[i][j] ^= 1;
                co[j] -= 1;
                ro[i] -= 1;
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        if(ro[i] != rh[i] || co[i] != ch[i])
        {
            cout<<"No"<<endl;
            return 0;
        }
    }
    cout<<"Yes"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<pu[i][j];
        }
        cout<<endl;
    }
    return 0;
}