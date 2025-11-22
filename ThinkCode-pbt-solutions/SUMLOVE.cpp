/******************************************************************************
Link: SUMLOVE
Code: SUMLOVE
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-22-18.15.01
*******************************************************************************/
#include<bits/stdc++.h>
//#define int long long
using namespace std;

const int SQRTN = 633, MAXK = 1e5;
const int MOD = 1e9 + 7;
int n, Q;

int dp[SQRTN + 5][MAXK + 5];
void solve(){
    cin >> n >> Q;

    vector<int> qr(Q);
    int maxval = 0;
    for(int i = 0; i < Q; ++i){
        cin >> qr[i];
        maxval = max(maxval, qr[i]);
    }

    dp[0][0] = 1;
    int lim = 2 * (int)sqrt(n) + 1;
    for (int i = 1; i <= lim; ++i){
        for (int j = i; j <= maxval; ++j){
            dp[i][j] = (1LL * dp[i][j] + dp[i][j - i]) % MOD;
            dp[i][j] = (1LL * dp[i][j] + ((2 * dp[i - 1][j - i]) % MOD)) % MOD;

            if (i >= 2) dp[i][j] = (1LL * dp[i][j] + dp[i - 2][j - i]) % MOD;
            if (j >= n + 1) dp[i][j] = (1LL * dp[i][j] - ((2 * dp[i - 1][j - (n + 1)]) % MOD) + MOD) % MOD;
            if (j >= 2 * (n + 1) && i >= 2) dp[i][j] = (1LL * dp[i][j] - dp[i - 2][j - 2 * (n + 1)] + MOD) % MOD;
        }
    }

    for(int i = 0; i < Q; ++i){
        const int& k = qr[i];

        int ans = 0;
        for (int i = 0; i <= SQRTN; ++i){
            ans = (1LL * ans + dp[i][k]) % MOD;
        }
        cout << (ans % MOD + MOD) % MOD << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    solve();

    return 0;
}

/*
5 5
1
2
3
4
5
*/
