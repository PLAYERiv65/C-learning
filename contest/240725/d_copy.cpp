#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e18;
void cmax(ll &x, ll y) {
    if (x < y) x = y;
}
int main() {
    ios::sync_with_stdio(0);
    int A, t;
    cin >> A >> t;
    vector<pair<int, int>> a(2);
    int P = 0, Q = 0;
    for (auto &[p, q] : a) {
        cin >> p >> q;
        P += p;
        Q += q;
    }
    int n = P * log(P) + 1;
    n = min(n, t);
    vector<vector<ll>> f(n + 1, vector<ll>(P, -inf));
    f[0][0] = A;
    ll ans = A;
    for (int i = 0; i <= n; i++) {
        for (int v = 0; v < P; v++) {
            if (f[i][v] <= -inf) continue ;
            ll cur = f[i][v] + 1ll * i * v;
            ll gg = cur + 1ll * (t - i + 1) * v;
            // cerr << i << ' ' << v << ' ' << cur << ' ' << gg << '\n';
            cmax(ans, gg);
            auto add = [&](int p, int q) {
                int diff = max(0ll, p - cur), turn;
                if (diff == 0) turn = 1;
                else if (v > 0) turn = (diff + v - 1) / v;
                else return ;
                int k = v + q, x = i + turn;
                ll y = cur + 1ll * turn * v - p;
                if (x > n) return ;
                if (k >= P) {
                    // cerr << "upd " << k << ' ' << x << ' ' << y << '\n';
                    ll dur = t - x + 1;
                    ll val = y + k * dur;
                    for (auto [p, q] : a) {
                        ll len = dur - 1 - (p - 1) / q;
                        if (len <= 0) continue ;
                        ll diff = (dur - 1 + dur - len) * len / 2 * q;
                        diff -= len * p;
                        assert(diff >= 0);
                        val += diff;
                    }
                    cmax(ans, val);
                    return ;
                }
                ll b = y - 1ll * x * k;
                cmax(f[x][k], b);
            };
            for (auto [p, q] : a) add(p, q);
            add(P, Q);
        }
    }
    cout << ans << '\n';
    return 0;
}
