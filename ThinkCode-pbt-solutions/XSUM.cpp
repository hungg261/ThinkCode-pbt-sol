/******************************************************************************
Link: XSUM
Code: XSUM
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-24-17.33.16
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("XSUM.INP","r",stdin);
    //freopen("XSUM.OUT","w",stdout);
    cin >> n >> m;

    int ans = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            ans += (i - 1) ^ (j - 1);
        }
    }

    cout << ans << '\n';

    return 0;
}
