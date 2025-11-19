/******************************************************************************
Link: GNUM
Code: GNUM
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-19-21.24.50
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n, m;
vector<int> adj[MAXN + 5], rev_adj[MAXN + 5];

bool mark[MAXN + 5];
vector<int> kosalist;
void dfs(int u){
    if(mark[u]) return;
    mark[u] = true;

    for(int v: adj[u]){
        dfs(v);
    }

    kosalist.push_back(u);
}

int scc_id[MAXN + 5], scc_cnt = 0;
vector<int> scc[MAXN + 5];
void kosaraju(int u){
    if(scc_id[u] != 0) return;
    scc_id[u] = scc_cnt;
    scc[scc_cnt].push_back(u);

    for(int v: rev_adj[u]){
        kosaraju(v);
    }
}

int res[MAXN + 5];
void solve(){
    int cnt = 0;
    long long ans = 0;
    for(int i = 1; i <= scc_cnt; ++i){
        for(int u: scc[i]){
            res[u] = ++cnt;
        }
        int x = scc[i].size();
        ans += 1LL * (x - 1) * x * (x + 1) / 6;
    }

    cout << ans << '\n';
    for(int i = 1; i <= n; ++i) cout << res[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("GNUM.INP","r",stdin);
    //freopen("GNUM.OUT","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) dfs(i);
    reverse(begin(kosalist), end(kosalist));

    for(int u: kosalist){
        if(scc_id[u] == 0){
            ++scc_cnt;
            kosaraju(u);
        }
    }

    solve();

    return 0;
}
