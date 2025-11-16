/******************************************************************************
Link: SAG
Code: SAG
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-16-10.19.40
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct DSU{
    int n;
    vector<int> par, sz;

    DSU() = default;
    DSU(int _sz): n(_sz){
        par.resize(_sz + 1, -1);
        sz.resize(_sz + 1);
    }

    void create(int v){
        par[v] = v;
        sz[v] = 1;
    }

    int find_set(int v){
        return par[v] == v ? v : par[v] = find_set(par[v]);
    }

    void union_sets(int u, int v){
        u = find_set(u);
        v = find_set(v);
        if(u != v){
            if(sz[u] < sz[v]) swap(u, v);

            par[v] = u;
            sz[u] += sz[v];
        }
    }
};

const int MAXN = 1e5;
int n, k, m;

vector<int> CCs[MAXN + 5];
vector<pair<int, int>> edges;
vector<int> adj[MAXN + 5];

vector<int> topo;
bool mark[MAXN + 5];
void toposort(int u){
    if(mark[u]) return;
    mark[u] = true;

    for(int v: adj[u]){
        toposort(v);
    }

    topo.push_back(u);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("SAG.INP","r",stdin);
    //freopen("SAG.OUT","w",stdout);
    cin >> n >> k >> m;

    DSU dsu(n);
    for(int i = 1; i <= n; ++i) dsu.create(i);

    for(int i = 1; i <= m; ++i){
        string inf;
        cin >> inf;

        for(int j = 0; j < inf.size(); ++j){
            if(inf[j] < '0' || inf[j] > '9'){
                int a = stoi(inf.substr(0, j)), b = stoi(inf.substr(j + 1));
                if(inf[j] == '>') swap(a, b);

                if(inf[j] == '=') dsu.union_sets(a, b);
                else edges.emplace_back(a, b);
            }
        }
    }

    for(const pair<int, int>& p: edges){
        int u, v; tie(u, v) = p;

        adj[dsu.find_set(u)].push_back(dsu.find_set(v));
    }

    for(int u = 1; u <= n; ++u){
        sort(begin(adj[u]), end(adj[u]));
        adj[u].erase(unique(begin(adj[u]), end(adj[u])), end(adj[u]));
    }

    for(int u = 1; u <= n; ++u) toposort(u);
    reverse(begin(topo), end(topo));

    for(int u = 1; u <= n; ++u){
        CCs[dsu.find_set(u)].push_back(u);
    }


    vector<int> low(n + 1, 1), high(n + 1, k);
    for(int i = 0; i < n; ++i){
        int u = topo[i];
        for(int v: adj[u]){
            low[v] = max(low[v], low[u] + 1);
        }

        u = topo[n - i - 1];
        for(int v: adj[u]){
            high[u] = min(high[u], high[v] - 1);
        }
    }

    string res(n, '?');
    for(int u = 1; u <= n; ++u){
        if(dsu.par[u] != u) continue;

        if(low[u] == high[u]){
            for(int id: CCs[u]){
                res[id - 1] = 'a' + low[u] - 1;
            }
        }
        else{

        }
    }

    cout << res << '\n';

    return 0;
}
