#include<bits/stdc++.h>
using namespace std;
int n,qj[1010][4],cnt=1;//l0,r1,pre2,next3
int main()
{
    cin>>n;
    int s,d;
    qj[1][0] = 1;
    qj[1][1] = 2e9;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&s,&d);
        bool tag = 0;
        for(int j = 1;j && qj[j][0]<=s;j = qj[j][3])
        {
            if(qj[j][0]<s && qj[j][1]>s+d-1)
            {
                qj[++cnt][0] = s+d;
                qj[cnt][1] = qj[j][1];
                qj[cnt][2] = j;
                qj[cnt][3] = qj[j][3];
                qj[j][1] = s-1;
                qj[j][3] = cnt;
                tag = 1;
            }
            else if(qj[j][0]==s && qj[j][1]>s+d-1)
            {
                qj[j][0] = s+d;
                tag = 1;
            }
            else if(qj[j][0]<s && qj[j][1]==s+d-1)
            {
                qj[j][1] = s-1;
                tag = 1;
            }
            else if(qj[j][0]==s && qj[j][1]==s+d-1)
            {
                qj[qj[j][2]][3] = qj[j][3];
                qj[qj[j][3]][2] = qj[j][2];
                tag = 1;
            }
            if(tag)
            {
                printf("%d %d\n",s,s+d-1);
                break;
            }
        }
        if(tag) continue;
        for(int j = 1;j;j = qj[j][3])
        {
            if(qj[j][1]-qj[j][0]+1 > d)
            {
                printf("%d %d\n",qj[j][0],qj[j][0]+d-1);
                qj[j][0] += d;
                break;
            }
            else if(qj[j][1]-qj[j][0]+1 == d)
            {
                printf("%d %d\n",qj[j][0],qj[j][1]);
                qj[qj[j][2]][3] = qj[j][3];
                qj[qj[j][3]][2] = qj[j][2];
                break;
            }
        }
    }
    return 0;
}