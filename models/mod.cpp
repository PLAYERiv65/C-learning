#include<bits/stdc++.h>
using namespace std;
const long long mod = 998244353;

class ll{
public:
    long long x;
    ll(long long x = 0): x(x) {}
    ll operator+(const ll &a) const { return (x + a.x) % mod; }
    ll operator-(const ll &a) const { return (x - a.x + mod) % mod; }
    ll operator*(const ll &a) const { return (x * a.x) % mod; }
    ll operator/(const ll &a) const { return (x * a.inv().x) % mod; }
    ll qpow(ll a, ll b) const {
        ll ans = 1;
        for (; b; b >>= 1, a = a * a) if (b & 1) ans = ans * a;
        return ans;
    }
    ll inv() const { return qpow(*this, mod - 2); }
    ll operator+=(const ll &a) { return *this = *this + a; }
    ll operator-=(const ll &a) { return *this = *this - a; }
    ll operator*=(const ll &a) { return *this = *this * a; }
    ll operator/=(const ll &a) { return *this = *this / a; }
    ll operator++() { return *this = *this + 1; }
    ll operator--() { return *this = *this - 1; }
    ll operator++(int) { ll tmp = *this; ++*this; return tmp; }
    ll operator--(int) { ll tmp = *this; --*this; return tmp; }
    bool operator==(const ll &a) const { return x == a.x; }
    bool operator!=(const ll &a) const { return x != a.x; }
    bool operator<(const ll &a) const { return x < a.x; }
    bool operator>(const ll &a) const { return x > a.x; }
    bool operator<=(const ll &a) const { return x <= a.x; }
    bool operator>=(const ll &a) const { return x >= a.x; }
    friend ostream& operator<<(ostream &os, const ll &a) { return os << a.x; }
    friend istream& operator>>(istream &is, ll &a) { return is >> a.x; }
};