/******************************************************************************
Link: SHOOT2D
Code: SHOOT2D
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-18-18.17.42
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

//#define int long long

namespace Utils{

vector<int> values;
void compress(){
    sort(begin(values), end(values));
    values.erase(unique(begin(values), end(values)), end(values));
}

int getVal(const int& val){
    return lower_bound(begin(values), end(values), val) - begin(values) + 1;
}

int dist(int x1, int y1, int x2, int y2){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
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
};

const int MAXN = 2e5;
int Q;
Query queries[MAXN + 5];

//set<int> nodes[MAXN * 4 + 5], lazy[MAXN * 4 + 5], poplazy[MAXN * 4 + 5];
//void down(const int& id){
//    for(const int& ele: lazy[id]){
//        nodes[id << 1].insert(ele);
//        lazy[id << 1].insert(ele);
//
//        nodes[id << 1 | 1].insert(ele);
//        lazy[id << 1 | 1].insert(ele);
//    }
//    lazy[id].clear();
//}
//void erase_down(const int& id){
//    for(const int& ele: poplazy[id]){
//        nodes[id << 1].erase(ele);
//        poplazy[id << 1].insert(ele);
//
//        nodes[id << 1 | 1].erase(ele);
//        poplazy[id << 1 | 1].insert(ele);
//    }
//    poplazy[id].clear();
//}
//
//void update(int id, int l, int r, int u, int v, int idx){
//    if(v < l || r < u) return;
//    if(u <= l && r <= v){
//        nodes[id].insert(idx);
//        lazy[id].insert(idx);
//        return;
//    }
//
//    down(id);
//    erase_down(id);
//
//    int mid = (l + r) >> 1;
//    update(id << 1, l, mid, u, v, idx);
//    update(id << 1 | 1, mid + 1, r, u, v, idx);
//
//    for(const int& ele: nodes[id << 1]) nodes[id].insert(ele);
//    for(const int& ele: nodes[id << 1 | 1]) nodes[id].insert(ele);
//}
//
//void pop(int id, int l, int r, int u, int v, int idx){
//    if(v < l || r < u) return;
//    if(u <= l && r <= v){
//        nodes[id].erase(idx);
//        poplazy[id].insert(idx);
//        return;
//    }
//
//    down(id);
//    erase_down(id);
//
//    int mid = (l + r) >> 1;
//    pop(id << 1, l, mid, u, v, idx);
//    pop(id << 1 | 1, mid + 1, r, u, v, idx);
//
//    for(const int& ele: nodes[id << 1]) nodes[id].insert(ele);
//    for(const int& ele: nodes[id << 1 | 1]) nodes[id].insert(ele);
//}
//
//set<int> get(int id, int l, int r, const int& idx){
//    if(r < idx || idx < l) return {};
//    if(l == r){
//        return nodes[id];
//    }
//
//    down(id);
//    erase_down(id);
//
//    int mid = (l + r) >> 1;
//    set<int> L = get(id << 1, l, mid, idx), R = get(id << 1 | 1, mid + 1, r, idx);
//    for(const int& ele: R) L.insert(ele);
//    return L;
//}

vector<int> nodes[MAXN * 4 + 5], lazy[MAXN * 4 + 5];
bool mark[MAXN + 5];
void down(const int& id){
    int sz = lazy[id].size();
    for(int i = 0; i < sz; ++i){
        nodes[id << 1].push_back(lazy[id][i]);
        lazy[id << 1].push_back(lazy[id][i]);

        nodes[id << 1 | 1].push_back(lazy[id][i]);
        lazy[id << 1 | 1].push_back(lazy[id][i]);
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

void pop(int idx){
    mark[idx] = true;
}

void get(int id, int l, int r, const int& idx, vector<int>& res){
    if(r < idx || idx < l) return;

    down(id);
    for(int ele: nodes[id]){
        if(!mark[ele]) res.push_back(ele);
    }

    if(l == r){
        return;
    }


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
            update(1, 1, MAXVAL, Utils::getVal(queries[i].x - queries[i].y), Utils::getVal(queries[i].x + queries[i].y), i);
        }
        else{
//            for(int ele: get(1, 1, MAXVAL, Utils::getVal(queries[i].x))){
//                cerr << "\t" << ele << '\n';
//            }
            vector<int> res;
            get(1, 1, MAXVAL, Utils::getVal(queries[i].x), res);
            for(int ele: res){
                if(Utils::dist(queries[i].x, queries[i].y, queries[ele].x, queries[ele].y) < queries[ele].y * queries[ele].y){
                    cout << ele << '\n';
                    pop(ele);
                    goto passed;
                }
            }

            cout << "-1\n";
            passed: NULL;
        }
    }

    return 0;
}

/*
8
1 0 12
2 -11 22
1 24 10
1 12 3
2 12 12
2 16 14
1 28 15
2 17 13

8
1 0 12
2 -11 22
1 24 10
1 12 3
2 12 12
2 16 14
1 28 15
2 12 12
*/
