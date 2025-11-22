/******************************************************************************
Link: 3COLOR
Code: 3COLOR
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-22-21.00.50
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e5;
int n, m;
vector<int> G[MAXN * 2 + 5];

int NOT(int x){
    return x + (x <= n ? n : -n);
}

void add_clause(int u, int v){
    G[NOT(u)].push_back(v);
    G[NOT(v)].push_back(u);

//    cerr << NOT(u) << ' ' << v << '\n';
//    cerr << NOT(v) << ' ' << u << '\n';
}

int id[MAXN << 1];
int num[MAXN << 1], low[MAXN << 1];
int timeDFS = 0, scc = 0;
int st[MAXN << 1];

void dfs(int u){
    num[u] = low[u] = ++timeDFS;
    st[++st[0]] = u;
    for(const int& v : G[u]){
        if(id[v] != 0) continue;
        if(num[v] == 0){
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], num[v]);
    }

    if(num[u] == low[u]){
        for(++scc; true; ){
            int v = st[st[0]--];
            id[v] = scc;
            if(v == u) break;
        }
    }
}

void two_sat(){
    for(int i = 1; i <= 2 * n; ++i){
        if(!id[i]) dfs(i);
    }

    bool answer = 1;
    for(int i = 1; i <= n; ++i){
        if(id[i] == id[NOT(i)]) answer = 0;
    }
    if(!answer){
        cout << "-1\n";
        exit(0);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("3COLOR.INP","r",stdin);
    //freopen("3COLOR.OUT","w",stdout);
    cin >> n >> m;

    vector<int> c(n + 1);
    for(int i = 1; i <= n; ++i) cin >> c[i];

    for(int i = 1; i <= m; ++i){
        int a, b;
        cin >> a >> b;

        for(int xu = 0; xu <= 1; ++xu){
            for(int xv = 0; xv <= 1; ++xv){
                int new_ca = (c[a] + (xu ? 1 : -1) + 3) % 3;
                int new_cb = (c[b] + (xv ? 1 : -1) + 3) % 3;

                int na = xu ? a : NOT(a);
                int nb = xv ? b : NOT(b);
                if(new_ca == new_cb){
                    add_clause(NOT(na), NOT(nb));
//                    cerr << "\tnot " << (na) << " and " << (nb) << '\n';
                }
                else{
//                    add_clause(na, nb);
//                    cerr << "\t" << na << ' ' << nb << '\n';
                }
            }
        }
    }

    two_sat();
    for(int i = 1; i <= n; ++i) cout << (c[i] + ((id[i] < id[NOT(i)]) ? 1 : -1) + 3) % 3 << " ";

    return 0;
}
