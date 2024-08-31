#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000 + 5
#define M 4000000 + 5

// above, right, below, left
const int Fx[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int n, m, id, q, Go[N][N][4], Id[N][N], Q[M], Ans[M];
bool In[N][N][4], Flag[N][N][4];
char s[N][N];

inline int Encode(int x, int y, int dir)
{
	return ((x - 1) * m + (y - 1)) * 4 + dir;
}

inline void Decode(int c, int &x, int &y, int &dir)
{
	dir = c & 3;
	c >>= 2;
	y = c % m + 1;
	c /= m;
	x = c + 1;
}

inline int Trans(int dir, char ch)
{
	// 0<->2
	if (ch == '-')
		return dir ^ (((dir & 1) ^ 1) << 1);
	// 1<->3
	if (ch == '|')
		return dir ^ ((dir & 1) << 1);
	// 0<->1, 2<->3
	if (ch == '/')
		return dir ^ 1;
	// 0<->3, 1<->2
	if (ch == '\\')
		return dir ^ 3;
	return -1;
}

inline bool Reflected(int dir, char ch)
{
	if (ch == '-' && (dir & 1))
		return false;
	if (ch == '|' && !(dir & 1))
		return false;
	return true;
}

inline int GetDir(const char* ch)
{
	if (ch[0] == 'a')
		return 0;
	if (ch[0] == 'r')
		return 1;
	if (ch[0] == 'b')
		return 2;
	if (ch[0] == 'l')
		return 3;
	return -1;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			for (int dir = 0; dir < 4; dir ++)
			{
				int c = Encode(i, j, dir);
				int _i = i + Fx[dir][0], _j = j + Fx[dir][1];
				if (1 <= _i && _i <= n && 1 <= _j && _j <= m)
				{
					int _dir = Trans(dir, s[_i][_j]);
					Go[i][j][dir] = Encode(_i, _j, _dir);
					In[_i][_j][_dir] = true;
				}
				else Go[i][j][dir] = -1;
			}
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			for (int dir = 0; dir < 4; dir ++)
				if (!In[i][j][dir])
				{
					id ++;
					int sz = 0, _i, _j, _dir;
					for (int c = Encode(i, j, dir); c != -1; c = Go[_i][_j][_dir])
					{
						Q[++ sz] = c;
						Decode(c, _i, _j, _dir);
						Flag[_i][_j][_dir] = true;
					}
					for (int t = sz, cnt = 0; t; t --)
					{
						if (t < sz)
						{
							Decode(Q[t + 1], _i, _j, _dir);
							bool ref = Reflected(Q[t] & 3, s[_i][_j]);
							if (ref && Id[_i][_j] != id)
								Id[_i][_j] = id, cnt ++;
						}
						Ans[Q[t]] = cnt;
					}
				}
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			for (int dir = 0; dir < 4; dir ++)
				if (!Flag[i][j][dir])
				{
					id ++;
					int sz = 0, cnt = 0, _i, _j, _dir;
					for (int c = Encode(i, j, dir); ; c = Go[_i][_j][_dir])
					{
						Q[++ sz] = c;
						Decode(c, _i, _j, _dir);
						if (Flag[_i][_j][_dir])
							break;
						Flag[_i][_j][_dir] = true;
					}
					for (int t = 1; t < sz; t ++)
					{
						Decode(Q[t + 1], _i, _j, _dir);
						bool ref = Reflected(Q[t] & 3, s[_i][_j]);
						if (ref && Id[_i][_j] != id)
							Id[_i][_j] = id, cnt ++;
					}
					for (int t = 1; t <= sz; t ++)
						Ans[Q[t]] = cnt;
				}
	scanf("%d", &q);
	for (int i, j; q; q --)
	{
		char ch[9];
		scanf("%d%d%s", &i, &j, ch);
		int dir = GetDir(ch);
		printf("%d\n", Ans[Encode(i, j, dir)]);
	}
	return 0;
}

