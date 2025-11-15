/******************************************************************************
Link: RADIO
Code: RADIO
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-18.51.20
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

struct Station{
    int t, Ll, Lr, Rl, Rr;

    void input(){
        cin >> t >> Ll >> Lr >> Rl >> Rr;
    }
};

const int INF = 1e18;
const int MAXN = 1e5;

int n;
int dp[MAXN + 5], bestDp[MAXN + 5];
Station stations[MAXN + 5];
vector<int> open[MAXN + 5], close[MAXN + 5];

int nodes[MAXN * 4 + 5];
void build(int id, int l, int r){
    if(l == r){
        nodes[id] = bestDp[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    nodes[id] = min(nodes[id << 1], nodes[id << 1 | 1]);
}

void update(int id, int l, int r, int idx, int val){
    if(r < idx || idx < l) return;
    if(l == r){
        nodes[id] = val;
        return;
    }

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, idx, val);
    update(id << 1 | 1, mid + 1, r, idx, val);
    nodes[id] = min(nodes[id << 1], nodes[id << 1 | 1]);
}

int get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return INF;
    if(u <= l && r <= v){
        return nodes[id];
    }

    int mid = (l + r) >> 1;
    return min(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}

void solve(){
    fill(bestDp + 1, bestDp + n + 1, INF);
    build(1, 1, n);

    dp[1] = 0;
    bestDp[1] = stations[1].t - 1;
    for(int i = 1; i <= n; ++i){
        for(int j: open[i]) update(1, 1, n, j, bestDp[j]);
        for(int j: close[i]) update(1, 1, n, j, INF);

        if(i == 1) continue;

        int best = get(1, 1, n, stations[i].Ll, stations[i].Lr);
        if(best == INF){
            cout << "-1 ";
            continue;
        }

        dp[i] = best + i + stations[i].t;
        bestDp[i] = dp[i] + stations[i].t - i;
        cout << dp[i] << ' ';
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("RADIO.INP","r",stdin);
    //freopen("RADIO.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        Station& cur = stations[i];
        cur.input();

        cur.Rl = max(cur.Rl, i + 1);

        open[cur.Rl].push_back(i);
        close[cur.Rr + 1].push_back(i);
    }

    solve();

    return 0;
}
