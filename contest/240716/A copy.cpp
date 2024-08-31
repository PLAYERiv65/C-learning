#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=5005;
int C[MAXN],pw[MAXN];
int main()
{
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=(pw[0]=1);i<=n;i++)
        pw[i]=pw[i-1]*2%q;
    for(int i=(C[0]=1);i<=n;i++)
        for(int j=i;j>0;j--)
            C[j]=(C[j]+C[j-1])%q;
    int res=0;
    for(int i=1;i<=n;i++)
    {
        int cur1=1,cur2=1;
        for(int j=1;j<=m-1;j++)
        {
            cur1=(ll)cur1*pw[n-i]%q;
            cur2=(ll)cur2*(pw[i]-1)%q;
        }
        res=(res+(ll)cur1*cur2%q*C[i])%q;
    }
    return 0*printf("%d\n",(res+q)%q);
}

