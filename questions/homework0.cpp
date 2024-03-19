#include<bits/stdc++.h>
using namespace std;
struct bian
{
	int to,next,w;
}bi[500010];
struct dist
{
	int po,di;
};
int n,m,head[100010],dd[100010],cnt,cnt2,dise[100010],fw,s;
bool v[100010];
bool operator <(const dist a,dist b)
{
	return a.di>b.di;
}
void pb(int a,int b,int c)
{
	bi[cnt].to=b;
	bi[cnt].w=c;
	bi[cnt].next=head[a];
	head[a]=cnt++;
}
void dij(int st)
{
	memset(v,0,sizeof(v));
	memset(dise,0x3f,sizeof(dise));
	fw=0;
	priority_queue<dist> dis;
	dist ds;
	ds.po=st;
	ds.di=0;
	dise[st]=0;
	dis.push(ds);
	while(!dis.empty())
	{
		int bai=dis.top().po,db=dis.top().di;
		dis.pop();
		if(v[bai]) continue;
		v[bai]=1;
		fw+=1;
		for(int j=head[bai];j!=-1;j=bi[j].next)
		{
			dist disl;
			if(dise[bai]+bi[j].w<dise[bi[j].to])
			{
				dise[bi[j].to]=dise[bai]+bi[j].w;
				disl.po=bi[j].to;
				disl.di=dise[bai]+bi[j].w;
				dis.push(disl);
			}
		}
	}
}
int main()
{
	memset(head,0xff,sizeof(head));
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		pb(x,y,z);
	}
	dij(s);
	for(int i=1;i<=n;i++)
	{
		if(dise[i]<dise[0]) cout<<dise[i]<<" ";
		else cout<<2147483647<<" ";
	}
	return 0;
}