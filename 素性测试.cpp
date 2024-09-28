#include <iostream>
#include <array>
using namespace std;

typedef long long ll;

ll mulmod(ll a, ll b, ll mod) {
    ll result = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1) result = (result + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return result;
}

ll modular_pow(ll base, ll exponent, ll mod) {
    ll result = 1;
    while (exponent > 0) {
        if (exponent & 1)
            result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

bool miller_test(ll d, ll n, ll a) {
    ll x = modular_pow(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1) {
        x = mulmod(x, x, n);
        d <<= 1;
        if (x == 1) return false;
        if (x == n - 1) return true;
    }
    return false;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    ll d = n - 1;
    while (d % 2 == 0) d >>= 1;

    array<ll, 12> bases = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
    for (ll a : bases) {
        if (a >= n) break;
        if (!miller_test(d, n, a)) return false;
    }
    return true;
}

int main() {
    ll n;
    cin >> n;
    if (is_prime(n))
        cout << "Yes";
    else
        cout << "No";
    return 0;
}