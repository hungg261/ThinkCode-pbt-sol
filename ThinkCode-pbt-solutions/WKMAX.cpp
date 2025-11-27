// Khanh Minh's: https://ideone.com/vjGr73

#include <bits/stdc++.h>
#define taskname "main"
using namespace std;
const int 
    maxN = 1e5,
    mod = 1e9 + 7;
int n, k,
    tro_l[maxN + 5],
    tro_r[maxN + 5];
long long 
    res_s,
    p[maxN + 1];
struct HasI{
    long long x; int i;
    void read(int _i){
        cin>>x;
        i = _i;
    }
    void print(){
        cout<<x<<' '<<i<<'\n';
    }
    bool operator < (const HasI &other)const{
        return x > other.x || x == other.x && i < other.i;
    }
} a[maxN + 5], org_a[maxN + 5];
struct FenTree{
    long long bit[maxN + 5];
private:
    long long get(int u){
        long long res = 0;
        for (int i = u; i > 0; i -= i & -i)
            res = (res + bit[i]) % mod;
        return res;
    }
public:
    void clear(){
        memset(bit, 0, sizeof bit);
    }
    void upd(int u, int val){
        for (int i = u; i <= n; i += i & -i)
            bit[i] = (bit[i] + val) % mod;
    }
    long long get_r(int u, int v){
        return (get(v) - get(u - 1) + mod) % mod;
    }
} ftcnt, ftsum;
queue <HasI> q;
int bs_l(int idx){
    int lo = 1, hi = idx, res = 0;
    while (lo <= hi){
        int mid = (lo + hi) >> 1;
        if (ftcnt.get_r(mid, idx)){
            lo = mid + 1;
            res = max(res, mid);
        }
        else hi = mid - 1;
    }
    return res;
}
int bs_r(int idx){
    int lo = idx, hi = n, res = n + 1;
    while (lo <= hi){
        int mid = (lo + hi) >> 1;
        if (ftcnt.get_r(idx, mid)){
            hi = mid - 1;
            res = min(res, mid);
        }
        else lo = mid + 1;
    }
    return res;
}
void init(){
    cin>>n>>k; 
    for (int i = 1; i <= n; i++){
        a[i].read(i);
        org_a[i] = a[i];
    }
    sort(a + 1, a + n + 1);
    ftcnt.clear(); ftsum.clear();
    for (int i = 1; i <= n; i++){
        int tmp_l = bs_l(a[i].i),
            tmp_r = bs_r(a[i].i);
        tro_l[a[i].i] = tmp_l;
        tro_r[a[i].i] = tmp_r;
        ftcnt.upd(a[i].i, 1);
    }
}
void f_slide(int &cnt, int &tmp, int tro[], int step, int lim){
    for (int i = 1; i <= step; i++){
        if (tro[tmp] != lim){
            cnt++;
            tmp = tro[tmp];
        }
    }
}
void upd_val(int idx){
    tro_r[tro_l[a[idx].i]] = a[idx].i;
    tro_l[tro_r[a[idx].i]] = a[idx].i;
    ftsum.upd(a[idx].i, a[idx].x);
    q.push(a[idx]);
}
void slide_1(int &tmp_l, int &tmp_r, long long &tmp_s){
    tmp_s -= org_a[tmp_l].x;
    tmp_l = tro_r[tmp_l];
    tmp_r = tro_r[tmp_r];
    tmp_s += org_a[tmp_r].x;
}
int xet(HasI org){
    long long res = 0;
    int tmp_l = org.i, cnt_l = 1,
        tmp_r = org.i, cnt_r = 1;
    f_slide(cnt_l, tmp_l, tro_l, k - 1, 0);
    f_slide(cnt_r, tmp_r, tro_r, k - cnt_l, n + 1);
    long long tmp_s = ftsum.get_r(tmp_l, tmp_r);
    if (cnt_l + cnt_r - 1 == k){
        while (tmp_l <= org.i && tmp_r <= n){
            res = (res + tmp_s * ((tmp_l - tro_l[tmp_l] + mod) % mod) % mod * ((tro_r[tmp_r] - tmp_r + mod) % mod)) % mod;
            slide_1(tmp_l, tmp_r, tmp_s);
        }
    }
    return res;
}
void f_big(){
    for (int i = 1; i <= n; i++){
        upd_val(i);
        res_s = (res_s + xet(a[i])) % mod;
    }
}
void f_small(){
    ftsum.clear();
    for (int i = 1; i <= n; i++){
        p[i] = (p[i - 1] + org_a[i].x) % mod;
        ftsum.upd(i, p[i]);
    }
    for (int i = 1; i < k; i++)
        res_s = (res_s + (i * p[i] % mod - ftsum.get_r(1, i - 1) + mod) % mod) % mod;
    for (int i = k; i <= n; i++)
        res_s = (res_s + ((k - 1) * p[i] % mod - ftsum.get_r(i - k + 1, i - 1) + mod) % mod) % mod;
    cout<<res_s;
}
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen(taskname".inp","r", stdin);
        freopen(taskname".out","w",stdout);
    #endif
    init(); f_big(); f_small();
}