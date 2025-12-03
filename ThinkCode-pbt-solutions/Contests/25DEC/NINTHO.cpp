/******************************************************************************
Link: NINTHO
Code: NINTHO
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-03-20.19.00
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e6;
int arr[MAXN + 5], n;
int L[MAXN + 5], R[MAXN + 5];

void compute(){
    vector<int> sta;
    for(int i = 1; i <= n; ++i){
        while(!sta.empty() && arr[sta.back()] < arr[i]) sta.pop_back();
        L[i] = sta.empty() ? 0 : sta.back();

        sta.push_back(i);
    }

    sta.clear();
    for(int i = n; i >= 1; --i){
        while(!sta.empty() && arr[sta.back()] <= arr[i]) sta.pop_back();
        R[i] = sta.empty() ? n + 1 : sta.back();

        sta.push_back(i);
    }
}

void solve(){
    int ans = 0;

    const int INF = 1e18;
    int maxIdx = max_element(arr + 1, arr + n + 1) - arr;

    arr[0] = arr[n + 1] = INF;
    for(int i = 1; i <= n; ++i){
        if(i == maxIdx) continue;

        int cur = min(arr[L[i]], arr[R[i]]);
        ans += cur;
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("NINTHO.INP","r",stdin);
    //freopen("NINTHO.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> arr[i];

    compute();
    solve();

    return 0;
}
