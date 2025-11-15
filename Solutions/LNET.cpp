/******************************************************************************
Link: LNET
Code: LNET
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-12.27.57
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int par[MAXN + 5],
    h[MAXN + 5],
    sz[MAXN + 5];

int ChainID[MAXN + 5],
    ChainHead[MAXN + 5],
    curChain = 1,

    Arr[MAXN + 5],
    Pos[MAXN + 5],
    curPos = 0;

vector<int> adj[MAXN + 5];
int n;

void dfs(int u, int prev){
    sz[u] = 1;

    for(int v: adj[u]){
        if(v == prev) continue;

        par[v] = u;
        h[v] = h[u] + 1;

        dfs(v, u);

        sz[u] += sz[v];
    }
}

void Hld(int u, int prev){
    if(!ChainHead[curChain]) ChainHead[curChain] = u;
    ChainID[u] = curChain;

    Arr[++curPos] = u;
    Pos[u] = curPos;

    int nxt = -1;
    for(int v: adj[u]){
        if(v == prev) continue;

        if(nxt == -1 || sz[nxt] < sz[v]) nxt = v;
    }
    if(nxt != -1) Hld(nxt, u);

    for(int v: adj[u]){
        if(v == prev || v == nxt) continue;

        ++curChain;
        Hld(v, u);
    }
}

int nodes[MAXN * 4 + 5], lazy[MAXN * 4 + 5];
void down(int id, int l, int r){
    int t = lazy[id];
    int mid = (l + r) >> 1;

    nodes[id << 1] += t;
    lazy[id << 1] += t;

    nodes[id << 1 | 1] += t;
    lazy[id << 1 | 1] += t;

    lazy[id] = 0;
}

void update(int id, int l, int r, int u, int v, int val){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        nodes[id] += val;
        lazy[id] += val;
        return;
    }

    down(id, l, r);

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, val);
    update(id << 1 | 1, mid + 1, r, u, v, val);
    nodes[id] = max(nodes[id << 1], nodes[id << 1 | 1]);
}

int get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return 0;
    if(u <= l && r <= v) return nodes[id];

    down(id, l, r);

    int mid = (l + r) >> 1;
    return max(get(id << 1, l, mid, u, v), get(id << 1 | 1, mid + 1, r, u, v));
}

void query(int u, int v, int val){
    while(ChainID[u] != ChainID[v]){
        if(ChainID[u] > ChainID[v]){
            update(1, 1, n, Pos[ChainHead[ChainID[u]]], Pos[u], val);
            u = par[ChainHead[ChainID[u]]];
        }
        else{
            update(1, 1, n, Pos[ChainHead[ChainID[v]]], Pos[v], val);
            v = par[ChainHead[ChainID[v]]];
        }
    }

    if(h[u] > h[v]) swap(u, v);
    update(1, 1, n, Pos[u], Pos[v], val);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("LNET.INP","r",stdin);
    //freopen("LNET.OUT","w",stdout);
    int q;
    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);
    Hld(1, -1);

    while(q--){
        int type, u, v;
        cin >> type >> u >> v;

        query(u, v, type == 0 ? 1 : -1);
        cout << nodes[1] << '\n';
    }

    return 0;
}
