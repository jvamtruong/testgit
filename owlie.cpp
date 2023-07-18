#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

// trivial divison for small prime factors and Pollard's Rho for the remaining
// fast check if a number is prime or not using Miller-Rabin test

const int MAX = 1E6;
vector < pair < long long, int > > factors;
long long base[13] = {2, 3, 5, 7, 11, 13, 17, 19, 23}; 
int min_prime[MAX + 3];

void sieve() {
    for (int i = 2 ; i <= sqrt(MAX); i++) {
        if (min_prime[i] == 0) {
            for (int j = i * i ; j <= MAX; j += i) {
                if (min_prime[j] == 0) {
                    min_prime[j] = i;
                }
            }
        }
    }
    for (int i = 2 ; i <= MAX; i++) if (min_prime[i] == 0) min_prime[i] = i;
}

long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
}

long long mul_mod(long long a, long long b, long long MOD) {
    long long res = 0;
    while (b) {
        if (b & 1) res = (res + a) % MOD;
        a = (a << 1) % MOD;
        b >>= 1;
    }
    return res;
}

long long fpow(long long a, long long n, long long MOD) {
    long long res = 1;
    while (n) {
        if (n & 1) res = mul_mod(res, a, MOD);
        a = mul_mod(a, a, MOD);   
        n >>= 1;
    }
    return res;
}

long long fpow(long long a, long long n) {
    long long res = 1;
    while (n) {
        if (n & 1) res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

bool test(long long n, long long d, long long s, long long a) {
    if (n == a) return true;
    long long p = fpow(a, d, n);
    if (p == 1) return true;
    for (int i = 0 ; i < s; i++) {
        if (p == n - 1) return true;
        p = mul_mod(p, p, n);
    }
    return false;
}

bool miller(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2; //n is even except 2
    long long d = n - 1;
    int s = 0;
    while (!(d & 1)) { // factor n - 1 into 2^s * d where d is odd
        s++;
        d >>= 1;
    }
    bool res = true;
    for (int i = 0 ; i < 9; i++) res &= test(n, d, s, base[i]);
    return res;
}

long long pollard_rho(long long n) {
    if (n == 1) return 1;
    if (n % 2 == 0) return 2;
    long long x = rand() % (n - 2) + 2;
    long long y = x;
    long long c = rand() % (n - 1) + 1;
    long long d = 1;
    while (d == 1) {
        x = (x * x % n + c + n) % n;
        y = (y * y % n + c + n) % n;
        y = (y * y % n + c + n) % n;
        d = gcd(abs(x - y), n);
        if (d == n) return pollard_rho(n);
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(time(NULL));
    sieve();
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        long long cur = n;
        long long ans = 1;
        for (int i = 2 ; i <= sqrt(n); i++) {
            int cnt = 0;
            if (n % i == 0) {
                while (n % i == 0) {
                    cnt++;
                    n /= i;
                }
                ans *= (fpow(i, cnt + 1) - 1) / (i - 1);
            }
            if (i > (int) 1E6) break;
        }
        if (n > 1) {
            if (miller(n)) ans *= (fpow(n, 2) - 1) / (n - 1);
            else {
                long long p1 = pollard_rho(n);
                long long p2 = n / p1;
                ans *= ((fpow(p1, 2) - 1) / (p1 - 1)) * ((fpow(p2, 2) - 1) / (p2 - 1));
            }
        }
        cout << (ans == 2 * cur) << endl;
    }
}
