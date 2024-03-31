#include <stdio.h>

int main()
{
    int N,L,x[1001]={-1},i,j,k,tmp,y[1001]={-1};
    scanf("%d%d",&N,&L);
    for(i=0;i<1001;i++)
    {
        x[i]=-1;
    }
    
    for(i=0;i<L;i++)
    {
        scanf("%d",&x[i]);
        for(j=1;j<=N;j++)
        {
            if(x[i]==x[i-j])
            {
                printf("YES %d\n",j);
                for(k=j;k<=N;k++)
                {
                    y[i-k]=x[i-k-1];
                }
                for(k=j;k<=N;k++)
                {
                    x[i-k]=y[i-k];
                }
                goto C;
            }
        }
        printf("NO\n");
        C:
         ;
    }

    return 0;
}