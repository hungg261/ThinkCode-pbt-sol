/******************************************************************************
Link: HATE
Code: HATE
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-19-08.43.16
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5;
int n, c[MAXN + 5];
multiset<int> adj[MAXN + 5];
bool mark[MAXN + 5];

int ans = 0;
void input(){
    ans = 0;

    cin >> n;
    for(int u = 1; u <= n; ++u){
        mark[u] = false;
        adj[u].clear();
    }

    for(int u = 1; u <= n; ++u){
        int v;
        cin >> c[u] >> v;

        if(v != -1){
            adj[u].insert(v);
            adj[v].insert(u);
        }
    }
}

int dp[MAXN + 5][2];
void solve(int u, int prev, const int& avoid){
//    cerr << "test: " << u << '\n';

    dp[u][0] = 0;
    dp[u][1] = u == avoid ? 0 : c[u];
    for(const int& v: adj[u]){
        if(v == prev) continue;

        solve(v, u, avoid);

        dp[u][0] += max(dp[v][1], dp[v][0]);
        if(u != avoid) dp[u][1] += dp[v][0];
    }
}

pair<int, int> popedge;
void dfs(int u, int prev){
    mark[u] = true;
    for(int v: adj[u]){
        if(v == prev) continue;

        if(mark[v]){
            popedge = {u, v};
        }
        else dfs(v, u);
    }
    return;
}

void getCCs(){
    for(int i = 1; i <= n; ++i){
        if(mark[i]) continue;
        popedge = {i, 0};
        dfs(i, 0);

        int u, v; tie(u, v) = popedge;
        auto it1 = adj[u].find(v);
        if(it1 != adj[u].end()) adj[u].erase(it1);

        auto it2 = adj[v].find(u);
        if(it2 != adj[v].end()) adj[v].erase(it2);

        int tempRes;

//        cerr << i << ' ' << "mark\n";
        solve(u, 0, u);
        tempRes = max(dp[u][0], dp[u][1]);
//        cerr << '\n';
//        cerr << max(dp[u][0], dp[u][1]) << ' ';

//        cerr << "mark " << u << ' ' << v << '\n';
        solve(u, 0, v);
        tempRes = max(tempRes, max(dp[u][0], dp[u][1]));
//        cerr << max(dp[u][0], dp[u][1]) << '\n';

        ans += tempRes;
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("HATE.INP","r",stdin);
    //freopen("HATE.OUT","w",stdout);
    int t;
    cin >> t;

    while(t--){
        input();
        getCCs();
    }

    return 0;
}

/*
1
5
1 2
1 3
1 4
1 2
1 -1

4
3
3 2
5 1
1 2
3
3 2
2 3
2 1
4
1 3
2 3
3 4
4 2
4
2 2
3 1
4 4
3 3
*/
