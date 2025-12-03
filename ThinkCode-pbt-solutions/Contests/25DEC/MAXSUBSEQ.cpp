/******************************************************************************
Link: MAXSUBSEQ
Code: MAXSUBSEQ
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-03-20.18.32
*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, L1, L2;
    cin >> n >> L1 >> L2;

    vector<long long> a(n + 1), pref(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    multiset<pair<long long,int>> ms;

    long long best = LLONG_MIN;
    int best_l = -1, best_r = -1;

    for(int r = 1; r <= n; r++){
        int addIndex = r - L1;
        if(addIndex >= 0){
            ms.insert({pref[addIndex], addIndex});
        }

        int removeIndex = r - L2 - 1;
        if(removeIndex >= 0){
            ms.erase(ms.find({pref[removeIndex], removeIndex}));
        }

        if(!ms.empty()){
            auto it = *ms.begin();
            long long cur = pref[r] - it.first;
            if(cur > best){
                best = cur;
                best_l = it.second + 1;
                best_r = r;
            }
        }
    }

    cout << best << "\n";
    cout << best_l << " " << best_r << "\n";

    return 0;
}

