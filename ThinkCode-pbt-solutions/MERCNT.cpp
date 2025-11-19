/******************************************************************************
Link: MERCNT
Code: MERCNT
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-19-15.44.55
*******************************************************************************/
#include<bits/stdc++.h>
//#define int long long
using namespace std;

const int MAXN = 7000;
const int MOD = 1e9 + 7;
int n;
long long pre[MAXN + 5];

inline long long sum(const int& l, const int& r){ return pre[r] - (l > 0 ? pre[l - 1] : 0); }

int prefDp[MAXN + 5][MAXN + 5];
void solve(){
    prefDp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
        int k = 0;
        for(int j = 1; j <= i; ++j){
            while(sum(k, j - 1) > sum(j, i)){
                ++k;
            }

            int cur = (1LL * prefDp[j - 1][j - 1] - (k > 0 ? prefDp[j - 1][k - 1] : 0)) % MOD;
            prefDp[i][j] = (1LL * prefDp[i][j - 1] + cur) % MOD;

        }
//
//        for(int j = 1; j <= i; ++j){
//            for(int k = 0; k < j; ++k){
//                if(sum(k, j - 1) <= sum(j, i)){
//                    dp[i][j] += dp[j - 1][k];
//                    dp[i][j] %= MOD;
//                }
//            }
//        }
    }

//    for(int i = 0; i <= n; ++i){
//        for(int j = 0; j <= i; ++j){
//            cerr << prefDp[i][j] << ' ';
//        } cerr << '\n';
//    } cerr << '\n';

//    for(int i = 1; i <= n; ++i){
//        cerr << dp[n][i] << ' ';
//    } cerr << '\n';

    long long ans = prefDp[n][n];
    cout << (ans % MOD + MOD) % MOD << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("MERCNT.INP","r",stdin);
    //freopen("MERCNT.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        int cur;
        cin >> cur;
        pre[i] = (pre[i - 1] + cur);
    }

    solve();

    return 0;
}

/*
4
795502939 984202618 8222566 93629221

3
221589607 910375646 377435208

*/
