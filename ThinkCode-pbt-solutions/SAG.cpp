/******************************************************************************
Link: SAG
Code: SAG
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-16-10.19.40
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int id[MAXN + 5], idcnt = 0;
vector<int> CCs[MAXN + 5];

vector<int> adj[MAXN + 5];
int n, k, m;

void createCC(int u){
    if(id[u] == 0){
        id[u] = ++idcnt;
        CCs[idcnt].push_back(u);
    }
}

void addToCC(int u, int CC){
    if(id[CC] == 0){
        if(id[u] != 0) swap(u, CC);
        else createCC(CC);
    }

    id[u] = id[CC];
    CCs[id[CC]].push_back(u);
}

void createEdge(int a, int b){
    createCC(a);
    createCC(b);

    adj[id[a]].push_back(id[b]);
}

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
    for(int i = 1; i <= m; ++i){
        string inf;
        cin >> inf;

        for(int j = 0; j < inf.size(); ++j){
            if(inf[j] < '0' || inf[j] > '9'){
                int a = stoi(inf.substr(0, j)), b = stoi(inf.substr(j + 1));
                if(inf[j] == '>') swap(a, b);

                if(inf[j] == '=') addToCC(a, b);
                else createEdge(a, b);
            }
        }
    }

    for(int i = 1; i <= idcnt; ++i) toposort(i);
    reverse(begin(topo), end(topo));

    string res(n, '?');
    vector<int> delta(idcnt + 1, 0);
    for(int u: topo){
        int d = delta[u];

        for(int v: adj[u]){
            delta[v] = max(delta[v], delta[u] + 1);
        }

        for(int pos: CCs[u]){
            res[pos - 1] = 'a' + d;
        }
    }

    cout << res << '\n';

//
//    for(int i = 1; i <= idcnt; ++i){
////        cerr << i << ": ";
////        for(int j: CCs[i]) cerr << j << ' '; cerr << '\n';
//
//        for(int j: adj[i]){
//            cerr << i << ' ' << j << '\n';
//        }
//    }


    return 0;
}
