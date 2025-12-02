/******************************************************************************
Link: WKMAX
Code: WKMAX
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-27-13.01.02
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct FenwickTree{
    int n;
    vector<int> BIT;

    FenwickTree() = default;
    FenwickTree(int sz): n(sz){
        BIT.resize(sz + 1, 0);
    }

    void update(int idx, int val){
        for(int i = idx; i <= n; i += i & -i){
            BIT[i] += val;
        }
    }

    int get(int idx){
        int res = 0;
        for(int i = idx; i > 0; i -= i & -i){
            res += BIT[i];
        }
        return res;
    }
    int get(int L, int R){ return get(R) - get(L - 1); }

    int jumpLeft(int idx, int steps){
        int target = get(idx) - steps + 1;
        int l = 1, r = idx, res = -1;
        while(l <= r){
            int mid = (l + r) >> 1, value = get(mid);
            if(value >= target){
                if(value == target) res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        return res;
    }

    int jumpRight(int idx, int steps){
        int target = get(idx) + steps - 1;
        int l = idx, r = n, res = -1;
        while(l <= r){
            int mid = (l + r) >> 1, value = get(mid);
            if(value >= target){
                if(value == target) res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }

        return res;
    }
};

const int MAXN = 1e5, MAXK = 100;
int n, k, arr[MAXN + 5];

pair<int, int> temp[MAXN + 5];
void trau(){
    for(int i = 1; i <= n; ++i){
        temp[i] = {arr[i], i};
    }
    sort(temp + 1, temp + n + 1, greater<>());

    FenwickTree mark(n);
    int ans = 0;
    for(int i = 1; i <= n; ++i){
        int cur, idx; tie(cur, idx) = temp[i];

        mark.update(idx, 1);
        for(int x = 0; x <= k; ++x){
            int y = k - x;

            int L = mark.jumpLeft(idx, x); if(L == -1) continue;
            int R = mark.jumpRight(idx, y); if(R == -1) continue;

            ans += (idx - L - 1) * (R - idx - 1) * cur;
        }
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("WKMAX.INP","r",stdin);
    //freopen("WKMAX.OUT","w",stdout);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
    }

    trau();

    return 0;
}
