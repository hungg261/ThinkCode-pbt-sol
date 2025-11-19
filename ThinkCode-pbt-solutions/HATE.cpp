/******************************************************************************
Link: HATE
Code: HATE
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-19-08.43.16
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int n c[MAXN + 5];
vector<int> adj[MAXN + 5];
int nxt[MAXN + 5];

void input(){
    cin >> n;
    for(int u = 1; u <= n; ++u) adj[u].clear();

    for(int u = 1; u <= n; ++u){
        int v;
        cin >> c[u] >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
        nxt[u] = v;
    }
}

int mark[MAXN + 5];
void dfs(int u, int prev){

}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("HATE.INP","r",stdin);
    //freopen("HATE.OUT","w",stdout);


    return 0;
}
