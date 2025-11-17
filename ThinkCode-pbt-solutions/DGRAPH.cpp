/******************************************************************************
Link: DGRAPH
Code: DGRAPH
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-17-22.49.56
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

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

    int get(int l, int r){ return get(r) - get(l - 1); }
    int get(){ return get(n); }
};

const int MAXN = 1e5, MAXLG = __lg(MAXN) + 1;
int St[MAXN + 5], En[MAXN + 5], Euler[MAXN + 5], Time = 0;
int table[MAXN + 5][MAXLG + 5], h[MAXN + 5];

vector<int> adj[MAXN + 5];
int n, q;

void compute(){
    for(int j = 1; j <= MAXLG; ++j){
        for(int i = 1; i <= n; ++i){
            table[i][j] = table[table[i][j - 1]][j - 1];
        }
    }
}

int lift(int u, int steps){
    for(int bit = MAXLG; bit >= 0; --bit){
        if(steps >> bit & 1){
            u = table[u][bit];
        }
    }
    return u;
}

void dfs(int u, int prev){
    Euler[++Time] = u;
    St[u] = Time;

    for(int v: adj[u]){
        if(v == prev) continue;

        table[v][0] = u;
        h[v] = h[u] + 1;
        dfs(v, u);
    }

    En[u] = Time;
}

void add(int u, int v, int& res, FenwickTree& fwt1, FenwickTree& fwt2){
    if(St[v] <= St[u] && En[u] <= En[v]){
        int nxt = lift(u, h[u] - h[v] - 1);
        res += fwt1.get(St[nxt], En[nxt]);
        res += fwt2.get(St[u]);

        fwt2.update(St[nxt], 1);
        fwt2.update(En[nxt] + 1, -1);
    }
    else{
        res += fwt1.get() - fwt1.get(St[v], En[v]);
        res += fwt2.get(St[u]);

        fwt2.update(1, 1);
        fwt2.update(n + 1, -1);

        fwt2.update(St[v], -1);
        fwt2.update(En[v] + 1, 1);
    }

    fwt1.update(St[u], 1);
}

void pop(int u, int v, int& res, FenwickTree& fwt1, FenwickTree& fwt2){
    fwt1.update(St[u], -1);
    if(St[v] <= St[u] && En[u] <= En[v]){
        int nxt = lift(u, h[u] - h[v] - 1);
        fwt2.update(St[nxt], -1);
        fwt2.update(En[nxt] + 1, 1);

        res -= fwt1.get(St[nxt], En[nxt]);
        res -= fwt2.get(St[u]);

    }
    else{
        fwt2.update(1, -1);
        fwt2.update(n + 1, 1);

        fwt2.update(St[v], 1);
        fwt2.update(En[v] + 1, -1);

        res -= fwt1.get() - fwt1.get(St[v], En[v]);
        res -= fwt2.get(St[u]);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("DGRAPH.INP","r",stdin);
    //freopen("DGRAPH.OUT","w",stdout);
    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    table[1][0] = 1;
    dfs(1, 0);
    compute();

    FenwickTree fwt1(n), fwt2(n + 1);
    int res = 0;
    while(q--){
        int type, a, b;
        cin >> type >> a >> b;

        if(type == 0){
            add(a, b, res, fwt1, fwt2);
        }
        else{
            pop(a, b, res, fwt1, fwt2);
        }

        cout << res << '\n';
    }

    return 0;
}
