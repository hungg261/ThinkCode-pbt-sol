/******************************************************************************
Link: SDINO
Code: SDINO
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-15-12.41.55
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e4;
int n, p[MAXN + 5];

queue<int> que;
vector<int> sta;

string res;
void Sort(int l, int r){
    if(l == r){
        return;
    }

    int mid = (l + r) >> 1;
    Sort(l, mid);
    Sort(mid + 1, r);

    for(int i = l; i <= mid; ++i){
        res += "C";
        que.push(sta.back());
        sta.pop_back();
    }

    int i = l, j = mid + 1;
    while(i <= mid && j <= r){
        if(que.front() < sta.back()){
            que.push(que.front());
            que.pop();

            res += "HC";
            ++i;
        }
        else{
            que.push(sta.back());
            sta.pop_back();

            res += "C";
            ++j;
        }
    }
    while(i <= mid){
        que.push(que.front());
        que.pop();

        res += "HC";
        ++i;
    }
    while(j <= r){
        que.push(sta.back());
        sta.pop_back();

        res += "C";
        ++j;
    }

    for(int i = l; i <= r; ++i){
        sta.push_back(que.front());
        que.pop();

        res += "H";
    }
    for(int i = l; i <= r; ++i){
        que.push(sta.back());
        sta.pop_back();

        res += "C";
    }
    for(int i = l; i <= r; ++i){
        sta.push_back(que.front());
        que.pop();

        res += "H";
    }
}

void solve(){
    Sort(1, n);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("SDINO.INP","r",stdin);
    //freopen("SDINO.OUT","w",stdout);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> p[i];
    }
    for(int i = n; i >= 1; --i){
        sta.push_back(p[i]);
    }

    solve();

    return 0;
}

/*
3
3 1 2
*/
