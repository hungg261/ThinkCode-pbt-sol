/******************************************************************************
Link: WATER
Code: WATER
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-06-21.20.01
*******************************************************************************/
#include<bits/stdc++.h>
//#define cerr if(false)cerr
using namespace std;

struct Segment{
    int l, r;

    Segment() = default;
    Segment(int _l, int _r): l(_l), r(_r){}

    bool operator < (const Segment& other){
        return this->l < other.l;
    }
};

const int MAXN = 1e5, MAXLG = __lg(MAXN * 2) + 1;
int n, m;
int nxt[MAXN * 2 + 5][MAXLG + 5];
Segment segments[MAXN * 2 + 5];
int len = 0;

void compute(){
    sort(segments + 1, segments + len + 1);
//    cerr << "\n"; for(int i = 1; i <= len; ++i) cerr << segments[i].l << ' ' << segments[i].r << '\n';

    int farthest = 0;
    int idx = 1;
    for(int i = 1; i <= n * 2; ++i){
        while(idx <= len && segments[idx].l <= i){
            farthest = max(farthest, segments[idx].r);
            ++idx;
        }

//        cerr << farthest + 1 << ' ';

        if(farthest < i) nxt[i][0] = i;
        else nxt[i][0] = min(n * 2 + 1, farthest + 1);
    }

    nxt[n * 2 + 1][0] = n * 2 + 1;
    for(int j = 1; j <= MAXLG; ++j){
        for(int i = 1; i <= n * 2 + 1; ++i){
            nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
        }
    }
}

void solve(){
    int ans = 1e9;
    for(int i = 1; i <= n; ++i){
        int j = i;
        int jumps = 0;

        for(int bit = MAXLG; bit >= 0; --bit){
            if(nxt[j][bit] <= i + n - 1){
                j = nxt[j][bit];
                jumps += 1 << bit;

            }
        }

        if(nxt[j][0] == j) continue;
        ans = min(ans, jumps + 1);
    }

    if(ans == (int)1e9) cout << "-1\n";
    else cout << m - ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("WATER.INP","r",stdin);
    //freopen("WATER.OUT","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int l, r;
        cin >> l >> r;

        if(l > r) r += n;
        segments[++len] = {l, r};
        segments[++len] = {l + n, r + n};
    }

    compute();
    solve();

    return 0;
}
