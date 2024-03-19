#include <bits/stdc++.h>
using namespace std;
int n;
int m[4000][4000], s[4000][4000], r[4000], c[4000];

void select(int i, int j) {
    s[i][j] ^= 1;
    r[i] += m[i][j], c[j] += m[i][j];
    m[i][j] = -m[i][j];
}

int main() {
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string s; cin >> s;
        for(int j = 0; j < n; ++j)
            m[i][j] = (s[j] == '+' ? 1 : -1);
    }
    
    for(int i = 0; i < n; ++i) cin >> r[i], r[i] = -r[i];
    for(int i = 0; i < n; ++i) cin >> c[i], c[i] = -c[i];

    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j)
        if(m[i][j] > 0) select(i, j);

    for(int i = 0; i < n; ++i) if(c[i] < 0 || r[i] < 0)
        return cout << "No\n", 0;

    vector<int> rr(n), cc(n);
    for(int i = 0; i < n; ++i) rr[i] = cc[i] = i;
    /*sort(rr.begin(), rr.end(), [](int x, int y) {
        return r[x] > r[y];
    });*/

    for(int i: rr) {
        sort(cc.begin(), cc.end(), [](int x, int y) {
            return c[x] > c[y];
        });
        for(int j: cc) {
            if(r[i] <= 0) break;
            if(c[j] > 0) select(i, j);
        }
    }

    for(int i = 0; i < n; ++i) if(c[i] || r[i]) return cout << "No\n", 0;

    cout << "Yes\n";
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) cout << s[i][j];
        cout << "\n";
    }

    return 0;
}

