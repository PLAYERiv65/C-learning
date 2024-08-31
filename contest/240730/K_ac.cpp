#include<bits/stdc++.h>
using namespace std;
#define int long long
const int C = 12;
const int N = 1e3 + 5;
int dp[N][N][30];
int a[N];
int pot[N][30];
int n;

inline int cal(int l, int r, int c, int p) {
	int x = min(a[p], dp[p][r][c + 1] - dp[l][p - 1][c - 1] >> 1); // (a[p - 1], a[p]] 
	if(x <= a[p - 1]) x = a[p - 1] + 1;
	return max(dp[l][p - 1][c - 1] + x, dp[p][r][c + 1] - x);
}
void solve() {
	cin >> n;
	memset(dp, 0x3f, sizeof dp);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int len = 1; len <= n; ++len) {
		for (int l = 1; l + len - 1 <= n; ++l) {
			int r = l + len - 1;
			for (int c = C - 10; c <= C + 10; ++c) {
				if(l == r) {
					dp[l][r][c] = (c - C) * a[l];
					pot[l][c] = l + 1;
				} else {
					while(pot[l][c] < r && cal(l, r, c, pot[l][c]) >= cal(l, r, c, pot[l][c] + 1)) {
						pot[l][c]++;
					} 
					while(pot[l][c] - 1 > l && cal(l, r, c, pot[l][c] - 1) <= cal(l, r, c, pot[l][c])) {
						pot[l][c]--;
					}
					dp[l][r][c] = cal(l, r, c, pot[l][c]);
				}
			}
		}
	}
	cout << dp[1][n][C];
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int _ = 1;
//	cin >> _;
	while(_--) solve();
	return 0;
}
