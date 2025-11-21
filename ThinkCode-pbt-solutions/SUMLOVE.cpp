/******************************************************************************
Link: SUMLOVE
Code: SUMLOVE
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-20-22.45.04
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MAXN = 1e5, MAXS = MAXN * (MAXN + 1) / 2;
const int MOD = 1e9 + 7;
int dp[MAXN + 5];
int n, Q;

void compute(){
    dp[0] = 1;
    for(int j = 1; j <= n; ++j){
        for(int i = j * (j + 1) / 2; i >= j; --i){
            dp[i] += dp[i - j];
            dp[i] %= MOD;
        }
    }
}

void solve(){
    int k;
    cin >> k;

    int ans = 0;
    for(int a = 0; a <= k; ++a){
        if(a < 0 || k - a < 0) continue;
        ans += dp[a] * dp[k - a] % MOD;
        ans %= MOD;
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("SUMLOVE.INP","r",stdin);
    //freopen("SUMLOVE.OUT","w",stdout);
    cin >> n >> Q;

    compute();
    while(Q--){
        solve();
    }

    return 0;
}
