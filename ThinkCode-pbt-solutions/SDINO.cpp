/******************************************************************************
Link: SDINO (Khanh Minh)
Code: SDINO (Khanh Minh)
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-19-01.04.42
*******************************************************************************/
#include <bits/stdc++.h>
#define int long long
#define taskname "main"
using namespace std;
const int maxN = 1e5;
int n,
    a[maxN + 1],
    tmp[maxN + 1];
string res;
void init(){
    cin>>n;
    for (int i = 1; i <= n; i++)
        cin>>a[i];
}
void don(int idx, int v, int type){
    while (idx <= v){
        tmp[++tmp[0]] = a[idx++];
        if (type == 1){
            res.push_back('H');
            res.push_back('C');
        }
        else res.push_back('C');
    }
}
void S_to_Q(int sz){
    for (int i = 1; i <= sz; i++)
        res.push_back('C');
}
void Q_to_S(int sz){
    for (int i = 1; i <= sz; i++)
        res.push_back('H');
}
int xet(int i, int j, int tang){
    if (tang)
        return a[i] <= a[j];
    return a[i] >= a[j];
}
void mer(int u1, int v1, int u2, int v2, int tang){
    tmp[0] = 0;
    int i = u1, j = u2;
    while (i <= v1 && j <= v2){
        if (xet(i, j, tang)){
            tmp[++tmp[0]] = a[i++];
            res.push_back('H');
            res.push_back('C');
        }
        else{
            tmp[++tmp[0]] = a[j++];
            res.push_back('C');
        }
    }
    don(i, v1, 1); don(j, v2, 2);
    for (int i = 1; i <= tmp[0]; ++i)
        a[i + u1 - 1] = tmp[i];
}
void sort_2(int u, int v, int tang){
    if (xet(u, v, tang))
        S_to_Q(2);
    else{
        swap(a[u], a[v]);
        S_to_Q(2);
        Q_to_S(1);
        S_to_Q(1);
    }
}
void duyet_a(){
    for (int i = 1; i <= n; i++)
        cout<<a[i]<<' ';
    cout<<'\n';
}
void mersort(int u, int v, int tang){
    if (u == v){
        res.push_back('C');
        return;
    }
    if (u == v - 1){
        sort_2(u, v, tang);
        return;
    }
    int mid = (u + v) >> 1,
        sz_a = mid - u + 1,
        sz_b = v - mid;

    mersort(u, mid, !tang);
    S_to_Q(sz_b);
    Q_to_S(sz_a + sz_b);
    reverse(a + u, a + v + 1);

    mersort(u, u + sz_b - 1, tang);

    mer(u, u + sz_b - 1, v - sz_a + 1, v, tang);
}
void solve(){
    mersort(1, n, 0);
    Q_to_S(n);
    cout<<res;
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen(taskname".inp","r", stdin);
        freopen(taskname".out","w",stdout);
    #endif
    init(); solve();
}
