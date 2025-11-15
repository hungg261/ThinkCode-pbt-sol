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
void Sort(int len){
    if(len == 1){
        return;
    }
    else if(len == 2){
        if(is_sorted(end(sta) - len, end(sta), greater<int>())) return;
        else{
            res += "CCHH";
            reverse(end(sta) - len, end(sta));
        }
    }

    int mid = len >> 1;
    Sort(mid);

    if(is_sorted(end(sta) - len, end(sta), greater<int>())) return;

    for(int i = 1; i <= len; ++i) res += "C";
    for(int i = 1; i <= len; ++i) res += "H";
    reverse(end(sta) - len, end(sta));

    if(is_sorted(end(sta) - len, end(sta), greater<int>())) return;

    Sort(len - mid);

    if(is_sorted(end(sta) - len, end(sta), greater<int>())) return;

    for(int i = 1; i <= len - mid; ++i) res += "C";
    for(int i = 1; i <= len - mid; ++i) res += "H";
    reverse(end(sta) - (len - mid), end(sta));

    for(int i = 1; i <= len; ++i) res += "C";
    for(int i = 1; i <= len; ++i) res += "H";
    reverse(end(sta) - len, end(sta));

    if(is_sorted(end(sta) - len, end(sta), greater<int>())) return;

    for(int i = 1; i <= mid; ++i){
        res += "C";
        que.push(sta.back());
        sta.pop_back();
    }

    int i = 1, j = 1;
    while(i <= mid && j <= len - mid){
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
    while(j <= len - mid){
        que.push(sta.back());
        sta.pop_back();

        res += "C";
        ++j;
    }

    for(int i = 1; i <= len; ++i){
        sta.push_back(que.front());
        que.pop();

        res += "H";
    }

    if(len == n){
        for(int i = 1; i <= len; ++i){
            que.push(sta.back());
            sta.pop_back();

            res += "C";
        }
        for(int i = 1; i <= len; ++i){
            sta.push_back(que.front());
            que.pop();

            res += "H";
        }
    }
}

void solve(){
    Sort(n);
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
