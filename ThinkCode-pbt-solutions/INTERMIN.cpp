/******************************************************************************
Link: INTERMIN
Code: INTERMIN
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-15.37.43
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, a, b;
long long dp[MAXN + 5];

void solve(){
    cin >> n >> a >> b;

    dp[1] = 0;
    for(int i = 2; i <= n; ++i){
        int l = 2, r = i, k = -1;

        dp[i] = 1e18;
        while(l <= r){
            int mid = (l + r) >> 1;
            long long L = a + dp[mid - 1], R = b + dp[i - mid + 1];

            dp[i] = min(dp[i], max(L, R));
            if(L > R) r = mid - 1;
            else l = mid + 1;
        }
    }

    cout << dp[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("INTERMIN.INP","r",stdin);
    //freopen("INTERMIN.OUT","w",stdout);
    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}
