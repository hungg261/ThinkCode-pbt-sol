/******************************************************************************
Link: GCAKE
Code: GCAKE
Time (YYYY-MM-DD-hh.mm.ss): 2025-12-03-21.02.55
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5;
int n, m;
vector<pair<int, int>> adj[MAXN + 5], rev_adj[MAXN + 5];

bool mark[MAXN + 5];
vector<int> topo;
void dfs(int u){
    if(mark[u]) return;
    mark[u] = true;

    for(const pair<int, int>& e: adj[u]){
        dfs(e.first);
    }

    topo.push_back(u);
}

int sccID[MAXN + 5], scc_cnt = 0;
int sccW[MAXN + 5];
void kosaraju(int u){
    if(sccID[u] != 0) return;
    sccID[u] = scc_cnt;

    for(const pair<int, int>& e: rev_adj[u]){
        if(sccID[e.first] == 0){
            sccW[scc_cnt] += e.second;
            kosaraju(e.first);
        }
        else if(sccID[e.first] == scc_cnt){
            sccW[scc_cnt] += e.second;
        }
    }
}

vector<pair<int, int>> temp_dag[MAXN + 5];
vector<pair<int, int>> dag[MAXN + 5];
int dp[MAXN + 5], best[MAXN + 5];

bool vis[MAXN + 5];
void toposort(int u){
    if(vis[u]) return;
    vis[u] = true;

    for(const pair<int, int>& e: dag[u]){
        toposort(e.first);
    }
    topo.push_back(u);
}

void solve(){
    for(int u = 1; u <= n; ++u){
        for(const pair<int, int>& e: adj[u]){
            if(sccID[u] != sccID[e.first]){
                temp_dag[sccID[e.first]].emplace_back(sccID[u], e.second);
            }
        }
    }

    for(int i = 1; i <= scc_cnt; ++i){
        if(temp_dag[i].empty()) continue;

        sort(begin(temp_dag[i]), end(temp_dag[i]));
        int weights = temp_dag[i][0].second;
        for(int j = 1; j < (int)temp_dag[i].size(); ++j){
            if(temp_dag[i][j - 1].first != temp_dag[i][j].first){
                dag[i].emplace_back(temp_dag[i][j - 1].first, weights);
                weights = temp_dag[i][j].second;
            }
            else weights += temp_dag[i][j].second;
        }
        dag[i].emplace_back(temp_dag[i].back().first, weights);
    }

    topo.clear();
    for(int i = 1; i <= scc_cnt; ++i){
        if(!vis[i]) toposort(i);
    }

    reverse(begin(topo), end(topo));
    for(int u: topo){
//        cerr << "t: " << u << '\n';

        dp[u] = max(dp[u], sccW[u]);
        for(const pair<int, int>& e: dag[u]){
//            cerr << u << " -> " << e.first << ": " << e.second << '\n';
            dp[e.first] = max(dp[e.first], dp[u] + e.second + sccW[e.first]);
        }
    }

    for(int i = 1; i <= n; ++i){
        cout << dp[sccID[i]] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("GCAKE.INP","r",stdin);
    //freopen("GCAKE.OUT","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;

        adj[a].emplace_back(b, c);
        rev_adj[b].emplace_back(a, c);
    }

    for(int i = 1; i <= n; ++i){
        if(!mark[i]) dfs(i);
    }

    reverse(begin(topo), end(topo));
    for(int i: topo){
        if(sccID[i] == 0){
            ++scc_cnt;
            kosaraju(i);
        }
    }

    solve();

//    for(int i = 1; i <= n; ++i){
//        cerr << sccW[sccID[i]] << '\n';
//        cerr << sccID[i] << '\n';
//    }

    return 0;
}
