/******************************************************************************
Link: LISX
Code: LISX
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-24-00.36.32
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

int LIS(int N){
    string S = to_string(N);
    vector<char> dp = {S[0]};

    int sz = S.size();
    for(int i = 1; i < sz; ++i){
        if(dp.back() < S[i]) dp.push_back(S[i]);
        else *lower_bound(begin(dp), end(dp), S[i]) = S[i];
    }

    return dp.size();
}

void solve(){
    int L, R;
    cin >> L >> R;

    int ans = 0, ways = 1;
    for(int i = L; i <= R; ++i){
        int cur = LIS(i);
        if(ans < cur){
            ans = cur;
            ways = 1;
        }
        else if(ans == cur) ++ways;
    }

    cout << ans << ' ' << ways << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("LISX.INP","r",stdin);
    //freopen("LISX.OUT","w",stdout);
    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}
