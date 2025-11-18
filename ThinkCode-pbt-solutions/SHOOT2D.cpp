/******************************************************************************
Link: SHOOT2D
Code: SHOOT2D
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-18-18.17.42
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

namespace Utils{

vector<int> values;
void compress(){
    sort(begin(values), end(values));
    values.erase(unique(begin(values), end(values)), end(values));
}

int getVal(const int& val){
    return lower_bound(begin(values), end(values), val) - begin(values) + 1;
}

long long pow2(int x){ return 1LL * x * x; }

long long dist(int x1, int y1, int x2, int y2){
    return pow2(x1 - x2) + pow2(y1 - y2);
}


}

struct Query{
    int type;
    int x, y;

    void input(){
        cin >> type >> x >> y;

        if(type == 1){
            Utils::values.push_back(x + y);
            Utils::values.push_back(x - y);
        }
        else{
            Utils::values.push_back(x);
        }
    }

    int getXplusY(){ return Utils::getVal(x + y); }
    int getXminusY(){ return Utils::getVal(x - y); }
    int getX(){ return Utils::getVal(x); }
    long long distTo(int _x, int _y){ return Utils::dist(x, y, _x, _y); }
    long long distTo(const Query& other){ return Utils::dist(x, y, other.x, other.y); }
};

const int MAXN = 2e5;
int Q;
Query queries[MAXN + 5];

vector<int> nodes[MAXN * 8 + 5], lazy[MAXN * 8 + 5];
bool mark[MAXN + 5];

void down(int id){
    for(int idx: lazy[id]){
        if(mark[idx]) continue;

        nodes[id << 1].push_back(idx);
        lazy[id << 1].push_back(idx);

        nodes[id << 1 | 1].push_back(idx);
        lazy[id << 1 | 1].push_back(idx);
    }
    lazy[id].clear();
}

void update(int id, int l, int r, int u, int v, int idx){
    if(v < l || r < u) return;
    if(u <= l && r <= v){
        nodes[id].push_back(idx);
        lazy[id].push_back(idx);
        return;
    }

    down(id);

    int mid = (l + r) >> 1;
    update(id << 1, l, mid, u, v, idx);
    update(id << 1 | 1, mid + 1, r, u, v, idx);
}

void get(int id, int l, int r, int idx, vector<int>& res){
    if(r < idx || idx < l) return;

    int sz = nodes[id].size();
    for(int i = 0; i < sz; ++i){
        while(i < sz && mark[nodes[id][i]]){
            swap(nodes[id][i], nodes[id][sz - 1]);
            nodes[id].pop_back();
            --sz;
        }
        if(i < sz && !mark[nodes[id][i]]){
            res.push_back(nodes[id][i]);
        }
    }

    if(l == r){
        return;
    }

    down(id);

    int mid = (l + r) >> 1;
    if(idx <= mid) get(id << 1, l, mid, idx, res);
    else get(id << 1 | 1, mid + 1, r, idx, res);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("SHOOT2D.INP","r",stdin);
    //freopen("SHOOT2D.OUT","w",stdout);

    cin >> Q;
    for(int i = 1; i <= Q; ++i){
        queries[i].input();
    }
    Utils::compress();

    const int MAXVAL = Utils::values.size() + 1;
    for(int i = 1; i <= Q; ++i){
        if(queries[i].type == 1){
            update(1, 1, MAXVAL, queries[i].getXminusY(), queries[i].getXplusY(), i);
        }
        else{
            vector<int> res;
            get(1, 1, MAXVAL, queries[i].getX(), res);
            for(int ele: res){
                if(mark[ele]) continue;
                if(queries[i].distTo(queries[ele]) < Utils::pow2(queries[ele].y)){
                    cout << ele << '\n';
                    mark[ele] = true;
                    goto passed;
                }
            }

            cout << "-1\n";
            passed: NULL;
        }
    }

    return 0;
}
