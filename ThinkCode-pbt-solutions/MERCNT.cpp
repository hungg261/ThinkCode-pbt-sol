/******************************************************************************
Link: MERCNT
Code: MERCNT
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-19-15.44.55
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 5000;
const int MOD = 1e9 + 7;
int n;
int arr[MAXN + 5];
int pre[MAXN + 5];

int sum(int l, int r){ return pre[r] - (l > 0 ? pre[l - 1] : 0); }

int dp[MAXN + 5][MAXN + 5];
int prefDp[MAXN + 5][MAXN + 5];
void solve(){
    dp[0][0] = 1;
    prefDp[0][0] = 1;
    for(int i = 1; i <= n; ++i){
//        int k = i;
//        for(int j = i; j >= 1; --j){
//            while(k >= 0 && sum(k, j - 1) <= sum(j, i)){
//                --k;
//            }
//            ++k;
//
//            cerr << k << ' ' << j << ' ' << i << '\n';
//
//            dp[i][j] += prefDp[j - 1][j - 1] - prefDp[j - 1][k - 1];
//            prefDp[i][j] = prefDp[i][j - 1] + dp[i][j];
//        }
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

    for(int i = 1; i <= n; ++i){
        cerr << dp[n][i] << ' ';
    } cerr << '\n';

    int ans = 0;
    for(int i = 1; i <= n; ++i){
        ans = (ans + dp[n][i]) % MOD;
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("MERCNT.INP","r",stdin);
    //freopen("MERCNT.OUT","w",stdout);
    cin >> n;
    if(n > 5000) return -1;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }

    solve();

    return 0;
}
