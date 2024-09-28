#include <iostream>
using namespace std;

typedef long long ll;

ll a, b, p;

struct point {
    ll x;
    ll y;
} p1, p2, pp;

ll modAdd(ll a, ll b, ll p) {
    return ((a + b) % p + p) % p;
}

ll modSub(ll a, ll b, ll p) {
    return ((a - b) % p + p) % p;
}

ll modMul(ll a, ll b, ll p) {
    return ((a * b) % p + p) % p;
}

ll modInverse(ll a, ll p) {
    ll m0 = p, x0 = 0, x1 = 1;
    if (p == 1) return 0;
    while (a > 1) {
        ll q = a / p;
        ll t = p;
        p = a % p;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    return x1 < 0 ? x1 + m0 : x1;
}

point AddPoint(point pp1, point pp2) {
    point n;
    ll kk = 0;
    if (pp1.x == -1 && pp1.y == -1) {
        return pp2;
    }
    else if (pp2.x == -1 && pp2.y == -1) {
        return pp1;
    }
    else {
        if (pp1.x == pp2.x) {
            if ((pp1.y + pp2.y) % p == 0) {
                n.x = -1;
                n.y = -1;
                return n;
            }
            else {
                ll t = modAdd(modMul(3, modMul(pp1.x, pp1.x, p), p), a, p);
                kk = modMul(t, modInverse(modMul(2, pp1.y, p), p), p);
            }
        }
        else {
            ll t = modSub(pp2.y, pp1.y, p);
            ll w = modSub(pp2.x, pp1.x, p);
            kk = modMul(t, modInverse(w, p), p);
        }
    }
    n.x = modSub(modSub(modMul(kk, kk, p), pp1.x, p), pp2.x, p);
    n.y = modSub(modMul(kk, modSub(pp1.x, n.x, p), p), pp1.y, p);
    return n;
}

void MulPoint(ll k) {
    if (k == 0) {
        cout << "-1 -1";
        return;
    }
    else {
        ll i = 0;
        p2.x = -1;
        p2.y = -1;
        pp = p2;

        while (k != 0) {
            if (i == 0) {
                pp = p1;
            }
            else {
                pp = AddPoint(pp, pp);
            }

            if (k & 1) {
                p2 = AddPoint(pp, p2);
            }
            k >>= 1;
            i++;
        }
        cout << p2.x << " " << p2.y;
        return;
    }
}

int main() {
    ll k;
    cin >> a >> b >> p;
    cin >> p1.x >> p1.y >> k;
    MulPoint(k);
    return 0;
}