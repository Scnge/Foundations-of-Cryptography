#include <iostream>
#include <cmath>
using namespace std;

bool IsPrime(long long a) {
    if (a < 2) 
        return false;
    if (a == 2) 
        return true;
    if (a % 2 == 0) 
        return false;

    long long limit = sqrt(a);
    for (long long divider = 3; divider <= limit; divider += 2) {
        if (a % divider == 0)
            return false;
    }
    return true;
}

long long modMultiply(long long a, long long b, long long mod) {
    long long result = 0;
    a = a % mod;
    while (b) {
        if (b & 1) {
            result = (result + a) % mod;
        }
        a = (2 * a) % mod;
        b >>= 1;
    }
    return result;
}

long long cal(long long a, long long n, long long m)
{
    long long result = 1;
    while (n > 0)
    {
        if (n & 1)
            result = modMultiply(result, a, m);
        a = modMultiply(a, a, m);
        n >>= 1;
    }
    return result;
}

long long gcd(long long a, long long b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;

    long long temp = a;
    while (temp != 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

long long mod(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;
    if (m == 0)
        return a;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() 
{
    long long p, q, e, c;
    cin >> p >> q >> e >> c;

    if (p == q)
    {
        cout << "p=q";
        return 0;
    }

    long long limit = pow(2, 31);
    if (p >= limit || p <= 2 || q >= limit || q <= 2)
    {
        cout << "p,q out of the limit";
        return 0;
    }

    bool judge = true;
    judge = IsPrime(p);
    if (judge == false)
    {
        cout << "p isnot the prime";
        return 0;
    }       
    judge = IsPrime(q);
    if (judge == false)
    {
        cout << "q isnot the prime";
        return 0;
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    if (e >= phi || e <= 0)
    {
        cout << "e out of the limit";
        return 0;
    }
    if (gcd(e, phi) != 1)
    {
        cout << "e isnot gcd with oula";
        return 0;
    }
    if (c > n)
        c = cal(c, 1, n);

    long long d = mod(e, phi);
    long long m = cal(c, d, n);
    cout << m;

    return 0;
}