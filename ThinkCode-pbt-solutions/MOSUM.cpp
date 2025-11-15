/******************************************************************************
Link: MOSUM
Code: MOSUM
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-11-17.24.29
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

int powmod(int a, int b, int mod){
    a %= mod;

    int res = 1;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

const int MOD = 1e9 + 7;
const int MAXN = 1e5, MAXVAL = 1e5;
int arr[MAXN + 5];
int n;

int sqi2[MAXVAL + 5], sq2i[MAXVAL + 5], G[MAXVAL + 5];
int freq[MAXVAL + 5];
void solve(){
    for(int i = 1; i <= n; ++i){
        ++freq[arr[i]];
    }

    for(int v = 1; v <= MAXVAL; ++v){
        for(int j = v; j <= MAXVAL; j += v){
            sqi2[v] += j * j * freq[j]; sqi2[v] %= MOD;
            sq2i[v] += j * freq[j]; sq2i[v] %= MOD;
        }
        G[v] = (sq2i[v] * sq2i[v] % MOD - sqi2[v]) * powmod(2, MOD - 2, MOD) % MOD;
    }

    for(int v = MAXVAL; v >= 1; --v){
        for(int j = v * 2; j <= MAXVAL; j += v){
            G[v] -= G[j]; G[v] %= MOD;
        }
    }

    int ans = 0;
    for(int v = 1; v <= MAXVAL; ++v){
        ans = (ans + G[v] * powmod(v, MOD - 2, MOD) % MOD) % MOD;
    }

    cout << (ans % MOD + MOD) % MOD << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("MOSUM.INP","r",stdin);
    //freopen("MOSUM.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    solve();

    return 0;
}
