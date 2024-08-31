#include<bits/stdc++.h>
using namespace std;

int cm1(int n, int m) {
    if (n > m) swap(n, m);
    if (m % 2 == 0) return ceil((n + 1) * (m + 1) / 2);
    return (n + 1) * (m + 1) / 2;
}

int cm2(int n, int m) {
    return n + m + floor(((n - 1) * (m - 1) + 1) / 2);
}

int main()
{
    for(int i=1; i<=1000; i++) {
        for(int j=1; j<=1000; j++) {
            int c1 = cm1(i, j), c2 = cm2(i, j);
            if(c1 != c2) {
                cout << i << " " << j << " " << c1 << " " << c2 << endl;
            }
        }
    }
}