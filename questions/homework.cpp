#include <bits/stdc++.h>
using namespace std;
#define INF 2147483647
int n, m, s;
int cnt, head[200005];
long long dist[200005], vis[200005];
struct Edge {
	long long to, dis, next;
}edge[400005];
void add_edge(int from, int to, int w)
{
	edge[++cnt].to = to;
	edge[cnt].dis = w;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
struct node {
	long long id, dis;
	bool operator <(const node &a) const { return a.dis < dis; }
};
//bool operator <(const node a,node b) { return a.dis > b.dis; }
void dijkstra()
{
	priority_queue<node>q;
	q.push(node{ s,0 });
	for (int i = 1; i <= n; i++) dist[i] = INF;
	dist[s] = 0;
	while (!q.empty())
	{
		node a = q.top(); q.pop();
		int now = a.id;
		if (vis[now]) continue;
		vis[now] = 1;
		for (int i = head[now]; i; i = edge[i].next)
		{
			int j = edge[i].to;
			if (dist[now] + edge[i].dis < dist[j])
			{
				dist[j] = dist[now] + edge[i].dis;
				q.push(node{ j,dist[j] });
			}
		}
	}
}
int main()
{
	cin>>n>>m>>s;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, w);
		//add_edge(v,u,w);
	}
	dijkstra();
	for (int i = 1; i <= n; i++)
		cout << dist[i] << ' ';
	cout<<endl;
	return 0;
 }