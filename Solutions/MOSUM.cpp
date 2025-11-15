#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;
const int MAXA = 2e5 + 5;

int binpow(int a, int b) {
    int res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int n, freq[MAXA], w[MAXA];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i < MAXA; i++) {
        w[i] = binpow(i, MOD - 2);
    }

    for (int i = 1; i < MAXA; i++) {
        for (int j = i * 2; j < MAXA; j += i) {
            w[j] = (w[j] - w[i] + MOD) % MOD;
        }
    }

    cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        freq[x] += x;
        ans -= x; ans %= MOD;
        if (ans < 0) ans += MOD;
    }

    for (int i = 1; i < MAXA; i++) {
        int sum = 0;
        for (int j = i; j < MAXA; j += i) {
            sum = (sum + freq[j]) % MOD;
        }
        ans = (ans + sum * sum % MOD * w[i] % MOD) % MOD;
    }

    ans = ans * binpow(2, MOD - 2) % MOD;
    cout << ans << "\n";
}
