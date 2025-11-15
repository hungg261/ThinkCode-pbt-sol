/******************************************************************************
Link: MTC
Code: MTC
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-06-18.02.45
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;
struct FenwickTree{
    vector<int> BIT;
    int n;

    FenwickTree() = default;
    FenwickTree(int sz, int place = 0){ this->n = sz; BIT.resize(sz + 1, place); }

    void update(int idx, int value){
        while(idx <= n){
            BIT[idx] = (BIT[idx] + value) % MOD;
            idx += idx & (-idx);
        }
    }

    int get(int idx){
        int res = 0;
        while(idx > 0){
            res = (res + BIT[idx]) % MOD;
            idx -= idx & (-idx);
        }
        return res;
    }

    int size(){ return this->n; }
};

void compute(vector<pair<int, int>> arr, vector<int>& dp, int n){
    sort(begin(arr) + 1, end(arr), [](pair<int, int>& u, pair<int, int>& v){ return u.first < v.first || (u.first == v.first && u.second > v.second); });

    FenwickTree fwt(n);
    for(int i = 1; i <= n; ++i){
        int idx = arr[i].second;
        dp[idx] = 1 + fwt.get(idx - 1); dp[idx] %= MOD;
        fwt.update(idx, dp[idx]);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("MTC.INP","r",stdin);
    //freopen("MTC.OUT","w",stdout);
    int n;
    cin >> n;

    vector<pair<int, int>> arr1(n + 1), arr2(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> arr1[i].first;
        arr1[i].second = i;

        arr2[i].first = arr1[i].first;
        arr2[i].second = n - i + 1;
    }

    vector<int> dpL(n + 1), dpR(n + 1);
    compute(arr1, dpL, n);
    compute(arr2, dpR, n);

    int ans = 1;
    for(int i = 1; i <= n; ++i){
        ans += dpL[i] * dpR[n - i + 1] % MOD; ans %= MOD;
    }

    cout << ans << '\n';

    return 0;
}
