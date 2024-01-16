#include<stdio.h>
#include<math.h>
int main()
{
	double x,n;
	double ex=1.0;
	double jc=1;
	scanf("%lf %lf",&x,&n);
	if(n>=0)
	{
		for(int i=1;i<=n;i++)
		{
			jc*=i;
			ex+=pow(x,i)/jc;	
		}
		printf("%.6lf\n",ex);
    }
    else printf("error");
    return 0;
}
